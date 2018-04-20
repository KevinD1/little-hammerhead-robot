/*
Copyright (c) 2018 LeRoy Miller

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses>

If you find this or any of my projects useful or enjoyable please support me.  
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller  

https://github.com/kd8bxp
https://www.youtube.com/channel/UCP6Vh4hfyJF288MTaRAF36w  
https://kd8bxp.blogspot.com/  
*/

/*
 * Based on code for Arduino Bluetooth RC car.
 * https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * https://sites.google.com/site/bluetoothrccar/home/3BluetoothModulesAndArduinoCode
 * 
 * For the Little Hammer Head Robot made by Rabbit Robots
 
*/

#include <Adafruit_SSD1306.h>
#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define ROBOTNAME "LeRoysBot" //Bluetooth Name HC-06
#define ROBOTPIN 1234 //Bluetooth Pin 1234 is default see setup()
#define LEFTSWITCH 6 //D6 Blue Connector Marked "B"
#define RIGHTSWITCH 5 //D5 Blue Connector Marked "G"
#define M1SPD 10 //D10 PWM M1 speed pin
#define M2SPD 11 //D11 PWM M2 speed pin
#define M2DIR 13 //D13 PWM M2 direction
#define M1DIR 12 //D12 M1 direction
#define BUZZER 4 //D4
#define PINGT 8 //D8 yellow connector
#define PINGR 7 //D7 yellow connector 

char command = 'S';
char prevCommand = 'A';
int velocity = 150;   
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started) 
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to that of your Bluetooth module.
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
delay(5000);
 pinMode(LEFTSWITCH, INPUT_PULLUP);
pinMode(RIGHTSWITCH, INPUT_PULLUP);
pinMode(M1SPD, OUTPUT);
pinMode(M2SPD, OUTPUT);
pinMode(M1DIR, OUTPUT);
pinMode(M2DIR, OUTPUT);
Serial.print("AT+NAME");
Serial.print(ROBOTNAME);
delay(1000);
//Serial.print("AT+PIN"); //These lines need uncommented
//Serial.print(ROBOTPIN); //if you want to change
//delay(1000);            //Bluetooth Pin
stop();
}

void loop(){
 
  if(Serial.available() > 0){ 
    timer1 = millis();   
    prevCommand = command;
    command = Serial.read(); 
    //Change pin mode only if new command is different from previous.   
    if(command!=prevCommand){
      Serial.println(command);
      switch(command){
      case 'F':
      setSpd(velocity);  
        
        //display.setTextSize(2);
        //display.clearDisplay();
        //display.setCursor(0,0);
        //display.println("Forward.");
        //display.display();
        lookDown();
        Forward;
        break;
      case 'B': 
      setSpdB(velocity); 
        //display.setTextSize(2);
        //display.clearDisplay();
        //display.setCursor(0,0);
        //display.println("Backward.");
        //display.display();
        lookUp();
        Backward();
        break;
      case 'L': 
      setSpd(velocity);
      //display.setTextSize(2);
        //display.clearDisplay();
        //display.setCursor(0,0);
        //display.println("Left.");
        //display.display();
        lookLeft(); 
        Left();
        break;
      case 'R':
      setSpd(velocity);
      //display.setTextSize(2);
        //display.clearDisplay();
        //display.setCursor(0,0);
        //display.println("Right.");
        //display.display();
        lookRight();
        Right();  
        break;
      case 'S':
      //display.clearDisplay();
      //display.display();
      lookStraight();  
        stop();
        break; 
      case 'I':  //FR  
        //yellowCar.ForwardRight_4W(velocity);
        break; 
      case 'J':  //BR  
        //yellowCar.BackRight_4W(velocity);
        break;        
      case 'G':  //FL  
        //yellowCar.ForwardLeft_4W(velocity);
        break; 
      case 'H':  //BL
        //yellowCar.BackLeft_4W(velocity);
        break;
      case 'W':  //Font ON Not Used
        //digitalWrite(pinfrontLights, HIGH);
        break;
      case 'w':  //Font OFF Not Used
        //digitalWrite(pinfrontLights, LOW);
        break;
      case 'U':  //Back ON Not Used
        //digitalWrite(pinbackLights, HIGH);
        break;
      case 'u':  //Back OFF Not Used
        //digitalWrite(pinbackLights, LOW);
        break; 
      case 'D':  //Everything OFF 
        //digitalWrite(pinfrontLights, LOW);
        //digitalWrite(pinbackLights, LOW);
        stop();
        break; 
       case 'V': //play charge (Horn ON command)
       display.setTextSize(2);
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Charge!");
        display.display();
       playCharge();
       break;        
      default:  //Get velocity
        if(command=='q'){
          velocity = 255;  //Full velocity
          setSpd(velocity);
        }
        else{ 
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
          if((command >= 48) && (command <= 57)){ 
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 25 changes the range from 0-9 to 0-225.
            velocity = (command - 48)*25;       
            setSpd(velocity);
          }
        }
      }
    }
  }
  else{
    timer0 = millis();  //Get the current time (millis since execution started).
    //Check if it has been 500ms since we received last command.
    if((timer0 - timer1)>500){  
      //More tan 500ms have passed since last command received, car is out of range.
      //Therefore stop the car and turn lights off.
      //digitalWrite(pinfrontLights, LOW);
      //digitalWrite(pinbackLights, LOW);
      stop();
    }
  }  
}

void Forward() {
  digitalWrite(M1DIR, HIGH);
  //digitalWrite(M1SPD, HIGH);
  digitalWrite(M2DIR, HIGH);
  //digitalWrite(M2SPD, HIGH);
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

void setSpd(int m) {  
  analogWrite(M1SPD, m);
  analogWrite(M2SPD, m);
}

void setSpdB(int m) {
  analogWrite(M1SPD, 255 - m);
  analogWrite(M2SPD, 255 - m);
}

void stop() {
  analogWrite(M1SPD, 0); 
  digitalWrite(M1DIR, LOW); 
  analogWrite(M2SPD, 0);
  digitalWrite(M2DIR, LOW);
}

void lookDown() {
  display.clearDisplay();
  //display.drawRoundRect(0, 0, 30, 60, 50, WHITE);
  display.drawCircle(50, 35, 15,  WHITE);
  display.drawCircle(90, 35, 15, WHITE);
  display.fillCircle(50, 40, 10, WHITE);
  display.fillCircle(90, 40, 10, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}

void lookUp() {
  display.clearDisplay();
  //display.drawRoundRect(0, 0, 30, 60, 50, WHITE);
  display.drawCircle(50, 35, 15,  WHITE);
  display.drawCircle(90, 35, 15, WHITE);
  display.fillCircle(50, 30, 10, WHITE);
  display.fillCircle(90, 30, 10, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}

void lookLeft() {
  display.clearDisplay();
  //display.drawRoundRect(0, 0, 30, 60, 50, WHITE);
  display.drawCircle(50, 35, 15,  WHITE);
  display.drawCircle(90, 35, 15, WHITE);
  display.fillCircle(45, 35, 10, WHITE);
  display.fillCircle(85, 35, 10, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}

void lookRight() {
  display.clearDisplay();
  //display.drawRoundRect(0, 0, 30, 60, 50, WHITE);
  display.drawCircle(50, 35, 15,  WHITE);
  display.drawCircle(90, 35, 15, WHITE);
  display.fillCircle(55, 35, 10, WHITE);
  display.fillCircle(95, 35, 10, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}

void lookStraight() {
  display.clearDisplay();
  //display.drawRoundRect(0, 0, 30, 60, 50, WHITE);
  display.drawCircle(50, 35, 15,  WHITE);
  display.drawCircle(90, 35, 15, WHITE);
  display.fillCircle(50, 35, 8, WHITE);
  display.fillCircle(90, 35, 8, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}
