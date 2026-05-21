/**
 * @file rgb_led.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief RGB LED durum bildirim katmanı dosyası.
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SERVICE_RGB_LED_H_
#define SERVICE_RGB_LED_H_

/**
 * @brief RGB LED renk kombinasyon tanımlamaları.
 */
typedef enum
{
    RGB_COLOR_OFF = 0, // Tüm LED'ler kapalı
    RGB_COLOR_RED,     // Kırmızı renk
    RGB_COLOR_GREEN,   // Yeşil renk
    RGB_COLOR_BLUE,    // Mavi renk
    RGB_COLOR_YELLOW,  // Sarı renk
    RGB_COLOR_WHITE    // Beyaz renk
} RGB_Color_t;

/**
 * @brief RGB LED pinlerini başlangıç durumuna getirir.
 */
void RGB_LED_Init(void);

/**
 * @brief RGB LED'in rengini belirtilen parametreye göre günceller.
 *
 * @param color Yakılmak istenen hedef renk
 */
void RGB_LED_Set_Color(RGB_Color_t color);

#endif /* SERVICE_RGB_LED_H_ */