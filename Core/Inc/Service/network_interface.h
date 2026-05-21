/**
 * @file network_interface.h
 * @author Emre Çakır (emrecakiroglu2@gmail.com)
 * @brief W5500 ağ ayarları ve TCP/HTTP Server işlemleri
 * @version 0.1
 * @date 2026-05-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef INC_SERVICE_NETWORK_INTERFACE_H_
#define INC_SERVICE_NETWORK_INTERFACE_H_

// Ağ Başlatma Fonksiyonu (Statik IP ve MAC ayarları)
void Network_Init(void);

// HTTP Sunucu Fonksiyonu
void Network_AppClient(void);

#endif /* INC_SERVICE_NETWORK_INTERFACE_H_ */
