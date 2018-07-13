// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/

#include <FastLED.h>
#include <LiquidCrystal.h>

// ========================================
// WS2812B Multi-Color Stripdf
// ----------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ========================================
#define FAST_LED_PIN   2
#define FAST_LED_PIN_B 3
#define NUM_LEDS       150
#define BRIGHTNESS     64
#define LED_TYPE       WS2812B
#define COLOR_ORDER    GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// ========================================
// LCD1602 LCD Screen
// ----------------------------------------
// Wire configuration
// -[VSS]   Connects to ground                 Powers the LCDs
// -[VDD]   Connects to a +5V power supply     Powers the LCDs
// -[VO]    Connects to a (10k) Potentiometer  Adjusts the contrast of LCD1602
// -[RS]    (see below)                        (LCD_REGISTER_SELECT) A register select pin that controls where in the LCD’s memory you are writing data
//                                             to. You can select either the data register, which holds what goes on the screen, or an
//                                             instruction register, which is where the LCD’s controller looks for instructions on what
//                                             to do next.
// -[R/W]   Connects to ground                 A Read/Write pin that selects reading mode or writing mode
// -[E]     (see below)                        (LCD_ENABLING_PIN) An enabling pin that, when supplied with low-level energy, causes the LDC module
//                                             to execute relevant instructions.
// -[D0-D7] (see below)                        Pins that read and write data
// -[A]     Connects to a +5V power supply     Powers the LCD backlight
// -[K]     Connects to ground                 Powers the LCD backlight
// ========================================
#define LCD_COLUMNS         16
#define LCD_ROWS            2

// Pin assignments
#define LCD_REGISTER_SELECT 7
#define LCD_ENABLING_PIN    8
#define LCD_D4              9
#define LCD_D5              10
#define LCD_D6              11
#define LCD_D7              12

LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLING_PIN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// ========================================
// Generic RGB LED
// ----------------------------------------
// Wire configuration
// [Blue]           (RGB_LED_PIN_B) Add a 220 Ohm resistor   ---|--\
// [Green]          (RGB_LED_PIN_G) Add a 220 Ohm resistor   ---|   \
// [Black/Cathode]  Connects to ground                     -----|   /
// [Red/Anode]      (RGB_LED_PIN_R) Add a 220 Ohm resistor   ---|--/
// ========================================
#define RGB_LED_PIN_B 4
#define RGB_LED_PIN_G 5
#define RGB_LED_PIN_R 6

void setup()
{
  delay( 3000 ); // power-up safety delay
  
  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN_B, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  

  // Setup LCD Screen
  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Setup RGB LED pins
  pinMode(RGB_LED_PIN_R, OUTPUT);
  pinMode(RGB_LED_PIN_G, OUTPUT);
  pinMode(RGB_LED_PIN_B, OUTPUT);  
  digitalWrite(RGB_LED_PIN_R, HIGH);
  digitalWrite(RGB_LED_PIN_G, LOW);
  digitalWrite(RGB_LED_PIN_B, LOW);
}

void loop()
{
    String paletteOutput = ChangePalettePeriodically();

    String rgbLedOutput = ChangeLedRgbPeriodically();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    String secondRow = rgbLedOutput;
    OutputLCD(paletteOutput, secondRow);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

String ChangeLedRgbPeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    String colorName = "";
    
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    
    uint8_t sA = 0;
    uint8_t sB = 85;
    uint8_t sC = 170;
    uint8_t sD = 255;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;

        uint8_t i = 0;
        uint8_t tick = 60 / 16;

        if( secondHand == (i += tick))  { r = sA;  g = sA;  b = sA; colorName = ""; } // 01
        if( secondHand == (i += tick))  { r = sA;  g = sA;  b = sB; colorName = ""; } // 02
        if( secondHand == (i += tick))  { r = sA;  g = sB;  b = sC; colorName = ""; } // 03
        if( secondHand == (i += tick))  { r = sA;  g = sB;  b = sD; colorName = ""; } // 04
        
        if( secondHand == (i += tick))  { r = sB;  g = sC;  b = sA; colorName = ""; } // 05
        if( secondHand == (i += tick))  { r = sB;  g = sC;  b = sB; colorName = ""; } // 06
        if( secondHand == (i += tick))  { r = sB;  g = sD;  b = sC; colorName = ""; } // 07
        if( secondHand == (i += tick))  { r = sB;  g = sD;  b = sD; colorName = ""; } // 08

        if( secondHand == (i += tick))  { r = sC;  g = sA;  b = sA; colorName = ""; } // 09
        if( secondHand == (i += tick))  { r = sC;  g = sA;  b = sB; colorName = ""; } // 10
        if( secondHand == (i += tick))  { r = sC;  g = sB;  b = sC; colorName = ""; } // 11
        if( secondHand == (i += tick))  { r = sC;  g = sB;  b = sD; colorName = ""; } // 12

        if( secondHand == (i += tick))  { r = sD;  g = sC;  b = sA; colorName = ""; } // 13
        if( secondHand == (i += tick))  { r = sD;  g = sC;  b = sB; colorName = ""; } // 14
        if( secondHand == (i += tick))  { r = sD;  g = sD;  b = sC; colorName = ""; } // 15
        if( secondHand == (i += tick))  { r = sD;  g = sD;  b = sD; colorName = ""; } // 16
    }
    
    OutputRGB(r, g, b);

    return String(r) + ":" + String(g) + ":" + String(b);

    //return colorName;
}

String ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;

        uint8_t paletteCounts = 2;
        
        uint8_t i = 0;
        uint8_t tick = 60 / paletteCounts;
        /*
        if( secondHand == (i += tick))  { currentPalette = RainbowColors_p;         currentBlending = NOBLEND; }      // 01
        if( secondHand == (i += tick))  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }  // 02
        if( secondHand == (i += tick))  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;     }  // 03
        if( secondHand == (i += tick))  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }  // 04
        if( secondHand == (i += tick))  { currentPalette = OceanColors_p;           currentBlending = NOBLEND;     }  // 05
        if( secondHand == (i += tick))  { currentPalette = OceanColors_p;           currentBlending = LINEARBLEND; }  // 05
        if( secondHand == (i += tick))  { currentPalette = CloudColors_p;           currentBlending = NOBLEND; }      // 06
        if( secondHand == (i += tick))  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }  // 07
        if( secondHand == (i += tick))  { currentPalette = LavaColors_p;            currentBlending = NOBLEND; }      // 08
        if( secondHand == (i += tick))  { currentPalette = LavaColors_p;            currentBlending = LINEARBLEND; }  // 09
        if( secondHand == (i += tick))  { currentPalette = ForestColors_p;          currentBlending = NOBLEND; }      // 10
        if( secondHand == (i += tick))  { currentPalette = ForestColors_p;          currentBlending = LINEARBLEND; }  // 11
        if( secondHand == (i += tick))  { currentPalette = PartyColors_p;           currentBlending = NOBLEND; }      // 12
        if( secondHand == (i += tick))  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }  // 13
        // ----------------------------------------------------------------------------------------------------------------
        if( secondHand == (i += tick))  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }  // 14
        if( secondHand == (i += tick))  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }  // 15
        if( secondHand == (i += tick))  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND;     }  // 16
        if( secondHand == (i += tick))  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }  // 17
        if( secondHand == (i += tick))  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;     }  // 18
        if( secondHand == (i += tick))  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }  // 19
        */
        
        if( secondHand == (i += tick))  { SetupHolidayPalette();                    currentBlending = LINEARBLEND; }  // 1
        if( secondHand == (i += tick))  { SetupAstrosPalette();                     currentBlending = LINEARBLEND; }  // 2
        
        SetupHolidayPalette();             currentBlending = LINEARBLEND;
        SetupAstrosPalette();             currentBlending = LINEARBLEND;
    }

    String linearDisplayName = (currentBlending == LINEARBLEND) ? "L" : "N";
    String blendingDisplayName = GetPaletteDisplayName(currentPalette);
    
    //11 L Rnbw Stripe
    return "" + String(lastSecond) + " " + linearDisplayName + " " + blendingDisplayName;
}

void OutputRGB(int red, int green, int blue) {
  analogWrite(RGB_LED_PIN_R, red);
  analogWrite(RGB_LED_PIN_G, green);
  analogWrite(RGB_LED_PIN_B, blue);
}

void OutputLCD(String firstRow, String secondRow)
{
  lcd.clear();
  
  lcd.setCursor(0, 0);  
  lcd.print(firstRow);

  lcd.setCursor(0, 1);  
  lcd.print(secondRow);
}

String GetPaletteDisplayName(CRGBPalette16 palette)
{
  String paletteName;
       if(palette == RainbowColors_p)       { paletteName = "Rainbow1"; }
  else if(palette == RainbowStripeColors_p) { paletteName = "Rainbow2"; }
  else if(palette == OceanColors_p)         { paletteName = "Ocean"; }
  else if(palette == CloudColors_p)         { paletteName = "Cloud"; }
  else if(palette == LavaColors_p)          { paletteName = "Lava"; }
  else if(palette == ForestColors_p)        { paletteName = "Forest"; }
  else if(palette == PartyColors_p)         { paletteName = "Party"; }
  else                                      { paletteName = "Custom"; }

  return paletteName;
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
      green,  green,  black, black,
      purple, purple, black, black,
      green,  green,  black, black,
      purple, purple, black, black
    );
}

void SetupHolidayPalette()
{
    CRGB redd = CHSV( HUE_RED, 255, 255);
    CRGB orng = CHSV( HUE_ORANGE, 255, 255);
    CRGB yllw = CHSV( HUE_YELLOW, 255, 255);
    CRGB gren = CHSV( HUE_GREEN, 255, 255);
    CRGB blue = CHSV( HUE_BLUE, 255, 255);
    CRGB prpl  = CHSV( HUE_PURPLE, 255, 255);
    
    CRGB blck  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
      redd, orng, redd, orng,
      redd, yllw, redd, yllw,
      orng, yllw, orng, yllw,
      redd, orng, redd, gren
    );
}

void SetupAstrosPalette()
{
    CRGB redd = CHSV( HUE_RED, 255, 255);
    CRGB orng = CHSV( HUE_ORANGE, 255, 255);
    CRGB yllw = CHSV( HUE_YELLOW, 255, 255);
    CRGB gren = CHSV( HUE_GREEN, 255, 255);
    CRGB blue = CHSV( HUE_BLUE, 255, 255);
    CRGB prpl  = CHSV( HUE_PURPLE, 255, 255);
    
    CRGB blck  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
      orng, orng, orng, blue,
      orng, orng, orng, blue,
      orng, orng, orng, blue,
      orng, orng, orng, blue
    );
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
