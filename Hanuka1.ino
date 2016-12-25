#include "Global.h"

#define DO NOTE_C4    // 262
#define RE NOTE_D4    // 294
#define MI NOTE_E4    // 330
#define FA NOTE_F4    // 349
#define SOL NOTE_G4   // 392
#define SL NOTE_G4   // 392
#define LA NOTE_A4    // 440
#define SI NOTE_B4    // 494

const int servo_2RestPosition   = 0;  //Starting position
const int servo_2TargetPosition = 90; //Position when event is detected

unsigned int piezoHanerot1Length      = 24;                                                      // amount of notes in melody
unsigned int piezoHanerot1Melody[]    = {SL, MI, MI, MI, MI, MI, MI, RE, DO, RE, MI, DO, 0  , SL, SL, SL, SL, SL, SL, FA, MI, FA, SL, MI}; // list of notes. List length must match HoorayLength!
unsigned int piezoHanerot1Durations[] = {8 , 4 , 8 , 16, 4 , 4 , 8 , 8 , 8 , 8 , 4 , 4 , 4  , 4 , 8 , 16, 4 , 4 , 8 , 8 , 8 , 8 , 4 , 4}; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!

unsigned int piezoHanerot2Length      = 19;                                                      // amount of notes in melody
unsigned int piezoHanerot2Melody[]    = {SL,SI,MI,FA,SL,   SL,DO,MI,FA,SL,  LA,SL,FA,MI,RE,SL,MI,RE,DO };
unsigned int piezoHanerot2Durations[] = {8, 8, 8, 8, 2,    8, 8, 8, 8, 2,   8, 8, 8, 8, 4, 4, 4, 4, 4 };

unsigned int piezoMaoz1Length      = 17;                                                      // amount of notes in melody
unsigned int piezoMaoz1Melody[]    = {DO,SL,DO,FA,MI,RE,DO, 0, SL,SL,LA,RE,MI,FA,MI,RE,DO};
unsigned int piezoMaoz1Durations[] = {4, 4, 4, 4, 4, 4, 4,  4, 8, 8, 4, 4, 8, 8, 4, 4, 2};

unsigned int piezoYevanim1Length       = 23;
unsigned int piezoYevanim1Melody[]     = {C13,F18,G20,GS21, AS23,GS21,GS21, AS23,GS21,AS23, C25,AS23,  0,  AS23,AS23,G20,GS21, GS21,G20, F18,G20,GS21,F18};
unsigned int piezoYevanim1Durations[]  = {4 ,  4 , 4 ,  4 , 4 ,   2 ,   2 ,  4 ,  4 ,  4 ,  4 ,  2 ,   2,   2 ,  4,  4,   2 ,  4, 4 ,    4 , 4 , 4, 4};
unsigned int piezoYevanim2Length       = 20;
unsigned int piezoYevanim2Melody[]     = {F18,G20,GS21,AS23,C25,C25, F30,F30, DS28,CS26,C25, 0, C25,F30,F30, DS28, F30,DS28,CS26,C25};
unsigned int piezoYevanim2Durations[]  = { 4 , 4 , 4 ,  4 ,  2 , 2 ,  4 , 4 ,  4 ,  4 ,  2,  2,  8 , 2 , 2 ,  8 ,   4 , 4 ,  2 , 2};
unsigned int piezoYevanim3Length       = 20;
unsigned int piezoYevanim3Melody[]     = {F30,C25,C25,C25, C25,AS23,C25,CS26,AS23, 0, GS21,AS23,C25,CS26, DS28,CS26, C25,AS23,AS23,GS21};
unsigned int piezoYevanim3Durations[]  = { 2 , 2 , 2 , 2 ,  4 , 4 ,  4 , 4 ,  2 ,  2,  4 ,  4 , 4 ,  4 ,   4 ,  4 ,    4 , 4 ,  1 ,  2};
unsigned int piezoYevanim4Length       = 18;
unsigned int piezoYevanim4Melody[]     = {GS21,CS26,CS26,C25, 0, GS21,C25,C25,AS23, AS23,F18,AS23, GS21,G20,GS21,AS23,C25};
unsigned int piezoYevanim4Durations[]  = { 4 ,  2 ,  2 ,  2 , 8,  4 ,  2 , 2 , 1 ,   2 ,  2,  2 ,   4 ,  4 , 2 ,  2 ,  1 };
unsigned int piezoYevanim5Length       = 18;
unsigned int piezoYevanim5Melody[]     = {GS21,CS26,CS26,C25, 0, GS21,C25,C25,AS23, AS23,F18,AS23, GS21,G20,F18,F18};
unsigned int piezoYevanim5Durations[]  = { 4 ,  2 ,  2 ,  2 , 8,  4 ,  2 , 2 , 1 ,   2 ,  2,  2 ,   4 ,  4 , 1 ,  2 };


const int CANDLES_ANGLE_START = 70;
const int CANDLES_AMPLITUDE = 5;
const int CANDLES_ANGLES[] = { 67, 72, 81, 83, 92, 95, 99, 105 };
const int CANDLES_PINS[] = { LED1_PIN_VIN, LED2_PIN_VIN, LED3_PIN_VIN, LED4_PIN_VIN, LED5_PIN_VIN, LED6_PIN_VIN, LED7_PIN_VIN, LED8_PIN_VIN };
LED candles[] = { led1, led2, led3, led4, led5, led6, led7, led8 };

int i;
//int servo1_angle;
int servo2Angle;

/* This code sets up the essentials for your circuit to work. It runs first every time your circuit is powered with electricity. */
void setup() {
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    Serial.println("start");
    
    pushButton.init();

    for (int i=0; i<8; i++) {
      candles[i].off();
    }
    servo_1.attach(SERVO_1_PIN);
    resetServos();
    //playMusic();
}

void loop() {
    if (pushButton.onPress()) {
        lightCandles(2);
    }
}




void resetServos() {
  moveServo1(90);
  //log("reset servo_2 angle: ", servo_2RestPosition);
  servo_2.attach(SERVO_2_PIN);
  servo_2.write(servo_2RestPosition);
  delay(100);
  servo_2.detach();
}

void moveServo1(int angle) {
  log("moveServo1: ", angle);
  //servo_1.attach(SERVO_1_PIN);
  servo_1.write(angle);
  delay(100);
  //servo_1.detach();
}

void lightCandles(int n) {
    log("lightCandles: ", n);
    for (i=n-1; i>=0; i--) {
        lightCandle(i);
        delay(1000);
    }
    moveServo1(90);
    playMusic();
}

void lightCandle(int c) {
    log("lightCandle: ", c);
    
    // turn arm
    //int angle = (int) CANDLES_ANGLE_START + c * CANDLES_AMPLITUDE;
    int angle = CANDLES_ANGLES[c];
    moveServo1(angle);

    // down arm
    servo_2.attach(SERVO_2_PIN);
    for (servo2Angle = servo_2RestPosition; servo2Angle < servo_2TargetPosition; servo2Angle++) {
        servo_2.write(servo2Angle);
        delay(30);
    }
    servo_2.write(servo_2TargetPosition);
    delay(100);

    // light led
    lightLed(c);

    // up arm
    /*for (int i=45; i>90; i++) {
        servo_2.write(i);
        delay(100);
    }*/
    servo_2.write(servo_2RestPosition);
    delay(100);
    servo_2.detach();

}

void lightLed(int i) {
  //log("lightLed: ", i);
  int pin = CANDLES_PINS[i];
  //log("pin: ", pin);
  digitalWrite(pin, HIGH);
}

void playMusic() {
  /*piezoSpeaker.playMelody(piezoHanerot1Length, piezoHanerot1Melody, piezoHanerot1Durations);
  piezoSpeaker.playMelody(piezoHanerot2Length, piezoHanerot2Melody, piezoHanerot2Durations); 
  piezoSpeaker.playMelody(piezoHanerot1Length, piezoHanerot1Melody, piezoHanerot1Durations);
  piezoSpeaker.playMelody(piezoHanerot2Length, piezoHanerot2Melody, piezoHanerot2Durations); 
  delay(1000);*/
  
  /*piezoSpeaker.playMelody(piezoMaoz1Length, piezoMaoz1Melody, piezoMaoz1Durations); 
  delay(500);
  piezoSpeaker.playMelody(piezoMaoz1Length, piezoMaoz1Melody, piezoMaoz1Durations); 
  delay(500); */

  piezoSpeaker.playMelody(piezoYevanim1Length, piezoYevanim1Melody, piezoYevanim1Durations); 
  delay(500);
  piezoSpeaker.playMelody(piezoYevanim2Length, piezoYevanim2Melody, piezoYevanim2Durations); 
  delay(1000);
  piezoSpeaker.playMelody(piezoYevanim3Length, piezoYevanim3Melody, piezoYevanim3Durations); 
  delay(500);
  piezoSpeaker.playMelody(piezoYevanim4Length, piezoYevanim4Melody, piezoYevanim4Durations); 
  delay(250);
  piezoSpeaker.playMelody(piezoYevanim5Length, piezoYevanim5Melody, piezoYevanim5Durations); 

}
/**************** Utils functions *************************/

void log(String str) {
  Serial.println(str);
}

void log(String desc, int num) {
  Serial.print(desc);
  Serial.println(num);
}

void log(String str1, int num, String str2) {
  Serial.print(str1);
  Serial.print(num);
  Serial.println(str2);
}



/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
