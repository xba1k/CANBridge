#ifndef MCPC_H
#define MCPC_H

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>
#include "util.h"
#include "settings.h"

#define CAN_DELAY 210

extern MCP_CAN *CAN;

void init_mcpc();
uint8_t recv_frame(unsigned long *id, uint8_t *frame, uint8_t *len);

#endif

