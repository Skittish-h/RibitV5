// #include <Arduino.h>
// #include <util/atomic.h>
// #include <Encoder.hpp>
// #include <LineSens.hpp>

// // Motor Pins: (pin with star is PWM)
// // Right Motor: PD6*, PD7 -> H: 6*,L: 7
// // Left Motor: PB0, PB1 -> H: 8, L: *9
// // Encoder Pins *-> interrupt:
// // Right Encoder: PD3*, PC3 -> 3, 17

// volatile int32_t posi = 0;

// Encoder enc_right (3 , 17, 6, 7, true);
// Encoder enc_left (2 , 15, 8, 9, false);

// LineSens line (12, 11, 13, 10);

// int error;
// int lastError = 0;

// const float kp = 0.2;
// const float kd = 1.4;

// const int speed = 140;

// //AVR GCC is fucking stupid
// void encRightStupidity() {
//   enc_right.encoderCallback();
// }
// void encLeftStupidity() {
//   enc_left.encoderCallback();
// }

// void setup() {
//   Serial.begin(9600);

//   enc_right.setUp();
//   enc_left.setUp();
  
//   attachInterrupt(digitalPinToInterrupt(3), encRightStupidity ,RISING);
//   attachInterrupt(digitalPinToInterrupt(2), encLeftStupidity ,RISING);
//   enc_left.setSpeed(100.0);
//   // enc_right.setSpeed(100.0);
//   // enc_left.motor.setSpeed(255);
  
// }

// void loop() {
//   // 12 counts per revolution revs = pos/12 each rev /9.96 - * whell circumference = 3.2cm 
//   // Serial.println(line.getLine());
//   // Serial.println(enc_left.getPosition());
//   float x = enc_left.controllLoop();
//   // if(x) {
//   //   Serial.print(x, 6);
//   //   Serial.print("\t");
//   //   Serial.println(enc_left.targetTime, 6);
//   // }
  
// }




