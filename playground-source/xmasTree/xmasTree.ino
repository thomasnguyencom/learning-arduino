// ------------------------------------------------------------------------------------------------------------------------
// http://fastled.io/
// ------------------------------------------------------------------------------------------------------------------------
#include <FastLED.h>

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
TBlendType    currentBlending;
CRGBPalette16 currentPalette;
String        currentPaletteName;

String PALETTE_GLOW      = "Glow";
String PALETTE_CANDYCANE = "Candy Cane";
String PALETTE_COLORFUL  = "Colorful";  
String PALETTE_HOLIDAY   = "Holiday";
String PALETTE_CHASE     = "Chase";
String PALETTE_SPARKLES  = "Sparkles";

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
#define UPDATES_PER_SECOND 10
#define NUM_LEDS           50
#define BRIGHTNESS         64
#define LED_TYPE           WS2811
#define COLOR_ORDER        RGB
CRGB leds[NUM_LEDS];

// Pin assignments
#define LED_PIN            2

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop()
{
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
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
// ChangePalettePeriodically
// ------------------------------------------------------------------------------------------------------------------------
void ChangePalettePeriodically()
{
    uint8_t paletteArrayLength = 6;
    
    unsigned long totalSeconds = millis() / 1000;
    unsigned long seconds = totalSeconds % 60;
    
    unsigned long totalMinutes = ( totalSeconds / 60 );
    unsigned long minutes = totalMinutes % 60;
    
    unsigned long totalHours = ( totalMinutes / 60 );
    
    unsigned long pointer = ( totalMinutes / 15 ) % ( paletteArrayLength);
    
    unsigned long i = 0;
    if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_HOLIDAY); }
    if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_CANDYCANE); }
    if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_COLORFUL); }
    if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_GLOW); }
    if( pointer == i++) { currentBlending = LINEARBLEND; GetPalette(PALETTE_SPARKLES); }
    if( pointer == i++) { currentBlending = LINEARBLEND; GetPalette(PALETTE_CHASE); }
}

// ========================================================================================================================
// PALETTE FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// GetPalette
// ------------------------------------------------------------------------------------------------------------------------
void GetPalette(String paletteName)
{
  if( paletteName == PALETTE_HOLIDAY)
  {  
    SetupHolidayPalette();
  }
  else if( paletteName == PALETTE_SPARKLES)
  {
    SetupSparklesPalette();
  }
  else if( paletteName == PALETTE_CHASE)
  {
    SetupChasePalette();
  }
  else if( paletteName == PALETTE_COLORFUL)
  {
    SetupColorfulPalette();
    return paletteName;
  }
  else if( paletteName == PALETTE_CANDYCANE)
  {
    SetupCandyCanePalette();
  }
  else if( paletteName == PALETTE_GLOW)
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
// SetupHolidayPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupHolidayPalette()
{
  CRGB c_red___ = CHSV( HUE_RED, 255, 255);
  CRGB c_green_ = CHSV( HUE_GREEN, 255, 255);
  
  currentPalette = CRGBPalette16(
    c_red___, c_green_, c_red___, c_green_,
    c_red___, c_green_, c_red___, c_green_,
    c_red___, c_green_, c_red___, c_green_,
    c_red___, c_green_, c_red___, c_green_
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupCandyCanePalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupCandyCanePalette()
{
  CRGB c_red___ = CRGB( 255,   0,   0);
  CRGB c_white_ = CRGB( 255, 255, 255);
  
  currentPalette = CRGBPalette16(
    c_red___, c_red___, c_white_, c_white_,
    c_red___, c_red___, c_white_, c_white_,
    c_red___, c_red___, c_white_, c_white_,
    c_red___, c_red___, c_white_, c_white_
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupColorfulPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupColorfulPalette()
{
  CRGB c_red___ = CHSV( HUE_RED, 255, 255);
  CRGB c_blue__ = CHSV( HUE_BLUE, 255, 255);
  CRGB c_yellow = CHSV( HUE_YELLOW, 255, 255);
  CRGB c_green_ = CHSV( HUE_GREEN, 255, 255);
  CRGB c_orange = CHSV( HUE_ORANGE, 255, 255);
  
  currentPalette = CRGBPalette16(
    c_red___, c_blue__, c_yellow, c_green_,
    c_orange, c_red___, c_blue__, c_yellow,
    c_green_, c_orange, c_red___, c_blue__,
    c_yellow, c_green_, c_red___, c_blue__
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupSparklesPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupSparklesPalette()
{
  CRGB bright = CRGB(255, 255, 0);
  CRGB medium = CRGB(253, 184, 19);
  
  for( int i = 0; i < 16; i++) {
    int val = random8() % 2;
    if(val == 0)
    {
      currentPalette[i] = bright;
    }
    else
    {
      currentPalette[i] = medium;
    }
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupChasePalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupChasePalette()
{
  int r = 0;
  int g = 0;
  int b = 0;
  
  int cnt = 256 / 4;
  
  CRGB c_0 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_1 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_2 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_3 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  
  currentPalette = CRGBPalette16(
    c_3, c_0, c_0, c_0,
    c_0, c_0, c_0, c_0,
    c_1, c_0, c_0, c_0,
    c_0, c_0, c_0, c_0
  );
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
  
  CRGB c_0 = CRGB( 253, 184,  19);
  CRGB c_1 = CRGB( 255, 222,   0);
  CRGB c_9 = CRGB( 255, 255, 255);
  
  currentPalette = CRGBPalette16(
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0
  );
}

//EOL
