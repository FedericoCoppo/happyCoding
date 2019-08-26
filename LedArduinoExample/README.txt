Tools: Arduino Sketch and Microsoft Visual Studio Express (or Visual Studio Code or Visual Studio Community). 
Note: no Arduino HW is needed.
************************************************************************
Specification:
1.	with Microsoft Visual Studio Express, create a solution with one C++ console application project. In file containing function main():
	•	define abstract class Led:
		o	public methods: SwitchOn, SwitchOff, Toggle, GetState;
		o	private members: m_state (on and off);
		o	private virtual abstract methods doSwitchOn, doSwitchOff;
		o	methods SwitchOn, SwitchOff, Toggle must call private methods doSwitch* named above;
	•	define concrete class LedWindows, just implementing private methods doSwitch* named above;
		o	methods doSwitch* must do something like printf("Led %d - State: %s\n", m_nId, m_bState ? "@" : "-");
	•	define unit test function TestLed to:
		o	instantiate 1 LedWindows instance;
		o	switch on the led and check if GetState returns the expected value;
		o	switch off the led and check if GetState returns the expected value;
		o	toggle the led and check if GetState returns the expected value;
		o	toggle again the led and check if GetState returns the expected value;
		o	switch off the led and check if GetState returns the expected value;
		o	toggle the led and check if GetState returns the expected value;
		o	toggle again the led and check if GetState returns the expected value;
	•	in function main:
		o	call function TestLed;
		o	instantiate two LedWindows instances;
		o	call function Init (described below);
		o	loop calling function Run (described below);
	•	define a function Init to:
		o	set both leds to on;
	•	define function Run to:
		o	exit if user presses 'e'; hint: to implement a non-blocking getch(), something like this is needed or GetAsyncKeyState()==VK_e;  
		o	switch both leds off if user presses 'f' and keep them off;
		o	switch both leds on if user presses 'n' and keep them on;
		o	set the first led to the opposite state than the second one if user presses 't';
		o	toggle both leds if last key pressed was 't';
	o	sleeps for 500ms;
****************************************************************************
2.	with Arduino Sketch, compile the file containing the Windows main, using compilation switches to enable Windows or Arduino header inclusions as needed;
	•	define class LedArduino, just implementing private methods doSwitch* named above; 
		o	methods doSwitch* must call Arduino API function to set the corresponding digital output to the desired state;
	•	instantiate 2 LedArduino instances; hint: each led must use a different digital output;
	•	in setup() function, call function Init;
	•	in loop() function, call function Run;
		o	in function Run, disable key handling with a proper compilation switch; the expected work mode is toggling for ever;
*****************************************************************************
3.	deployment: done the code change, check that everything is OK:
	•	Windows: project must compile and run successfully;
	•	Arduino: project must compile successful
*****************************************************************************
Solution 1: see LedApp
Solution 2,3: see LedAppArduino
