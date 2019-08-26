/*******************************************************************************
	File        : Led.h
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Abstract Led class interface
*******************************************************************************/

#ifndef LED_H_
#define LED_H_

/*******************************************************************************
	Includes 
*******************************************************************************/

#include <stdint.h>

/*******************************************************************************
	Class declaration 
*******************************************************************************/

/// Abstract Class 
class Led
{
public:

	// Led status
	enum class Status : uint8_t { Off = 0, On = 1 };

	// Constructors
	Led(const char *p_name, Status status);

	// Distructor 
	virtual ~Led();

	// On 
	void SwitchOn();

	// Off 
	void SwitchOff();

	// Toggle
	void Toggle();

	// Status getter
	Status GetState() { return m_state; }

	// Name getter
	const char * GetName() { return p_name; } 

protected:

	// Led name
	const char * p_name;

	// Led status 
	Status m_state;

private:

	// Virtual pure methods 
	virtual void doSwitchOn() = 0;

	virtual void doSwitchOff() = 0;
};


#endif /* LED_H_ */