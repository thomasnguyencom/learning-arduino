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
const String LED_STATE_KEY = "#LED_STATE_KEY#";

int _digitalPin = 0;

int D_0 = 0;
int D_1 = 1;
int D_2 = 2;
int D_3 = 3;
int D_4 = 4;
int D_5 = 5;
int D_6 = 6;
int D_7 = 7;
int D_8 = 8;

int D_9 = 9;
int D_10 = 10;
int D_11 = 11;
int D_12 = 12;
int D_13 = 13;
int D_14 = 14;
int D_15 = 15;

CRGBPalette16 currentPalette;
TBlendType    currentBlending = NOBLEND;
String        currentPaletteName = "PALETTE_SLOWCHASE";
int           currentPalettePointer = 0;

String PALETTE_SLOWCHASE = "Slow Chase";
String PALETTE_RANDOM    = "Random";
String PALETTE_GLOW      = "Glow";
String PALETTE_CANDYCANE = "Candy Cane";
String PALETTE_COLORFUL  = "Colorful";  
String PALETTE_HOLIDAY   = "Holiday";
String PALETTE_CHASE     = "Chase";
String PALETTE_SPARKLES  = "Sparkles";
String PALETTE_AMERICA   = "America";
String PALETTE_ZEBRA     = "Zebra";

// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p
String PALETTE_RAINBOW1  = "RainbowColors"; //RainbowColors_p
String PALETTE_RAINBOW2  = "RainbowStripeColors"; //RainbowStripeColors_p
String PALETTE_OCEAN     = "Ocean"; //OceanColors_p
String PALETTE_CLOUD     = "Cloud"; //CloudColors_p
String PALETTE_LAVA      = "Lava"; //LavaColors_p
String PALETTE_FOREST    = "Forest"; //ForestColors_p
String PALETTE_PARTY     = "Party"; //PartyColors_p

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
#define UPDATES_PER_SECOND 100
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
    GetHtmlPage(0);
  });

  delay(1000);
  
  ConfigureRoutes();
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();

  //leds
  String paletteOutput = PalettePicker();
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;    
  FillLEDsFromPaletteColors( startIndex);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

void GetHtmlPage(int digitalPin){
  _digitalPin = digitalPin;

  SetDigitalPin(digitalPin);

  ConfigureRoutes();

  String d0 = GetButtonTag(D_0, digitalPin);

  String d1 = GetButtonTag(D_1, digitalPin);
  String d2 = GetButtonTag(D_2, digitalPin);
  String d3 = GetButtonTag(D_3, digitalPin);
  String d4 = GetButtonTag(D_4, digitalPin);

  String d5 = GetButtonTag(D_5, digitalPin);
  String d6 = GetButtonTag(D_6, digitalPin);
  String d7 = GetButtonTag(D_7, digitalPin);
  String d8 = GetButtonTag(D_8, digitalPin);

  String d9 = GetButtonTag(D_9, digitalPin);
  String d10 = GetButtonTag(D_10, digitalPin);
  String d11 = GetButtonTag(D_11, digitalPin);
  String d12 = GetButtonTag(D_12, digitalPin);
  String d13 = GetButtonTag(D_13, digitalPin);
  String d14 = GetButtonTag(D_14, digitalPin);
  String d15 = GetButtonTag(D_15, digitalPin);

  String off = "<a href=\"Off\"><button>OFF</button></a>";
  
  String buttons = "<p>" + d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9 + d10 + d11 + d12 + d13 + d14 + d15 + "</p>";
  String css = "<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/mini.css/3.0.1/mini-default.min.css\">";
  String menu = "<a href=\"#\" class=\"logo\">Tom's Magic Lantern</a>";
  
  String headerTags = "<header>" + css + menu + "</header>";
  String bodyTags = "<body>" + buttons + "<p>#LED_STATE_KEY#</p></body>";
  
  String pageTemplate = "<html>" + headerTags + bodyTags + "</html>";

  pageTemplate.replace(LED_STATE_KEY, ConvertToPaletteName(digitalPin));
  String page = pageTemplate;
  
  server.send(200, "text/html", page);
}

String ConvertToPaletteName(int digitalPin) {
  if(digitalPin == D_0) { return PALETTE_SLOWCHASE; }
  
  if(digitalPin == D_1) { return PALETTE_CANDYCANE; }
  if(digitalPin == D_2) { return PALETTE_AMERICA; }
  if(digitalPin == D_3) { return PALETTE_COLORFUL; }
  if(digitalPin == D_4) { return PALETTE_SPARKLES; }
  
  if(digitalPin == D_5) { return PALETTE_HOLIDAY; }
  if(digitalPin == D_6) { return PALETTE_CHASE; }
  if(digitalPin == D_7) { return PALETTE_ZEBRA; }
  if(digitalPin == D_8) { return PALETTE_CHASE; }
  
  if(digitalPin == D_9) { return PALETTE_RAINBOW1; }
  if(digitalPin == D_10) { return PALETTE_RAINBOW2; }
  if(digitalPin == D_11) { return PALETTE_OCEAN; }
  if(digitalPin == D_12) { return PALETTE_CLOUD; }
  if(digitalPin == D_13) { return PALETTE_LAVA; }
  if(digitalPin == D_14) { return PALETTE_FOREST; }
  if(digitalPin == D_15) { return PALETTE_PARTY; }
}

void ConfigureRoutes() {
  server.on(("/" + String(D_0)), [](){ GetHtmlPage(D_0); } );
  server.on(("/" + String(D_1)), [](){ GetHtmlPage(D_1); } );
  server.on(("/" + String(D_2)), [](){ GetHtmlPage(D_2); } );
  server.on(("/" + String(D_3)), [](){ GetHtmlPage(D_3); } );
  server.on(("/" + String(D_4)), [](){ GetHtmlPage(D_4); } );
  server.on(("/" + String(D_5)), [](){ GetHtmlPage(D_5); } );
  server.on(("/" + String(D_6)), [](){ GetHtmlPage(D_6); } );  
  server.on(("/" + String(D_7)), [](){ GetHtmlPage(D_7); } );
  server.on(("/" + String(D_8)), [](){ GetHtmlPage(D_8); } );

  server.on(("/" + String(D_9)), [](){ GetHtmlPage(D_9); } );
  server.on(("/" + String(D_10)), [](){ GetHtmlPage(D_10); } );
  server.on(("/" + String(D_11)), [](){ GetHtmlPage(D_11); } );
  server.on(("/" + String(D_12)), [](){ GetHtmlPage(D_12); } );
  server.on(("/" + String(D_13)), [](){ GetHtmlPage(D_13); } );
  server.on(("/" + String(D_14)), [](){ GetHtmlPage(D_14); } );
  server.on(("/" + String(D_15)), [](){ GetHtmlPage(D_15); } );
}

void SetDigitalPin(int digitalPin) {
  if(digitalPin == D_0) { GetPalette(ConvertToPaletteName(D_0)); Serial.println("Digital " + D_0); }

  
  if(digitalPin == D_1) { GetPalette(ConvertToPaletteName(D_1)); Serial.println("Digital " + D_1); }
  if(digitalPin == D_2) { GetPalette(ConvertToPaletteName(D_2)); Serial.println("Digital " + D_2); }
  if(digitalPin == D_3) { GetPalette(ConvertToPaletteName(D_3)); Serial.println("Digital " + D_3); }
  if(digitalPin == D_4) { GetPalette(ConvertToPaletteName(D_4)); Serial.println("Digital " + D_4); }
  
  if(digitalPin == D_5) { GetPalette(ConvertToPaletteName(D_5)); Serial.println("Digital " + D_5); }
  if(digitalPin == D_6) { GetPalette(ConvertToPaletteName(D_6)); Serial.println("Digital " + D_6); }
  if(digitalPin == D_7) { GetPalette(ConvertToPaletteName(D_7)); Serial.println("Digital " + D_7); }
  if(digitalPin == D_8) { GetPalette(ConvertToPaletteName(D_8)); Serial.println("Digital " + D_8); }
  
  if(digitalPin == D_9) { GetPalette(ConvertToPaletteName(D_9)); Serial.println("Digital " + D_9); }
  if(digitalPin == D_10) { GetPalette(ConvertToPaletteName(D_10)); Serial.println("Digital " + D_10); }
  if(digitalPin == D_11) { GetPalette(ConvertToPaletteName(D_11)); Serial.println("Digital " + D_11); }
  if(digitalPin == D_12) { GetPalette(ConvertToPaletteName(D_12)); Serial.println("Digital " + D_12); }
  if(digitalPin == D_13) { GetPalette(ConvertToPaletteName(D_13)); Serial.println("Digital " + D_13); }
  if(digitalPin == D_14) { GetPalette(ConvertToPaletteName(D_14)); Serial.println("Digital " + D_14); }
  if(digitalPin == D_15) { GetPalette(ConvertToPaletteName(D_15)); Serial.println("Digital " + D_15); }
}

String GetButtonTag(int route, int selectedRoute) {
  String SELECTED_BUTTON_KEY = "#SELECTED_BUTTON_KEY#";
  String text = ConvertToPaletteName(route);

  String buttonTag = "<a href=\"" + String(route) + "\"><button #SELECTED_BUTTON_KEY#>" + text + "</button></a>";
  
  if(selectedRoute == route) { buttonTag.replace(SELECTED_BUTTON_KEY, "class=\"inverse\""); }
  
  return buttonTag;
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
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

// ------------------------------------------------------------------------------------------------------------------------
// PalettePicker
// ------------------------------------------------------------------------------------------------------------------------
String PalettePicker()
{
  GetPalette(currentPaletteName);

  return currentPaletteName;
}

// ------------------------------------------------------------------------------------------------------------------------
// GetPalette
// ------------------------------------------------------------------------------------------------------------------------
String GetPalette(String paletteName)
{
  if( paletteName      == PALETTE_SLOWCHASE)   { SetupSlowChasePalette(); }
  else if( paletteName == PALETTE_HOLIDAY)   { SetupHolidayPalette(); }
  else if( paletteName == PALETTE_SPARKLES)  { SetupSparklesPalette(); }
  else if( paletteName == PALETTE_CHASE)     { SetupChasePalette(); }
  else if( paletteName == PALETTE_COLORFUL)  { SetupColorfulPalette(); }
  else if( paletteName == PALETTE_CANDYCANE) { SetupCandyCanePalette(); }
  else if( paletteName == PALETTE_GLOW)      { SetupGlowPalette(); }
  else if( paletteName == PALETTE_AMERICA)   { SetupAmericaPalette(); }
  else if( paletteName == PALETTE_ZEBRA)     { SetupBlackAndWhiteStripedPalette(); }

  else if( paletteName == PALETTE_RAINBOW1)  { SetupDefaultPalette(PALETTE_RAINBOW1); }
  else if( paletteName == PALETTE_RAINBOW2)  { SetupDefaultPalette(PALETTE_RAINBOW2); }
  else if( paletteName == PALETTE_OCEAN)     { SetupDefaultPalette(PALETTE_OCEAN); }
  else if( paletteName == PALETTE_CLOUD)     { SetupDefaultPalette(PALETTE_CLOUD); }
  else if( paletteName == PALETTE_LAVA)      { SetupDefaultPalette(PALETTE_LAVA); }
  else if( paletteName == PALETTE_FOREST)    { SetupDefaultPalette(PALETTE_FOREST); }
  else if( paletteName == PALETTE_PARTY)     { SetupDefaultPalette(PALETTE_PARTY); }
  
  else if( paletteName == PALETTE_RANDOM)    { SetupTotallyRandomPalette(); }
  else                                       { SetupTotallyRandomPalette(); }

  currentPaletteName = paletteName;

  return currentPaletteName;
}

// ------------------------------------------------------------------------------------------------------------------------
// SetupHolidayPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupHolidayPalette()
{
  currentBlending = NOBLEND;
    
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
  currentBlending = NOBLEND;
  
  CRGB c_red___ = CRGB( 155,   0,   0);
  CRGB c_white_ = CRGB( 100, 100, 100);
  
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
  currentBlending = NOBLEND;
  
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
// SetupColorfulPalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupAmericaPalette()
{
  currentBlending = NOBLEND;
  
  CRGB c_red___ = CRGB( 155,   0,   0);
  CRGB c_white_ = CRGB( 100, 100, 100);
  CRGB c_blue__ = CRGB(   0,   0, 155);
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  currentPalette = CRGBPalette16(
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
  currentBlending = LINEARBLEND;
    
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
  currentBlending = LINEARBLEND;
  
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
// SetupSlowChasePalette
// ------------------------------------------------------------------------------------------------------------------------
void SetupSlowChasePalette()
{
  currentBlending = NOBLEND;
  
  CRGB c_white_ = CRGB( 100, 100, 100);
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  currentPalette = CRGBPalette16(
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
  currentBlending = NOBLEND;
  
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

void SetupDefaultPalette(String defaultPaletteName)
{
  if(defaultPaletteName      == PALETTE_RAINBOW1) { currentPalette = RainbowColors_p; }
  else if(defaultPaletteName == PALETTE_RAINBOW2) { currentPalette = RainbowStripeColors_p; }
  else if(defaultPaletteName == PALETTE_OCEAN)    { currentPalette = OceanColors_p; }
  else if(defaultPaletteName == PALETTE_CLOUD)    { currentPalette = CloudColors_p; }
  else if(defaultPaletteName == PALETTE_LAVA)     { currentPalette = LavaColors_p; }
  else if(defaultPaletteName == PALETTE_FOREST)   { currentPalette = ForestColors_p; }
  else if(defaultPaletteName == PALETTE_PARTY)    { currentPalette = PartyColors_p; }
}

//EOL
