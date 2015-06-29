#include "pushButton.h"

// to include "x.h"

/*
	the actual embedded functions will be written via header file "x.h"
	This shall include pushBtn_asInput(), pushBtn_asNotInput()
*/


/*** PushButton functions ***/
pushButton pb

/*** Using the button ***/

bool pushButton::inUse = false;
bool pushButton::isPressed = false;

void pushButton::open(bool yn)
{
	if (yn)		//clear DDR values
		pushBtn_asInput();
	else		//set DDR values
		pushBtn_asNotInput();	

	inUse = yn;
}

int pushButton::getPeriod(void)
{
	return debouncePeriod;
}

void pushButton::setPeriod(int debounce)
{
	if(debounce < 40){
		debouncePeriod = debounce;
	}
	else
	{
		debouncePeriod = 40;
	}
		
}

char pushButton::getPrevPress(void)
{
	return prevPress;
}

/*
	The following functions are logic functions
*/

/*
void pushButton::setOnLongPress()
{
	// Set what should happen on long press
}

void pushButton::setOnShortPress()
{
	// Set what should happen on short press
}

void pushButton::setOnDoublePress()
{
	// Set what should happen on double press
}
*/

/***/
