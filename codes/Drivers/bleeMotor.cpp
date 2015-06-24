/*change separate functions for setSpeed() and switchOn(), to overloaded functions. */ 

#include "bleeMotor.h"

// to include "x.h"

/*
	the actual embedded functions will be written via header file "x.h"
	This shall include mtr_asOutput(), mtr_asNotOutput(), mtr_run(), mtr_stop()
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

void motor::switchOn(bool yn)
{
	if (yn)		//start LED
		mtr_run();
	else			//stop LED
		mtr_stop();

	isOn = yn;
}


//returns intensity of the motor: on 255 [X/2.55 : gives %]
int motor::getSpeed(void)
{
	return motorIntensity;
}

//this shall set the motor direction/speed accordingly
void motor::setSpeed(int speed)
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
		
}

void motor::setLowerLimit(int lowSpeed)
{
	lowerLimit = lowSpeed;
}

/*** ***/
