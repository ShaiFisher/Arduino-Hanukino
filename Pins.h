#ifndef PINS_H
#define PINS_H

// 8 candles (middle one, Shamash is always on)
// Shift Register sn74hc595
#define SHIFT_DATA_PIN 2
#define SHIFT_LATCH_PIN 3
#define SHIFT_CLOCK_PIN 4

/*#define LED1_PIN_VIN  9     // first candle, right side (in front)
#define LED2_PIN_VIN  8
#define LED3_PIN_VIN  7
#define LED4_PIN_VIN  6
#define LED5_PIN_VIN  5
#define LED6_PIN_VIN  4
#define LED7_PIN_VIN  3
#define LED8_PIN_VIN  2*/

/*#define RGBLED_PIN_R	9
#define RGBLED_PIN_G	6
#define RGBLED_PIN_B	5*/
#define PUSHBUTTON_PIN_1	13      // 1st leg: 5v; 2nd leg: I. 10k resistor to GND, II. pin 10
#define SERVO_1_PIN	8
#define SERVO_2_PIN	9
#define PIEZOSPEAKER_PIN_SIG  11    // +: 5v; -: left leg of Transistor BC557
                                    // BC557:   Left: Piezzo -; 
                                    //          Mid: 1k resistor to pin 11
                                    //          Right; GND

#endif //PINS_H
