/*   
    
 
   PINS :
  -----------------------------------------------------------------------------------------
              MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
              Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
  Signal      Pin          Pin           Pin       Pin        Pin              Pin
  -----------------------------------------------------------------------------------------
  RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
  SPI SS      SDA(SS)      10            53        D10        10               10
  SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
  SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
  SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#include <IRremote.h>
//#include <IRremoteInt.h>

const int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;    // code de la telecommande

#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Creation instance RFID

//String Password = "<Your Password>";
String AuthorsizedCardUID = "79 5E 16 B4";
//char LoginKey = KEY_RETURN;
// 
void setup() 
{
  Serial.begin(9600);   // Initialisation communication serie
  SPI.begin();      // Initialisation  bus SPI 
  mfrc522.PCD_Init();   // Initialiation MFRC522 ( RFID ) 
  irrecv.enableIRIn();    // Initialisation IR telecommande
  irrecv.blink13(true);
  
//  Serial.println("Approchez la carte pour déverouiller votre session...");
//  Serial.println();
//  Keyboard.begin();

}
void loop() 
{
//  // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  Serial.print("UID tag :");
//  String content= "";
//  byte letter;
//  for (byte i = 0; i < mfrc522.uid.size; i++) 
//  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//  Serial.println();
//  Serial.print("Message : ");
//  content.toUpperCase();
//  if (content.substring(1) == AuthorsizedCardUID) // on peut changer la cle d'acces ici
//  {
//    Serial.println(" Acces autorisé !");
//    Serial.println();
////    Keyboard.println(Password);
////    Keyboard.write(LoginKey);
//    delay(1000);
//  }
// 
// else   {
//    Serial.println(" Acces refusé");
////    Keyboard.println();
////    Keyboard.write(LoginKey);
//    delay(500);
//  }

   if (irrecv.decode(&results)){          // Reception code telecommande
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
  delay(100);
} 
