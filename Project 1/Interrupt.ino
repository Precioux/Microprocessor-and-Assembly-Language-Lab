#include<string.h>
const byte led1 = 1;
const byte led2= 0;
const byte led3 = 14;
const byte led4= 15;
const byte led5 = 16;
const byte led6= 17;
const byte interruptKey1 = 2;
const byte interruptKey2 = 3;
const byte interruptKey3 = 18;
volatile boolean flag_key1 = false;
volatile boolean flag_key2 = false;

void setup() {
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);
 pinMode(interruptKey1, INPUT_PULLUP);
 pinMode(interruptKey2, INPUT_PULLUP);
 pinMode(interruptKey3, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(interruptKey1), blinkOneISR, CHANGE);
 attachInterrupt(digitalPinToInterrupt(interruptKey2), blinkTwoISR, CHANGE);
 attachInterrupt(digitalPinToInterrupt(interruptKey3), blinkThree, CHANGE);
}

void loop() {
if(flag_key1)
{
  blinkOne();
  flag_key1=false;
  }
  if(flag_key2)
{
  blinkTwo();
  flag_key2=false;
  }
}
void blinkOneISR(){
  flag_key1=true;
}
void blinkTwoISR(){
  flag_key2=true;
}
void blinkOne()
{
digitalWrite(led1,HIGH);
 delay(100);
digitalWrite(led2,HIGH);
 delay(100);
digitalWrite(led3,HIGH);
 delay(100);
digitalWrite(led4,HIGH);
 delay(100);
digitalWrite(led5,HIGH);
 delay(100);
digitalWrite(led6,HIGH);
}
void blinkTwo()
{
char name[] = "samin";
int n=strlen(name);
for(int i=0;i<n;i++)
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
 delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
delay(100);
}

 digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
}
void blinkThree()
{

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

}
