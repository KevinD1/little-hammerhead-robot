#include <Adafruit_SSD1306.h>
#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

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
 // delay(2000);
}

void loop() {
  lookStraight();
  delay(1000);
lookDown();
delay(1000);
lookUp();
delay(1000);
lookLeft();
delay(1000);
lookRight();
delay(1000);
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
  display.fillCircle(50, 35, 10, WHITE);
  display.fillCircle(90, 35, 10, WHITE);
  // put your main code here, to run repeatedly:
display.display();
}
