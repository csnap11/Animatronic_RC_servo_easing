//OLAF Servo Smoothing Code V2
//Carlitos
#include <Servo.h>
//#include <ServoEasing.hpp>
#include <math.h>


#define RC_Signal_PIN 11//PIN that will read PWM signal from the RC receiver
#define Servo_signal_PIN 5//PIN that will send PWM signal to the servo
int channel;
int pos_current; //current pos
int pos_target; //desired pos
int delta_pos;//difference between x0 and x1
int pos_max;
int pos_min;
int vel; //delta div by ticks
int ticks; // delay
Servo myservo;


void setup() {
  // setup comms
  pinMode(RC_Signal_PIN, INPUT);
  Serial.begin(9600);
  myservo.attach(Servo_signal_PIN);

  //init values
  pos_current = 90;
  ticks = 10;
  pos_max = 180;
  pos_min = 0;
}

void loop() {
  // Controller Read and map
  channel = pulseIn(RC_Signal_PIN, HIGH);
  //Serial.println(channel);
  pos_target = limit(map(channel, 985, 1970, 0, 180), pos_min, pos_max);

  //Velocity section
  delta_pos = pos_target - pos_current;
  Serial.println(delta_pos);
  vel = delta_pos / ticks;
  Serial.println(vel);


  
  //Update and write
  pos_current = pos_current + vel;
  Serial.println(pos_current);
  pos_current = limit(pos_current, pos_min, pos_max);
  Serial.println(pos_current);
  myservo.write(pos_current);
  delay(25);
}

int limit( int val, int minVal, int maxVal) {
   if (val < minVal) {
      val = minVal;
   }
   if (val > maxVal) {
      val = maxVal;
   }
   return val;
}
