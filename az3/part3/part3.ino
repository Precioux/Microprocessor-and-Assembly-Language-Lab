#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 =3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
lcd.begin(16, 2);
setTime(12,0,0,2,3,22);  
lcd.setCursor(0, 0);     
lcd.print(year());
lcd.print("-");
lcd.print(month());
lcd.print("-");
lcd.print(day());

int i=9;
int j=0;
while(true){
lcd.setCursor(i,j);
lcd.print(".");
delay(1000);
if(i==15){
j++;
i=0;
}
i++;
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
