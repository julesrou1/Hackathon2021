#ifndef FUNCTIONS_H

#define FUNCTIONS_H

#include <Arduino.h>
#include <math.h>
#include <stdio.h>
#include <TimerOne.h>
#include <TimerFour.h>
#include <Keypad.h>
#include "LiquidCrystal.h"
#include "TimerThree.h"
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <IRremote.h>

typedef struct Potentiometer{
    String Name;
    int Position;
    int prevPosition;
    int algPin;
    int ledPin;
    int send;
    int mute;
} Potentiometer;


//Use to to check if value for mic/Speaker volume change enough to be consider a input from user.
//We don't want electrical noise to change volume
void sendConditionCheck(Potentiometer* P1,Potentiometer* P2);

int PotenFillStruc(Potentiometer* P1,Potentiometer* P2);

void sendPotToPc(Potentiometer* P1,Potentiometer* P2);


#endif