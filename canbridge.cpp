#include <Arduino.h>
#include "util.h"
#include "esp8266.h"
#include "mcpc.h"

#define SERIAL_BAUD 9600
#define POLL_INTERVAL 100

char buf[128];
long last_status = 0;

void setup() {

#ifdef MEGA
	Serial.begin(SERIAL_BAUD);
#endif
	DEBUGP("Starting CANBridge\r\n");

	if (init_wifi()>0) {
		DEBUGP("Wifi initialized\r\n");
	} else {
		DEBUGP("Wifi initialization error\r\n");
	}

	init_mcpc();

	delay(2000);
	DEBUGP("Init complete\r\n");
}

void loop() {
	uint8_t frame_len;

	struct {
		unsigned long id;
		uint8_t can_frame[64];
	} datagram;

	if(millis() > last_status + 60000) {
		DEBUGP("Uptime: %us\r\n", (int)(millis() / 1000));
		DEBUGP("Free memory: %u\r\n", freeMemory());
		last_status = millis();
	}

	if (recv_frame(&datagram.id, datagram.can_frame, &frame_len)) {
		DEBUGP("received can frame with length %u\r\n", frame_len);
		wifi_send_data((uint8_t*)&datagram, frame_len+4);
	}

	delay(POLL_INTERVAL);
}
