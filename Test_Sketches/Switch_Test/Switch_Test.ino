/*
 * Very Simple Sketch to Test the Switches
 * By LeRoy Miller Dec 2017
 * For use with Keyes L-298P Shield
 * 
 * Sketch will display left or right for each push of the
 * switch.
 * 
 */

#define LEFTSWITCH 6 //D6 Blue Connector Marked "B"
#define RIGHTSWITCH 5 //D5 Blue Connector Marked "G"

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LEFTSWITCH, INPUT_PULLUP);
pinMode(RIGHTSWITCH, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
if (digitalRead(LEFTSWITCH) == LOW) {Serial.println("Left");}
if (digitalRead(RIGHTSWITCH) == LOW) {Serial.println("Right");}

}
