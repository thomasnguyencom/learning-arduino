// https://www.teachmemicro.com/simple-nodemcu-web-server/
// SETUP/INSTALLATION:
// Add boards to IDE: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Install Boards Manager - ESP8266
// Reference NodeMCU 1.0 ESP-12E
/*
pinMode_1 = 5;
pinMode_2 = 4;
pinMode_3 = 0;
pinMode_4 = 2;
pinMode_5 = 14;
pinMode_6 = 12;
pinMode_7 = 13;
pinMode_8 = 15;
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

// Network contants
const char* ssid = "gorideabike";
const char* password = "tomisthebomb";

//instantiate server at port 80 (http port)
ESP8266WebServer server(80);

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
CRGBPalette16 _currentPalette;
TBlendType    _currentBlending     = NOBLEND;
String        _currentPaletteName  = "PALETTE_OFF";
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

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================

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

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup(void){
  // power-up safety delay
  delay(3000);

  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  // Start connection
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", [](){
    GetHtmlPage(_currentPaletteName);
  });

  delay(1000);
  
  ConfigureRoutes();
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();

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

void ConfigureRoutes() {
  /*for(int i = 0; i <= _paletteCount; i++) {
    String paletteName = _palettes[i];
    server.on(("/" + paletteName), [](){ GetHtmlPage(paletteName); } );
  }*/

  server.on(("/" + _palettes[0]), [](){ GetHtmlPage(_palettes[0]); } );
  server.on(("/" + _palettes[1]), [](){ GetHtmlPage(_palettes[1]); } );
  server.on(("/" + _palettes[2]), [](){ GetHtmlPage(_palettes[2]); } );
  server.on(("/" + _palettes[3]), [](){ GetHtmlPage(_palettes[3]); } );
  server.on(("/" + _palettes[4]), [](){ GetHtmlPage(_palettes[4]); } );
  server.on(("/" + _palettes[5]), [](){ GetHtmlPage(_palettes[5]); } );
  server.on(("/" + _palettes[6]), [](){ GetHtmlPage(_palettes[6]); } );
  server.on(("/" + _palettes[7]), [](){ GetHtmlPage(_palettes[7]); } );
  server.on(("/" + _palettes[8]), [](){ GetHtmlPage(_palettes[8]); } );
  server.on(("/" + _palettes[9]), [](){ GetHtmlPage(_palettes[9]); } );
  server.on(("/" + _palettes[10]), [](){ GetHtmlPage(_palettes[10]); } );
  server.on(("/" + _palettes[11]), [](){ GetHtmlPage(_palettes[11]); } );
  server.on(("/" + _palettes[12]), [](){ GetHtmlPage(_palettes[12]); } );
  server.on(("/" + _palettes[13]), [](){ GetHtmlPage(_palettes[13]); } );
  server.on(("/" + _palettes[14]), [](){ GetHtmlPage(_palettes[14]); } );
  server.on(("/" + _palettes[15]), [](){ GetHtmlPage(_palettes[15]); } );
  server.on(("/" + _palettes[16]), [](){ GetHtmlPage(_palettes[16]); } );
}

void GetHtmlPage(String paletteName){
  _currentPaletteName = paletteName;

  ConfigureRoutes();

  Serial.println("~/:" + paletteName);
  SetupPalette(paletteName);

  for (int i = 0; i < server.args(); i++) {
    String key = server.argName(i);
    String value = server.arg(i);

    String message = "parameter[" + String(i) + "] –> " + key + ": " + value;
    Serial.println(message);

    HandleParameters(key, value);
  }

  int paletteSpeed = _currentPaletteSpeed;

  String paletteButtons = "";
  for(int i = 0; i <= _paletteCount; i++) {
    paletteButtons += GetButtonTag(_palettes[i], paletteName, paletteSpeed);
  }

  String speedButtons = "";
  for(int i = 1; i <= 5; i++) {
    speedButtons += GetSpeedTag(i, paletteSpeed, paletteName);
  }

  String css = "<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/mini.css/3.0.1/mini-default.min.css\" />";
  String menu = "<a href=\"#\" class=\"logo\">Tom's Magic Lantern</a>";
  String headerTags = "<header>" + css + menu + "</header>";

  String paletteRegion = "<p>" + paletteButtons + "</p>";
  String speedRegion = "<p>" + speedButtons + "</p>";

  String bodyTags = "<body>" + paletteRegion + speedRegion + " </body>";

  String page = "<html>" + headerTags + bodyTags + "</html>";

  server.send(200, "text/html", page);
}

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
