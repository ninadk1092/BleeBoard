#include <SoftwareSerial.h>

SoftwareSerial wifiPort(10, 11); // RX, TX
//char charray[] = {'a','b','\0'};
//String str(charray);    //converting character array into string. ***'\0' is necessary at the end of the char array
int flag=0;
int led=0;
int recvCount=0;

void setup()  
{
  Serial.begin(9600);
  wifiPort.begin(9600);
  wifiPort.println("AT+RST");
  delay(1000);
  wifiPort.println("AT");
  digitalWrite(3,LOW);
    digitalWrite(2,LOW);
  recvCount=0;
  connectWifi();
  
}

void loop() 
{
  String str = "";
  int len,i;
  
  wifiPort.listen();
  delay(500);     //wait 1000ms for all serial data to arrive
  len = wifiPort.available() ;
  
  for(i=0;i<len;i++) {
    
    str += char(wifiPort.read());
   // Serial.println(str);
  }
  if(str!="")
    Serial.println(str);
    
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
          Serial.println("t received");
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
/*
  if (Serial.available() ){
    wifiPort.write(Serial.read());
  }*/
   // Serial.flush();
    wifiPort.flush();
    
    if(recvCount>2){
    resetConn();
        recvCount=0;

    }
}

String sendData(String cmd, int wait){
  
  String response= "";
  
  wifiPort.print(cmd);
  delay(wait);
  
  while(wifiPort.available()){
      response += char(wifiPort.read());
     
  }
  Serial.println(response);
  
  return response;
}

void connectWifi(){
  
  sendData("AT+RST\r\n",2000);
  Serial.println("reset");
  sendData("AT+CWMODE=1\r\n",1000); 
  //sendData("AT+CWJAP=\"\",\"\"\r\n",4000);
  //Serial.println(sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n",5000));
  sendData("AT+CWJAP=\"AndroidAP\",\"nzzn8521\"\r\n",5000);
  delay(7000);
  Serial.println("Joined Hotspot");
  sendData("AT+CIPMUX=1\r\n",1000);
  sendData("AT+CIPSERVER=1,6000\r\n",2000);
  
  Serial.println("Connection Established");
}

void toggleLed(){
 digitalWrite(4,HIGH);
 delay(500);
 digitalWrite(4,LOW);
  
}

void resetConn(){
  digitalWrite(2,HIGH);
    sendData("AT+CIPCLOSE=0\r\n",4000);
    sendData("AT+CIPCLOSE=1\r\n",4000);
    sendData("AT+CIPCLOSE=2\r\n",4000);
    sendData("AT+CIPCLOSE=3\r\n",4000);
    sendData("AT+CIPCLOSE=4\r\n",4000);
    digitalWrite(2,LOW);
}

void playSeq(){
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
    
     digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
    
     digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
    
     digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
}
