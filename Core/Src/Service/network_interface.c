/**
 * @file network_interface.c
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief  W5500 Ağ arayüzü ve TCP Socket (HTTP) yönetimi
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "command_parser.h"
#include "network_interface.h"
#include "wizchip_conf.h"
#include "socket.h"
#include "string.h"

#define SOCK_TCPS 0
#define PORT_TCPS 80
#define DATA_BUF_SIZE 1024

// Sunucunun IP adresi
uint8_t target_ip[4] = {192, 168, 1, 18};
#define TARGET_PORT 8080

// HTTP Request'in tutulacağı tampon bellek
uint8_t rx_buffer[DATA_BUF_SIZE];

// W5500 Statik IP Yapılandırması
wiz_NetInfo gWIZNETINFO = {
    .mac = {0x00, 0x08, 0xDC, 0xAB, 0xCD, 0xEF}, // Wiznet MAC Adresi
    .ip = {192, 168, 1, 100},                    // Modülün IP Adresi
    .sn = {255, 255, 255, 0},                    // Subnet Mask
    .gw = {192, 168, 1, 1},                      // Gateway
    .dns = {8, 8, 8, 8},                         // Google DNS
    .dhcp = NETINFO_STATIC};

/**
 * @brief Ağ yapılandırmasını W5500 çipine yükler
 */
void Network_Init(void)
{
    wizchip_setnetinfo(&gWIZNETINFO);
}

/**
 * @brief Cihazı Client modunda çalıştıran fonksiyon
 */
void Network_AppClient(void)
{
    uint16_t len = 0;

    switch (getSn_SR(SOCK_TCPS))
    {
    case SOCK_ESTABLISHED: // Sunucuya bağlandı
        if (getSn_IR(SOCK_TCPS) & Sn_IR_CON)
        {
            setSn_IR(SOCK_TCPS, Sn_IR_CON);
            // Sunucudan komutları ister
            char *http_request = "GET /komutlar HTTP/1.1\r\nHost: 192.168.1.18\r\nConnection: close\r\n\r\n";
            send(SOCK_TCPS, (uint8_t *)http_request, strlen(http_request));
        }

        if ((len = getSn_RX_RSR(SOCK_TCPS)) > 0)
        {
            if (len > DATA_BUF_SIZE - 1)
                len = DATA_BUF_SIZE - 1;
            recv(SOCK_TCPS, rx_buffer, len);
            rx_buffer[len] = '\0';

            Parse_HTTP_Command((char *)rx_buffer);
            disconnect(SOCK_TCPS);
        }
        break;

    case SOCK_CLOSE_WAIT:
        disconnect(SOCK_TCPS);
        break;

    case SOCK_INIT:
        // Client mod
        connect(SOCK_TCPS, target_ip, TARGET_PORT);
        break;

    case SOCK_CLOSED:
        socket(SOCK_TCPS, Sn_MR_TCP, SOCK_TCPS, 0x00);
        break;
    }
}
