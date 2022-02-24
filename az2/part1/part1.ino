#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
const byte led[] ={9,8,7,6,5,4,3,2,10};
String inputString;
long inputInt;

byte pin_rows[ROW_NUM] ={A6,A5,A4,A3}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {A2, A1, A0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
pinMode(led[0], OUTPUT);
pinMode(led[1], OUTPUT);
pinMode(led[2], OUTPUT);
pinMode(led[3], OUTPUT);
pinMode(led[4], OUTPUT);
pinMode(led[5], OUTPUT);
pinMode(led[6], OUTPUT);
pinMode(led[7], OUTPUT);
pinMode(led[8], OUTPUT);
for(int i=0;i<9;i++){
  digitalWrite(led[i],LOW);
}
}


void loop() {
 char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {     // only act on numeric keys
      inputString += key;               // append new character to input string
      inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = ""; 
      lightUp(inputInt);
    } else if (key == '#' || key == '*' ) {
        inputString = "";               // clear input
    }
  }
}

void lightUp(int n){
  for(int i=0;i<n;i++){
    digitalWrite(led[i], HIGH);
    delay(100);
  }
  for(int i=0;i<9;i++){
  digitalWrite(led[i],LOW);
}
}
void check(int i)
{
  digitalWrite(led[i],HIGH);
  delay(150);
  digitalWrite(led[i],LOW);
}
