#include "NextionNumber.h"


bool getValue(unsigned char *objName, uint32_t *number)
{
    String cmd = String("get ");
    cmd += objName;
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool setValue(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    cmd += objName();
    cmd += ".val=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}