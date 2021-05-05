
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, A4, A5);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
int LCDCol = 0;
int LCDRow = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.setCursor(LCDCol, LCDRow);
   }
  const String password = "12345678";
String password_entered;

void loop(){
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bonjour");
  delay(1500);
  lcd.clear();
  lcd.print("Entrez num CIN :");
  password_entered = "";
  lcd.setCursor(0,1);
  while(password_entered.length() <8){
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print(key);
    }
  }
  if(password_entered == password){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Succes !");
    delay(1000);
    lcd.clear();
    lcd.print("CIN correct !");
    delay(5000);
    
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Erreur !");
    delay(1000);
    lcd.clear();
    lcd.print("CIN incorrect !");
    delay(5000);
  }
}