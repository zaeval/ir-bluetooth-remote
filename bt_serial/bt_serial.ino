#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출
 
int blueTx=10;   //Tx (보내는핀 설정)at
int blueRx=11;   //Rx (받는핀 설정)
bool event = false;
String command = "";
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
 
void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼
}
void loop()
{
  if (mySerial.available()) {
    char c = mySerial.read();       
    event=true;
    command += c;
  }
  else if(!mySerial.available() && event){
    event=false;
    Serial.print(command);
    command = "";
    
  }
  if (Serial.available()) {         
    mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
}
