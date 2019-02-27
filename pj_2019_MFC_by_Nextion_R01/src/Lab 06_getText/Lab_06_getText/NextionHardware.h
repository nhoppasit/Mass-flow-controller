#ifndef __NEXHARDWARE_H__
#define __NEXHARDWARE_H__
#include <Arduino.h>

bool systemInit(void);
bool recvRetNumber(uint32_t *number, uint32_t timeout = 100);
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout = 100);
uint16_t recvRetString2(char *buffer, uint16_t len, uint32_t timeout = 100);
void sendCommand(const char* cmd);
bool recvRetCommandFinished(uint32_t timeout = 100);

#endif /* #ifndef __NEXHARDWARE_H__ */
