/*
 * Ultra Sonic Distance Sensor Test
 * Slightly modified for use with the Keyes L-298P Shield
 * by LeRoy Miller Dec 2017
 * 
 * Use the Serial Console to verify your ultra sonic sensor is
 * working.
 * 
 */

#define PINGT 8 //D8 yellow connector
#define PINGR 7 //D7 yellow connector

float pingTime;  //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=776.5; //Speed of sound in miles per hour when temp is 77 degrees.
const int DURATION_PER_INCH = 550; //The approximate duration in microseconds of the echo for an object one inch away.
unsigned long echoDuration = 0; //Used to store the duration of the echo in microseconds

void setup(){
  Serial.begin(9600);
}


void loop(){ 
  pinMode(PINGT,OUTPUT);
  digitalWrite(PINGT, LOW);
  delayMicroseconds(2000);
  digitalWrite(PINGT, HIGH); //Send voltage to the trigger pin to begin the ultrasound pusle
  delayMicroseconds(15); //Pause the program for 10 microseconds (to produce a 10 microsecond pulse)
  digitalWrite(PINGT, LOW); //Stop sendig voltage to the trigger pin, ending the pulse
  delayMicroseconds(10);
  pinMode(PINGR,INPUT);
  echoDuration = pulseIn(PINGR, HIGH); //Get the duration of the echo coming back in microseconds 
  pingTime = echoDuration;
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  targetDistance=targetDistance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*63360;    //Convert miles to inches by multipling by 63360 (inches per mile)
  
  Serial.print(targetDistance);
  Serial.print("   ");
  Serial.println(echoDuration);
  delay(50);
}

