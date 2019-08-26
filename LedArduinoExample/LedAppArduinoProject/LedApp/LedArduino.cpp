/*******************************************************************************
	File        : LedArduino.cpp
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Arduino led class implementation
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/

#include <stdio.h>
#include "LedArduino.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif

/*******************************************************************************
	Methods implementation
*******************************************************************************/

// Constructors 
LedArduino::LedArduino(const char *p_name, uint8_t pin, Status status) :
	Led(p_name, status)
{
	// Led port init 
	this->digital_output = pin;

	#ifdef ARDUINO
	pinMode(this->digital_output, OUTPUT);
	#endif

}

// Destructor .
LedArduino::~LedArduino()
{
	doSwitchOff();
}

void LedArduino::doSwitchOn()
{
	this->m_state = Status::On;
    
	#ifdef ARDUINO
	digitalWrite(this->digital_output, HIGH);
	Serial.print(p_name);
	Serial.println(": switched ON");
	Serial.println();
	#endif
}

void LedArduino::doSwitchOff()
{
	this->m_state = Status::Off;

	#ifdef ARDUINO
	digitalWrite(this->digital_output, LOW);
	Serial.print(p_name);
	Serial.print(": switched OFF\n");
	Serial.println();
	#endif
}
