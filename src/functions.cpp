#include "functions.h"

int PotenFillStruc(Potentiometer* P1,Potentiometer* P2){
    P1->Name="Mic";
    P1->prevPosition=0;
    P1->algPin=A0;
    P1->ledPin=41;
    P1->send=0;

    P2->Name="Speaker";
    P2->prevPosition=0;
    P2->algPin=A1;
    P2->ledPin=43;
    P2->send=0;

    return 1;
}

void sendConditionCheck(Potentiometer* P1,Potentiometer* P2){
    if(P1->Position<10){
        P1->Position=0;
        digitalWrite(P1->ledPin,LOW);}
    else{digitalWrite(P1->ledPin,HIGH);}

    if(P1->Position!=P1->prevPosition){P1->send=1;}
    

    if(P2->Position<10){
        P2->Position=0;
        digitalWrite(P2->ledPin,LOW);}
    else{digitalWrite(P2->ledPin,HIGH);}
    
    if(P2->Position!=P2->prevPosition){P2->send=1;}

}

<<<<<<< Updated upstream
=======
void sendPotToPc(Potentiometer* P1,Potentiometer* P2){
    char* buf;
    if (P1->send==1){
        buf="01;"+P1->Position+"!"//en gros le format c'est "MOD;CODE!" avec MOD sur 2 bits 
        Serial.println(buf); //MOD = 01 pour mic; 02 pour Speaker
        P1->send=0;
        buf="";//je sais pas si c'est bon mais l'idée c'est de vider le buffer pour pas se retrouver avec des données parasites
    }
    else if (P2->send==1){
        buf="02;"+P2->Position+"!"
        Serial.println(buf);
        P2->send=0;
        buf="";
    }
}

void sendButToPc(Button Bx){
    //même idée, MOD = 03, et après le code correspond au bouton.
    //CODE=01 -> mute
    //CODE=02-> unmute
    //le reste est à mapper
}
>>>>>>> Stashed changes
