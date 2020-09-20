/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can send/receive any data using WidgetTerminal object.

  App project setup:
    Terminal widget attached to Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FastLED.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "oIRYZXmQ-sCl2zPjU_UQfCH1wVldhdia";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "gorideabike";
char pass[] = "tomisthebomb";

// ========================================================================================================================
// <GLOBAL>

// Global variables
CRGBPalette16 _currentPalette;
TBlendType    _currentBlending     = NOBLEND;
String        _currentPaletteName  =  "PALETTE_OFF";
int           _currentPaletteSpeed = 5;

String PALETTE_OFF       = "off";
String PALETTE_DRIP      = "drip";
String PALETTE_RANDOM    = "random";
String PALETTE_GLOW      = "glow";
String PALETTE_CANDYCANE = "candycane";
String PALETTE_COLORFUL  = "colorful";  
String PALETTE_HOLIDAY   = "holiday";
String PALETTE_CHASE     = "chase";
String PALETTE_SPARKLES  = "sparkles";
String PALETTE_AMERICA   = "america";
String PALETTE_ZEBRA     = "zebra";
String PALETTE_RAINBOW1  = "rainbowflow"; //RainbowColors_p
String PALETTE_RAINBOW2  = "rainbow"; //RainbowStripeColors_p
String PALETTE_OCEAN     = "ocean"; //OceanColors_p
String PALETTE_CLOUD     = "cloud"; //CloudColors_p
String PALETTE_LAVA      = "lava"; //LavaColors_p
String PALETTE_FOREST    = "forest"; //ForestColors_p
String PALETTE_PARTY     = "party"; //PartyColors_p

const int _paletteCount = 17;
String _palettes[_paletteCount] = {
  PALETTE_OFF,
  PALETTE_DRIP,
  PALETTE_CANDYCANE,
  PALETTE_AMERICA,
  PALETTE_COLORFUL,
  PALETTE_SPARKLES,
  PALETTE_HOLIDAY,
  PALETTE_CHASE,
  PALETTE_ZEBRA,
  PALETTE_RANDOM,
  PALETTE_RAINBOW1,
  PALETTE_RAINBOW2,
  PALETTE_OCEAN,
  PALETTE_CLOUD,
  PALETTE_LAVA,
  PALETTE_FOREST,
  PALETTE_PARTY  
};

// </GLOBAL>
// ========================================================================================================================

// ========================================================================================================================
// <INITIALIZE HARDWARE>

// ------------------------------------------------------------------------------------------------------------------------
// INIT : WS2811
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
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
#define NUM_LEDS           150 //150
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB

// Pin assignments
#define FAST_LED_PIN        5 //pinMode_1

// </INITIALIZE HARDWARE>
// ========================================================================================================================

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1)
{
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  
  Serial.println("V2 Button value is: " + String(pinValue));
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  
  Serial.println("V3 Slider value is: " + String(pinValue));
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  
  Serial.println("V4 Step value is: " + String(pinValue));

  int paletteId = pinValue % 17;
  _currentPaletteName = _palettes[paletteId];
  Serial.println("Palette: " + String(paletteId) + " (" + _currentPaletteName + ")");
  
  terminal.println(_currentPaletteName);
  //terminal.write(param.getBuffer(), param.getLength());
  terminal.flush();
}

void setup()
{
  // power-up safety delay
  delay(3000);

  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Clear the terminal content
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
}

void loop()
{
  Blynk.run();

  //leds
  SetupPalette(_currentPaletteName);
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;    
  FillLEDsFromPaletteColors(startIndex);
  
  FastLED.show();
  FastLED.delay(ConvertSpeedToDelay(_currentPaletteSpeed));
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

void HandleParameters(String key, String value) {
  if(key == "speed") { _currentPaletteSpeed = value.toInt(); }
}

String GetButtonTag(String paletteName, String selectedPaletteName, int paletteSpeed) {
  String SELECTED_BUTTON_KEY = "#SELECTED_BUTTON_KEY#";

  String buttonTag = "<a href=\"" + paletteName + "?speed=" + String(paletteSpeed) + "\"><button #SELECTED_BUTTON_KEY#>" + paletteName + "</button></a>";
  
  if(selectedPaletteName == paletteName) { buttonTag.replace(SELECTED_BUTTON_KEY, "class=\"inverse\""); }
  
  return buttonTag;
}

String GetSpeedTag(int paletteSpeed, int selectedPaletteSpeed, String paletteName) {
  String SELECTED_SPEED_KEY = "#SELECTED_SPEED_KEY#";
  
  String buttonTag = "<a href=\"" + paletteName + "?speed=" + String(paletteSpeed) + "\"><button #SELECTED_SPEED_KEY#>" + String(paletteSpeed) + "</button></a>";
  
  if(selectedPaletteSpeed == paletteSpeed) { buttonTag.replace(SELECTED_SPEED_KEY, "class=\"inverse\""); }
  
  return buttonTag;
}

int ConvertSpeedToDelay(int paletteSpeed) {
  int delayMilliseconds = 0;
  
  if(_currentPaletteSpeed == 1) { delayMilliseconds = 100; }
  if(_currentPaletteSpeed == 2) { delayMilliseconds = 75; }
  if(_currentPaletteSpeed == 3) { delayMilliseconds = 50; }
  if(_currentPaletteSpeed == 4) { delayMilliseconds = 10; }
  if(_currentPaletteSpeed == 5) { delayMilliseconds = 0; }

  return delayMilliseconds;
}

// ========================================================================================================================
// PALETTE FUNCTIONS
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// FillLEDsFromPaletteColors
// ------------------------------------------------------------------------------------------------------------------------
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( _currentPalette, colorIndex, brightness, _currentBlending);
    colorIndex += 3;
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupPalette(String paletteName)
{
  if(      paletteName == PALETTE_OFF)       { SetupOffPalette(); }
  else if( paletteName == PALETTE_AMERICA)   { SetupAmericaPalette(); }
  else if( paletteName == PALETTE_CANDYCANE) { SetupCandyCanePalette(); }
  else if( paletteName == PALETTE_CHASE)     { SetupChasePalette(); }
  else if( paletteName == PALETTE_CLOUD)     { SetupDefaultPalette(PALETTE_CLOUD); }
  else if( paletteName == PALETTE_COLORFUL)  { SetupColorfulPalette(); }
  else if( paletteName == PALETTE_FOREST)    { SetupDefaultPalette(PALETTE_FOREST); }
  else if( paletteName == PALETTE_GLOW)      { SetupGlowPalette(); }
  else if( paletteName == PALETTE_HOLIDAY)   { SetupHolidayPalette(); }
  else if( paletteName == PALETTE_LAVA)      { SetupDefaultPalette(PALETTE_LAVA); }
  else if( paletteName == PALETTE_OCEAN)     { SetupDefaultPalette(PALETTE_OCEAN); }
  else if( paletteName == PALETTE_PARTY)     { SetupDefaultPalette(PALETTE_PARTY); }
  else if( paletteName == PALETTE_RAINBOW1)  { SetupDefaultPalette(PALETTE_RAINBOW1); }
  else if( paletteName == PALETTE_RAINBOW2)  { SetupDefaultPalette(PALETTE_RAINBOW2); }
  else if( paletteName == PALETTE_RANDOM)    { SetupTotallyRandomPalette(); }
  else if( paletteName == PALETTE_DRIP)      { SetupSlowChasePalette(); }
  else if( paletteName == PALETTE_SPARKLES)  { SetupSparklesPalette(); }
  else if( paletteName == PALETTE_ZEBRA)     { SetupBlackAndWhiteStripedPalette(); }  
  else                                       { SetupSlowChasePalette(); }
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupOffPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupOffPalette()
{
  _currentBlending = NOBLEND;
  
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  _currentPalette = CRGBPalette16(
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupHolidayPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupHolidayPalette()
{
  _currentBlending = NOBLEND;
    
  CRGB c_red___ = CHSV( HUE_RED, 255, 255);
  CRGB c_green_ = CHSV( HUE_GREEN, 255, 255);
  
  _currentPalette = CRGBPalette16(
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
  _currentBlending = NOBLEND;
  
  CRGB c_red___ = CRGB( 155,   0,   0);
  CRGB c_white_ = CRGB( 100, 100, 100);
  
  _currentPalette = CRGBPalette16(
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
  _currentBlending = NOBLEND;
  
  CRGB c_red___ = CHSV( HUE_RED, 255, 255);
  CRGB c_blue__ = CHSV( HUE_BLUE, 255, 255);
  CRGB c_yellow = CHSV( HUE_YELLOW, 255, 255);
  CRGB c_green_ = CHSV( HUE_GREEN, 255, 255);
  CRGB c_orange = CHSV( HUE_ORANGE, 255, 255);
  
  _currentPalette = CRGBPalette16(
    c_red___, c_blue__, c_yellow, c_green_,
    c_orange, c_red___, c_blue__, c_yellow,
    c_green_, c_orange, c_red___, c_blue__,
    c_yellow, c_green_, c_red___, c_blue__
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupColorfulPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupAmericaPalette()
{
  _currentBlending = NOBLEND;
  
  CRGB c_red___ = CRGB( 155,   0,   0);
  CRGB c_white_ = CRGB( 100, 100, 100);
  CRGB c_blue__ = CRGB(   0,   0, 155);
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  _currentPalette = CRGBPalette16(
    c_red___, c_white_, c_blue__, c_black_,
    c_red___, c_white_, c_blue__, c_black_,
    c_red___, c_white_, c_blue__, c_black_,
    c_red___, c_white_, c_blue__, c_black_
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupSparklesPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupSparklesPalette()
{
  _currentBlending = LINEARBLEND;
    
  CRGB bright = CRGB(105, 105, 105);
  CRGB medium = CRGB( 25,  25,  25);
  
  for( int i = 0; i < 16; i++) {
    int val = random8() % 2;
    if(val == 0)
    {
      _currentPalette[i] = bright;
    }
    else
    {
      _currentPalette[i] = medium;
    }
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupChasePalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupChasePalette()
{
  _currentBlending = LINEARBLEND;
  
  int r = 0;
  int g = 0;
  int b = 0;
  
  int cnt = 256 / 4;
  
  CRGB c_0 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_1 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_2 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  CRGB c_3 = CRGB( r, g, b); r = r + cnt - 1; g = g + cnt - 1; b = b + cnt - 1;
  
  _currentPalette = CRGBPalette16(
    c_3, c_0, c_0, c_0,
    c_0, c_0, c_0, c_0,
    c_1, c_0, c_0, c_0,
    c_0, c_0, c_0, c_0
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupSlowChasePalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupSlowChasePalette()
{
  _currentBlending = NOBLEND;
  
  CRGB c_white_ = CRGB( 100, 100, 100);
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  _currentPalette = CRGBPalette16(
    c_white_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_
  );
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupGlowPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupGlowPalette()
{
  _currentBlending = NOBLEND;
  
  int r = 0;
  int g = 0;
  int b = 0;
  
  int cnt = 256 / 4;
  
  CRGB c_0 = CRGB( 253, 184,  19);
  CRGB c_1 = CRGB( 255, 222,   0);
  CRGB c_9 = CRGB( 255, 255, 255);
  
  _currentPalette = CRGBPalette16(
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0,
    c_1, c_0, c_1, c_0
  );
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        _currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( _currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    _currentPalette[0] = CRGB::White;
    _currentPalette[4] = CRGB::White;
    _currentPalette[8] = CRGB::White;
    _currentPalette[12] = CRGB::White;
    
}

void SetupDefaultPalette(String defaultPaletteName)
{
  if(defaultPaletteName      == PALETTE_RAINBOW1) { _currentPalette = RainbowColors_p; }
  else if(defaultPaletteName == PALETTE_RAINBOW2) { _currentPalette = RainbowStripeColors_p; }
  else if(defaultPaletteName == PALETTE_OCEAN)    { _currentPalette = OceanColors_p; }
  else if(defaultPaletteName == PALETTE_CLOUD)    { _currentPalette = CloudColors_p; }
  else if(defaultPaletteName == PALETTE_LAVA)     { _currentPalette = LavaColors_p; }
  else if(defaultPaletteName == PALETTE_FOREST)   { _currentPalette = ForestColors_p; }
  else if(defaultPaletteName == PALETTE_PARTY)    { _currentPalette = PartyColors_p; }
}

//EOL
