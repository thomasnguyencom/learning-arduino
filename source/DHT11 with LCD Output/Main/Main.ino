// Author: Thomas Nguyen
//

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// RGB LED Pins
#define BLUE 3
#define GREEN 5
#define RED 6

void setup() {
  lcd.begin(16, 2);
  //lcd.print("Hello, World!");

  // setup RGB LED
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// RGB LED variables
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void loop() {
  stepPrimary(4, 25);
  
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

void output(int red, int green, int blue) {
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);

  lcd.setCursor(0, 0);
  lcd.print("R:"); lcd.print(red); lcd.print(" ");
  lcd.print("G:"); lcd.print(green); lcd.print(" ");
  lcd.print("B:"); lcd.print(blue); lcd.print(" ");

  String fullHex = "#";
  fullHex += toHex(red);
  fullHex += toHex(green);
  fullHex += toHex(blue);
  
  lcd.setCursor(0, 1);
  lcd.print(fullHex);
}

String toHex(int colorValue) {
  int h1 = int(colorValue / 16);
  int h2 = colorValue - (h1 * 16);

  String hex = "";
  hex += String(h1, HEX);
  hex += String(h2, HEX);

  return hex;
}

void stepPrimary(int stepCount, int delayTime) {
  stepRed(stepCount, delayTime);
  stepGreen(stepCount, delayTime);
  stepBlue(stepCount, delayTime);
}

void stepRed(int stepCount, int delayTime) {
  // RGB LED OUTPUT
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
  for(int i = 0; i < 255; i += stepCount) {
    output(redValue, greenValue, blueValue);
            
    redValue += stepCount;
    
    delay(delayTime);
  }
}

void stepGreen(int stepCount, int delayTime) {
  // RGB LED OUTPUT
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
  for(int i = 0; i < 255; i += stepCount) {
    output(redValue, greenValue, blueValue);
            
    greenValue += stepCount;
    
    delay(delayTime);
  }
}

void stepBlue(int stepCount, int delayTime) {
  // RGB LED OUTPUT
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
  for(int i = 0; i < 255; i += stepCount) {
    output(redValue, greenValue, blueValue);
            
    blueValue += stepCount;
    
    delay(delayTime);
  }
}

