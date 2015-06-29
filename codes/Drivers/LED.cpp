/*changes :
blink() and toggle() functions should not be in the driver. Move them to src.
*/

#include "LED.h"
// to include "x.h"

/*
	the actual embedded functions will be written via header file "x.h"
	This shall include LED_asOutput(), LED_asNotOutput(), LED_setHigh(), LED_setLow()
*/

/*** LED functions ***/
LED LED

/*** Using the LED ***/

bool LED::inUse = false;
bool LED::isOn = false;


//this shall set the DDR register accordingly
void LED::open(bool yn)
{
	if (yn)		//set LED pin
		LED_asOutput();
	
	else			//ddr = 0;
		LED_asNotOutput();

	inUse = yn;
}

//this shall set the PORT register accordingly
void LED::switchOn(bool yn)
{
	if (yn)		//start LED
		LED_setHigh();
	else			//stop LED
		LED_setLow();

	isOn = yn;
}

/*** Blink LED ***/
void LED::blink(int numberOfTimes, int Delay_OnTime, int Delay_OffTime)
{
	int i = 0;
	bool prevState = isOn;

	//clear LED
	switchOn(false);

	//for loop for blinking
	for(i=0; i<numberOfTimes; i++)
	{
		toggle();
		_delay(Delay_OnTime);
		toggle();
		_delay(Delay_OffTime);
	}
	
	// bring back to previous state
	switchOn(prevState);
}

/*** Toggle LED ***/

void LED::toggle()		
{
	// toggle previous state
	switchOn(~isOn);
	//updateCondition();
}

/*** ***/

