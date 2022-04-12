#include <LiquidCrystal.h>
#include <Keypad.h>
#include<string.h>

// setup LCD
const int rs = 35, en = 36, d4 = 40, d5 = 41, d6 = 42, d7 =43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// setup keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'#','0','=', '+'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Phonebook record
typedef struct 
{
    char* contact_name;
    char* telephone;
} contact;

//phonebook
contact contacts[100];
contact original[100];

//number of contacts in phonebook
int count = 0;

void setup() {
  
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  
  
}

void loop() {
  print_menu();
  char key = keypad.getKey();
  if (key){
    Serial.println("");
    Serial.println(key);
    lcd.clear();
    
    switch (key){
      // add
      case '+':
      {
        add_new_contact();
        break;
      }
      //show  
      case '/':
      {
        lcd.print("1. Sort by name");
        lcd.setCursor(0, 1);
        lcd.print("2. Sort by phone");
        char keypad_key = keypad.waitForKey();
        show_contacts(keypad_key);
        break;
      }
      
      //search  
      case '*':
      {
        lcd.print("1.Search by name");
        lcd.setCursor(0, 1);
        lcd.print("2.Search by phone");
        char ikey = keypad.waitForKey();
        lcd.clear();
        int num = 0;
        num = ikey - '0';
        Serial.println(num);
        search(num);
        break;
      }
      case '-':
      {
        deleteContact();
        break;
      }
      case '#':
      {
        lcd.print("1. Filter by name");
        lcd.setCursor(0, 1);
        lcd.print("2. Filter by phone");
        char keypad_key = keypad.waitForKey();
        filter_contacts(keypad_key);
      }
    }
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    
  }

}

void deleteContact(void){
    //allocating memory
    char* entered_name = malloc(sizeof(char) * 30);
    
    //initializing
    int indx=0;
    int iflag=0;
    
    //getting name
    lcd.print("Enter name: ");
    
    while(iflag==0){
     if(Serial.available() > 0 ){
      long key_ascii = Serial.read();
      char key = key_ascii;
      lcd.print(key);
      Serial.print(key);

     // 13 -> ascii code for enter
     if(key_ascii == 13){

          int n2 = strlen(entered_name);
          int flag = -1;
          int check = 0;
          while(flag != 0 && check < count){  //if name is found flag=0
            flag=strcmp(contacts[check].contact_name, entered_name);
            check ++;
          }
          
          if(flag!=0){
            lcd.setCursor(0 ,2);
            lcd.print("Not found");
          }else{
           memset(contacts, 0, sizeof(contact));
           int t = 0;
           int i = 0;
           while(t<100){
             if(t != check - 1){
              contacts[i].contact_name = original[t].contact_name;
              contacts[i].telephone = original[t].telephone;
              t ++;
              i ++;
             }else{
              t ++;
             }
           }

           lcd.setCursor(0, 2);
           lcd.print("Deleted!");
          }
          count --;
       
          iflag=1;
          
    // still no enter so add new char to str
     }else{
          entered_name[indx++] = key;
     }
   }
 }
}

void search(int mode){
 switch(mode)
 {
  case 1:
  {
    //allocating memory
    char* entered_name = malloc(sizeof(char) * 30);
    
    //initializing
    int indx = 0;
    int iflag = 0;
    
    //getting name
    lcd.print("Enter name: ");
    while(iflag == 0){
      if(Serial.available() > 0 ){
        long key_ascii = Serial.read();
        char key = key_ascii;
        lcd.print(key);
        Serial.print(key);
    
         // 13 -> ascii code for enter
         if(key_ascii == 13){
    
              int n2 = strlen(entered_name);
              int flag = -1;
              int check = 0;
              while(flag != 0 && check < count){  //if name is found flag=0
                flag = strcmp(contacts[check].contact_name, entered_name);
                check ++;
              }
              
              if(flag != 0){
                lcd.setCursor(0, 2);
                lcd.print("Not found");
              }else{
                lcd.setCursor(0, 2);
                lcd.print("-> ");
                lcd.print(contacts[check - 1].telephone);
    
              }
              iflag=1;
              
             // still no enter so add new char to str
          }else
            entered_name[indx++] = key;
               
     }
   }
    break;
  }
  case 2:
  {
    //allocating memory
    char* phoneNumber = malloc(sizeof(char) * 12);
    int indx = 0;
    lcd.setCursor(0, 0);
    lcd.print("Enter phone number: ");
    int iflag=0;
    char input;
    do{
          input = keypad.getKey();
          if(input && input != '='){
           phoneNumber[indx]=input;
           lcd.print(input);
           Serial.print(input);
           indx++;
        }
        
    }while(input != '=');
        
        //Serial.println(phoneNumber);
        //Serial.println("");
        int flag=-1;
        int check=0;
        int p2=strlen(phoneNumber);
        
        while(flag!=0 && check<count){  //if phone number is found flag=0 
              flag=strcmp(contacts[check].telephone,phoneNumber);
              int p1=strlen(contacts[check].telephone);
              check ++;
            }
            if(flag!=0){
              lcd.setCursor(0, 2);
              lcd.print("Not found");
            }
            else{ 
              lcd.setCursor(0, 2);
              lcd.print("-> ");
              lcd.print(contacts[check - 1].contact_name);
            } 
    break;    
  }
 }
  
}

void add_new_contact(){
  lcd.print("Enter name & phone: ");
  lcd.setCursor(0, 1);
  
  //allocating memory
  char* contact_name = malloc(sizeof(char) * 30);
  char* telephone =  malloc(sizeof(char) * 12);
  int tel_cnt = 0;
  int name_cnt = 0;

  //input char
  char keypad_key;

  //get input from user
  do {
    keypad_key = keypad.getKey();
    
    if(Serial.available() > 0)  {
      char serial_key = Serial.read();
      Serial.print(serial_key);
      contact_name[name_cnt ++] = serial_key;
      lcd.print(serial_key);
  
    }   
    
    if(keypad_key && keypad_key != '='){
      telephone[tel_cnt ++] = keypad_key;
      lcd.print(keypad_key);
    }
    
  }while(keypad_key != '=');

  
  int tel_size = sizeof telephone / sizeof telephone[0];
//  if(tel_size >= 8 && tel_size <= 11){
  if(true){

    //save contact and show it
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Contact added!");
    lcd.setCursor(0, 1);
    lcd.println(contact_name);
    lcd.setCursor(0, 2);
    lcd.println(telephone);
    
    contact_name[name_cnt ++] = '\0';
    telephone[tel_cnt ++] = '\0';
    contacts[count].contact_name = contact_name;
    contacts[count].telephone = telephone;
    original[count].contact_name= contact_name;
    original[count].telephone = telephone;
    
    count ++;
    
  }else{
    // show error
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Contact NOT added!");
    lcd.setCursor(0, 1);
    lcd.println("phone # is <8 or >11");
  }
}

void show_contacts(int sort_by){
  lcd.clear();

  if(sort_by == '1'){
    qsort (contacts, count, sizeof(contact), compare_name);
  }
  else if(sort_by == '2'){
    qsort (contacts, count, sizeof(contact), compare_phone);
  }
  
  for(int i=0; i<count; i++){
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(contacts[i].contact_name);
      Serial.print(" - ");
      Serial.println(contacts[i].telephone);
  }
}

//compare by phone number
int compare_phone (const void * a, const void * b)
{
  contact *data_1 = (contact *)a;
  contact *data_2 = (contact *)b;
  int phone_1 = atoi(data_1->telephone);
  int phone_2 = atoi(data_2->telephone);
  
  return phone_1 - phone_2;
  
}

//compare by name
int compare_name (const void * a, const void * b)
{
  contact *data_1 = (contact *)a;
  contact *data_2 = (contact *)b;
  
  return strcmp( data_1->contact_name , data_2->contact_name );
}

void print_menu(){
  lcd.setCursor(0, 0);
  lcd.print("+ : add new contact!");
  lcd.setCursor(0, 1);
  lcd.print("/ : show contacts!");
  lcd.setCursor(0, 2);
  lcd.print("x : search contact!");
  lcd.setCursor(0, 3);
  lcd.print("- : delete contact!");
}

void filter_contacts(char mode){
 lcd.clear();
 switch(mode)
 {
  case '1':
  {
    //allocating memory
    char* entered_name = malloc(sizeof(char) * 30);
    
    //initializing
    int indx = 0;
    int iflag = 0;
    
    //getting name
    lcd.print("Enter name: ");
    while(iflag == 0){
      if(Serial.available() > 0 ){
        long key_ascii = Serial.read();
        char key = key_ascii;
        lcd.print(key);
        Serial.print(key);
    
         // 13 -> ascii code for enter
         if(key_ascii == 13){
    
              int n2 = strlen(entered_name);
              int flag = -1;
              int check = 0;
              while(check < count){  //if name is found flag=0
                if(strstr(contacts[check].contact_name, entered_name)){
                  Serial.print(contacts[check].contact_name);
                  Serial.print(" - ");
                  Serial.println(contacts[check].telephone);
                  flag = 0;
                }
                  check ++;
              }
              
              if(flag != 0){
                lcd.setCursor(0, 2);
                lcd.print("Not found");
              }
              iflag=1;
             // still no enter so add new char to str
          }else
            entered_name[indx++] = key;
               
     }
   }
    break;
  }
  case '2':
  {
    //allocating memory
    char* phoneNumber = malloc(sizeof(char) * 12);
    int indx = 0;
    lcd.setCursor(0, 0);
    lcd.print("Enter phone number: ");
    int iflag=0;
    char input;
    do{
          input = keypad.getKey();
          if(input && input != '='){
           phoneNumber[indx]=input;
           lcd.print(input);
           Serial.print(input);
           indx++;
        }
        
    }while(input != '=');
        
        Serial.println(phoneNumber);
        Serial.println("");
        int flag=-1;
        int check=0;
        int p2=strlen(phoneNumber);
        
        while(check<count){  //if phone number is found flag=0 
              if(strstr(contacts[check].telephone,phoneNumber)){
                Serial.print(contacts[check].contact_name);
                Serial.print(" - ");
                Serial.println(contacts[check].telephone);
                flag = 0;
              }
              check ++;
            }
            if(flag!=0){
              lcd.setCursor(0, 2);
              lcd.print("Not found");
            }
    break;    
  }
 }
  
}
