/*******************************************************************************
	File        : TestLed.cpp
	Date        : 10/11/2018
	Author      : Federico Coppo
	Description : Test module routine
*******************************************************************************/

/*******************************************************************************
	Includes
*******************************************************************************/

#ifndef ARDUINO
#include<conio.h>
#include <windows.h>
#else
#include<Arduino.h> 
#endif

#include <stdio.h>
#include "LedWindows.h"

/*******************************************************************************
	Routines implementation
*******************************************************************************/

// Switch on test
static bool testSwitchOn(Led * ptr)
{
	bool ret = false;

	ptr->SwitchOn();

	if (ptr->GetState() == Led::Status::On)
	{
		printf("%s switch ON test pass\n", ptr->GetName());
		ret = true;
	}
	else
	{
		printf("%s switch ON test fail!\n", ptr->GetName());
	}

	return ret;
}

// Switch off test
static bool testSwitchOff(Led * ptr)
{
	bool ret = false;

	ptr->SwitchOff();

	if (ptr->GetState() == Led::Status::Off)
	{
		printf("%s switch OFF test pass\n", ptr->GetName());
		ret = true;
	}
	else
	{
		printf("%s switch OFF test fail!\n", ptr->GetName());
	}

	return ret;
}

// Toggle test
static bool testToggle(Led * ptr)
{
	bool ret = false;

	// Store the status
	Led::Status tmp = ptr->GetState();

	ptr->Toggle();

	if (ptr->GetState() != tmp)
	{
		printf("%s Toggle test pass\n", ptr->GetName());
		ret = true;
	}
	else
	{
		printf("%s Toggle test fail!\n", ptr->GetName());
	}

	return ret;
}

// Unit test function
bool TestLed()
{
	bool success = true;

	// Testing Led A on port zero switched off 
	LedWindows * ptTestWinLed = new LedWindows("Led_A", 0u, LedWindows::Status::Off);  

	if (ptTestWinLed != NULL)
	{
		// Switch ON
		success &= testSwitchOn(ptTestWinLed);

		// Switch OFF
		success &= testSwitchOff(ptTestWinLed);

		// Toggle
		success &= testToggle(ptTestWinLed);
		success &= testToggle(ptTestWinLed);

		// Switch OFF
		success &= testSwitchOff(ptTestWinLed);

		// Toggle
		success &= testToggle(ptTestWinLed);
		success &= testToggle(ptTestWinLed);

		delete ptTestWinLed;
	}
	else
	{
		success = false;
	}

	return success;
}

#ifndef ARDUINO
// Non blocking key checker
static int getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}
#endif

// Print the key options
static void printMenu()
{
	printf("\nMenu options:\n");
	printf(" e Exit\n");
	printf(" h Print this menu\n");
	printf(" f Switch off both led\n");
	printf(" n Switch on both led\n");
	printf(" t Set led 1 opposite to led 2\n");
}

// Init led
void Init(Led * pt1, Led * pt2)
{
	if (pt1 != NULL)
	{
		// Late binding
		pt1->SwitchOn();
	}

	if (pt2 != NULL)
	{
		// Late binding
		pt2->SwitchOn();
	}
}

// Run Function
void Run(Led * pt1, Led * pt2)
{
	char c;
	char lastKeyPressed = 'a';
	bool finish = false;

	printMenu();

	while (!finish)
	{
    #ifndef ARDUINO
		c = getch_noblock();
		if ( (c != -1) && (c != 0) )
		{
			lastKeyPressed = c;

			switch (c)
			{
			case 'e':
				finish = true;
				break;

			case 'f':
				pt1->SwitchOff();
				pt2->SwitchOff();
				break;

			case 'n':
				pt1->SwitchOn();
				pt2->SwitchOn();
				break;

			case 't':
				if (pt2->GetState() == Led::Status::On)
					pt1->SwitchOff(); 
				else
					pt1->SwitchOn();
				break;

			case 'h':
				 printMenu();
				 break;

			default:
				printf("\nInvalid option!\n");
				break;
			}
		}
		else
		{
			// Continuous toggling since any valid/invalid key is pushed
			if (lastKeyPressed == 't')
			{
				pt1->Toggle();
				pt2->Toggle();
			}
		}
   
   Sleep(500);
   
   #else
   // Arduino Board toggling [4 sec]
   pt1->Toggle();
   pt2->Toggle();  
   delay(4000); 
   #endif
	}
}
