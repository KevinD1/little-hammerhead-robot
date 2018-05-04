/* 
 *  Very Simple Sketch to test the 9G Servo
 *  Uses the RIGHT and LEFT switches to move raise and lower
 *  the servo. 
 *  This can be used to calibrate for your servo, and pen setup
 *  By LeRoy Miller Dec 2017 
 *  for use with the Keyes L-298P Shield
 */
#include <Servo.h>

#define LEFTSWITCH 6 //D6 Blue Connector Marked "B"
#define RIGHTSWITCH 5 //D5 Blue Connector Marked "G"

int raise = 180; //Move the servo to position 180
int lower = 90; //Move the servo to position 90

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(LEFTSWITCH, INPUT_PULLUP);
  pinMode(RIGHTSWITCH, INPUT_PULLUP);
  penUp();
  Serial.println("Use Left Switch to Lower Pen");
  Serial.println("Use Right Switch to Raise Pen");
}

void loop() {
 if (digitalRead(LEFTSWITCH) == LOW) {penDown();}
 if (digitalRead(RIGHTSWITCH) == LOW) {penUp();}

}

void penUp() {
  myservo.write(raise);
  delay(100);
}

void penDown() {
  myservo.write(lower);
  delay(100);
}

