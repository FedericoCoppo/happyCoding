/*******************************************************************************
	File        : LedWindows.cpp
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Windows led class implementation
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/

#include <stdio.h>
#include "LedWindows.h"

/*******************************************************************************
	Static class member initialization
*******************************************************************************/

uint32_t LedWindows::usedLedNum = 0;

/*******************************************************************************
	Methods implementation
*******************************************************************************/

// Constructors 
LedWindows::LedWindows(const char *p_name, uint8_t port, Status status):
	Led(p_name, status)
{
	// Led port init 
	this->port = port;
	usedLedNum++;
}

LedWindows::LedWindows():
	Led("LED Unknow", Status::Off)
{
	this->port = 0;
	usedLedNum++;
}

// Destructor .
LedWindows::~LedWindows()
{
	doSwitchOff();
	usedLedNum--;
}

void LedWindows::doSwitchOn()
{
	this->m_state = Status::On;
	printf("%s: switched ON\n", p_name);
}

void LedWindows::doSwitchOff()
{	
	this->m_state = Status::Off;
	printf("%s: switched OFF\n", p_name);
}
