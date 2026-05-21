# Barfas_RTOS_MotorControl

STM32 tabanlı, FreeRTOS destekli gömülü sistem projesi. W5500 Ethernet modülü üzerinden TCP istemci (Client) mimarisiyle haberleşerek L298N motor sürücüsünü ve RGB durum LED'lerini gerçek zamanlı kontrol eder. Donanımsal acil durum kesmesi (EXTI) ve durum makinesi (State Machine) mimarilerini içerir. Bu proje ayrıca, donanımdan bağımsızlaştırma (HAL) yaklaşımını ve deterministik görev yönetimini endüstriyel standartlarda barındırır.

---

## 📑 İçindekiler

1. [Donanım Mimarisi](#-donanım-mimarisi-ve-bileşenler)
2. [Yazılım ve Sistem Mimarisi](#-yazılım-katmanları-ve-sistem-mimarisi)
3. [RTOS Görev Yönetimi](#-deterministik-görev-yönetimi-freertos)
4. [Sıfır Gecikmeli Kesme ve Güvenlik](#-sıfır-gecikmeli-kesme-ve-güvenlik-zero-latency-isr)
5. [Ağ ve Haberleşme Mimarisi](#-ağ-ve-haberleşme-mimarisi)
6. [Sistem Akış Diyagramı](#-sistem-akış-diyagramı-veri-ve-sinyal-iletimi)
7. [Komut Seti Referansı](#️-komut-seti-ve-api-referansı)
8. [Kurulum ve Çalıştırma](#-kurulum-ve-çalıştırma)

---

## 🛠 Donanım Mimarisi ve Bileşenler

Sistem, gerçek zamanlı kontrol gereksinimlerini karşılamak üzere aşağıdaki donanım bileşenleri üzerine inşa edilmiştir:

- **Ana Mikrodenetleyici (MCU):** STM32F030R8T6 (ARM® Cortex®-M0, 48 MHz, 64 KB Flash, 8 KB SRAM)
- **Ağ Arayüzü (PHY/MAC):** Wiznet W5500 Ethernet Modülü (Donanımsal TCP/IP Yığını, SPI Haberleşmesi)
- **Sürüş Birimi:** L298N Çift H-Köprüsü Motor Sürücü (Timer 3 tabanlı donanımsal PWM hız ve GPIO yön kontrolü)
- **Kullanıcı Arayüzü:** Ortak Katot RGB Durum Gösterge LED'i
- **Güvenlik Donanımı:** Endüstriyel Acil Durum (E-Stop) Butonu (Active-Low Bağlantı, Donanımsal EXTI)

---

## 🏗 Yazılım Katmanları ve Sistem Mimarisi

Sistem, donanımdan bağımsızlaştırma ve sürdürülebilirlik ilkelerine uygun olarak izole edilmiş katmanlı (Layered Architecture) bir yapıda geliştirilmiştir:

    +-----------------------------------------------------------------------+
    |                         Uygulama Katmanı                              |
    |          (task_manager.c, state_machine.c, command_parser.c)          |
    +-----------------------------------------------------------------------+
    |                          Sürücü Katmanı                               |
    |               (motor_driver.c, rgb_led.h, emergency.c)                |
    +-----------------------------------------------------------------------+
    |                 Donanım Soyutlama Katmanı (HAL)                       |
    |           (user_spi_w5500.c, STM32 HAL, ioLibrary_Driver)             |
    +-----------------------------------------------------------------------+
    |                            Fiziksel Katman                            |
    |             (STM32 MCU, W5500 PHY, L298N Motor Driver)                |
    +-----------------------------------------------------------------------+

---

## ⏱ Deterministik Görev Yönetimi (FreeRTOS)

İşletim sistemi katmanı, öncelik tabanlı (Priority-Based) ve kesintili (Preemptive) zamanlama ile koşan 5 temel görev ve 1 güvenli mesaj kuyruğu (`Queue_NetCmd`) üzerinden işletilir:

| Görev İsmi          | Öncelik Seviyesi | Döngü | Görev Tanımı                                                                                    |
| :------------------ | :--------------- | :---- | :---------------------------------------------------------------------------------------------- |
| **Task_Dispatch**   | `Realtime`       | 10ms  | FSM'yi günceller, ağ kuyruğunu tüketir ve alt motor görevlerini yönlendirir.                    |
| **Task_NetComm**    | `Normal`         | 1ms   | W5500 SPI donanım ilklendirmesini ve sürekli TCP Client soket polling'ini işletir.              |
| **Task_DriveRight** | `High`           | 10ms  | Sağ yöne tam hız (%100) sürüş algoritmasını yürütür.                                            |
| **Task_DriveLeft**  | `Low`            | 50ms  | Sol yöne tam hız (%100) sürüş algoritmasını yürütür.                                            |
| **Task_DriveRamp**  | `High`           | 10ms  | Bloklamasız (Non-blocking) yumuşak ivmeli kalkış (Rampa) ve Blink LED algoritmasını çalıştırır. |

### Sonlu Durum Makinesi (State Machine)

Sistem mod geçişlerini ve kararlılığını yöneten ana FSM 3 eksende çalışır:

- `STATE_INIT`: Başlangıç donanım testlerinin yapıldığı ve TCP el sıkışmasının (Handshake) arandığı ilk mod.
- `STATE_NORMAL`: Ağdan gelen komutların güvenli bir şekilde yürütüldüğü ana operasyon modu.
- `STATE_EMERGENCY`: Kritik donanımsal kesme ile tetiklenen koruma modu.

---

## ⚡ Sıfır Gecikmeli Kesme ve Güvenlik (Zero-Latency ISR)

Sistemde can ve donanım güvenliğini maksimize etmek için kritik hata (fail-safe) senaryosu kurgulanmıştır:

- **Asenkron Müdahale:** Acil durum butonuna basıldığı an, donanımsal dış kesme (`HAL_GPIO_EXTI_Callback`) RTOS zamanlayıcısını anında ezerek ana döngüyü keser.
- **Sıfır Gecikmeli Frenleme:** Kesme servis rutini (ISR) içerisinden `Emergency_Trigger()` doğrudan çağrılarak Timer PWM register'ları sıfırlanır, motor kilitlenir ve durum Kırmızı LED ile bildirilir.
- **Volatile Optimizasyonu:** Acil durum bayrağı, derleyicinin RAM üzerindeki hatalı okumalarını ve register seviyesi optimizasyonlarını önlemek için `volatile` anahtar kelimesi ile güvence altına alınmıştır.

---

## 🌐 Ağ ve Haberleşme Mimarisi

- **TCP İstemci (Client) Yaklaşımı:** W5500 modülü ağ üzerinde aktif bir istemci olarak davranır ve hedef sunucuya periyodik HTTP GET istekleri atarak (`Polling`) "Bana komutlarımı ver" mantığıyla çalışır.
- **SPI Burst Mode Optimizasyonu:** `user_spi_w5500.c` köprüsü üzerinden Wiznet kütüphanesine kaydedilen çoklu okuma/yazma (Burst Mode) fonksiyonları sayesinde TCP paketleri işlemciyi yormadan tek seferde çekilir.
- **Bağlantı Dayanıklılığı:** W5500 soketi `SOCK_CLOSE_WAIT` veya `SOCK_CLOSED` durumuna düştüğünde sistem otomatik olarak soketi yeniden açar ve hedef IP'ye bağlanmayı tekrar dener.

---

## 📈 Sistem Akış Diyagramı (Veri ve Sinyal İletimi)

    [ Hedef Sunucu / Hercules ]
            │ (TCP Port: 8080)
            ▼
    [ W5500 Ağ Soketi ] ───────▶ TCP Client Modu (Sürekli Veri Okuma)
            │
            ▼ (HTTP Metin Paketi)
    [ command_parser.c ] ──────▶ Gelen string veriyi ayrıştır (strstr "CMD=X")
            │
            ▼ (RTOS osMessagePut)
    [ Queue_NetCmdHandle ] ────▶ FreeRTOS Kuyruk Yönetimi (Derinlik: 3)
            │
            ▼ (osMessageGet - 10ms Periyot)
    [ task_manager.c ] ────────▶ TaskManager_Dispatch_Process()
            │
            ├───► [ STATE_NORMAL ] ──► Motor_Set_Speed_Direction() ──► L298N Sürücü
            │
            └─► [ STATE_EMERGENCY ] ◄─ (Donanım Kesmesi / EXTI) ◄── [ E-STOP BUTONU ]

---

## ⚙️ Komut Seti ve API Referansı

Sistem, ağ üzerinden gelen HTTP parametrelerini ayrıştırarak çalışır:

- `CMD=0` : Durma / Frenleme modu (LED: Mavi)
- `CMD=1` : İleri/Sağ Yön - Tam Hız %100 (LED: Yeşil)
- `CMD=2` : Geri/Sol Yön - Tam Hız %100 (LED: Sarı)
- `CMD=3` : Yumuşak İvmeli Kalkış / Rampa Modu (LED: Kırmızı Blink)
- `CMD=4` : Acil Durum Sıfırlama (Reset) ve Sistemi Yeniden Başlatma

---

## 🚀 Kurulum ve Çalıştırma

Sistemi laboratuvar veya ofis ortamında test etmek için aşağıdaki adımları izleyin:

### 1. Ağ Konfigürasyonları

- `network_interface.c` dosyası içerisinde hedef sunucu IP adresini (Bilgisayarınızın IP adresi) belirleyin:
  ```c
  uint8_t target_ip[4] = {192, 168, 1, 18}; // Kendi IP adresinize göre düzenleyin
  ```
  W5500 modülünün Statik IP, Gateway ve MAC ayarlarını yine aynı dosyadaki gWIZNETINFO yapısı üzerinden kendi yerel ağınıza (Subnet) uygun olarak güncelleyin:

```c
  wiz_NetInfo gWIZNETINFO = {
    .mac = {0x00, 0x08, 0xDC, 0xAB, 0xCD, 0xEF}, // Kendi belirlediğiniz MAC adresi
    .ip = {192, 168, 1, Y}, // 'Y' yerine W5500 modülünün almasını istediğiniz boş IP'yi girin
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 1, 1}, // Ağınızın varsayılan ağ geçidi (Modem IP'si)
    .dns = {8, 8, 8, 8},
    .dhcp = NETINFO_STATIC
  };
```

W5500 modülünden çıkan Ethernet kablosunu ağınızdaki bir switch/modeme veya doğrudan bilgisayarınıza bağlayın. (Not: Bilgisayara yapılan direkt bağlantılarda işletim sistemi üzerinden Ethernet bağdaştırıcısına manuel statik IP verilmesi zorunludur)
