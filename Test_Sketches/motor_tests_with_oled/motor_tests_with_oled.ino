/*
 * Pre-Programmed "Dance" By LeRoy Miller Dec 2017
 * for Keyes L-298P Shield.
 * Moves the robot forward for a short distance,
 * spins left, then right, and then left
 * and move the robot backward for a short distance.
 * Speed is set using PWM.
 * Direction is set by enabling the Direction PIN HIGH for forward
 * or LOW for backward. (M1DIR and M2DIR)
 * There is no true distance measurment.
 * 
 * If your Motors move in the wrong direction, switch the wires
 * for that motor.
 * Program waits for the RIGHT switch to be pressed before
 * moving the motors. Once the "Dance" is done, the program 
 * waits again for the RIGHT switch to be pressed, and starts
 * over again.
 */
#include <Adafruit_SSD1306.h>
#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define LEFTSWITCH 6 //D6 Blue Connector Marked "B"
#define RIGHTSWITCH 5 //D5 Blue Connector Marked "G"
#define M1SPD 10 //D10 PWM M1 speed pin
#define M2SPD 11 //D11 PWM M2 speed pin
#define M2DIR 13 //D13 PWM M2 direction
#define M1DIR 12 //D12 M1 direction
#define BUZZER 4 //D4

int lowspd = 100; //PWM for stall of motors
int setspd = 150; //This is PWM the motors will run at.

void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();   
display.clearDisplay();
display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,20);
  display.println("Little Hammerhead");
  display.setCursor(45, 29);
  display.println("Robot!");
  display.display();
  delay(2000);
  
Serial.begin(9600);
pinMode(LEFTSWITCH, INPUT_PULLUP);
pinMode(RIGHTSWITCH, INPUT_PULLUP);
pinMode(M1SPD, OUTPUT);
pinMode(M2SPD, OUTPUT);
pinMode(M1DIR, OUTPUT);
pinMode(M2DIR, OUTPUT);
stop();
}

void loop() {
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0,52);
  display.println("Hit RIGHT Switch....");
  display.display();
while(digitalRead(RIGHTSWITCH) == HIGH) {
  delay(1);
//Waiting for RIGHTSWITCH Button to be pushed to continue
}

playCharge();

setSpd(setspd,setspd); //set the PWM for motor1 and motor2 
//can be used to set different speeds and cause turns
//this is not a direction control.
display.setTextSize(2);
display.clearDisplay();
display.setCursor(0,0);
display.println("Forward.");
display.display();
Forward();
delay(500);
display.clearDisplay();
display.setCursor(0,0);
display.println("Left.");
display.display();
Left();
delay(200);
display.clearDisplay();
display.setCursor(0,0);
display.println("Right.");
display.display();
Right();
delay(400);
display.clearDisplay();
display.setCursor(0,0);
display.println("Left.");
display.display();
Left();
delay(200);
display.clearDisplay();
display.setCursor(0,0);
display.println("Backward.");
display.display();
setSpd(255 - setspd, 255 - setspd);
Backward();
delay(500);

stop();

  for (int i=0;i<2;i++) {
tone(BUZZER, 3600);
delay(100);
tone(BUZZER, 3200);
delay(100);
}
noTone(4);

//start over

}

void stop() {
  analogWrite(M1SPD, 0); 
  digitalWrite(M1DIR, LOW); 
  analogWrite(M2SPD, 0);
  digitalWrite(M2DIR, LOW);
}

void setSpd(int m1, int m2) {
  if (m1 < lowspd) {m1 = lowspd;}
  if (m2 < lowspd) {m2 = lowspd;}
  if (m1 > 255) {m1 = 255;}
  if (m2 > 255) {m2 = 255;}
  analogWrite(M1SPD, m1);
  analogWrite(M2SPD, m2);
}
void Forward() {
  digitalWrite(M1DIR, LOW);
  digitalWrite(M2DIR, LOW);
  }

void Backward() {
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, HIGH);
}

void Left() {
  digitalWrite(M1DIR, HIGH);
  digitalWrite(M2DIR, LOW);
}

void Right() {
  digitalWrite(M1DIR, LOW);
  digitalWrite(M2DIR, HIGH);
}

void playCharge() {
  int note[] = {262, 262, 392, 523, 392, 523};
int duration[] = {100, 100, 100, 300, 100, 300};
 for (int thisNote = 0; thisNote < 6; thisNote ++) {
     // play the next note:
     tone(BUZZER, note[thisNote]);
     // hold the note:
     delay(duration[thisNote]);
     // stop for the next note:
     noTone(BUZZER);
     delay(25);
}
}

