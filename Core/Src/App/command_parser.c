/**
 * @file command_parser.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief Gelen ağ paketlerinden motor komutlarını ayrıştıran birim kütüphanesidir
 * @version 0.2
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "command_parser.h"
#include "string.h"
#include "cmsis_os.h"

// Kuyruk yöneticisi paterni
extern osMessageQId Queue_NetCmdHandle;

/**
 * @brief Gelen ham HTTP istek metnini analiz ederek motor kontrol komutlarını ayrıştırır
 * Geçerli bir komut (CMD=1, 2, 3, 4 vb.) bulunduğunda, bu komutu RTOS
 * kuyruğuna (Queue_NetCmd) göndererek Dispatch Task'ini tetikler
 *
 * @param http_request Ağ üzerinden alınan ve incelenecek olan null sonlandırmalı ham HTTP metin dizisi
 */
void Parse_HTTP_Command(const char *http_request)
{
    uint8_t parsed_cmd = CMD_STOP; // Varsayılan durum
    uint8_t cmd_found = 0;

    // Gelen metnin içinde "CMD=" parametresini ara ve görevlere yönlendir
    if (strstr(http_request, "CMD=0") != NULL)
    {
        parsed_cmd = CMD_STOP;
        cmd_found = 1;
    }
    else if (strstr(http_request, "CMD=1") != NULL)
    {
        parsed_cmd = CMD_DRIVE_RIGHT;
        cmd_found = 1;
    }
    else if (strstr(http_request, "CMD=2") != NULL)
    {
        parsed_cmd = CMD_DRIVE_LEFT;
        cmd_found = 1;
    }
    else if (strstr(http_request, "CMD=3") != NULL)
    {
        parsed_cmd = CMD_DRIVE_RAMP;
        cmd_found = 1;
    }
    else if (strstr(http_request, "CMD=4") != NULL)
    {
        parsed_cmd = CMD_RESET;
        cmd_found = 1;
    }

    // Eğer geçerli bir komut bulunduysa bunu RTOS kuyruğuna gönder
    if (cmd_found == 1)
    {
        if (Queue_NetCmdHandle != NULL) // Kuyruk tanımlıysa gönder
        {
            // Kuyruğa veriyi koy
            osMessagePut(Queue_NetCmdHandle, (uint32_t)parsed_cmd, 0);
        }
    }
}