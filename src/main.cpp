#include <Arduino.h>
#include <TimerOne.h>
#include <stdio.h>
#include "functions.h"

int mod1position,mod2position;
int prevmod1,prevmod2;
int fill;
struct Potentiometer P1;
struct Potentiometer P2;

void tim1(){
  P1.Position = map(analogRead(P1.algPin), 0, 1023, 0,100);
  P2.Position = map(analogRead(P2.algPin), 0, 1023, 0,100);

  sendConditionCheck(&P1,&P2);

  P1.prevPosition = P1.Position;
  P2.prevPosition = P2.Position;
  }

void setup() {

  Serial.begin(9600); 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(tim1);

  pinMode(41,OUTPUT); 
  pinMode(43,OUTPUT);

  // put your setup code here, to run once:
}

void loop() {
  if(fill!=1){fill=PotenFillStruc(&P1,&P2);}

  Serial.print(P2.Position);
  Serial.print("\t");
  Serial.print(P2.send);
  Serial.print("\t");
  Serial.print("\t");
  delay(1000);
  P2.send=0;
}