
const int unBouton = 3; // un bouton sur la broche 3
const int buttonPin = 2; // broche du capteur PIR
const int ledPin = 13; // la LED du Arduino
int buttonState = 0; // etat de la sortie du capteur
 
void setup()
{
 pinMode(unBouton, INPUT)
  pinMode(ledPin, OUTPUT); //la broche de la LED est mise en sortie
  pinMode(buttonPin, INPUT); //la broche du capteur est mise en entree
}
 
void loop()
{
  if (unBouton== low) //boutton n'est pas appuiee
{  
  buttonState = digitalRead(buttonPin);//lecture du capteur
  if (buttonState == HIGH) //si quelquechose est detecte
  {
    digitalWrite(ledPin, HIGH); //on allume la LED
  }
}
  else //sinon
  {
    digitalWrite(ledPin, LOW); //on eteint la LED
  }
}
