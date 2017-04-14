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

#define R true
#define G true
#define B true
#define x false

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

void loop() {
  int stepCount = 4;
  int delayTime = 25;

  stepRGB("red    ", R, x, x, stepCount, delayTime);
  stepRGB("green  ", x, G, x, stepCount, delayTime);
  stepRGB("blue   ", x, x, B, stepCount, delayTime);
  
  stepRGB("yellow ", R, G, x, stepCount, delayTime);
  stepRGB("cyan   ", x, G, B, stepCount, delayTime);
  stepRGB("magenta", R, x, B, stepCount, delayTime);
  
  stepRGB("white  ", R, G, B, stepCount, delayTime);

  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

void output(String color, int red, int green, int blue) {
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);

  lcd.setCursor(0, 0);
  lcd.print("R:"); lcd.print(red); lcd.print(" ");
  lcd.print("G:"); lcd.print(green); lcd.print(" ");
  lcd.print("B:"); lcd.print(blue); lcd.print(" ");

  String fullHex = toHex(red, green, blue);
  
  lcd.setCursor(0, 1);
  lcd.print(fullHex); lcd.print(" "); lcd.print(color);
}

void stepRGB(String color, bool rFlag, bool gFlag, bool bFlag, int stepCount, int delayTime) {
  // Reset RGB LED output
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  for(int i = 0; i < 255; i += stepCount) {
    output(color, redValue, greenValue, blueValue);

    if(rFlag) redValue += stepCount;
    if(gFlag) greenValue += stepCount;
    if(bFlag) blueValue += stepCount;
    
    delay(delayTime);
  }
}

String toRGB(int redValue, int greenValue, int blueValue) {
  String rgb = "";

  rgb += "R:";
  rgb += redValue;
  rgb += "G:";
  rgb += greenValue;
  rgb += "B:";
  rgb += blueValue;

  return rgb;
}

String toHex(int colorValue) {
  int h1 = int(colorValue / 16);
  int h2 = colorValue - (h1 * 16);

  String hex = "";
  hex += String(h1, HEX);
  hex += String(h2, HEX);

  return hex;
}

String toHex(int redValue, int greenValue, int blueValue) {
  String fullHex = "#";
  
  fullHex += toHex(redValue);
  fullHex += toHex(greenValue);
  fullHex += toHex(blueValue);

  return fullHex;
}
