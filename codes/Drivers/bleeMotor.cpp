/*change separate functions for setSpeed() and switchOn(), to overloaded functions. */ 

#include "bleeMotor.h"

// to include "x.h"

/*
	the actual embedded functions will be written via header file "x.h"
	This shall include mtr_asOutput(), mtr_asNotOutput(), mtr_run(), mtr_stop()
	delay functions
*/


/*** Motor functions ***/
motor motor

/*** Using the motor ***/

bool motor::inUse = false;
bool motor::isOn = false;

//this shall set the timer accordingly
void motor::open(bool yn)
{
	if (yn)		//configure timers and pwm pin
		mtr_asOutput();
	else		//disable pwm mode
		mtr_asNotOutput();

	inUse = yn;
}

//this shall run the motor at maximum intensity
void motor::switchOn()
{
	motorIntensity = FULL_INTENSITY;
}

// run motor at max intensity for a given time
void motor::switchOn(long delay)
{
	motorIntensity = FULL_INTENSITY;
	bleeDelay(delay, MOTOR);				/*this delay function shall be in "x.h"*/
}

//this shall set the motor direction/speed accordingly
void motor::switchOn(int speed)
{
	if(speed > lowerLimit){
		motorIntensity = speed;
		isOn = true;
	}
	else
	{
		motorIntensity = 0;
		isOn = false
	}
	
	isOn = yn;
}

void motor::switchOn(int speed, long delay)
{
	if(speed > lowerLimit){
		motorIntensity = speed;
		isOn = true;
	}
	else
	{
		motorIntensity = 0;
		isOn = false
	}

	bleeDelay(delay, MOTOR);

	isOn = yn;
}

//returns intensity of the motor: on 255 [X/2.55 : gives %]
int motor::getSpeed(void)
{
	return motorIntensity;
}

void motor::setLowerLimit(int lowSpeed)
{
	lowerLimit = lowSpeed;
}

/*** ***/
