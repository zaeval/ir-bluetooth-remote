#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

#define TV_POWER 0x20DF10EF
#define BTV_POWER 0x1FE807F
#define CHANNEL_UP 0x1FE02FD
#define CHANNEL_DOWN 0x1FE827D
#define AUDIO_UP 0x1FEC23D
#define AUDIO_DOWN 0x1FE42BD

#define DEFAULT_BIT 32
 
int blueTx=10;   //Tx (보내는핀 설정)at
int blueRx=11;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
IRsend irsend;
bool event = false;
String str = "";

void setup(){
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼
}

void sendTvPower(){
  irsend.sendNEC(TV_POWER,DEFAULT_BIT);
}
void sendBTvPower(){
  irsend.sendNEC(BTV_POWER,DEFAULT_BIT);
}
void sendChannelUp(){
  irsend.sendNEC(CHANNEL_UP,DEFAULT_BIT);
}
void sendChannelDown(){
  irsend.sendNEC(CHANNEL_DOWN,DEFAULT_BIT);
}
void sendAudioUp(){
  irsend.sendNEC(AUDIO_UP,DEFAULT_BIT);
}
void sendAudioDown(){
  irsend.sendNEC(AUDIO_DOWN,DEFAULT_BIT);
}
void loop(){
   while (mySerial.available()) {
      delay(10);  //small delay to allow input buffer to fill

    char c = mySerial.read();  //gets one byte from serial buffer
    if (c == ',') {
      event=true;
      break;
    }  //breaks out of capture loop to print readstring
    str += c; 
    
  } //makes the string readString  

  if(event){
    event=false;
    
    if(str.equals("tv")){
      sendTvPower();
    }
    else if(str.equals("btv")){
      sendBTvPower();
    }
    else if(str.equals("channelup")){
      sendChannelUp();
    }
    else if(str.equals("channeldown")){
      sendChannelDown();
    }
    else if(str.equals("audioup")){
      sendAudioUp();
    }
    else if(str.equals("audiodown")){
      sendAudioDown();
    }
    delay(1000);
    Serial.println(str);
    str = "";
  }
  if (Serial.available()) {         
    mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
}
