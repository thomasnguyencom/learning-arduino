//  Pick a pattern for LED strip
//    Connect to WiFi
//    Start Web Server
//    Show page with buttons to pick LED pattern
//
//  Reference Links
//    Creating a Simple NodeMCU Web Server: https://www.teachmemicro.com/simple-nodemcu-web-server/
//    https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
//    http://fastled.io/

//  ------------------------------------------------------------------------------------------------------------------------
//  INCLUDES

//  https://github.com/FastLED/FastLED/wiki/ESP8266-notes
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//  ------------------------------------------------------------------------------------------------------------------------
//  GLOBAL

//  Network contants
const char* ssid = "gorideabike";
const char* password = "tomisthebomb";

//  Find/Replace contants
const String LED_STATE_KEY = "#LED_STATE_KEY#";

//  Instantiate server at port 80
ESP8266WebServer server(80);

//  ------------------------------------------------------------------------------------------------------------------------
//  INIT : WS2811
//  Wire configuration
//    [GND] Connects to ground
//    [DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and  
//      the strip data input pin to reduce noise on that line
//    [5V]  Connects to a +5V power supply
//  ------------------------------------------------------------------------------------------------------------------------

//  Palette set up
#define FAST_LED_PIN       15

TBlendType    currentBlending;
CRGBPalette16 currentPalette;
String        currentPaletteName;
int           currentPalettePointer = 0;

String PALETTE_GLOW      = "glow";
String PALETTE_CANDYCANE = "candycane";
String PALETTE_COLORFUL  = "colorful";
String PALETTE_HOLIDAY   = "holiday";
String PALETTE_CHASE     = "chase";
String PALETTE_SPARKLES  = "sparkles";
String PALETTE_MURCA = "murca";

String _paletteName;

#define UPDATES_PER_SECOND 100
#define NUM_LEDS           100
#define BRIGHTNESS         64
#define LED_TYPE           WS2811
#define COLOR_ORDER        RGB // okay
CRGB leds[NUM_LEDS];

//  ------------------------------------------------------------------------------------------------------------------------
void setup(void){
  //  power-up safety delay
  delay(3000);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  //  Wait for connection
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
    GetHtmlPage("");
  });

  delay(1000);
  
  ConfigureRoutes();
  
  server.begin();
  Serial.println("Web server started!");

  //  Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}
 
//  ------------------------------------------------------------------------------------------------------------------------
void loop(void){
  server.handleClient();

  //  Process palette
  GetPalette(_paletteName);
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;    
  FillLEDsFromPaletteColors( startIndex);
  
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

//  ------------------------------------------------------------------------------------------------------------------------
void GetHtmlPage(String paletteName){
  _paletteName = paletteName;

  ConfigureRoutes();
  
  String d1 = "<p><a href=\"" + PALETTE_CANDYCANE + "\"><button>" + PALETTE_CANDYCANE + "</button></a></p>";
  String d2 = "<p><a href=\"" + PALETTE_GLOW + "\"><button>" + PALETTE_GLOW + "</button></a></p>";
  String d3 = "<p><a href=\"" + PALETTE_COLORFUL + "\"><button>" + PALETTE_COLORFUL + "</button></a></p>";
  String d4 = "<p><a href=\"" + PALETTE_SPARKLES + "\"><button>" + PALETTE_SPARKLES + "</button></a></p>";
  String d5 = "<p><a href=\"" + PALETTE_HOLIDAY + "\"><button>" + PALETTE_HOLIDAY + "</button></a></p>";
  String d6 = "<p><a href=\"" + PALETTE_CHASE + "\"><button>" + PALETTE_CHASE + "</button></a></p>";  
  String d7 = "<p><a href=\"" + PALETTE_MURCA + "\"><button>" + PALETTE_MURCA + "</button></a></p>";
  String d8 = "<p><a href=\"" + PALETTE_CANDYCANE + "\"><button>" + PALETTE_CANDYCANE + "</button></a></p>";

  String d_1 = d1 + d2 + d3 + d4;
  String d_2 = d5 + d6 + d7 + d8;

  String off = "<a href=\"Off\"><button>OFF</button></a>";
  
  String s = d_1 + d_2;
  
  String pageTemplate = "<html><body><h1>Tom's Magic Lantern</h1>" + s + "<p>#LED_STATE_KEY#</p></body></html>";

  pageTemplate.replace(LED_STATE_KEY, paletteName);
  String page = pageTemplate;
  
  server.send(200, "text/html", page);
}

//  ------------------------------------------------------------------------------------------------------------------------
void ConfigureRoutes() {
  server.on(("/" + PALETTE_CANDYCANE), [](){ GetHtmlPage(PALETTE_CANDYCANE); } );
  server.on(("/" + PALETTE_GLOW)     , [](){ GetHtmlPage(PALETTE_GLOW); } );
  server.on(("/" + PALETTE_COLORFUL) , [](){ GetHtmlPage(PALETTE_COLORFUL); } );
  server.on(("/" + PALETTE_SPARKLES) , [](){ GetHtmlPage(PALETTE_SPARKLES); } );
  server.on(("/" + PALETTE_HOLIDAY)  , [](){ GetHtmlPage(PALETTE_HOLIDAY); } );
  server.on(("/" + PALETTE_CHASE)    , [](){ GetHtmlPage(PALETTE_CHASE); } );  
  server.on(("/" + PALETTE_MURCA)    , [](){ GetHtmlPage(PALETTE_MURCA); } );
  server.on(("/" + PALETTE_CANDYCANE), [](){ GetHtmlPage(PALETTE_CANDYCANE); } );
}

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
  }
  else if( paletteName == PALETTE_CANDYCANE)
  {
    SetupCandyCanePalette();
  }
  else if( paletteName == PALETTE_GLOW)
  {
    SetupGlowPalette();
  }
  else if( paletteName == PALETTE_MURCA)
  {
    SetupColorfulMurca();
  }
  else
  {
    paletteName = "UNKNOWN";
  }

  currentPaletteName = paletteName;
}

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
void SetupCandyCanePalette()
{
  CRGB c_red___ = CRGB(   0, 255,   0);
  CRGB c_white_ = CRGB( 255, 255, 255);
  CRGB c_black_ = CRGB(   0,   0,   0);
  currentPalette = CRGBPalette16(
    c_red___, c_white_, c_red___, c_white_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_black_, c_black_, c_black_, c_black_
  );
}

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

// ------------------------------------------------------------------------------------------------------------------------
void SetupColorfulMurca()
{
  //                      G    R    B
  CRGB c_red___ = CRGB(   0, 255,   0); 
  CRGB c_white_ = CRGB( 254, 254, 254); //CRGB( 255, 255, 255);
  CRGB c_blue__ = CRGB(   0,   0, 255);
  CRGB c_black_ = CRGB(   0,   0,   0);
  
  currentPalette = CRGBPalette16(
    c_red___, c_white_, c_blue__, c_black_,
    c_black_, c_black_, c_black_, c_black_,
    c_red___, c_white_, c_blue__, c_black_,
    c_black_, c_black_, c_black_, c_black_
  );
}

//EOL
