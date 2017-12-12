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
TBlendType    currentBlending;
CRGBPalette16 currentPalette;
String        currentPaletteName;
int           currentPalettePointer = 0;

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
#define UPDATES_PER_SECOND 100
#define NUM_LEDS           150
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB

// Pin assignments
#define FAST_LED_PIN        2

// ------------------------------------------------------------------------------------------------------------------------
// INIT : LCD1602 LCD Screen
// ------------------------------------------------------------------------------------------------------------------------
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
// ------------------------------------------------------------------------------------------------------------------------
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
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  // Setup LCD Screen
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop()
{
  String paletteOutput = PalettePicker();
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;    
  FillLEDsFromPaletteColors( startIndex);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  
  String secondRow = "TEST";
  OutputLCD(paletteOutput, secondRow);
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
String PalettePicker()
{
  uint8_t paletteArrayLength = 6;
  
  unsigned long totalSeconds = millis() / 1000;
  unsigned long seconds = totalSeconds % 60;
  
  unsigned long totalMinutes = ( totalSeconds / 60 );
  unsigned long minutes = totalMinutes % 60;
  
  unsigned long totalHours = ( totalMinutes / 60 );
  
  unsigned long pointer = ( totalMinutes / 15 ) % ( paletteArrayLength);
  
  unsigned long i = 0;
  if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_CANDYCANE); }
  if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_GLOW); }
  if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_COLORFUL); }
  if( pointer == i++) { currentBlending = LINEARBLEND; GetPalette(PALETTE_SPARKLES); }
  if( pointer == i++) { currentBlending = NOBLEND;     GetPalette(PALETTE_HOLIDAY); }
  if( pointer == i++) { currentBlending = LINEARBLEND; GetPalette(PALETTE_CHASE); }

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

// ------------------------------------------------------------------------------------------------------------------------
// OutputLCD
// ------------------------------------------------------------------------------------------------------------------------
void OutputLCD(String firstRow, String secondRow)
{
  lcd.clear();
  
  lcd.setCursor(0, 0);  
  lcd.print(firstRow);
  
  lcd.setCursor(0, 1);  
  lcd.print(secondRow);
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
    c_red___, c_red___, c_red___, c_red___,
    c_green_, c_green_, c_green_, c_green_,
    c_red___, c_red___, c_red___, c_red___,
    c_green_, c_green_, c_green_, c_green_
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
    c_red___, c_red___, c_red___, c_red___,
    c_white_, c_white_, c_white_, c_white_,
    c_red___, c_red___, c_red___, c_red___,
    c_white_, c_white_, c_white_, c_white_
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
