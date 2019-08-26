/*******************************************************************************
	File        : LedWindows.h
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Windows led class interface
*******************************************************************************/

#ifndef LED_WINDOWS_H_
#define LED_WINDOWS_H_

/*******************************************************************************
	Includes
*******************************************************************************/

#include <stdint.h>
#include "Led.h"

/*******************************************************************************
	Class declaration
*******************************************************************************/

// Class that implements the led
class LedWindows : public Led
{
public:

	// Constructors
	LedWindows(const char *p_name, uint8_t port, Status status = Status::Off);
	
	LedWindows();

	// Destructor
	~LedWindows();

	// Used leds getter
	static uint32_t GetLedNum() { return usedLedNum; }

private:
	
	void doSwitchOn();
	
	void doSwitchOff();

	// Number of used leds 
	static uint32_t usedLedNum;

	// Led port id
	uint8_t port;

};

#endif /* LED_WINDOWS_H_ */