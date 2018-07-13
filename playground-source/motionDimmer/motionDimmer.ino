// ------------------------------------------------------------------------------------------------------------------------
// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/
// ------------------------------------------------------------------------------------------------------------------------
#include <FastLED.h>

// ------------------------------------------------------------------------------------------------------------------------
// http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
// ------------------------------------------------------------------------------------------------------------------------
// VCC Power
// OUT inputPin
// GND Ground
// ------------------------------------------------------------------------------------------------------------------------

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
boolean _pirLastStatus = LOW; // start, assuming no motion detected
boolean _pirActualStatus = LOW; // variable for reading the pin status

String PALETTE_GLOW      = "Glow";

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================
// ------------------------------------------------------------------------------------------------------------------------
// INIT : SR501 Sensor
// ------------------------------------------------------------------------------------------------------------------------
int inputPin = 7;               // choose the input pin (for PIR sensor)
// ------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------
// INIT : LED Pin
// ------------------------------------------------------------------------------------------------------------------------
int ledPin = 8;                // choose the pin for the LED

uint8_t ledDelay_ms = 100;
// ------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------
// INIT : WS2812B Multi-Color Strip
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ------------------------------------------------------------------------------------------------------------------------
#define UPDATES_PER_SECOND 100
#define NUM_LEDS           15
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB

// Pin assignments
#define FAST_LED_PIN        9

uint8_t stepper = 1;
uint8_t fastLedDelay_ms = 10;
uint8_t max_bright = 255;

CRGB darkest = CRGB(0, 0, 0);
CRGB brightest = CRGB(max_bright, max_bright, max_bright);
// ------------------------------------------------------------------------------------------------------------------------
  
// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup()
{
  delay( 3000 ); // power-up safety delay

  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
 
  Serial.begin(9600);

  ledBlink(ledDelay_ms);
  ledBlink(ledDelay_ms);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop()
{
  // read sensor
  _pirActualStatus = digitalRead(inputPin);

  // update LED
  digitalWrite(ledPin, _pirActualStatus);

  // update fastLED
  if (_pirActualStatus != _pirLastStatus)
  {
    _pirLastStatus = _pirActualStatus;
    
    Serial.println("[" + convertToTimeStamp(millis()) + "] " + convertPirStatusToMessage(_pirActualStatus));
    
    fade(_pirActualStatus, stepper, fastLedDelay_ms);
  }
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// void fade(boolean type, uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fade(boolean turnOn, uint8_t stepper, uint8_t delay_ms)
{
  CRGB startingPoint = turnOn ? darkest : brightest;
  fill_solid(leds, NUM_LEDS, startingPoint);
 
  for(uint16_t counter = 0; counter < max_bright; counter+=stepper)
  {    
    turnOn ? fill_solid(leds, NUM_LEDS, CRGB(counter, counter, counter)) : fadeToBlackBy(leds, NUM_LEDS, stepper);
    FastLED.show();
    
    delay(delay_ms);
  }

  CRGB endingPoint = turnOn ? brightest : darkest;
  fill_solid(leds, NUM_LEDS, endingPoint);
  FastLED.show();
}

// ------------------------------------------------------------------------------------------------------------------------
// void ledBlink(uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void ledBlink(uint8_t delay_ms)
{
  digitalWrite(ledPin, HIGH);
  delay(delay_ms);
  
  digitalWrite(ledPin, LOW);
  delay(delay_ms);
}

// ------------------------------------------------------------------------------------------------------------------------
// void convertToTimeStamp(long ms)
// ------------------------------------------------------------------------------------------------------------------------
String convertPirStatusToMessage(boolean pirStatus)
{
  return (pirStatus == HIGH) ? "ON" : "OFF";
}

// ------------------------------------------------------------------------------------------------------------------------
// void convertToTimeStamp(long ms)
// ------------------------------------------------------------------------------------------------------------------------
String convertToTimeStamp(long milliseconds)
{
  uint8_t hourHand    = ((milliseconds / 1000) / 60  / 60) % 60;
  uint8_t minuteHand  = ((milliseconds / 1000) / 60) % 60;
  uint8_t secondHand  = ( milliseconds / 1000) % 60;
  uint16_t millisHand = ( milliseconds % 1000);
  
  String hh = String(hourHand) + " hour(s)";
  String mm = String(minuteHand) + " minute(s)";
  String ss = String(secondHand) + " second(s)";
  String ms = String(millisHand) + " milli(s)";
  
  String timeStamp = hh + ", " + mm + ", " + ss + ", " + ms;

  return timeStamp;
}

//EOL

