/*******************************************************************************
	File        : LedApp.cpp
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Main function used to test LedWindows class
*******************************************************************************/
#ifndef ARDUINO

#include "pch.h"
#include <stdio.h>
#include "LedWindows.h"
#include "TestLed.h"

#include "LedArduino.h"

int main()
{
	printf("Single led Test start!\n\n");

	// Testing  single led 
	if (TestLed() == false)
	{ 
		printf("Led Test Fail!\n\n");
	}
	
	printf("\nRun Test start!\n\n");

	// Testing 2 led
	LedWindows * pt_led1 = new LedWindows("Led_B", 1u);
	
	if (pt_led1 != NULL)
	{
		LedWindows * pt_led2 = new LedWindows("Led_C", 2u);

		if (pt_led2 != NULL)
		{
			Init(pt_led1, pt_led2);
			
			// Run cycle
			Run(pt_led1, pt_led2);

			delete pt_led2;
		}

		delete pt_led1;
	}

	printf("\nGoodbye Test!\n");
}

#endif
