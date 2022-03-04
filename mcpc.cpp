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
		//CAN->clearBufferTransmitIfFlags();
		return result == CAN_OK;
	}

	return 0;
}
