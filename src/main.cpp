#include <Arduino.h>
#include "functions.h"


int mod1position,mod2position;
int prevmod1,prevmod2;
int fill;
struct Potentiometer P1;
struct Potentiometer P2;
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(8,9,4,5,6,7);
int i;
int buzzerPin=3;
char * messagePadded = (char*)"       CECI EST UN TEST              ";    // msg qui scroll
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

void tim1(){
  P1.Position = map(analogRead(P1.algPin), 0, 1023, 0,100);
  P2.Position = map(analogRead(P2.algPin), 0, 1023, 0,100);

  sendConditionCheck(&P1,&P2);
  //appeller les sendto ici
  P1.prevPosition = P1.Position;
  P2.prevPosition = P2.Position;
  }

void tim4(){}
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
void msgBouge(void){
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
     tone(buzzerPin, 1000);     // buzzer qui sonne 
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
  
void stop_buzzer(){             // FONCTION ARRET BUZZER ( a revoir ) 
  lcd.clear();    // version basique
  lcd.setCursor(0,0);
  lcd.print(" BIEN ETTIRE ? ");
  
}

void setup() {

  Serial.begin(9600); 

  Timer1.initialize(5000);
  Timer1.attachInterrupt(tim1);
  Timer4.initialize(500);
  Timer4.attachInterrupt(tim4);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(41,OUTPUT); 
  pinMode(43,OUTPUT);

  lcd.begin(16,2);
  pinMode(buttonPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), stop_buzzer, CHANGE);                  // Le interrupt du bouton buzzer

  Timer3.initialize(5000000);
  Timer3.attachInterrupt(msgBouge); // Affiche message eau toutes les 5 secondes


}

void loop() {
  if(fill!=1){fill=PotenFillStruc(&P1,&P2);}

  // Serial.print(P2.Position);
  // Serial.print("\t");
  // Serial.print(P2.send);
  // Serial.print("\t");
  // Serial.print("\t");
  
  P2.send=0;
}