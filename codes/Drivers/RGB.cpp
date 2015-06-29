/* move blink out of the driver file */

#include "RGB.h"
// to include x.h

/*** RGB LED functions ***/
RGB RGB


/*** Using the RGB LED ***/

bool RGB::inUse = false;

//use or stop using RGB led
void RGB::open(bool yn)
{
	if (yn)			//open RGB-LED driver
 		RGB_asOutput();	/* this function will set PWM and timer modes. It will also mark the pins as Output*/

	else			//close RGB-LED driver
		RGB_asNotOutput();	/*the led pins could be made input or pulled low. The timer will be in CTC mode or NON-PWM*/
					/*the functions RGB_asOutput will be defined in the core embedded file "x.h"*/
	inUse = yn;
}

/*** Get the Color ***/
void RGB::getRGB()
{
	return [red, green, blue];
}

/*** Change the Color ***/
void RGB::setRGB(int redx, int greenx, int bluex)
{
	// assign PWM values to each channel: common anode
	red = 255 - redx;
	green = 255 - greenx;
	blue = 255 - bluex;
}

/*** Blink LED ***/
void RGB::blink(int numberOfTimes, int Delay_OnTime, int Delay_OffTime)
{
	int i = 0;
	int rgb[] = {red, green, blue};
	//for loop for blinking
	for(i=0; i<numberOfTimes; i++)
	{
		setRGB(0,0,0);
		_delay(Delay_OnTime);
		setRGB(rgb[0],rgb[1],rgb[2]);
		_delay(int Delay_OffTime);
	}
	
	// bring back to previous state
	setRGB(rgb[0],rgb[1],rgb[2]);
}
/*** ***/

