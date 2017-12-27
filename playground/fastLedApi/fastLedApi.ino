// ------------------------------------------------------------------------------------------------------------------------
// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/
// ------------------------------------------------------------------------------------------------------------------------
#include <FastLED.h>
#include <LiquidCrystal.h>

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
String LINEBREAK_1 = "=============================================================================";
String LINEBREAK_2 = "-----------------------------------------------------------------------------";

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// INIT : WS2812B Multi-Color Strip
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ------------------------------------------------------------------------------------------------------------------------
#define NUM_LEDS           150
CRGB _leds[NUM_LEDS];
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
void setup()
{
  delay( 3000 ); // power-up safety delay
  
  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  //Serial
  Serial.begin(9600);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop()
{
  fill_solid_examples(0);

  while(true) {
    fill_solid_examples(1);
  }
}

// ========================================================================================================================
// MODULE SAMPLES
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// fill_solid (struct CRGB *leds, int numToFill, const struct CRGB &color)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_examples(uint8_t option)
{
  uint8_t stepper = 16;
  uint8_t delay_ms = 10;
  
  String optionPrefix = "Starting fill_solid - ";
  
  switch(option)
  {
    case 0:
      PRINT_BR_1(optionPrefix + "Reset");
      fill_solid_reset();
      break;
    case 1:
      PRINT_BR_1(optionPrefix + "RGB");
      fill_solid_rgb(stepper, delay_ms);
      break;
    
    default: 
      break;
  }
}

void fill_solid_reset()
{
  fill_solid_easy(0, 0, 0, 0, "Reset");
}

void fill_solid_rgb(uint8_t stepper, uint8_t delay_ms)
{  
  int16_t r = 0;
  int16_t g = 0;
  int16_t b = 0;
  int16_t x = 0;
  
  /* NOTE easy to overflow, if not careful!
   * uint8_t is 0-255
   * uint16_t is 0-65,535
   */
  
  r =   0; g =   0; b =   0; for(r =   0; r < 255; r+=stepper) { fill_solid_easy(delay_ms, r, g, b, "[black  ] [red    ] "); }
  r = 255; g =   0; b =   0; for(g =   0; g < 255; g+=stepper) { fill_solid_easy(delay_ms, r, g, b, "[red    ] [yellow ] "); }
  r = 255; g = 255; b =   0; for(r = 255; r >=  0; r-=stepper) { fill_solid_easy(delay_ms, r, g, b, "[yellow ] [green  ] "); }
  r =   0; g = 255; b =   0; for(b =   0; b < 255; b+=stepper) { fill_solid_easy(delay_ms, r, g, b, "[green  ] [cyan   ] "); }
  r =   0; g = 255; b = 255; for(g = 255; g >=  0; g-=stepper) { fill_solid_easy(delay_ms, r, g, b, "[cyan   ] [blue   ] "); }
  r =   0; g =   0; b = 255; for(r =   0; r < 255; r+=stepper) { fill_solid_easy(delay_ms, r, g, b, "[blue   ] [magenta] "); }
  r = 255; g =   0; b = 255; for(g =   0; g < 255; g+=stepper) { fill_solid_easy(delay_ms, r, g, b, "[magenta] [white  ] "); }
  x = 255;                   for(x = 255; x >=  0; x-=stepper) { fill_solid_easy(delay_ms, x, x, x, "[white  ] [black  ] "); }
}

void fill_solid_easy(uint8_t d, uint8_t r, uint8_t g, uint8_t b)
{
  fill_solid_easy(r, g, b, "");
}

void fill_solid_easy(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
{  
  String rgb = prefix + String(r) + "." + String(g) + "." + String(b);
  Serial.println(rgb);
  
  fill_solid(_leds, NUM_LEDS, CRGB(r, g, b));
  
  FastLED.show();
  FastLED.delay(delay_ms);
}

// ========================================================================================================================
// MISC
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// Misc
// ------------------------------------------------------------------------------------------------------------------------
void PRINT_BR_1(String message)
{
  Serial.println(LINEBREAK_1);
  Serial.println(message);
  Serial.println(LINEBREAK_1);
}

void PRINT_BR_2(String message)
{
  Serial.println(LINEBREAK_2);
  Serial.println(message);
  Serial.println(LINEBREAK_2);
}
      
//EOL
