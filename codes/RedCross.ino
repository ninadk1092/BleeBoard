//Includes
#include<SoftwareSerial.h>
#include<EnableInterrupt.h>


SoftwareSerial debug(11,12);

int R = 7, G = 6, B = 8, motor=9, flag = 0, led = 4, stat=5;
boolean charging, debug;
volatile int state = LOW;

int recvCount=0;

void setup()
{
  pinMode(R, OUTPUT);
  digitalWrite(R,HIGH);
  pinMode(G, OUTPUT);
  digitalWrite(G,HIGH);
  pinMode(B, OUTPUT);
  digitalWrite(B,HIGH);

  pinMode(A2,OUTPUT);
  pinMode(motor,OUTPUT);
  digitalWrite(A2,LOW);
  
  //Enabling Interrupts
  enableInterrupt(5, charger, CHANGE);
  enableInterrupt(0, button, FALLING);
  
  if(digitalRead(stat) == HIGH)
  charging = false;
  else
  charging = true;
  
  Serial.begin(9600);
  Serial.flush();
  
  debug.begin(9600);
  Serial.flush();
  
  delay(200);
  toggleLed();
      delay(100);
      
  if(connectWifi())
  {
     digitalWrite(LOW,B);   
     digitalWrite(HIGH,R);
     digitalWrite(HIGH,G);    //BLUE
  }
}

void loop()
{
  
  
  if(state){
    digitalWrite(A2,HIGH);    //CH_PD pin, enable ESP
    
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
  
    String str = "";
  int len,i;
  
  len = Serial.available();
  
  for(i=0;i<len;i++) {
    
    str += char(Serial.read());
  }
  
  //if(str!="")
   // Serial.println(str);
    
    for(flag=0,i=0;i<len;i++)
    {
        if(str[i] == ':')
         {
         flag=1;
        continue;
          }
      
      if(flag==1 && str[i] == 't')
      {
          toggleLed();
          //Serial.println("t received");
          recvCount++;
          break;
    }
    
      if(flag==1 && str[i] == 'p')
      {
          playSeq();
          Serial.println("p received");
          recvCount++;
          break;
    }
    
    }

    Serial.flush();
    
    if(recvCount>3){
    resetConn();
        recvCount=0;

    }
  
  
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
     if(Serial.find("OK"))
     flag++;
   
     Serial.print("AT+RST\r\n");
     if(Serial.find("OK") || Serial.find("ready"))
     flag++;
  
      Serial.print("AT+CWMODE=1\r\n");
      delay(1000);
      flag++;
  
      Serial.print("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n");
      if(Serial.find("OK"))
      flag++;
    
      Serial.print("AT+CIPMUX=1\r\n");
      delay(500);
      flag++;

      Serial.print("AT+CIPSERVER=1,6000\r\n");
      if(Serial.find("OK"))
      flag++;
      
      return flag;

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


