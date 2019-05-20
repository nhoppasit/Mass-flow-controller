#ifndef __NEXHARDWARE_H__
#define __NEXHARDWARE_H__
#include <Arduino.h>

bool systemInit(void);
bool recvRetNumber(uint32_t *number, uint32_t timeout = 1500);
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout = 1500);
void sendCommand(const char* cmd);
bool recvRetCommandFixnished(uint32_t timeout = 1500);

#endif /* #ifndef __NEXHARDWARE_H__ */
