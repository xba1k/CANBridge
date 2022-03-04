#ifndef SETTINGS_H
#define SETTINGS_H

#define MEGA
// Serial for Nano, Serial1 for Mega
#ifdef MEGA
#define wifiSerial (&Serial1)
#else
#define wifiSerial (&Serial)
#endif

// serial baudrate to ESP82666
#define DEFAULT_WIFI_BAUDRATE 115200

// wifi network credentials
#define WIFI_SSID "mynetwork"
#define WIFI_PASSWORD "mypassword"

// target address and port
#define BROADCAST_ADDR "255.255.255.255"
#define BROADCAST_PORT "1080"

// CANBus speed and MCP2515 chip select pin (10 for Nano, 53 for Mega)
#define CAN_SPEED CAN_500KBPS

#ifdef MEGA
#define CAN_CS_PIN 53
#else
#define CAN_CS_PIN 10
#endif

#endif
