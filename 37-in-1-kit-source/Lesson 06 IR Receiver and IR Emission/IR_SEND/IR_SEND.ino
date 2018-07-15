//www.elegoo.com
//2016.06.13

#define ADD 0x00
int IR_S =  12;    
void setup() 
{ 
  pinMode(IR_S, OUTPUT);

}
void loop() 
{
  uint8_t dat,temp=("123456");

     
    IR_Send38KHZ(280,1);
    IR_Send38KHZ(140,0);
     
    IR_Sendcode(ADD);
    dat=~ADD;
    IR_Sendcode(dat);
     
    IR_Sendcode(temp);
    dat=~temp;
    IR_Sendcode(dat);
     
    IR_Send38KHZ(21,1);

  delay(200);
}
void IR_Send38KHZ(int x,int y) 
{ 
for(int i=0;i<x;i++)
{ 
           if(y==1)
           {
     digitalWrite(IR_S,1);
            delayMicroseconds(9);
     digitalWrite(IR_S,0);
            delayMicroseconds(9);
           }
           else
           {
     digitalWrite(IR_S,0);
            delayMicroseconds(20);
           }            
}
}
void IR_Sendcode(uint8_t x) 
{
    for(int i=0;i<8;i++)
     {
       if((x&0x01)==0x01)
        {
           IR_Send38KHZ(23,1);
           IR_Send38KHZ(64,0);             
        }
        else
         {
            IR_Send38KHZ(23,1);
            IR_Send38KHZ(21,0);  
         }
       x=x>>1;
     }  
}
