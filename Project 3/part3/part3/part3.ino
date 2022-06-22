#include <StringSplitter.h>
#include <LiquidCrystal.h>
#include <string.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 =2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char str [17];
int i = 0 ;

void setup() {
lcd.begin(16, 2);
Serial.begin(9600);  
}

void loop(){
  if(Serial.available() > 0 ){

    // print entered char in both lcd and VT
    long key_ascii = Serial.read();
    char key = key_ascii;
 
    lcd.print(key);
    
    // 13 -> ascii code for enter
    if(key_ascii == 13){
      for(int i=0;i<strlen(str);i++)
      {
        int n=str[i];
        if(n<48 && n>41) 
         splitAndSolve(str,str[i]);
      }

    // still no enter so add new char to str
    }else{
      str[i++] = key;
    }
  }
}

void splitAndSolve(String input,char t){
    int a[2];
    int ans=0;
    StringSplitter *splitter = new StringSplitter(input, t, 2);
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
//    char answer[1];
//    itoa(ans,answer,10);
    lcd.setCursor(0,1);
    lcd.print(ans);
    Serial.println(ans);
    delay(1000);

    // reset everything
    lcd.clear();
    i = 0;
    memset(str, 0, 17);
}
