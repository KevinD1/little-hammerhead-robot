/* 
 *  Very Simple Sketch to test the 9G Servo
 *  Uses the RIGHT and LEFT switches to move raise and lower
 *  the servo. 
 *  This can be used to calibrate for your servo, and pen setup
 *  By LeRoy Miller Dec 2017 
 *  for use with the Keyes L-298P Shield
 */


#define LEFTSWITCH 6 //D6 Blue Connector Marked "B"
#define RIGHTSWITCH 5 //D5 Blue Connector Marked "G"

int servopin=9;// define the digital 9 is connected to servo signal line 
int raise = 160; //Move the servo to position 180
int lower = 90; //Move the servo to position 90

int pulsewidth;// define the pulsewidth variable

void setup() {
  Serial.begin(9600);
 pinMode(servopin,OUTPUT);// set the servo interface as OUTPUT
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
  servopulse(servopin, raise);
  //delay(100);
}

void penDown() {
  servopulse(servopin, lower);
  //delay(100);
}

void servopulse(int servopin,int myangle)// define a pulse function 
{
pulsewidth=(myangle*11)+500;// convert the angle into pulse width of 500-2480 
digitalWrite(servopin,HIGH);// set the servo pin to HIGH 
delayMicroseconds(pulsewidth);// delay the microseconds of pulsewidth
digitalWrite(servopin,LOW);// set the servo pin to LOW
delay(20-pulsewidth/1000);
}

