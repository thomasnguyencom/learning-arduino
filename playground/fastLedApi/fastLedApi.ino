// ------------------------------------------------------------------------------------------------------------------------
// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/
// ------------------------------------------------------------------------------------------------------------------------
#include <FastLED.h>

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables

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
//#define NUM_LEDS           150 // whole strip
#define NUM_LEDS           105 // whole strip
//#define NUM_LEDS           30 // my mini strips (15 each)
CRGB _leds[NUM_LEDS];
//CRGB _leds[NUM_LEDS];
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
  printHeader(1, "Starting loop");
  
  fill_examples(0); //FILL_RESET
  
  //fill_examples(1); // FILL_SOLID_RGB
  //fill_examples(2); // FILL_SOLID_HSV

  //fill_examples(3); // FILL_RAINBOW_RGB
  //fill_examples(4); // FILL_RAINBOW_HSV
  
  //fill_examples(5); // FILL_GRADIENT_HSV_RANGE
  //fill_examples(6); // FILL_GRADIENT_HSV_DIRECTION_CODE
  //fill_examples(7); // FILL_GRADIENT_HSV_TWO
  //fill_examples(8); // FILL_GRADIENT_HSV_THREE
  //fill_examples(9); // FILL_GRADIENT_HSV_FOUR
  
  fill_examples(10); // FADE_LIGHT_BY
  fill_examples(11); // FADE_TO_BLACK_BY
  
  printHeader(99, "Loop ended");
   FastLED.delay(5000);
}

// ========================================================================================================================
// MODULE SAMPLES
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// fill_solid, fill_rainbow, fill_gradient
// ------------------------------------------------------------------------------------------------------------------------
void fill_examples(uint8_t option)
{
  uint8_t stepper = 16;
  uint8_t delay_ms = 10;
  
  String optionPrefix = "";

  switch(option)
  {
    case 0: //FILL_RESET:
      //printHeader(2, optionPrefix + "Fill Solid RGB Reset");
      fill_solid_rgb_reset(delay_ms);
      break;
    case 1: //FILL_SOLID_RGB:
      printHeader(2, optionPrefix + "Fill Solid RGB - red, green, blue");
      fill_solid_rgb(stepper, delay_ms);
      break;
    case 2: //FILL_SOLID_HSV:
      printHeader(2, optionPrefix + "Fill Solid HSV - hue, saturation, value (brightness)");
      fill_solid_hsv(stepper, delay_ms);
      break;
    case 3: //FILL_RAINBOW_RGB:
      printHeader(2, optionPrefix + "Fill Rainbow RGB");
      fill_rainbow_rgb(stepper, delay_ms);
      break;
    case 4: //FILL_RAINBOW_HSV:
      printHeader(2, optionPrefix + "Fill Rainbow HSV - hue, saturation, value (brightness)");
      fill_rainbow_hsv(stepper, delay_ms);
      break;
    case 5: //FILL_GRADIENT_HSV_RANGE:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv(stepper, delay_ms);
      break;
    case 6: //FILL_GRADIENT_HSV_DIRECTION_CODE:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv_codes(stepper, delay_ms);
      break;
    case 7: //FILL_GRADIENT_HSV_TWO:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv_two(stepper, delay_ms);
      break;
    case 8: //FILL_GRADIENT_HSV_THREE:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv_three(stepper, delay_ms);
      break;
    case 9: //FILL_GRADIENT_HSV_FOUR:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv_four(stepper, delay_ms);
      break;
    case 10: //FADE_LIGHT_BY:
      printHeader(2, optionPrefix + "Fade Light by");
      fade_light_by(stepper, delay_ms);
      break;
    case 11: //FADE_TO_BLACK_BY:
      printHeader(2, optionPrefix + "Fade to Black by");
      fade_to_black_by(stepper, delay_ms);
      break;
    default:
      printHeader(2, optionPrefix + "Unknown - " + option);
      break;
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// fill_solid_rgb_reset(uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_rgb_reset(uint8_t delay_ms)
{
  fill_solid_rgb_details(delay_ms, 0, 0, 0, "Reset");
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
  
  r =   0; g =   0; b =   0; for(r =   0; r < 255; r+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [black  ] [red    ] "); }  FastLED.delay(1000);
  r = 255; g =   0; b =   0; for(g =   0; g < 255; g+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [red    ] [yellow ] "); }
  r = 255; g = 255; b =   0; for(r = 255; r >=  0; r-=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [yellow ] [green  ] "); }  FastLED.delay(1000);
  r =   0; g = 255; b =   0; for(b =   0; b < 255; b+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [green  ] [cyan   ] "); }
  r =   0; g = 255; b = 255; for(g = 255; g >=  0; g-=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [cyan   ] [blue   ] "); }  FastLED.delay(1000);
  r =   0; g =   0; b = 255; for(r =   0; r < 255; r+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [blue   ] [magenta] "); }
  r = 255; g =   0; b = 255; for(g =   0; g < 255; g+=stepper) { fill_solid_rgb_details(delay_ms, r, g, b, "fill_solid(...) RGB [magenta] [white  ] "); }
  x = 255;                   for(x = 255; x >=  0; x-=stepper) { fill_solid_rgb_details(delay_ms, x, x, x, "fill_solid(...) RGB [white  ] [black  ] "); }
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_solid_rgb_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
// ------------------------------------------------------------------------------------------------------------------------
void fill_solid_rgb_details(uint8_t delay_ms, uint8_t r, uint8_t g, uint8_t b, String prefix)
{  
  String rgb = prefix + " " + String(r) + "." + String(g) + "." + String(b);
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
  h =   0; s =   0; v =   0; for(v =   v; v < 255; v+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (brightness) [black : white] "); } FastLED.delay(1000);

  // saturation (0 - 255)
  h =   0; s =   0; v = 255; for(s =   0; s < 255; s+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (saturation) [white : red  ] "); } FastLED.delay(1000);

  /* hue (0 - 255)
   *   0 - 0°   red primary
   *  85 - 120° green primary
   * 170 - 240° blue primary
   * 255 - 360° red primary (again)
*/
  h =   0; s = 255; v = 250; for(h =   0; h <  85; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue       ) [R     : G    ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h =  86; h < 170; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue       ) [G     : B    ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h = 171; h < 255; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue       ) [B     : R    ] "); } FastLED.delay(1000);

  //hsv fade out
  h =   0; s = 255; v = 255; for(s = 255; s >=   0; s-=stepper)    { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (saturation) [red   : white] "); } FastLED.delay(1000);
  h =   0; s =   0; v = 255; for(v =   v; v >=   0; v-=stepper)    { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (brightness) [white : black] "); } FastLED.delay(1000);
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

// ------------------------------------------------------------------------------------------------------------------------
// void fill_rainbow_rgb(uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fill_rainbow_rgb(uint8_t stepper, uint8_t delay_ms)
{
  uint8_t deltahue = 8;
  fill_rainbow(_leds, NUM_LEDS, 0, deltahue);
  
  FastLED.show();
  FastLED.delay(2000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_rainbow_hsv(uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fill_rainbow_hsv(uint8_t stepper, uint8_t delay_ms)
{
  uint8_t deltahue = 16;
  fill_rainbow(_leds, NUM_LEDS, 0, deltahue);
  
  FastLED.show();
  FastLED.delay(2000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms)
// fill_gradient (T *targetArray, 
//   uint16_t startpos, 
//   CHSV startcolor, 
//   uint16_t endpos, 
//   CHSV endcolor, 
//   TGradientDirectionCode directionCode=SHORTEST_HUES)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms)
{
  uint8_t lastLed = NUM_LEDS - 1;

  for(uint8_t pos = 0      ; pos < NUM_LEDS; pos += 1) { fill_gradient_hsv(stepper, delay_ms, 0      , pos, CHSV(HUE_RED  , 255, 255), CHSV(HUE_GREEN, 255, 255), SHORTEST_HUES, "fill_gradient(...) HSV sweep [black : R-G  ] "); }
  for( int8_t pos = lastLed; pos >= 0      ; pos -= 1) { fill_gradient_hsv(stepper, delay_ms, lastLed, pos, CHSV(HUE_GREEN, 255, 255), CHSV(HUE_BLUE , 255, 255), SHORTEST_HUES, "fill_gradient(...) HSV sweep [R-G   : B-G  ] "); }
  for(uint8_t pos = 0      ; pos < NUM_LEDS; pos += 1) { fill_gradient_hsv(stepper, delay_ms, 0      , pos, CHSV(HUE_BLUE , 255, 255), CHSV(HUE_RED  , 255, 255), SHORTEST_HUES, "fill_gradient(...) HSV sweep [B-G   : B-R  ] "); }
  for( int8_t pos = lastLed; pos >= 0      ; pos -= 1) { fill_gradient_hsv(stepper, delay_ms, lastLed, pos, CHSV(HUE_RED  ,   0,   0), CHSV(      0  ,   0,   0), SHORTEST_HUES, "fill_gradient(...) HSV sweep [B-R   : black] "); }
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms, uint16_t startPosition, uint16_t endPosition, CHSV startHue, CHSV endHue, String prefix)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms, uint16_t startPosition, uint16_t endPosition, CHSV startHue, CHSV endHue, TGradientDirectionCode code, String prefix)
{
  //String hues = "Hues (" + String(startHue) + ", " + String(endHue) + ")";
  String range = "Range (" + String(startPosition) + ", " + String(endPosition) + ")";
  String output = prefix + " " + range; // + "  " + hues;
  
  Serial.println(output);
  
  fill_gradient(_leds, startPosition, startHue, endPosition, endHue, code); 
  
  FastLED.show(); 
  FastLED.delay(delay_ms);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv_codes(uint8_t stepper, uint8_t delay_ms)
// fill_gradient (T *targetArray, 
//   uint16_t startpos, 
//   CHSV startcolor, 
//   uint16_t endpos, 
//   CHSV endcolor, 
//   TGradientDirectionCode directionCode=SHORTEST_HUES)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv_codes(uint8_t stepper, uint8_t delay_ms)
{
  // HUE_RED    =   0 
  // HUE_ORANGE =  32  
  // HUE_YELLOW =  64  
  // HUE_GREEN  =  96  
  // HUE_AQUA   = 128  
  // HUE_BLUE   = 160  
  // HUE_PURPLE = 192  
  // HUE_PINK   = 224

  fill_gradient_hsv(stepper, 0,  0,  14, CHSV(HUE_RED, 255, 255), CHSV(HUE_BLUE  , 255, 255), FORWARD_HUES , "fill_gradient(...) HSV forward  [R-O-Y-G-A-B  ] ");
  fill_gradient_hsv(stepper, 0,  15, 29, CHSV(HUE_RED, 255, 255), CHSV(HUE_BLUE  , 255, 255), BACKWARD_HUES, "fill_gradient(...) HSV backward [R-P-P-B      ] ");
  FastLED.delay(3 * 1000);
  
  fill_gradient_hsv(stepper, 0,  0,  14, CHSV(HUE_RED, 255, 255), CHSV(HUE_BLUE  , 255, 255), SHORTEST_HUES , "fill_gradient(...) HSV forward  [R-P-P-B      ] ");
  fill_gradient_hsv(stepper, 0,  15, 29, CHSV(HUE_RED, 255, 255), CHSV(HUE_BLUE  , 255, 255), LONGEST_HUES  , "fill_gradient(...) HSV backward [R-O-Y-G-A-B  ] ");
  FastLED.delay(3 * 1000);

  fill_gradient_hsv(stepper, 0,  0,  14, CHSV(HUE_RED, 255, 255), CHSV( HUE_GREEN, 255, 255), SHORTEST_HUES, "fill_gradient(...) HSV shortest [R-O-Y-G      ] ");
  fill_gradient_hsv(stepper, 0,  15, 29, CHSV(HUE_RED, 255, 255), CHSV( HUE_GREEN, 255, 255), LONGEST_HUES , "fill_gradient(...) HSV longest  [R-P-P-B-A-G  ] ");
  FastLED.delay(3 * 1000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms)
// fill_gradient (T *targetArray, 
//   uint16_t numLeds, 
//   const CHSV &c1, 
//   const CHSV &c2, 
//   TGradientDirectionCode directionCode=SHORTEST_HUES)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv_two(uint8_t stepper, uint8_t delay_ms)
{
  fill_gradient (_leds, NUM_LEDS, CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), SHORTEST_HUES);
  
  FastLED.show();
  FastLED.delay(3 * 1000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv_three(uint8_t stepper, uint8_t delay_ms)
// fill_gradient (T *targetArray, 
//   uint16_t numLeds, 
//   const CHSV &c1, 
//   const CHSV &c2, 
//   const CHSV &c3, 
//   TGradientDirectionCode directionCode=SHORTEST_HUES)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv_three(uint8_t stepper, uint8_t delay_ms)
{
  fill_gradient (_leds, NUM_LEDS, CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), CHSV (HUE_RED, 255, 255), SHORTEST_HUES);
  
  FastLED.show();
  FastLED.delay(3 * 1000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv_four(uint8_t stepper, uint8_t delay_ms)
// fill_gradient (T *targetArray, 
//   uint16_t numLeds, 
//   const CHSV &c1, 
//   const CHSV &c2, 
//   const CHSV &c3, 
//   TGradientDirectionCode directionCode=SHORTEST_HUES)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv_four(uint8_t stepper, uint8_t delay_ms)
{
  fill_gradient (_leds, NUM_LEDS, CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), SHORTEST_HUES);
  
  FastLED.show();
  FastLED.delay(3 * 1000);
}

// ------------------------------------------------------------------------------------------------------------------------
// void fade_light_by(uint8_t stepper, uint8_t delay_ms)
// fadeLightBy (CRGB *leds, uint16_t num_leds, uint8_t fadeBy)
// ------------------------------------------------------------------------------------------------------------------------
void fade_light_by(uint8_t stepper, uint8_t delay_ms)
{
  String output = "Show gradient";
  Serial.println(output);
  
  fill_gradient(_leds, NUM_LEDS, CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), CHSV (HUE_BLUE, 255, 255), CHSV (HUE_RED, 255, 255), SHORTEST_HUES);
  
  FastLED.show();
  FastLED.delay(1000);

  for(uint8_t counter = 0; counter < 255; counter++)
  {
    String output = "fade_light_by: " + String(counter);
    Serial.println(output);
    
    fadeLightBy(_leds, NUM_LEDS, 8);

    FastLED.show();
    FastLED.delay(10);
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// void fade_to_black_by(uint8_t stepper, uint8_t delay_ms)
// fadeToBlackBy (CRGB *leds, uint16_t num_leds, uint8_t fadeBy)
// ------------------------------------------------------------------------------------------------------------------------
void fade_to_black_by(uint8_t stepper, uint8_t delay_ms)
{
  String output = "Show gradient";
  Serial.println(output);
  
  fill_gradient (_leds, NUM_LEDS, CHSV (HUE_RED, 255, 255), CHSV (HUE_GREEN, 255, 255), CHSV (HUE_BLUE, 255, 255), CHSV (HUE_RED, 255, 255), SHORTEST_HUES);
  
  FastLED.show();
  FastLED.delay(1000);

  for(uint8_t counter = 0; counter < 255; counter++)
  {
    String output = "fadeToBlackBy: " + String(counter);
    Serial.println(output);
    
    fadeToBlackBy(_leds, NUM_LEDS, 8);

    FastLED.show();
    FastLED.delay(10);
  }
}

// ========================================================================================================================
// MISC
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// Misc
// ------------------------------------------------------------------------------------------------------------------------
void printHeader(int borderType, String message)
{
  String border;
  switch(borderType)
  {
    case 1:
      border = "=========================================";
      break;
    case 2:
      border = "*****************************************";
      break;
    case 99:
      border = ".........................................";
      break;
    default:
      border = "";
      break;
    
  }
  
  Serial.println("");
  
  if(border == "")
  {
    Serial.println(message);
  }
  else
  {
    Serial.println(border);
    Serial.println(message);
    Serial.println("-----------------------------------------");
  }
}
      
//EOL
