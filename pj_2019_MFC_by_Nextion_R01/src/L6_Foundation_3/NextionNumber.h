#ifndef __NEXNUMBER_H__
#define __NEXNUMBER_H__


#include "NextionHardware.h"
   
/**
 * Get number attribute of component.
 *
 * @param number - buffer storing text returned. 
 * @return The real length of text returned. 
 */
bool getValue(uint32_t *number);
    
/**
 * Set number attribute of component.
 *
 * @param number - number buffer. 
 * @return true if success, false for failure. 
 */
bool setValue(uint32_t number);
	
/**
 * Get bco attribute of component
 *
 * @param number - buffer storing data retur
 * @return the length of the data 
 */
#endif /* #ifndef __NEXTEXT_H__ */   