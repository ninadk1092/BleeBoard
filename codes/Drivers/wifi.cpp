
#include "wifi.h"

/*
	the actual embedded functions will be written via header file "x.h"
	User will not be able to change baud rate unless he makes changes to the driver file
	open:
		baud_rate, AT and then look for OK, if all is well, proceed, else, return FALSE. check AP or nonAP mode. 
		retrieve first default wifi AP details. connectWifi()
	write:
		acknowledgements of data reception to sender
		disable() : CH_PD LOW
	read: 
		request for data from the API/ mobile
	ioctl:
		look for data on serial ports
	close:
		Serial.end()
		
*/

Wifi wifi;

/*** Using the LED ***/

bool Wifi::inUse = false;
bool Wifi::isOn = false;


//################ Open #####################

void Wifi::open(bool yn)
{

	Serial.begin(9600);
	connect();
}

private void connect()
{
	int success = 0;
	char storedaplist[][];

	//reset
	sendData(RST); 	//RST macro is defined in Wifi.h
  	if(debug) while(Serial.available()) debugport.println(Serial.read());
	else if(OK) success++;

	//if debug is enabled, success value will not match. Ignore it.  
	
	//set AP, nonAP, both
	if(state[AP] == 'A')
  	sendData(APMODE);
	if(state[AP] == 'N')
  	sendData(STMODE);
	//both code here
	
	//----------------------------

	//try to Join access points stored in EEPROM, one by one
	storedaplist = getstoredAPlist();
	//sendData(); 
  	//Serial.println(sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n"));
  	sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n");
  	sendData("AT+CIPMUX=1\r\n");
  	sendData("AT+CIPSERVER=1,6000\r\n");
  
 	Serial.println("Connection Established");
}

//################ Write #####################

void Wifi::sendData(String cmd)
{
	String response= "";
  
  	Serial.print(cmd);
  
  	while(Serial.available()){
      	response += char(Serial.read());
     
  }
	if(debug)
  	Serial.println(response);
  
  return response;
}

//################ Read #####################




//################ Close #####################

void Wifi::disableWifi()
{
	digitalWrite(A2, LOW);	//CH_PD LOW
}
