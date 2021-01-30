#include <Arduino.h>
#include "functions.h"


int mod1position,mod2position;
int prevmod1,prevmod2;
int fill;
int authorized=0;
struct Potentiometer P1;
struct Potentiometer P2;
int j,k;
const int RECV_PIN = 10;
const int btn1=21;
IRrecv irrecv(RECV_PIN);
decode_results results;    // code de la telecommande

#define SS_PIN 53
#define RST_PIN 12
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Creation instance RFID

//String Password = "<Your Password>";
String AuthorsizedCardUID = "79 5E 16 B4";
//char LoginKey = KEY_RETURN;
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(8,9,4,5,6,7);
int i=1;
int buzzerPin=3;
char * messagePadded = (char*)"       CECI EST UN TEST  hey hey            ";    // msg qui scroll
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
  if (authorized == 1){
    P1.Position = map(analogRead(P1.algPin), 0, 1023, 0, 100);
    P2.Position = map(analogRead(P2.algPin), 0, 1023, 0, 100);

    sendConditionCheck(&P1, &P2);

    sendPotToPc(&P1, &P2);

    //appeller les sendto ici
    P1.prevPosition = P1.Position;
    P2.prevPosition = P2.Position;
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
  //delay(50000);
}
void tim4(){
  if(j==0 && authorized == 1){
    if (k == (int)strlen(messagePadded) - 16){k=0;}
  else
  {
    k++;
    showLetters(0, k);
  }
  
}
}
void msgBouge(void){
  if (authorized == 1){
  if(j==1){
   // buttonState = digitalRead(buttonPin);
    lcd.clear();    // version basique
    lcd.setCursor(0,0);
    lcd.print("C'EST L'HEURE DE ");
    lcd.setCursor(0,1);
    lcd.print("  BOUGER UN PEU ! ");
  }else{
    i=(i+1)%361;
    //i=(i+1)%3;
    String mess;
    mess="Volume=";
    mess+=P1.Position;
    mess+="   Mic :"+P2.Position;
    lcd.setCursor(0, 0);
    lcd.print("   Bienvenue  ");
    // for (int letter = 0; letter <= strlen(messagePadded) - 16; letter++) //From 0 to upto n-16 characters supply to below function
    // {
    //   showLetters(0, letter);
    //   delay(50000);
    // }
    if(i==0){j=1;}
    } 
  }
  // modulo 2 donc 2 etats possibles  ( pour test uniquement ) 
  //lcd.createChar(3,man);       // decommenter pour afficher un mec qui cours ( bug pour l'instant ) 
//      Serial.print("HAUT");
//     }
//     else{
//      Serial.print("BAS");
//      lcd.clear();    // version basique
//      lcd.setCursor(0,0);
//      lcd.print(" BIEN ETTIRE ? ");
//     }
  
  }
  void btn1int(){
    P2.mute=(P2.mute+1)%2;
    P2.send=1;
    Serial.print(P2.mute);
    //sendPotToPc(&P1,&P2);

  }
void stop_buzzer(){             // FONCTION ARRET BUZZER ( a revoir ) 
  lcd.clear();    // version basique
  lcd.setCursor(0,0);
  lcd.print(" BIEN ETTIRE ? ");
  
}

void setup() {

  Serial.begin(9600); 

  Timer1.initialize(10000);
  Timer1.attachInterrupt(tim1);
  Timer4.initialize(500000);
  Timer4.attachInterrupt(tim4);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(btn1, INPUT);
  
  pinMode(41,OUTPUT); 
  pinMode(43,OUTPUT);

  lcd.begin(16,2);
  pinMode(buttonPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), stop_buzzer, CHANGE);                  // Le interrupt du bouton buzzer
  // attachInterrupt(digitalPinToInterrupt(btn1), btn1int, HIGH);
  Timer3.initialize(5000000);
  Timer3.attachInterrupt(msgBouge); // Affiche message eau toutes les 5 secondes

  SPI.begin();      // Initialisation  bus SPI 
  mfrc522.PCD_Init();   // Initialiation MFRC522 ( RFID ) 
  irrecv.enableIRIn();    // Initialisation IR telecommande
  irrecv.blink13(true);

}

void loop() {
  if(fill!=1){fill=PotenFillStruc(&P1,&P2);}
   // Look for new cards
  if (authorized == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bonjour");
    lcd.setCursor(0, 1);
    lcd.print("Presentez badge");
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    //Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    //byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == AuthorsizedCardUID) // on peut changer la cle d'acces ici
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acces autorise");
      //    Keyboard.println(Password);
      //    Keyboard.write(LoginKey);
      delay(1000);
      authorized=1;
    }

    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acces refuse");
      //    Keyboard.println();
      //    Keyboard.write(LoginKey);
      delay(1000);
    }
    // if(digitalRead(btn1)==1){
    //     P2.mute=(P2.mute+1)%3;
    //     P2.send=1;
    //     Serial.print(P2.mute);
    //     delay(1000);
    // };
  }
  if (irrecv.decode(&results)){          // Reception code telecommande
  //lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print(results.value);
  switch(results.value){
          case 0x92DFD41F: // MUTE 
          String remote = "03";
          remote += ";";
          remote += "00";
          remote += "!";
          Serial.println(remote);
          }

        switch(results.value){
          case 0x6BC6597B: //BOUTON 1 : CHROME
          String remote = "04";
          remote += ";";
          remote += "01";
          remote += "!";
          Serial.println(remote);
          }
         switch(results.value){
          case 0x735B797E: //BOUTON 2 : MOODLE
          String remote = "05";
          remote += ";";
          remote += "01";
          remote += "!";
          Serial.println(remote);
          }

//         switch(results.value){
//          case 0x1EC81DBF: //BOUTON 3 : CHROME
//          digitalWrite(greenPin, HIGH);
//          delay(2000);
//          digitalWrite(greenPin, LOW);
//          }
        irrecv.resume();
  }
  delay(100);
}
