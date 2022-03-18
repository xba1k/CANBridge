#ifndef ESP8266_H
#define ESP8266_H

#include <Arduino.h>
#include "settings.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <IPAddress.h>
extern WiFiUDP Udp;
#else
#include "HardwareSerial.h"
#endif

int init_wifi();
int wifi_send_data(uint8_t *data, int len);
int init_server();
int recv_datagram(uint8_t *data, int len);

#endif
