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

