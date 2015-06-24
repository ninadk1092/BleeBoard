
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
	/*if (yn)		//set LED pin
		LED_asOutput();
	
	else			//ddr = 0;
		LED_asNotOutput();

	inUse = yn;*/
}

private void connect()
{


	sendData(RST); 	//RST macro is defined in Wifi.h
//	if(Serial.find("OK"))
  	Serial.println("reset");
  	sendData("AT+CWMODE=1\r\n"); 
  	//sendData("AT+CWJAP=\"\",\"\"\r\n");
  	//Serial.println(sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n"));
  	sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n");
  	delay(7000);
  	Serial.println("Joined Hotspot");
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
