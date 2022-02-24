#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
int incomingByte = 0; // for incoming serial data
String inputString;
long inputInt;

byte pin_rows[ROW_NUM] ={A6,A5,A4,A3}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {A2, A1, A0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
}


void loop() {

 char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {     // only act on numeric keys
      inputString += key;               // append new character to input string
      inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = ""; 
      showUp(inputInt);
    } else if (key == '#' || key == '*' ) {
        inputString = "";               // clear input
    }
  }
}
void showUp(int n){
  Serial.print("got =>");
  Serial.println(n);
}
