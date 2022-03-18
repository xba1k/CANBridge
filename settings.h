#ifndef SETTINGS_H
#define SETTINGS_H


// ESP8266, NANO or MEGA
#define ESP8266

// Serial for Nano, Serial1 for Mega
#ifdef MEGA
#define wifiSerial (&Serial1)
#endif

#ifdef NANO
#define wifiSerial (&Serial)
#endif

// serial baudrate to ESP82666
#define DEFAULT_WIFI_BAUDRATE 115200

// wifi network credentials
#define WIFI_SSID "mynetwork"
#define WIFI_PASSWORD "mypassword"

// target address and port
#define BROADCAST_ADDR "255.255.255.255"
#if defined(ESP8266)
#define BROADCAST_PORT 1080
#else
#define BROADCAST_PORT "1080"
#endif

// CANBus speed and MCP2515 chip select pin (10 for Nano, 53 for Mega, 15 ESP8266)
#define CAN_SPEED CAN_500KBPS

#ifdef MEGA
#define CAN_CS_PIN 53
#endif

#ifdef NANO
#define CAN_CS_PIN 10
#endif

#ifdef ESP8266
#define CAN_CS_PIN 15
#endif

#endif
