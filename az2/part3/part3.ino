
const byte led[] ={9,8,7,6,5,4,3,2,10};
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
lightOff();
}


void loop() {
Serial.println("Enter number:");
while(Serial.available()==0){}
int n=Serial.parseInt();
if(n<=9){
lightUp(n);
}
else{
  Serial.println("Invalid Input");
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
void lightOff(){
  for(int i=0;i<9;i++){
  digitalWrite(led[i],LOW);
}
}
