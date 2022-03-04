#ifndef ESP8266_H
#define ESP8266_H

#include <Arduino.h>
#include "settings.h"
#include "HardwareSerial.h"

int init_wifi();
int wifi_send_data(uint8_t *data, int len);

#endif
