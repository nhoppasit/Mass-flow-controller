#include "NextionText.h"

uint16_t getText(const char *objName, char *buffer, uint16_t len)
{
    String cmd;
    cmd += "get ";
    cmd += objName;
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool setText(const char *objName, const char *buffer)
{
    String cmd;
    cmd += objName;
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

bool callPage(const char *pageId)
{
	String cmd;
	cmd += "page ";
	cmd += pageId;
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();    
}