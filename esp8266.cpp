#include "util.h"
#include "esp8266.h"

#define BUF_SIZ 256
char wifi_buf[BUF_SIZ];

void flush_input() {
	if (wifiSerial->available() > 0) {
		DEBUGP("characters in the receive buffer, discarding...\r\n");
		while (wifiSerial->available() > 0)
			wifiSerial->read();
	}
}

int esp_cmd(char *cmd, char *resp) {
	int bytes = 0;

	wifiSerial->write(cmd);
	wifiSerial->flush();
	delay(100);

	bytes = wifiSerial->available();

	if (bytes > 0) {
		bytes = wifiSerial->readBytes(resp, min(bytes, BUF_SIZ-1));
		resp[min(bytes, BUF_SIZ-1)] = '\0';
		DEBUGP("%s\r\n", resp);
	}

	flush_input();
	delay(100);
	return bytes;
}

char* disable_echo() {
	DEBUGP("disable echo\r\n");
	esp_cmd("ATE0\r\n", wifi_buf);
	return wifi_buf;
}

char* reset_module() {
	DEBUGP("reset module\r\n");
	esp_cmd("AT+RST\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char* set_station_mode() {
	DEBUGP("set station mode\r\n");
	esp_cmd("AT+CWMODE=1\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char* set_network(char *ssid, char *password) {
	char network_command[64];

	DEBUGP("select network\r\n");

	sprintf(network_command, "AT+CWJAP_CUR=\"%s\",\"%s\"\r\n", ssid, password);
	esp_cmd(network_command, wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char* set_target_address(char *address, char *port) {
	char address_command[64];

	DEBUGP("setup UDP target\r\n");

	sprintf(address_command, "AT+CIPSTART=\"UDP\",\"%s\",%s\r\n", address,
			port);
	esp_cmd("AT+CIPSTART=\"UDP\",\"255.255.255.255\",1080\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char* get_module_version() {
	DEBUGP("check module version\r\n");
	esp_cmd("AT+GMR\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char* get_module_mac() {
	DEBUGP("check module MAC\r\n");
	esp_cmd("AT+CIPSTAMAC_CUR?\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

char *get_conn_status() {
	DEBUGP("check connection status\r\n");
	esp_cmd("AT+CIPSTATUS\r\n", wifi_buf);
	return rtrim(ltrim(wifi_buf));
}

int wifi_send_data(uint8_t *data, int len) {
	char cmd[20];

	DEBUGP("send datagram\r\n");

	sprintf(cmd, "AT+CIPSEND=%u\r\n", len);
	esp_cmd(cmd, wifi_buf);

	wifiSerial->write(data, len);
	wifiSerial->flush();
	delay(100);

	flush_input();
	delay(200);
}

int init_wifi() {
	DEBUGP("init_wifi\r\n");

	wifiSerial->begin(DEFAULT_WIFI_BAUDRATE);

	reset_module();
	delay(1000);
	flush_input();
	disable_echo();

	// Put ESP into station mode. This can also be replaced with SoftAP mode for some use cases.
	set_station_mode();
	DEBUGP("Set station mode: %s\r\n", wifi_buf);

	set_network(WIFI_SSID, WIFI_PASSWORD);
	DEBUGP("Set network: %s\r\n", wifi_buf);

	wifi_buf[0] = '\0';

	// It may take a bit to acquire registration. Obviously we can get stuck here forever too...
	while(strstr(wifi_buf, "STATUS:2") != wifi_buf) {
		get_conn_status();
		DEBUGP("Connection status: %s\r\n", wifi_buf);
		delay(1000);
	}

	set_target_address(BROADCAST_ADDR, BROADCAST_PORT);
	DEBUGP("Set target address: %s\r\n", wifi_buf);

	return 1;

}
