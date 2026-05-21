/**
 * @file state_machine.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief Sistem durum makinesi geçiş algoritmaları ve mod yönetimi
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "state_machine.h"
#include "emergency.h"
#include "rgb_led.h"

// Varsayılan başlangıç durumu
static System_State_t current_state = STATE_INIT;

/**
 * @brief Sistemin o anki aktif durum bilgisini güvenli şekilde dış modüllere sunar
 *
 * @return System_State_t Aktif durum
 */
System_State_t State_Get_Current(void)
{
    return current_state;
}

/**
 * @brief Flag ve kesme durumlarını inceleyerek durumlar arası geçişi yönetir
 */
void State_Machine_Update(void)
{
    // Eğer acil durum flag'i set edildiyse durumu doğrudan EMERGENCY moduna zorla
    if (Emergency_Get_Status() == 1)
    {
        current_state = STATE_EMERGENCY;
    }

    // Durum Makinesi Dallanması
    switch (current_state)
    {
    case STATE_INIT:
        // Ağ bekleniyor anlamında Mavi led
        RGB_LED_Set_Color(RGB_COLOR_BLUE);
        current_state = STATE_NORMAL;
        break;

    case STATE_NORMAL:
        // Normal modda ekstra bir durum geçişi tetiklenmediği sürece kalmaya devam et
        break;

    case STATE_EMERGENCY:
        // Sistem acil durumda ise kilitli kal.
        if (Emergency_Get_Status() == 0)
        {
            // Eğer acil durum bayrağı temizlendiyse sistemi tekrar NORMAL moda döndür
            current_state = STATE_INIT;
        }
        break;

    default:
        current_state = STATE_INIT;
        break;
    }
}