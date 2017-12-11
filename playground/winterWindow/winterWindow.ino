// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/

#include <FastLED.h>
#include <LiquidCrystal.h>

// ========================================================================================================================
// INIT : WS2812B Multi-Color Stripdf
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ========================================================================================================================
// Configuration
#define UPDATES_PER_SECOND 100
#define NUM_LEDS           150
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB

// Pin assignments
#define FAST_LED_PIN        2

// Global variables
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// ========================================================================================================================
// INIT : LCD1602 LCD Screen
// ------------------------------------------------------------------------------------------------------------------------
// LCD display grid
#define LCD_COLUMNS         16
#define LCD_ROWS            2
// ========================================================================================================================
// Wire configuration
// -[VSS]   Connects to ground                 Powers the LCDs
// -[VDD]   Connects to a +5V power supply     Powers the LCDs
// -[VO]    Connects to a (10k) Potentiometer  Adjusts the contrast of LCD1602
// -[RS]    (see below)                        (LCD_REGISTER_SELECT) A register select pin that controls where in the LCD’s
//                                             memory you are writing data to. You can select either the data register,
//                                             which holds what goes on the screen, or an instruction register, which is 
//                                             where the LCD’s controller looks for instructions on what to do next.
// -[R/W]   Connects to ground                 A Read/Write pin that selects reading mode or writing mode
// -[E]     (see below)                        (LCD_ENABLING_PIN) An enabling pin that, when supplied with low-level energy,
//                                             causes the LDC module to execute relevant instructions.
// -[D0-D7] (see below)                        Pins that read and write data
// -[A]     Connects to a +5V power supply     Powers the LCD backlight
// -[K]     Connects to ground                 Powers the LCD backlight
// ========================================================================================================================
// Pin assignments
#define LCD_REGISTER_SELECT 7
#define LCD_ENABLING_PIN    8
#define LCD_D4              9
#define LCD_D5              10
#define LCD_D6              11
#define LCD_D7              12

LiquidCrystal lcd(LCD_REGISTER_SELECT, LCD_ENABLING_PIN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// ========================================================================================================================
// MAIN : setup
// ========================================================================================================================
void setup()
{
  delay( 3000 ); // power-up safety delay
  
  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  

  // Setup LCD Screen
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
}

// ========================================================================================================================
// MAIN : loop
// ========================================================================================================================
void loop()
{
    String paletteOutput = ChangePalettePeriodically();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    String secondRow = "TEST";
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

String ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    if( lastSecond != secondHand) {
        lastSecond = secondHand;

        uint8_t paletteCounts = 2;
        
        uint8_t i = 0;
        uint8_t tick = 60 / paletteCounts;

        if( secondHand == (i += tick))  { SetupHolidayPalette();                    currentBlending = LINEARBLEND; }  // 1
        if( secondHand == (i += tick))  { SetupHolidayPalette();                    currentBlending = LINEARBLEND; }  // 2
    }

    String linearDisplayName = (currentBlending == LINEARBLEND) ? "L" : "N";
    String blendingDisplayName = GetPaletteDisplayName(currentPalette);
    
    //11 L Rnbw Stripe
    return "" + String(lastSecond) + " " + linearDisplayName + " " + blendingDisplayName;
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

void SetupHolidayPalette()
{
    CRGB c_red___ = CHSV( HUE_RED, 255, 255);
    CRGB c_orange = CHSV( HUE_ORANGE, 255, 255);
    CRGB c_yellow = CHSV( HUE_YELLOW, 255, 255);
    CRGB c_green_ = CHSV( HUE_GREEN, 255, 255);
    CRGB c_blue__ = CHSV( HUE_BLUE, 255, 255);
    
    currentPalette = CRGBPalette16(
      c_red___, c_red___, c_red___, c_red___,
      c_green_, c_green_, c_green_, c_green_,
      c_red___, c_red___, c_red___, c_red___,
      c_green_, c_green_, c_green_, c_green_
    );
}

// ========================================================================================================================
// REFERENCE FUNCTIONS
// ========================================================================================================================

