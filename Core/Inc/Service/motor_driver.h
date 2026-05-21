/**
 * @file motor_driver.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief L298N Motor Sürücü donanım kontrol katmanı dosyası.
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SERVICE_MOTOR_DRIVER_H_
#define SERVICE_MOTOR_DRIVER_H_

#include <stdint.h>

/**
 * @brief Motor hareket yönü tanımlamaları.
 */
typedef enum
{
    MOTOR_DIR_STOP = 0, // Motoru durdurma durumu
    MOTOR_DIR_FORWARD,  // Motoru ileri yönde döndürme durumu
    MOTOR_DIR_REVERSE   // Motoru geri yönde döndürme durumu
} Motor_Direction_t;

/**
 * @brief Motor sürücü çevre birimlerini ve PWM kanalını başlatır.
 */
void Motor_Init(void);

/**
 * @brief Motorun yönünü ve hızını ayarlar.
 *
 * @param direction Motorun döneceği yön
 * @param speed_percent %0 ile %100 arasında motor hız değeri
 */
void Motor_Set_Speed_Direction(Motor_Direction_t direction, uint8_t speed_percent);

#endif /* SERVICE_MOTOR_DRIVER_H_ */