#include <StringSplitter.h>
#include <LiquidCrystal.h>
#include <string.h>
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 =3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
lcd.begin(16, 2);
Serial.begin(9600);  
 int myTime=250;
  Serial.setTimeout(myTime);
}

void loop(){
 
  while(Serial.available() > 0 ){
    String str = Serial.readStringUntil('\n');
    printer(str,0);
    for(int i=0;i<str.length();i++)
    {
      int n=str[i];
      if(n<48 && n>41)
      {
       splitAndSolve(str,str[i]);
      }
    }
  }
}
void splitAndSolve(String str,char t){
    int a[2];
        int ans=0;
        StringSplitter *splitter = new StringSplitter(str, t, 2);
        int itemCount = splitter->getItemCount();
        for(int j = 0; j < itemCount; j++){
         String item = splitter->getItemAtIndex(j);
         a[j]=item.toInt();
        }
        int n=t;
        
        switch(n){
          case 43:
               ans=a[1]+a[0];
               break;
          case 45:
               ans=a[0]-a[1];
               break;
          case 42:
               ans=a[0]*a[1];
               break;
          case 47:
               ans=a[0]/a[1];  
               break;         
        }
        char answer[1];
        itoa(ans,answer,10);
        printer(answer,1);
}
void printer(String data,int mode)
{
  if(mode==0){
  lcd.clear();
  lcd.print(data);
 // Serial.println(data);
  }
   if(mode==1){
  lcd.setCursor(0,1);
  lcd.print(data);
  Serial.println(data);
  }
}
