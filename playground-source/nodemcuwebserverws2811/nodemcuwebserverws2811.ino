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

CRGBPalette16 currentPalette;
TBlendType    currentBlending = NOBLEND;
String        currentPaletteName = "PALETTE_COLORFUL";
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

  String d_1 = d1 + d2 + d3 + d4;
  String d_2 = d5 + d6 + d7 + d8;

  String off = "<a href=\"Off\"><button>OFF</button></a>";
  
  String s = "<p>" + d0 + "</p><p>" + d_1 + "</p><p>" + d_2 + "</p>";

  String headerTags = "<header><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/mini.css/3.0.1/mini-default.min.css\"></header>";
  
  String pageTemplate = "<html>" + headerTags + "<body><h1>Tom's Magic Lantern</h1>" + s + "<p>#LED_STATE_KEY#</p></body></html>";

  pageTemplate.replace(LED_STATE_KEY, String(digitalPin));
  String page = pageTemplate;
  
  server.send(200, "text/html", page);
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
}

void SetDigitalPin(int digitalPin) {  
  if(digitalPin == D_1) { GetPalette(PALETTE_CANDYCANE); Serial.println("Digital 1"); }
  if(digitalPin == D_2) { GetPalette(PALETTE_GLOW);      Serial.println("Digital 2"); }
  if(digitalPin == D_3) { GetPalette(PALETTE_COLORFUL);  Serial.println("Digital 3"); }
  if(digitalPin == D_4) { GetPalette(PALETTE_SPARKLES);  Serial.println("Digital 4"); }
  
  if(digitalPin == D_5) { GetPalette(PALETTE_HOLIDAY);   Serial.println("Digital 5"); }
  if(digitalPin == D_6) { GetPalette(PALETTE_CHASE);     Serial.println("Digital 6"); }
  if(digitalPin == D_7) { GetPalette(PALETTE_CHASE);     Serial.println("Digital 7"); }
  if(digitalPin == D_8) { GetPalette(PALETTE_CHASE);     Serial.println("Digital 8"); }
}

String GetButtonTag(int route, int selectedRoute) {
  String SELECTED_BUTTON_KEY = "#SELECTED_BUTTON_KEY#";
  String text = "LED " + String(route);

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
  if( paletteName == PALETTE_HOLIDAY)
  {  
    currentBlending = NOBLEND;
    SetupHolidayPalette();
  }
  else if( paletteName == PALETTE_SPARKLES)
  {
    currentBlending = LINEARBLEND;
    SetupSparklesPalette();
  }
  else if( paletteName == PALETTE_CHASE)
  {
    currentBlending = LINEARBLEND;
    SetupChasePalette();
  }
  else if( paletteName == PALETTE_COLORFUL)
  {
    currentBlending = NOBLEND;
    SetupColorfulPalette();
  }
  else if( paletteName == PALETTE_CANDYCANE)
  {
    currentBlending = NOBLEND;
    SetupCandyCanePalette();
  }
  else if( paletteName == PALETTE_GLOW)
  {
    currentBlending = NOBLEND;
    SetupGlowPalette();
  }
  else
  {
    currentBlending = NOBLEND;
    SetupColorfulPalette();
  }

  currentPaletteName = paletteName;

  return currentPaletteName;
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
