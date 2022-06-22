#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 =3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
lcd.begin(16, 2);
setTime(12,0,0,12,3,22);  
lcd.setCursor(0, 0);     
int i=0;
int j=0;

while(true){
lcd.setCursor(i,j);
lcd.print(year());
lcd.print("-");
lcd.print(month());
lcd.print("-");
lcd.print(day());
delay(1000);
lcd.clear();
i++;
if(i==15){
  if(j==1)
  {
    j=0;
    i=0;
  }
  else{ j++;
i=0;
  }
}

}

}

void loop() {
  // put your main code here, to run repeatedly:

}
