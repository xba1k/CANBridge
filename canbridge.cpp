#include <Arduino.h>
#include "util.h"
#include "esp8266.h"
#include "mcpc.h"

#ifdef ESP8266
#define SERIAL_BAUD 115200
#else
#define SERIAL_BAUD 9600
#endif
#define POLL_INTERVAL 100

char buf[128];
long last_status = 0;

void setup() {

#if defined(MEGA) || defined(ESP8266)
	Serial.begin(SERIAL_BAUD);
#endif
	DEBUGP("Starting CANBridge\r\n");

	if (init_wifi()>0) {
		DEBUGP("Wifi initialized\r\n");
	} else {
		DEBUGP("Wifi initialization error\r\n");
	}

	init_mcpc();

	if (init_server() > 0) {
		DEBUGP("UDP server started\r\n");
	}

	delay(2000);
	DEBUGP("Init complete\r\n");
}

void loop() {
	uint8_t dlen;

	struct {
		unsigned long id;
		uint8_t can_frame[64];
	} datagram;

	if(millis() > last_status + 60000) {
		DEBUGP("Uptime: %us\r\n", (int)(millis() / 1000));
		DEBUGP("Free memory: %u\r\n", freeMemory());
		last_status = millis();
	}

	if (recv_frame(&datagram.id, datagram.can_frame, &dlen)) {
		DEBUGP("received can frame with length %u\r\n", dlen);
		wifi_send_data((uint8_t*)&datagram, dlen+4);
	}

	if ((dlen = recv_datagram((uint8_t*) &datagram, sizeof(datagram))) > 0) {
#ifdef ESP8266
		DEBUGP("Received UDP datagram from %s with size %hhu\r\n", Udp.remoteIP().toString().c_str(), dlen);
#endif

#ifdef DEBUG
		for(int i = 0; i < dlen; i++) {
			DEBUGP("%hhx ", ((char*)&datagram)[i]);
		}
#endif

		DEBUGP("\r\n");
		send_frame(datagram.id, datagram.can_frame, dlen - sizeof(datagram.id));
	}

	delay(POLL_INTERVAL);
}
