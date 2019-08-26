/*******************************************************************************
  File        : LedApp.cpp
  Date        : 10/11/2018
  Author      : Federico Coppo
  Description : Arduino main
*******************************************************************************/

/*******************************************************************************
  Includes 
*******************************************************************************/

#include "LedArduino.h"
#include "TestLed.h"

/*******************************************************************************
  Define 
*******************************************************************************/
#ifndef ARDUINO
#define ARDUINO
#endif

// Definition of static label
static const uint8_t LED_MAX_NUM = 2;
static LedArduino * pt_led[LED_MAX_NUM];
  
void setup() {

    // Led construction
    pt_led[0] = new LedArduino("Arduino Led_A", 13, Led::Status::Off);
    pt_led[1] = new LedArduino("Arduino Led_B", 2, Led::Status::Off);
  
   // Init call (switch on the leds)
   if ( (pt_led[0] != NULL) && (pt_led[1] != NULL) )
   {
       Init(pt_led[0], pt_led[1]);
   }
   
   Serial.begin(9600);
   // wait for serial port to connect
   while (!Serial) {
                    ; 
                   }
}

void loop() {

    if ((pt_led[0] != NULL) && (pt_led[1] != NULL))  
    {
      // Infinite toggling
      Run(pt_led[0], pt_led[1]);
    }  

    // Code reached when something fail
    for (int i = 0; i < LED_MAX_NUM; i++)
    {
      if (pt_led[i] != NULL)
      {
        delete pt_led[i];
      }  
    }
}
