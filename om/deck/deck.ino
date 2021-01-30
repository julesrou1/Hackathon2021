#include "LiquidCrystal.h"
#include "TimerThree.h"

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(8,9,4,5,6,7);
int i;
int buzzerPin=3;
char * messagePadded = "       CECI EST UN TEST              ";    // msg qui scroll

const int buttonPin = 20;  // interruption bouton buzzer


byte man[] = {         //  mec qui cours ( a revoir à la fin ) 
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};



void setup() {
lcd.begin(16,2);
pinMode(buttonPin, INPUT_PULLUP);
//attachInterrupt(digitalPinToInterrupt(buttonPin), stop_buzzer, CHANGE);                  // Le interrupt du bouton buzzer

Timer3.initialize(5000000);
Timer3.attachInterrupt(msgBouge); // Affiche message eau toutes les 5 secondes


} 


void msgBouge(void){
  int j;
  i=(i+1)%2;            // modulo 2 donc 2 etats possibles  ( pour test uniquement ) 
  if(i==0){
   // buttonState = digitalRead(buttonPin);
     lcd.clear();    // version basique
     lcd.setCursor(0,0);
     lcd.print("C'EST L'HEURE DE ");
     lcd.setCursor(0,1);
     lcd.print("  BOUGER UN PEU ! ");
     
     //lcd.createChar(3,man);       // decommenter pour afficher un mec qui cours ( bug pour l'instant ) 

     
//     if(digitalRead(buttonPin) == HIGH){                                      // PARTIE BOUTON BUZZER ( a modifier ) 
//      Serial.print("HAUT");
//      //tone(buzzerPin, 1000);     // buzzer qui sonne 
//     }
//     else{
//      Serial.print("BAS");
//      lcd.clear();    // version basique
//      lcd.setCursor(0,0);
//      lcd.print(" BIEN ETTIRE ? ");
//     }
     
  }
    else{
      lcd.clear();
  lcd.setCursor(0,0);
//text to print
  lcd.print("   Bienvenue");
  
  for (int letter = 0; letter <= strlen(messagePadded) - 16; letter++) //From 0 to upto n-16 characters supply to below function
  {
    showLetters(0, letter);
  }
  
  }
 

}
  
void showLetters(int printStart, int startLetter)                 // FONCTION POUR SCROLL TEXTE 
{
  lcd.setCursor(printStart, 1);
  for (int letter = startLetter; letter <= startLetter + 15; letter++) // Print 16 chars sur ligne #2 commence à 'startLetter'
  {
    lcd.print(messagePadded[letter]);
  }
  lcd.print(" ");
  delay(50000);
}

void stop_buzzer(){             // FONCTION ARRET BUZZER ( a revoir ) 
  lcd.clear();    // version basique
  lcd.setCursor(0,0);
  lcd.print(" BIEN ETTIRE ? ");
  
}



void loop()
{
  
  
 }
