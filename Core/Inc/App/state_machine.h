/**
 * @file state_machine.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief Sistemin genel durum yönetimini sağlayan dosya
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef APP_STATE_MACHINE_H_
#define APP_STATE_MACHINE_H_

/**
 * @brief Sistemin operasyonel durum tanımlamaları.
 */
typedef enum
{
    STATE_INIT = 0, // Sistem ilk durumu
    STATE_NORMAL,   // Normal çalışma modu
    STATE_EMERGENCY // Acil durum kilitlenme modu
} System_State_t;

/**
 * @brief Sistemin anlık durumunu döndürür.
 *
 * @return System_State_t Aktif sistem durumu.
 */
System_State_t State_Get_Current(void);

/**
 * @brief Girdilere göre sistem durumunu günceller.
 */
void State_Machine_Update(void);

#endif /* APP_STATE_MACHINE_H_ */