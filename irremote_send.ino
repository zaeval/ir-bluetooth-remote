#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#define DEFAULT_BIT 32
IRsend irsend;

void  setup ( )
{
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud
  
}
void sendTvPower();
void sendChannelUp();
void sendBTvPower();
void  loop ( )
{
  sendTvPower();
  delay(1000);
  sendTvPower();
  sendBTvPower();
  delay(5000);

}
void sendTvPower()
{
  irsend.sendNEC(0x20DF10EF,DEFAULT_BIT);
}
void sendBTvPower()
{
  irsend.sendNEC(0x1FE807F,DEFAULT_BIT); 
}
void sendChannelUp(){
  irsend.sendNEC(0x1FE02FD,DEFAULT_BIT);
}
