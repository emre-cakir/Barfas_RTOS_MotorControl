/**
 * @file emergency.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief Donanımsal acil durum buton kesmesi ve güvenlik katmanı başlık dosyası.
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SERVICE_EMERGENCY_H_
#define SERVICE_EMERGENCY_H_

#include <stdint.h>

/**
 * @brief Sistemin emergency bayrağını döndürür.
 *
 * @return uint8_t 1: Sistem acil durumda, 0: Sistem normal çalışıyor.
 */
uint8_t Emergency_Get_Status(void);

/**
 * @brief Acil durum durumunu temizler ve sistemi yeniden başlatılabilir hale getirir.
 */
void Emergency_Reset_Status(void);

/**
 * @brief Acil durum tetiklendiğinde sistemi güvenli moda sokan fonksiyon.
 */
void Emergency_Trigger(void);

#endif /* SERVICE_EMERGENCY_H_ */