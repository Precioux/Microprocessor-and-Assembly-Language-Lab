#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#define DEVICE_ADDRESS 0b1010000

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte numRows= 4; //number of rows on the keypad  
const byte numCols= 4; //number of columns on the keypad 
char keymap[numRows][numCols]=  
  {  
  {'O', '0', '=', '+'},  
  {'1', '2', '3', '-'},  
  {'4', '5', '6', '*'},  
  {'7', '8', '9', '/'}  
  };  
    
  //Code that shows the the keypad connections to the arduino terminals  
  byte rowPins[numRows] = {37,35,33,31}; //Rows 0 to 3  
  byte colPins[numCols]= {23,25,27,29}; //Columns 0 to 3  
  char key;  
  long int Number = 0 ; //for entered number
  int begin = 0;
  int current_state = 0;  //for showing states
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
void setup() {
  Wire.begin(); //This function initializes the Wire library and join the I2C bus as a controller or a peripheral
  Serial.begin(9600);
  Wire.beginTransmission(DEVICE_ADDRESS); //This function begins a transmission to the I2C peripheral device with the given address. Subsequently, queue bytes for transmission with the write() function and transmit them by calling endTransmission().
  Wire.write(0x00); //address to write and read
  Wire.write(0xAA); //address to write and read
  Wire.write(current_state);
  Wire.endTransmission();
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
}
int times[] ={0,0,0,0}; // array of given times for each procedure 
int n_time_setted = 0; //number of given times
int stopped = 1; // checking flag for stopping
void loop() {
   key = myKeypad.getKey();
  if (key!=NO_KEY){
    DetectButtons();
  lcd.clear();
  lcd.print(Number);
  }
  if (stopped == 0){
 
  for(int i=0;i < current_state;i++){
    digitalWrite(50+i,HIGH);
  }
  if (n_time_setted > 4 & current_state <= 3){
      int counter = current_state;
      while (counter < 4 && stopped == 0)
      {
         counter = current_state;
        Serial.print("Current State : ");
        switch(current_state){
          case 0 :
            Serial.println("Pre washing");
            break;
          case 1 :
            Serial.println("Washing with detergent");
            break;
          case 2 :
            Serial.println("Washing with water");
            break;                      
          case 3 :
            Serial.println("Drying");
            break;          
        }
       Serial.println("Waiting for process to end..");
        digitalWrite(50+counter,HIGH); //turning on dedicated led
      
        for(int j =0;j<times[counter];j++){ //printing count down time on LCD
            lcd.print(times[counter]-j);
            delay(1000);
            lcd.clear();
        }
          Wire.beginTransmission(DEVICE_ADDRESS); //enter data to EEPROM
          Wire.write(0x00);
          Wire.write(0xAA);
          Wire.write(counter);
          Wire.endTransmission();
          key = myKeypad.getKey();
          if (key==NO_KEY) 
              current_state++;  // go to next state
          else {
            if( key == '/'){
          stopped = 1;
          lcd.clear();
          lcd.print("STOPPED");
          delay(1000);
          lcd.clear();
            }
            else current_state++;
          }
      }
      
  }

  }
}
void DetectButtons()
{ 
    if (key=='O' && begin == 0)
    {
      Serial.println ("Starting washing machine.."); 
      Serial.println ("Enter duration of each washing part: ");
      digitalWrite(49,HIGH);
      Number = 0;
      begin =1;
      stopped = 0;
    }
    
     if (key == '1') //If Button 1 is pressed
    {Serial.println ("Button 1"); 
    if (Number==0)
    Number=1;
    else
    Number = (Number*10) + 1; //Pressed twice
    }
    
     if (key == '4') //If Button 4 is pressed
    {Serial.println ("Button 4"); 
    if (Number==0)
    Number=4;
    else
    Number = (Number*10) + 4; //Pressed twice
    }
    
     if (key == '7') //If Button 7 is pressed
    {Serial.println ("Button 7");
    if (Number==0)
    Number=7;
    else
    Number = (Number*10) + 7; //Pressed twice
    } 
  

    if (key == '0')
    {Serial.println ("Button 0"); //Button 0 is Pressed
    if (Number==0)
    Number=0;
    else
    Number = (Number*10) + 0; //Pressed twice
    }
    
     if (key == '2') //Button 2 is Pressed
    {Serial.println ("Button 2"); 
     if (Number==0)
    Number=2;
    else
    Number = (Number*10) + 2; //Pressed twice
    }
    
     if (key == '5')
    {Serial.println ("Button 5"); 
     if (Number==0)
    Number=5;
    else
    Number = (Number*10) + 5; //Pressed twice
    }
    
     if (key == '8')
    {Serial.println ("Button 8"); 
     if (Number==0)
    Number=8;
    else
    Number = (Number*10) + 8; //Pressed twice
    }   
    
     if (key == '3')
    {Serial.println ("Button 3"); 
     if (Number==0)
    Number=3;
    else
    Number = (Number*10) + 3; //Pressed twice
    }
    
     if (key == '6')
    {Serial.println ("Button 6"); 
    if (Number==0)
    Number=6;
    else
    Number = (Number*10) + 6; //Pressed twice
    }
    
     if (key == '9')
    {Serial.println ("Button 9");
    if (Number==0)
    Number=9;
    else
    Number = (Number*10) + 9; //Pressed twice
    }  
    if (key == '='){
      if(n_time_setted < 3){
        Serial.print("Duration of part " );
        Serial.print(n_time_setted);
        Serial.print(" added successfully");
        Serial.println("");
        Serial.print("Number is: ");
        Serial.println(Number);
        times[n_time_setted++] = Number;
        Number = 0;
      }
        else if (n_time_setted ==3){
          Serial.println("Duration of part 3 added successfully");
          Number = 0;
          Serial.println ("Times Setted");
          Serial.println ("Enter Operation : ");
          Serial.println ("1 for pre washing");
          Serial.println ("2 for washing with detergent");
          Serial.println ("3 for washing with water");
          Serial.println ("4 for drying");
          lcd.print("Enter #OP : ");
          n_time_setted++;
        }
        else if(n_time_setted ==4) {
          current_state = Number - 1; //setting current state
          Wire.beginTransmission(DEVICE_ADDRESS);
          Wire.write(0x00);
          Wire.write(0xAA);
          Wire.write(current_state);
          Wire.endTransmission();
          Serial.print ("Current state Setted : ");
          Serial.println (current_state+1);
          n_time_setted++;
          Number = 0;
        }
        else{
          Serial.println(current_state+1);
        }
    }
       if (key == '*')
    {
      stopped = 0;
      lcd.clear();
      lcd.print("Started again");
      delay(1000);
      lcd.clear();
      Serial.println ("Restoring Last State");
      Wire.beginTransmission(DEVICE_ADDRESS);
      Wire.write(0x00);
      Wire.write(0xAA);
      Wire.endTransmission();
      Wire.requestFrom(DEVICE_ADDRESS,1); //This function is used by the controller device to request bytes from a peripheral device. The bytes may then be retrieved with the available() and read() functions. 
      current_state = Wire.read()+1;
      Serial.print("Last State was ");
      Serial.println(current_state);
    } 
           if (key == '-')
    {
          current_state = 0;
          stopped =1;
            for(int i=0;i < 4;i++){
                digitalWrite(50+i,LOW);
                }
          Wire.beginTransmission(DEVICE_ADDRESS);
          Wire.write(0x00);
          Wire.write(0xAA);
          Wire.write(current_state);
          Wire.endTransmission();
          lcd.print("Reseted");
          n_time_setted =3;
          Serial.print("Current State IS : ");
          Serial.println(current_state+1);
          delay(1000);
          begin = 0;
          lcd.clear();
    } 
             if (key == '/')
    {
          stopped = 1;
          lcd.clear();
          lcd.print("STOPPED");
          delay(1000);
          lcd.clear();
    }
//        if (key == 'O')
//    {
//          stopped = 0;
//          lcd.clear();
//          lcd.print("Started");
//          delay(1000);
//          lcd.clear();
//    }
}
