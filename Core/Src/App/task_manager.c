/**
 * @file task_manager.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief RTOS kuyruk dinleme, durum makinesi entegrasyonu ve motor/LED yürütücü birimi
 * @version 0.2
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "task_manager.h"
#include "emergency.h"
#include "state_machine.h"
#include "command_parser.h"
#include "motor_driver.h"
#include "rgb_led.h"
#include "cmsis_os.h"

// Kuyruk referansı
extern osMessageQId Queue_NetCmdHandle;

// Aktif görev degiskeni
volatile uint8_t active_task = CMD_STOP;

/**
 * @brief Yönlendirici Task'i
 */
void TaskManager_Dispatch_Process(void)
{
    osEvent event;
    uint8_t received_cmd = 255;
    uint8_t cmd_source_valid = 0;

    State_Machine_Update();

    // Ağ kuyruğundan mesaj bekle
    event = osMessageGet(Queue_NetCmdHandle, 10);
    if (event.status == osEventMessage)
    {
        received_cmd = (uint8_t)event.value.v;
        cmd_source_valid = 1;
    }

    if (cmd_source_valid == 1)
    {
        // Sıfırlama komutu her durumdan bağımsız çalışır
        if (received_cmd == CMD_RESET)
        {
            Emergency_Reset_Status();
            active_task = CMD_STOP;
            RGB_LED_Set_Color(RGB_COLOR_BLUE);
        }
        else
        {
            active_task = received_cmd; // Gelen komutu aktif görev olarak ata
        }
    }

    // Acil durum tetiklendiyse her şeyi ez ve kilitle
    if (State_Get_Current() == STATE_EMERGENCY)
    {
        active_task = CMD_STOP;
        Motor_Set_Speed_Direction(MOTOR_DIR_STOP, 0);
        RGB_LED_Set_Color(RGB_COLOR_RED);
    }
    else if (active_task == CMD_STOP)
    {
        // Hiçbir komut yoksa dur ve bekle
        Motor_Set_Speed_Direction(MOTOR_DIR_STOP, 0);
        RGB_LED_Set_Color(RGB_COLOR_BLUE);
    }
}

/**
 * @brief Görev taskidir. (High Priority - Yeşil LED, Sağ Yön, Tam Hız)
 */
void TaskManager_DriveRight_Process(void)
{
    if (active_task == CMD_DRIVE_RIGHT && State_Get_Current() == STATE_NORMAL)
    {
        Motor_Set_Speed_Direction(MOTOR_DIR_FORWARD, 100);
        RGB_LED_Set_Color(RGB_COLOR_GREEN);
    }
}

/**
 * @brief Görev taskidir. (Low Priority - Sarı LED, Sol Yön, Tam Hız)
 */
void TaskManager_DriveLeft_Process(void)
{
    if (active_task == CMD_DRIVE_LEFT && State_Get_Current() == STATE_NORMAL)
    {
        Motor_Set_Speed_Direction(MOTOR_DIR_REVERSE, 100);
        RGB_LED_Set_Color(RGB_COLOR_YELLOW);
    }
}

/**
 * @brief Görev taskidir.  (High Priority - Kırmızı Blink, Sağ Yöne Yavaş Hızlanma)
 */
void TaskManager_DriveRamp_Process(void)
{
    static uint8_t speed = 0;
    static uint8_t led_state = 0;
    static uint32_t blink_counter = 0;
    static uint8_t ramp_divider = 0;

    if (active_task == CMD_DRIVE_RAMP && State_Get_Current() == STATE_NORMAL)
    {
        // Rampalama
        ramp_divider++;
        if (ramp_divider >= 10)
        {
            ramp_divider = 0;
            if (speed < 100)
                speed++; // 100'ü geçmeyecek
        }

        if (speed > 100)
            speed = 100;

        Motor_Set_Speed_Direction(MOTOR_DIR_FORWARD, speed);

        // Kırmızı LED Blink
        blink_counter++;
        if (blink_counter >= 50)
        {
            blink_counter = 0;
            led_state = !led_state;
            RGB_LED_Set_Color(led_state ? RGB_COLOR_RED : RGB_COLOR_OFF);
        }
    }
    else
    {
        speed = 0; // Görev değişince hızı sıfırla
        ramp_divider = 0;
    }
}