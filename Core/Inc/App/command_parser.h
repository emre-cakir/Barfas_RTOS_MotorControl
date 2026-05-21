/**
 * @file command_parser.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief  Gelen ağ paketlerinden motor komutlarını ayrıştıran birim kütüphanesi
 * @version 0.2
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef INC_APP_COMMAND_PARSER_H_
#define INC_APP_COMMAND_PARSER_H_

#include <stdint.h>

// Komut Tanımlamaları
#define CMD_STOP 0
#define CMD_DRIVE_RIGHT 1
#define CMD_DRIVE_LEFT 2
#define CMD_DRIVE_RAMP 3
#define CMD_RESET 4

// Ağ üzerinden gelen ham metni ayrıştıran fonksiyon
void Parse_HTTP_Command(const char *http_request);

#endif /* INC_APP_COMMAND_PARSER_H_ */