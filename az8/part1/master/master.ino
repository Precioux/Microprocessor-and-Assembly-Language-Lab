#include <SPI.h>

const int slaveSelectPin1 = 49;


void setup() {
  
  pinMode(slaveSelectPin1, OUTPUT);
  digitalWrite(slaveSelectPin1, HIGH);

  SPI.begin();
}

void loop() {
  sendData("Samin9839039/Hosna98323010", 25);
  delay(200);
}

void sendData (char data[], int _size)
{
  digitalWrite(slaveSelectPin1, LOW);
  
  delay(100);
  for (int i = 0; i < _size; i++)
  {
    SPI.transfer(data[i]);
    delay(25);
  }
  SPI.transfer('z');
  delay(100);

  digitalWrite(slaveSelectPin1, HIGH);
}
