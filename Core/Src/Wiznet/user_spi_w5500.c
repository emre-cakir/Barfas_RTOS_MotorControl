/**
 * @file user_spi_w5500.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief STM32 SPI donanımı ile W5500 ioLibrary_Driver arasındaki donanım soyutlama (HAL) köprü fonksiyonları.
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "user_spi_w5500.h"
#include "wizchip_conf.h"
#include "spi.h"
#include "gpio.h"

// CubeMX'te SPI1 için otomatik oluşturulan struct
extern SPI_HandleTypeDef hspi1;

/* --- W5500 Chip Select (CS) Fonksiyonları --- */
/**
 * @brief W5500 modülünün CS (Chip Select) pinini aktife (LOW) çeker.
 * SPI haberleşmesini başlatmak için donanımı dinleme moduna alır.
 */
void W5500_Select(void)
{
    HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_RESET);
}

/**
 * @brief W5500 modülünün CS (Chip Select) pinini pasife (HIGH) çeker.
 * SPI haberleşmesini sonlandırır ve SPI hattını serbest bırakır.
 */
void W5500_Unselect(void)
{
    HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_SET);
}

/* --- SPI Tekli Okuma/Yazma Fonksiyonları --- */
/**
 * @brief SPI hattı üzerinden W5500 modülüne tek bir byte (8-bit) veri yazar.
 *
 * @param byte İletilecek olan 8-bitlik veri.
 */
void W5500_WriteByte(uint8_t byte)
{
    HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
}

/**
 * @brief SPI hattı üzerinden W5500 modülünden tek bir byte (8-bit) veri okur.
 *
 * @return uint8_t W5500'den okunan 8-bitlik veri.
 */
uint8_t W5500_ReadByte(void)
{
    uint8_t tx_data = 0xFF; // Boş veri gönder ki saat sinyali oluşsun
    uint8_t rx_data = 0;
    HAL_SPI_TransmitReceive(&hspi1, &tx_data, &rx_data, 1, HAL_MAX_DELAY);
    return rx_data;
}

/* --- SPI Çoklu Okuma/Yazma (Burst Mode) Fonksiyonları --- */
/**
 * @brief SPI üzerinden W5500 modülüne çoklu (burst mode) veri bloğu gönderir.
 *
 * @param pBuf Gönderilecek verilerin bulunduğu bellek dizisinin (buffer) başlangıç adresi.
 * @param len Gönderilecek verinin byte cinsinden toplam uzunluğu.
 */
void W5500_WriteBuffer(uint8_t *pBuf, uint16_t len)
{
    HAL_SPI_Transmit(&hspi1, pBuf, len, HAL_MAX_DELAY);
}

/**
 * @brief SPI üzerinden W5500 modülünden çoklu (burst mode) veri bloğu okur.
 *
 * @param pBuf Okunan verilerin kaydedileceği bellek dizisinin (buffer) başlangıç adresi.
 * @param len Okunacak verinin byte cinsinden toplam uzunluğu.
 */
void W5500_ReadBuffer(uint8_t *pBuf, uint16_t len)
{
    HAL_SPI_Receive(&hspi1, pBuf, len, HAL_MAX_DELAY);
}

/* --- Wiznet Kütüphanesine Donanımı Kaydetme --- */
/**
 * @brief STM32 donanım fonksiyonlarını Wiznet ioLibrary_Driver'ına bağlar (Callback Registration)
 * ve W5500 soket bellek konfigürasyonlarını gerçekleştirir.
 */
void W5500_Hardware_Init(void)
{
    // 1. CS Pin Kontrol Fonksiyonlarını Kaydet
    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);

    // 2. SPI Byte Okuma/Yazma Fonksiyonlarını Kaydet
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);

    // 3. SPI Çoklu (Burst) Okuma/Yazma Fonksiyonlarını Kaydet
    reg_wizchip_spiburst_cbfunc(W5500_ReadBuffer, W5500_WriteBuffer);

    // 4. W5500 RX/TX Buffer Belleklerini Ayarla (Her soket için 2KB ayırıyoruz)
    uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
    wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
}