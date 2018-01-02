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
  fill_solid_examples(2);
  
  //fill_solid_examples(0);
  //fill_solid_examples(1);
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
      PRINT_BR_1(optionPrefix + "RGB Reset");
      fill_solid_rgb_reset();
      break;
    case 1:
      PRINT_BR_1(optionPrefix + "RGB - red, green, blue");
      fill_solid_rgb(stepper, delay_ms);
      break;
    case 2:
      PRINT_BR_1(optionPrefix + "HSV - hue, saturation, value (brightness)");
      fill_solid_hsv(stepper, delay_ms);
      break;
    
    default: 
      break;
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// fill_solid_rgb_reset()
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_rgb_reset()
{
  fill_solid_rgb_details(0, 0, 0, 0, "Reset");
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_solid_rgb(uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
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
  
  r =   0; g =   0; b =   0; for(r =   0; r < 255; r+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [black  ] [red    ] "); }
  r = 255; g =   0; b =   0; for(g =   0; g < 255; g+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [red    ] [yellow ] "); }
  r = 255; g = 255; b =   0; for(r = 255; r >=  0; r-=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [yellow ] [green  ] "); }
  r =   0; g = 255; b =   0; for(b =   0; b < 255; b+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [green  ] [cyan   ] "); }
  r =   0; g = 255; b = 255; for(g = 255; g >=  0; g-=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [cyan   ] [blue   ] "); }
  r =   0; g =   0; b = 255; for(r =   0; r < 255; r+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [blue   ] [magenta] "); }
  r = 255; g =   0; b = 255; for(g =   0; g < 255; g+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "RGB [magenta] [white  ] "); }
  x = 255;                   for(x = 255; x >=  0; x-=stepper) { fill_solid_rgb_details(delay_ms, x, x, x, "RGB [white  ] [black  ] "); }
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_solid_rgb_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_rgb_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
{  
  String rgb = prefix + String(r) + "." + String(g) + "." + String(b);
  Serial.println(rgb);
  
  fill_solid(_leds, NUM_LEDS, CRGB(r, g, b));
  
  FastLED.show();
  FastLED.delay(delay_ms);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_solid_hsv(uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_hsv(uint8_t stepper, uint8_t delay_ms)
{  
  int16_t h = 0;
  int16_t s = 0;
  int16_t v = 0;
  int16_t x = 0;
  
  /* NOTE easy to overflow, if not careful!
   * uint8_t is 0-255
   * uint16_t is 0-65,535
   */

  // brightness (0 - 255)
  h =   0; s =   0; v =   0; for(v =   v; v < 255; v+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (brightness) [black  ] [white  ] "); } FastLED.delay(1000);

  // saturation (0 - 255)
  h =   0; s =   0; v = 255; for(s =   0; s < 255; s+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (saturation) [white  ] [red    ] "); } FastLED.delay(1000);

  /* hue (0 - 255)
   *   0 - 0°   red primary
   *  85 - 120° green primary
   * 170 - 240° blue primary
   * 255 - 360° red primary (again)
*/
  h =   0; s = 255; v = 250; for(h =   0; h <  85; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (hue) [red    ] [green  ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h =  86; h < 170; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (hue) [green  ] [blue   ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h = 171; h < 255; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (hue) [blue   ] [red    ] "); } FastLED.delay(1000);

  //hsv fade out
  h =   0; s = 255; v = 255; for(s = 255; s >=   0; s-=stepper)     { fill_solid_hsv_details(delay_ms * 10, h, s, v, "HSV (saturation) [red    ] [white  ] "); } FastLED.delay(1000);
  h =   0; s =   0; v = 255; for(v =   v; v >=   0; v-=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "HSV (brightness) [white  ] [black  ] "); } FastLED.delay(1000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_solid_hsv_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_hsv_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
{  
  String rgb = prefix + String(r) + "." + String(g) + "." + String(b);
  Serial.println(rgb);
  
  fill_solid(_leds, NUM_LEDS, CHSV(r, g, b));
  
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
