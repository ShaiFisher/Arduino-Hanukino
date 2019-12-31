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
unsigned int piezoYevanim2Durations[]  = { 4 , 4 , 4 ,  4 ,  2 , 2 ,  4 , 4 ,  4 ,  4 ,  2,  2,  8 , 2 , 2 ,  4 ,   4 , 4 ,  4 , 2};
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
const int CANDLES_ANGLES[] = { 67, 70, 74, 78, 87, 91, 95, 102 };
const int CANDLES_BYTE_VALUES[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
//const int CANDLES_LOW_BYTE_VALUES[] = { 254, 253, 251, 247, 239, 223, 191, 121 }; 

int i;
byte ledsShiftByte = 0;
//int servo1_angle;
int servo2Angle;
int rnd;

// functions
void resetServos();
void lightCandles(int n);
void moveServo1(int angle);
void lightCandle(int c);
void playMusic();
void lightLed(int i);
void lightLedsUntil(int i);
void flickerCandles(int n);
void log(String str);
void log(String desc, int num);
void log(String str1, int num, String str2);


/* This code sets up the essentials for your circuit to work. It runs first every time your circuit is powered with electricity. */
void setup() {
    Serial.begin(9600);
    Serial.println("start");
    
    pushButton.init();

    // init leds
    pinMode(SHIFT_DATA_PIN, OUTPUT);
    pinMode(SHIFT_LATCH_PIN, OUTPUT);  
    pinMode(SHIFT_CLOCK_PIN, OUTPUT);
    ledsShiftByte = 255;
    updateShiftRegister();
    
    servo_1.attach(SERVO_1_PIN);
    resetServos();

    randomSeed(analogRead(0));
}

void loop() {
    if (pushButton.onPress()) {
        ledsShiftByte = 0;
        updateShiftRegister();
        lightCandles(8);
        playMusic();
        flickerCandles(8);
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
  //log("moveServo1: ", angle);
  servo_1.write(angle);
  delay(100);
}

void lightCandles(int n) {
    //log("lightCandles: ", n);
    for (i=n-1; i>=0; i--) {
        lightCandle(i);
        delay(1000);
    }
    moveServo1(90);
}

void lightCandle(int c) {
    //log("lightCandle: ", c);
    // turn arm
    int angle = CANDLES_ANGLES[c];
    //log("servo1 angle: ", angle);
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
    servo_2.write(servo_2RestPosition);
    delay(100);
    servo_2.detach();

}

void lightLed(int i) {
  //log("lightLed: ", i);
  ledsShiftByte = ledsShiftByte | CANDLES_BYTE_VALUES[i];
  //log("ledsShiftByte after: ", ledsShiftByte);
  updateShiftRegister();
}

void lightLedOnly(int i) {
  //log("lightLed: ", i);
  ledsShiftByte = CANDLES_BYTE_VALUES[i];
  //log("ledsShiftByte after: ", ledsShiftByte);
  updateShiftRegister();
}

void updateShiftRegister() {
    //log("updateShiftRegister: ", ledsShiftByte);
    digitalWrite(SHIFT_LATCH_PIN, LOW);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, ledsShiftByte);
    digitalWrite(SHIFT_LATCH_PIN, HIGH);
}

void playMusic() {
  //log("playMusic");
  playMelody(piezoHanerot1Length, piezoHanerot1Melody, piezoHanerot1Durations);
  playMelody(piezoHanerot2Length, piezoHanerot2Melody, piezoHanerot2Durations); 
  playMelody(piezoHanerot1Length, piezoHanerot1Melody, piezoHanerot1Durations);
  playMelody(piezoHanerot2Length, piezoHanerot2Melody, piezoHanerot2Durations); 
  delay(1000);
  
  /*piezoSpeaker.playMelody(piezoMaoz1Length, piezoMaoz1Melody, piezoMaoz1Durations); 
  delay(250);
  piezoSpeaker.playMelody(piezoMaoz1Length, piezoMaoz1Melody, piezoMaoz1Durations); 
  delay(1000);*/

  playMelody(piezoYevanim1Length, piezoYevanim1Melody, piezoYevanim1Durations); 
  delay(500);
  playMelody(piezoYevanim2Length, piezoYevanim2Melody, piezoYevanim2Durations); 
  delay(1000);
  playMelody(piezoYevanim3Length, piezoYevanim3Melody, piezoYevanim3Durations); 
  delay(500);
  playMelody(piezoYevanim4Length, piezoYevanim4Melody, piezoYevanim4Durations); 
  delay(125);
  playMelody(piezoYevanim5Length, piezoYevanim5Melody, piezoYevanim5Durations); 

}

void flickerCandles(int n) {
    while (true) {
        // light leds 1..n
        ledsShiftByte = CANDLES_BYTE_VALUES[n] - 1;   //example: 8 => 7 (111)
        updateShiftRegister();

        // shut down 1 random led
        rnd = random(0,n);
        //log("rnd:", rnd);
        ledsShiftByte &= ~(1UL << rnd);   // ledsShiftByte & byte of all 1 except one bit
        updateShiftRegister();

        // wait a bit
        delay(25);
    }
}

void playMelody(unsigned int len, unsigned int *melody, unsigned int *noteDurations)
{
  // Based on https://www.arduino.cc/en/Tutorial/toneMelody
  for (int thisNote = 0; thisNote < len; thisNote++) {
  
    // light led
    int noteFreq = melody[thisNote];
    int candle = 0;
    if (noteFreq <= C13) {
      candle = 0;
    } else if (noteFreq <= D4) {
      candle = 1;
    } else if (noteFreq <= E4) {
      candle = 2;
    } else if (noteFreq <= F18) {
      candle = 3;
    } else if (noteFreq <= GS21) {
      candle = 4;
    } else if (noteFreq <= B4) {
      candle = 5;
    } else if (noteFreq <= CS26) {
      candle = 6;
    } else {
      candle = 7;
    }
   
    lightLedOnly(candle);

    TimerFreeTone(PIEZOSPEAKER_PIN_SIG, melody[thisNote], 1000 / noteDurations[thisNote]); 
    delay(50);
  }
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
