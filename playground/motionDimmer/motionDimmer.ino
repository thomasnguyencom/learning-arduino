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
// When the dials are facing you
// Left: sensitivity
// Right: time delay

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
int pirState = LOW;            // we start, assuming no motion detected
int val = 0;                   // variable for reading the pin status
String pirStatus = "OFF";

TBlendType    currentBlending;
CRGBPalette16 currentPalette;
String        currentPaletteName;
int           currentPalettePointer = 0;

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

uint8_t stepper = 8;
uint8_t delay_ms = 10;
uint8_t max_bright = 255;
// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup() {
  delay( 3000 ); // power-up safety delay

  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop(){
  boolean showChange = false;
  uint8_t secondHand = (millis() / 1000) % 60;
  uint8_t minuteHand = ((millis() / 1000) / 60) % 60;
  uint8_t hourHand = ((millis() / 1000) / 60 / 60) % 60;
  
// ------------------------------------------------------------------------------------------------------------------------

  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      pirStatus = "ON";
      
      Serial.println("[" + String(secondHand) + "] " + pirStatus);
      fade_light_by(stepper, delay_ms);
      
      showChange = true;
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      pirStatus = "OFF";
      
      Serial.println("[" + String(secondHand) + "] " + pirStatus);
      fade_to_black_by(stepper, delay_ms);
      
      showChange = true;
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
// ------------------------------------------------------------------------------------------------------------------------
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

  if(showChange)
  {
    Serial.println("[" + String(hourHand) + " hour(s), " + String(minuteHand) + " minute(s), " + String(secondHand) + " second(s)] " + pirStatus);
    showChange = false;
  }
  
  //delay(1000);
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// void fade_light_by(uint8_t stepper, uint8_t delay_ms)
// fadeLightBy (CRGB *leds, uint16_t num_leds, uint8_t fadeBy)
// ------------------------------------------------------------------------------------------------------------------------
void fade_light_by(uint8_t stepper, uint8_t delay_ms)
{
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  
  for(uint16_t counter = 0; counter < max_bright; counter+=stepper)
  {
    String output = "fade_light_by: " + String(counter);
    Serial.println(output);
    
    fill_solid(leds, NUM_LEDS, CRGB(counter, counter, counter));
    FastLED.show();
  }

  fill_solid(leds, NUM_LEDS, CRGB(max_bright, max_bright, max_bright));
  FastLED.show();
}

// ------------------------------------------------------------------------------------------------------------------------
// void fade_to_black_by(uint8_t stepper, uint8_t delay_ms)
// fadeToBlackBy (CRGB *leds, uint16_t num_leds, uint8_t fadeBy)
// ------------------------------------------------------------------------------------------------------------------------
void fade_to_black_by(uint8_t stepper, uint8_t delay_ms)
{
  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
  
  for(uint16_t counter = 0; counter < max_bright; counter+=stepper)
  {
    String output = "fadeToBlackBy: " + String(counter);
    Serial.println(output);
    
    fadeToBlackBy(leds, NUM_LEDS, stepper);
    FastLED.show();
  }

  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();
}

//EOL

