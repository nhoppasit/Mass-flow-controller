#ifndef __NEXTEXT_H__
#define __NEXTEXT_H__

#include "NextionHardware.h"

/**
 * Get text attribute of component.
 *
 * @param buffer - buffer storing text returned. 
 * @param len - length of buffer. 
 * @return The real length of text returned. 
 */
uint16_t getText(const char *objName, char *buffer, uint16_t len);

/**
 * Set text attribute of component.
 *
 * @param buffer - text buffer terminated with '\0'. 
 * @return true if success, false for failure. 
 */
bool setText(const char *objName, const char *buffer);    

/**
 * Call page.
 *
 * @param pageId - page id text buffer terminated with '\0'. 
 * @return true if success, false for failure. 
 */
bool callPage(const char *pageId);


#endif /* #ifndef __NEXTEXT_H__ */
