#include <LiquidCrystal.h>
#include<string.h>

// setup LCD
const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 =11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// is usernamed entered completly?
boolean is_username_entered = false;

// storing username that user is entring
char entered_username[17];

// storing password that user is entring
char entered_password[17];

int entered_username_len = 0;
int entered_password_len = 0;

// correct username and password
char USERNAME[4] = "123";
char PASSWORD[4] = "456";

void setup() {
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter username :");
  lcd.setCursor(0, 1);
  Serial.begin(9600);
  
}

void loop() {
  
  if(Serial.available() > 0)  {
    // get entered key
    char key = Serial.read();
    Serial.print(key);
    // user finishe entering username => setup for entering password
    if (key == '*' && !is_username_entered){
      is_username_entered = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter password :");
      lcd.setCursor(0, 1);
    }

    // user finishe entering password => check corectness
    else if (key == '*' && is_username_entered){
      lcd.clear();
      lcd.setCursor(0, 0);
      
      if(strcmp(entered_username, USERNAME)){
        lcd.print("username invalid");
      }
      else if(strcmp(entered_password, PASSWORD)){
        lcd.print(" wrong password ");
      }else{
        lcd.print("enter successful");
      }

    // use is entering username  
    }else if(!is_username_entered){
      lcd.print(key);
      entered_username[entered_username_len ++] = key;
     
    // use is entering password  
    }else if(is_username_entered){
      lcd.print(key);
      entered_password[entered_password_len ++] = key;
    }
  }

}
