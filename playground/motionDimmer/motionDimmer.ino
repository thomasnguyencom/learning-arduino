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
int ledPin = 8;                // choose the pin for the LED
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
// INIT : WS2812B Multi-Color Strip
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ------------------------------------------------------------------------------------------------------------------------
#define UPDATES_PER_SECOND 100
#define NUM_LEDS           150
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB

// Pin assignments
#define FAST_LED_PIN        2

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
  
  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop(){
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirStatus = "ON";
      
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirStatus = "OFF";
      
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

// ------------------------------------------------------------------------------------------------------------------------

  String paletteOutput = PalettePicker(val);
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;    
  FillLEDsFromPaletteColors( startIndex);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

// ------------------------------------------------------------------------------------------------------------------------

  uint8_t secondHand = (millis() / 1000) % 60;
  uint8_t minuteHand = ((millis() / 1000) % 60) % 60;
  
  Serial.println("[" + String(minuteHand) + ":" + String(secondHand) + "] " + pirStatus);
  
  //delay(1000);
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// FillLEDsFromPaletteColors
// ------------------------------------------------------------------------------------------------------------------------
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// PalettePicker
// ------------------------------------------------------------------------------------------------------------------------
String PalettePicker(boolean stat)
{
  uint8_t paletteArrayLength = 6;
  
  unsigned long totalSeconds = millis() / 1000;
  unsigned long seconds = totalSeconds % 60;
  
  unsigned long totalMinutes = ( totalSeconds / 60 );
  unsigned long minutes = totalMinutes % 60;
  
  unsigned long totalHours = ( totalMinutes / 60 );
  
  unsigned long pointer = ( totalMinutes / 15 ) % ( paletteArrayLength);
  
  unsigned long i = 0;
  if( pointer == i++) { currentBlending = LINEARBLEND; GetPalette(PALETTE_GLOW); }

  String displayHours = "";
  if(totalHours < 10)
  {
    displayHours = "0" + String(totalHours);
  }
  else
  {
    displayHours = String(totalHours);
  }
  
  String displayMinutes = "";
  if(minutes < 10)
  {
    displayMinutes = "0" + String(minutes);
  }
  else
  {
    displayMinutes = String(minutes);
  }
  
  String displaySeconds = "";
  if(seconds < 10)
  {
    displaySeconds = "0" + String(seconds);
  }
  else
  {
    displaySeconds = String(seconds);
  }

  String displayTime = displayHours + ":" + displayMinutes + ":" + displaySeconds;
  String displayPalette = String(pointer + 1) + "-" + currentPaletteName;
  
  return displayTime + " " + displayPalette;
}

// ========================================================================================================================
// PALETTE FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// GetPalette
// ------------------------------------------------------------------------------------------------------------------------
void GetPalette(String paletteName)
{
  if( paletteName == PALETTE_GLOW)
  {
    SetupGlowPalette();
  }
  else
  {
    paletteName = "UNKNOWN";
  }

  currentPaletteName = paletteName;
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupGlowPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupGlowPalette()
{
  int r = 0;
  int g = 0;
  int b = 0;
  
  int cnt = 256 / 4;
  
  CRGB c_0 = CRGB(   0,   0,   0); //
  CRGB c_1 = CRGB(  50,  50,  50); //
  CRGB c_9 = CRGB(  25,  25,  25); //
  
  currentPalette = CRGBPalette16(
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0
  );
}

//EOL

