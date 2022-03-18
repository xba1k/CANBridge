#include "mcpc.h"

MCP_CAN *CAN;

void init_mcpc() {
	CAN = new MCP_CAN(CAN_CS_PIN);
	while (CAN->begin(CAN_SPEED, MCP_8MHz) != CAN_OK) {
		DEBUGP("Unable to start CAN bus\n");
		delay(1000);
	}
}

uint8_t recv_frame(unsigned long *id, uint8_t *frame, uint8_t *len) {
	int result;
	if (CAN->checkReceive() == CAN_MSGAVAIL) {
		result = CAN->readMsgBufID(id, len, frame);
		return result == CAN_OK;
	}
	return 0;
}

uint8_t send_frame(unsigned long id, uint8_t *frame, uint8_t len) {
	uint8_t result;
	result = CAN->sendMsgBuf(id, 0, len, frame);
	delay(CAN_DELAY);
	return result;
}

