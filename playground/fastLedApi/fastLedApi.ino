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
//#define NUM_LEDS           150 / (10) // whole strip
#define NUM_LEDS           30 // my mini strips (15 each)
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
  
  //fill_examples(5); // FILL_GRADIENT_RGB
  fill_examples(6); // FILL_GRADIENT_HSV
  
  printHeader(99, "Loop ended");
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
    case 5: //FILL_GRADIENT_RGB:
      printHeader(2, optionPrefix + "Fill Gradient RGB");
      //fill_gradient_rgb(stepper, delay_ms);
      break;
    case 6: //FILL_GRADIENT_HSV:
      printHeader(2, optionPrefix + "Fill Gradient HSV - hue, saturation, value (brightness)");
      fill_gradient_hsv(stepper, delay_ms);
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
  h =   0; s =   0; v =   0; for(v =   v; v < 255; v+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (brightness) [black  ] [white  ] "); } FastLED.delay(1000);

  // saturation (0 - 255)
  h =   0; s =   0; v = 255; for(s =   0; s < 255; s+=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (saturation) [white  ] [red    ] "); } FastLED.delay(1000);

  /* hue (0 - 255)
   *   0 - 0°   red primary
   *  85 - 120° green primary
   * 170 - 240° blue primary
   * 255 - 360° red primary (again)
*/
  h =   0; s = 255; v = 250; for(h =   0; h <  85; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue) [red    ] [green  ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h =  86; h < 170; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue) [green  ] [blue   ] "); } FastLED.delay(1000);
  h =   0; s = 255; v = 250; for(h = 171; h < 255; h+=(stepper/2)) { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (hue) [blue   ] [red    ] "); } FastLED.delay(1000);

  //hsv fade out
  h =   0; s = 255; v = 255; for(s = 255; s >=   0; s-=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (saturation) [red    ] [white  ] "); } FastLED.delay(1000);
  h =   0; s =   0; v = 255; for(v =   v; v >=   0; v-=stepper)     { fill_solid_hsv_details(delay_ms, h, s, v, "fill_solid(...) HSV (brightness) [white  ] [black  ] "); } FastLED.delay(1000);
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

// ************

// ------------------------------------------------------------------------------------------------------------------------
// void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms)
// ------------------------------------------------------------------------------------------------------------------------
void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms)
{
  uint8_t deltahue = 8;
  /* fill_gradient (
        T *targetArray, 
        uint16_t startpos, 
        CHSV startcolor, 
        uint16_t endpos, 
        CHSV endcolor, 
        TGradientDirectionCode directionCode=SHORTEST_HUES) FORWARD_HUES, BACKWARD_HUES, SHORTEST_HUES, LONGEST_HUES */

  uint8_t startPosition = 0;
  uint8_t endPosition = 0;

  //startPosition = 0;               endPosition = startPosition + 3; fill_gradient_hsv(stepper, delay_ms, startPosition,   0, endPosition,  85, "Rainbow 1/3 - ");
  //startPosition = endPosition + 2; endPosition = startPosition + 3; fill_gradient_hsv(stepper, delay_ms, startPosition,  86, endPosition, 170, "Rainbow 2/3 - ");
  //startPosition = endPosition + 2; endPosition = startPosition + 3; fill_gradient_hsv(stepper, delay_ms, startPosition, 171, endPosition, 255, "Rainbow 3/3 - ");

  fill_examples(0); //FILL_RESET
  for(uint8_t pos =              0; pos < NUM_LEDS; pos += 1) { fill_gradient_hsv(stepper, delay_ms,               0, CHSV(  0, 255, 255), pos, CHSV( 85, 255, 255), "Expand - (red - green)"); }
  for( int8_t pos = (NUM_LEDS - 1); pos >= 0      ; pos -= 1) { fill_gradient_hsv(stepper, delay_ms,  (NUM_LEDS - 1), CHSV( 86, 255, 255), pos, CHSV(170, 255, 255), "Expand - (green - blue)"); }
  for(uint8_t pos =              0; pos < NUM_LEDS; pos += 1) { fill_gradient_hsv(stepper, delay_ms,               0, CHSV(171, 255, 255), pos, CHSV(255, 255, 255), "Expand - (blue - red)"); }
  for( int8_t pos = (NUM_LEDS - 1); pos >= 0      ; pos -= 1) { fill_gradient_hsv(stepper, delay_ms,  (NUM_LEDS - 1), CHSV(  0,   0,   0), pos, CHSV(  0,   0,   0), "Expand - (red - black)"); }
  

  fill_examples(0); //FILL_RESET
}

void fill_gradient_hsv(uint8_t stepper, uint8_t delay_ms, uint16_t startPosition, CHSV startHue, uint16_t endPosition, CHSV endHue, String prefix)
{
  //String hues = "Hues (" + String(startHue) + ", " + String(endHue) + ")";
  String range = "Range (" + String(startPosition) + ", " + String(endPosition) + ")";
  String output = prefix + " " + range; // + "  " + hues;
  
  Serial.println(output);
  
  fill_gradient(_leds, startPosition, startHue, endPosition, endHue, SHORTEST_HUES); 
  
  FastLED.show(); 
  FastLED.delay(delay_ms);
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
      border = "=====-=====-=====-=====-=====-=====-=====";
      break;
    case 2:
      border = "-----.-----.-----.-----.-----.-----.-----";
      break;
    case 99:
      border = ".....-.....-.....-.....-.....-.....-.....";
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
