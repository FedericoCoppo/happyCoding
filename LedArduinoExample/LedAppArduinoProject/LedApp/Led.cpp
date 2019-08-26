/*******************************************************************************
	File        : Led.cpp
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Abstract Led class implementation
*******************************************************************************/

/*******************************************************************************
	Includes 
*******************************************************************************/

#include "Led.h"
#include <stdio.h>

/*******************************************************************************
	Methods implementation 
*******************************************************************************/

// Constructor 
Led::Led(const char *p_name, Status status)
{
	// Led name initialization
	if (p_name != NULL)
	{
		this->p_name = p_name;
	}
	else
	{
		this->p_name = "LED Unknow";
	}

	// Led internal status init 
	this->m_state = status;
}

// Destructor .
Led::~Led()
{
  // nothing
}

// Led on
void Led::SwitchOn()
{
	doSwitchOn();
}

// Led off
void Led::SwitchOff()
{
	doSwitchOff();
}

// Toggle the led status
void Led::Toggle()
{
	if (m_state == Status::On)
	{
		doSwitchOff();
	}
	else
	{
		doSwitchOn();
	}
}
