#include <Keypad.h>
#include "pitches.h"
#include "EyIran.h"
#include "jingle_bells.h"
#include "Ode_to_Joy.h"
#include "the_imperial_march.h"
#include "frere_jacques.h"
#include "PiratesOfCaribbean.h"


#define TEMPO1 210
#define TEMPO2 210
#define TEMPO3 150
#define TEMPO4 150
#define TEMPO5 135
#define TEMPO6 150


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {29, 30, 31, 32}; 
byte colPins[COLS] = {22, 23, 24};


const int potPin = A0, buttonPin = 0, soundPin = 8;
bool play = false;
float scale = 0;
int song = 0;


//initializing Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//initializing button
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  play = 1 - digitalRead(buttonPin);
  char recieve = keypad.getKey();
  if (recieve)
  {
    switch(recieve){
      case '1':
        song = 1;
        break;
       case '2':
        song = 2;
        break;
       case '3':
        song = 3;
        break;
       case '4':
        song = 4;
        break;
       case '5':
        song = 5;
        break;
       case '6':
        song = 6;
        break;   
    }
  }
  //Ey Iran 
  if(play && song == 1)
  {
    for (int note = 0; note < sizeof(song1) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO1 * noteDurations1[note]);
      tone(soundPin, (int) (song1[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    } 
  }else if(play && song == 2){ //jingle bells
    for (int note = 0; note < sizeof(song2) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO2 * noteDurations2[note]);
      tone(soundPin, (int) (song2[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }else if(play && song == 3){//Ode to joy
    for (int note = 0; note < sizeof(song3) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO3 * noteDurations3[note]);
      tone(soundPin, (int) (song3[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }else if(play && song == 4){ //imperial march
    for (int note = 0; note < sizeof(song4) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO4 * noteDurations4[note]);
      tone(soundPin, (int) (song4[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }else if(play && song == 5){ //frere jacques
    for (int note = 0; note < sizeof(song5) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO5 * noteDurations5[note]);
      tone(soundPin, (int) (song5[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }else if(play && song == 6){//Pirates Of caribbean
    for (int note = 0; note < sizeof(song6) / sizeof(int); note++) {
      scale = analogRead(potPin) / 512.0;
      int duration = 2 * 60 * 1000.0 / (TEMPO6 * noteDurations6[note]);
      tone(soundPin, (int) (song6[note] * scale), duration);
      delay( (int) duration );
      if (digitalRead(buttonPin)) {
        break;
      }
    }
  }
}
