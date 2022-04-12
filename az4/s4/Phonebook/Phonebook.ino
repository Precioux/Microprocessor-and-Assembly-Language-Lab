#include <LiquidCrystal.h>
#include <Keypad.h>
#include<string.h>

// setup LCD
const int rs = 35, en = 36, d4 = 40, d5 = 41, d6 = 42, d7 =43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// setup keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'^','0','=', '+'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad

//Phonebook
char phonebook_names [10][29];
char phonebook_phones [10][29];
int count = 0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  
}

void loop() {
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    switch (key){
      case '+':
        add_new_contact();
        break;
      case '/':
        lcd.print("1. sort by name");
        lcd.setCursor(0, 1);
        lcd.print("2. sort by phone");
        char keypad_key = keypad.waitForKey();
        show_contacts(keypad_key);
        break;
    }
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    
  }

}

void add_new_contact(){
  char keypad_key = keypad.getKey();
  char contact_name[29] = {};
  char telephone[12] = {};
  int tel_cnt = 0;
  int name_cnt = 0;
  while (keypad_key != '='){
    if(Serial.available() > 0)  {
      // get entered key
      char serial_key = Serial.read();
      Serial.print(serial_key);
      if(serial_key != '\n'){
        contact_name[name_cnt ++] = serial_key;
        lcd.print(serial_key);
      }else
        lcd.setCursor(0, 1);
    }
    
    keypad_key = keypad.getKey();
    if(keypad_key && keypad_key != '='){
      telephone[tel_cnt ++] = keypad_key;
      lcd.print(keypad_key);
    }
  }

  int tel_size = sizeof telephone / sizeof telephone[0];
  if(tel_size >= 8 && tel_size <= 11){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Contatc added!");
    lcd.setCursor(0, 1);
    lcd.println(contact_name);
    lcd.setCursor(0, 2);
    lcd.println(telephone);

    int i = 0;
    while(contact_name[i] != '\0'){
      phonebook_names[count][i] = contact_name[i];
      i ++;
    }
    phonebook_names[count][i] = '\0';
    
    i = 0;
    while(telephone[i] != '\0'){
      phonebook_phones[count][i] = telephone[i];
      i ++;
    }
    phonebook_phones[count][i] = '\0';
    
    count ++;
    
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Contact NOT added!");
    lcd.setCursor(0, 1);
    lcd.println("phone # is <8 or >11");
  }
}

void show_contacts(int sort_by){
  lcd.clear();
  lcd.setCursor(0, 0);
  if(sort_by == '1'){
    Serial.println(count);
    for(int i=0; i<count; i++){
      lcd.setCursor(0, i);
      lcd.print(phonebook_names[i]);
      lcd.print(" - ");
      lcd.print(phonebook_phones[i]);
    }
  }else if(sort_by == '2'){
    
  }
}
