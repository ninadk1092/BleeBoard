//Includes
//#include<SoftwareSerial.h>
#include<EnableInterrupt.h>


//SoftwareSerial debugPort(11,12);

int R = 7, G = 6, B = 8, motor=9, flag = 0, led = 4, stat=5,count=0, rec=0;
boolean charging, debug;
volatile int state = HIGH;

int recvCount=0;

void setup()
{
  pinMode(A0,OUTPUT);
  
  digitalWrite(A0,HIGH);
  
  pinMode(R, OUTPUT);
  digitalWrite(R,LOW);
  pinMode(G, OUTPUT);
  digitalWrite(G,LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B,LOW);

  pinMode(A2,OUTPUT);
  pinMode(motor,OUTPUT);
  digitalWrite(A2,LOW);
  
  
  //Enabling Interrupts
  enableInterrupt(6, charger, CHANGE);
  enableInterrupt(3, button, FALLING);
  
  
//initializing charging state on boot
if(digitalRead(stat) == HIGH)
  	charging = false;
else
  	charging = true;
  
//Initializing ESP8266 baud rates
Serial.begin(9600);
Serial.flush();
  
//debugPort.begin(9600);
//debugPort.flush();
  
  delay(200);
  toggleLed();
      delay(100);
      
      
      
  if(connectWifi())
  {
     digitalWrite(LOW,B);   
     digitalWrite(HIGH,R);
     digitalWrite(HIGH,G);    //BLUE
     delay(2000);
  }
  else
  {
     digitalWrite(HIGH,B);   
     digitalWrite(HIGH,R);
     digitalWrite(HIGH,G);    //OFF
     delay(2000);
  }    
}

void loop()
{
  
  
  if(state){
    digitalWrite(A2,HIGH);    //CH_PD pin, enable ESP
    digitalWrite(R,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(B,HIGH);
   // digitalWrite(9,HIGH);
  }
  else{
    //Switching OFF device
   digitalWrite(A2,LOW);    //CH_PD pin, disable ESP
   digitalWrite(4,LOW);    //switching off Red LED
   digitalWrite(9,LOW);     //switching OFF motor
  digitalWrite(R, ~state);
  digitalWrite(G, ~state);
  digitalWrite(B, ~state);  //switching off RGB LED

  }
  
	if(charging)
	{
		digitalWrite(4,HIGH);
	}
	else
	{
		digitalWrite(4,LOW);
	}

  count = 0;
  if(Serial.available())
   {
    if(Serial.find("IPD"))
    {
      rec++;
      digitalWrite(R,HIGH);
      digitalWrite(G,HIGH);
      digitalWrite(B,LOW);
      delay(1000);
      digitalWrite(R,HIGH);
      digitalWrite(G,HIGH);
      digitalWrite(B,HIGH);
    }
   }
      if(rec%2 == 1)
      {
                digitalWrite(A0,LOW);
      delay(200);
     digitalWrite(A0,HIGH);
      delay(400);
     digitalWrite(A0,LOW);
      delay(90);
     digitalWrite(A0,HIGH);
     delay(400);
             digitalWrite(A0,LOW);
      delay(90);
     digitalWrite(A0,HIGH);
      delay(400);
      }

    Serial.flush();
      

}

//ISRs

void button(){
 state = ~state; 
}

void charger(){
 charging = ~charging; 
}

int connectWifi(){
     flag = 0;
  
     //Enable ESP
     digitalWrite(A2,HIGH);    //CH_PD pin, enable ESP
     delay(200);
  
     Serial.print("AT\r\n");
     if(Serial.find("OK")){
     flag++;
     }
     
     Serial.print("AT+RST\r\n");
     if(Serial.find("OK") || Serial.find("ready")){
     flag++;
     }
  
      Serial.print("AT+CWMODE=1\r\n");
      delay(1000);
      flag++;
  
      Serial.print("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n");
      count = 0;
      
      while(count < 10){
        if(Serial.find("OK")){
        flag++;
        break;
        }
        else
        count++;
      }
      
    
      Serial.print("AT+CIPMUX=1\r\n");
      delay(500);
      flag++;

      Serial.print("AT+CIPSERVER=1,6000\r\n");
      count = 0;
      
      while(count < 10){
        if(Serial.find("OK")){
        flag++;
        break;
        }
        else
        count++;
      }
      
    
      if(flag == 6)
      return true;
      else
      return false;

}

void toggleLed(){
        digitalWrite(led,HIGH);
        digitalWrite(9,HIGH);
      delay(500);
     digitalWrite(led,LOW);
      digitalWrite(9,LOW);
      delay(500);
     digitalWrite(led,HIGH);
     digitalWrite(9,HIGH);
      delay(500);
     digitalWrite(led,LOW);
     digitalWrite(9,LOW);
}

void playSeq(){
           digitalWrite(led,HIGH);
           digitalWrite(9,HIGH);
      delay(2500);
     digitalWrite(led,LOW);
     digitalWrite(9,LOW);
      delay(500);
     digitalWrite(led,HIGH);
     digitalWrite(9,HIGH);
      delay(2500);
     digitalWrite(led,LOW);
     digitalWrite(9,LOW);
}
