/**
 * @file rgb_led.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief RGB LED GPIO kontrol ve renk durum yönetim algoritmaları
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "rgb_led.h"
#include "gpio.h"

/**
 * @brief RGB LED pinlerini başlangıç durumuna getirir.
 */
void RGB_LED_Init(void)
{
    RGB_LED_Set_Color(RGB_COLOR_OFF);
}

/**
 * @brief Hedef renge göre ilgili GPIO pinlerini HIGH veya LOW yapar.
 */
void RGB_LED_Set_Color(RGB_Color_t color)
{
    switch (color)
    {
    case RGB_COLOR_RED:
        // Kırmızı
        HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_RESET);
        break;

    case RGB_COLOR_GREEN:
        // Yeşil
        HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, GPIO_PIN_RESET);
        break;

    case RGB_COLOR_BLUE:
        // Mavi
        HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_RESET);
        break;

    case RGB_COLOR_YELLOW:
        // Sarı
        HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_SET);
        break;

    case RGB_COLOR_OFF:
    default:
        // Tüm pinler kapalı
        HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_RESET);
        break;
    }
}