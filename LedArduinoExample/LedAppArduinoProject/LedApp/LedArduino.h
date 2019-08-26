/*******************************************************************************
	File        : LedArduino.h
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Arduino led class interface
*******************************************************************************/

#ifndef LED_ARDUINO_H_
#define LED_ARDUINO_H_

/*******************************************************************************
	Includes
*******************************************************************************/

#include <stdint.h>
#include "Led.h"

/*******************************************************************************
	Class declaration
*******************************************************************************/

// Class that implements the led
class LedArduino : public Led
{
public:

	// Constructors
	LedArduino(const char *p_name, uint8_t pin, Status status = Status::Off);

	// Destructor
	~LedArduino();

private:

	void doSwitchOn();

	void doSwitchOff();

	// Led port id
	uint8_t digital_output;

};

#endif /* LED_ARDUINO_H_ */