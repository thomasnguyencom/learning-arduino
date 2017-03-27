//www.elegoo.com
//2016.06.13

#include <IRremote.h>
 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //初始化红外遥控
  pinMode(13,1);
}
 
void loop() {
  if (irrecv.decode(&results)) {
if(results.value==16753245)      //确认接收到的第一排按键1的编码，此码是预先读出来的按键编码。
  {
  digitalWrite(13,1);                //点亮LED
   Serial.println("turn on LED"); //串口显示开灯
  }
  else if(results.value==16736925)   //确认接收到的第一排按键2的编码
  {
   digitalWrite(13,0);            //熄灭LED
    Serial.println("turn off LED");    //串口显示关灯
  }
    irrecv.resume(); // 接收下一个值
  }
}
