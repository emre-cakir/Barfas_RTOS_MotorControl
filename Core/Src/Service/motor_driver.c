/**
 * @file motor_driver.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief L298N motor sürücü yön ve donanımsal PWM hız kontrol fonksiyonları.
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "main.h"
#include "motor_driver.h"
#include "tim.h"
#include "gpio.h"

// Timer 3 paterni
extern TIM_HandleTypeDef htim3;

/**
 * @brief PWM sinyalini başlatır
 */
void Motor_Init(void)
{
    // PWM sinyal üretimini sıfır duty ile başlatır
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    // Güvenlik için başlangıçta motoru durdur
    Motor_Set_Speed_Direction(MOTOR_DIR_STOP, 0);
}

/**
 * @brief Motorun yön GPIO pinlerini sürer ve PWM register değerini (CCR) günceller.
 */
void Motor_Set_Speed_Direction(Motor_Direction_t direction, uint8_t speed_percent)
{
    // Hız sınırlandırması
    if (speed_percent > 100)
        speed_percent = 100;

    uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim3);
    uint32_t ccr_value = (speed_percent * arr_value) / 100;

    // Yön Kontrolü
    switch (direction)
    {
    case MOTOR_DIR_FORWARD:
        // SAĞA
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_SET);
        break;

    case MOTOR_DIR_REVERSE:
        // SOLA
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
        break;

    case MOTOR_DIR_STOP:
    default:
        // DUR
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
        ccr_value = 0;
        break;
    }

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr_value);
}