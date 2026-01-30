//OLAF Servo Smoothing Code V2
//Carlitos
#include <Servo.h>
//#include <ServoEasing.hpp>
#include <math.h>


#define RC_Signal_PIN 11//PIN that will read PWM signal from the RC receiver
#define Servo_signal_PIN 5//PIN that will send PWM signal to the servo
int channel; //RC signal Channel
int pos_current; //current position, x0
int pos_target; //desired position, x1
int delta_pos;//difference between x0 and x1
int pos_max; //Max of Servo usually 180
int pos_min;// Min of Servo usually 90
int vel; //velocity, delta divided by ticks
int vel0;
int accel;
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
  vel0 = 0;
}

void loop() {
  // Controller Read and map
  channel = pulseIn(RC_Signal_PIN, HIGH); //converts RC signal in pulse that can be read
  //Serial.println(channel);
  pos_target = limit(map(channel, 985, 1970, 0, 180), pos_min, pos_max); //Maps the incoming Pulse and maps it to standard servo range 0-180

  //Velocity section
  delta_pos = pos_target - pos_current;
  Serial.println(delta_pos);
  vel = delta_pos / ticks;
  Serial.println(vel);

  //Acceleration section
  accel = ((vel - vel0) / ticks);
  vel0 = vel0 + accel;
  //Other ideas
  //

  //Update and write
  pos_current = pos_current + vel0;
  Serial.println(pos_current);
  pos_current = limit(pos_current, pos_min, pos_max);
  Serial.println(pos_current);
  myservo.write(pos_current);
  delay(25);
}

int limit( int val, int minVal, int maxVal) {   //used to ensure signal sent to servo is always within range
   if (val < minVal) {                          //if current position is less than Minimum value set position to 0
      val = minVal;
   }
   if (val > maxVal) {                          //if current position is greater than Maximum value set position to 180
      val = maxVal;
   }
   return val;
}
