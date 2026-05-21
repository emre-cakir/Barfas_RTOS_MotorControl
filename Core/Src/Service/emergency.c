/**
 * @file emergency.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief Donanımsal kesme (EXTI) yakalama ve motor/LED acil durdurma algoritmaları
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "emergency.h"
#include "motor_driver.h"
#include "rgb_led.h"
#include "gpio.h"
#include "cmsis_os.h"

// Acil durum bayrağı
static volatile uint8_t emergency_flag = 0;

/**
 * @brief Sistemin anlık acil durum bayrak bilgisini döndürür
 *
 * @return uint8_t 1: Sistem acil durumda, 0: Sistem normal çalışma modunda.
 */
uint8_t Emergency_Get_Status(void)
{
    return emergency_flag;
}

/**
 * @brief Acil durum bayrağını sıfırlayarak sistemi yeniden başlatılabilir konuma getirir.
 */
void Emergency_Reset_Status(void)
{
    emergency_flag = 0;
}

/**
 * @brief Sistemi acil durum moduna sokar, motoru kilitler ve görsel uyarıyı başlatır.
 */
void Emergency_Trigger(void)
{
    // Emergency bayrağı set olur
    emergency_flag = 1;

    // Motoru frenler ve PWM'i kapatır
    Motor_Set_Speed_Direction(MOTOR_DIR_STOP, 0);

    // RGB LED'i kullanıcıyı uyarmak için Kırmızı yanar
    RGB_LED_Set_Color(RGB_COLOR_RED);
}

/**
 * @brief EXTI Callback Fonksiyonudur.
 * Butona basıldığı an işlemci ne yapıyorsa bırakarak doğrudan buraya atlar ve koruma modunu tetikler.
 *
 * @param GPIO_Pin Kesmeyi tetikleyen pin numarası.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Kesmenin Emergency butonumuzdan gelip gelmediğini kontrol et
    if (GPIO_Pin == BTN_EMERGENCY_Pin)
    {
        // Basit debounce
        if (HAL_GPIO_ReadPin(BTN_EMERGENCY_GPIO_Port, BTN_EMERGENCY_Pin) == GPIO_PIN_RESET)
        {
            Emergency_Trigger();
        }
    }
}