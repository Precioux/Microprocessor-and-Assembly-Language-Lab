#include<string.h>
const byte led1 = 1;
const byte led2= 0;
const byte led3 = 14;
const byte led4= 15;
const byte led5 = 16;
const byte led6= 17;
volatile byte state1 = LOW;
volatile byte state2 = LOW;
volatile byte state3 = LOW;
volatile byte state4 = LOW;
volatile byte state5 = LOW;
volatile byte state6 = LOW;
const byte key1 = 2;
const byte key2 = 3;
const byte key3 = 18;
void setup() {
  // put your setup code here, to run once:
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);
 pinMode(key1, INPUT_PULLUP);
 pinMode(key2, INPUT_PULLUP);
 pinMode(key3, INPUT_PULLUP);
 blinkThree();
}

void loop() {
  if(digitalRead(key1)==LOW){
  blinkOne();
  }
   if(digitalRead(key2)==LOW){
  blinkTwo();
   }
  if(digitalRead(key3)==LOW){
  blinkThree();
   }
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
delay(100);
}
void blinkTwo()
{
char name[] = "samin";
int n = strlen(name);
for(int i=0;i<n;i++)
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  delay(150);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  delay(150);
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
