// ------------------------------------------------------------------------------------------------------------------------
// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// http://fastled.io/
// ------------------------------------------------------------------------------------------------------------------------
https://github.com/FastLED/FastLED/wiki/ESP8266-notes
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>

// https://www.teachmemicro.com/simple-nodemcu-web-server/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Network contants
const char* ssid = "gorideabike";
const char* password = "tomisthebomb";
const String LED_STATE_KEY = "#LED_STATE_KEY#";

//instantiate server at port 80 (http port)
ESP8266WebServer server(80);

// Pin definitions
int pin_D1 =  5;
int pin_D2 =  4;
int pin_D3 =  0;
int pin_D4 =  2;
int pin_D5 = 14;
int pin_D6 = 12;
int pin_D7 = 13;
//int pin_D8 = 15;

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
// INIT : WS2811
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ------------------------------------------------------------------------------------------------------------------------
#define UPDATES_PER_SECOND 100
#define NUM_LEDS           50
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         64
#define LED_TYPE           WS2811
#define COLOR_ORDER        RGB

// Pin assignments
#define FAST_LED_PIN        15

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup(void){
  delay( 3000 ); // power-up safety delay

  //make the LED pin output and initially turned off
  pinMode(pin_D1, OUTPUT);
  pinMode(pin_D2, OUTPUT);
  pinMode(pin_D3, OUTPUT);
  pinMode(pin_D4, OUTPUT);
  pinMode(pin_D5, OUTPUT);
  pinMode(pin_D6, OUTPUT);
  pinMode(pin_D7, OUTPUT);
  //pinMode(pin_D8, OUTPUT);
  digitalWrite(pin_D1, LOW);
  digitalWrite(pin_D2, LOW);
  digitalWrite(pin_D3, LOW);
  digitalWrite(pin_D4, LOW);
  digitalWrite(pin_D5, LOW);
  digitalWrite(pin_D6, LOW);
  digitalWrite(pin_D7, LOW);
  //digitalWrite(pin_D8, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
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
    //server.send(200, "text/html", GetHtmlPage(""));
    GetHtmlPage("");
  });
  
  server.on("/D1", [](){ GetHtmlPage("D1"); } );
  server.on("/D2", [](){ GetHtmlPage("D2"); } );
  server.on("/D3", [](){ GetHtmlPage("D3"); } );
  server.on("/D4", [](){ GetHtmlPage("D4"); } );
  server.on("/D5", [](){ GetHtmlPage("D5"); } );
  server.on("/D6", [](){ GetHtmlPage("D6"); } );
  server.on("/D7", [](){ GetHtmlPage("D7"); } );
  server.on("/D8", [](){ GetHtmlPage("D8"); } );
  
  delay(1000);
  
  server.on("/LEDOff", [](){
    //server.send(200, "text/html", GetHtmlPage("OFF"));
    GetHtmlPage("OFF");
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");

  // Setup WS2812B Strip
  FastLED.addLeds<LED_TYPE, FAST_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.setBrightness(  BRIGHTNESS );
}
 
void loop(void){
  server.handleClient();
}

void GetHtmlPage(String ledState){
  String d1 = "<a href=\"D1\"><button>D1</button></a>";
  String d2 = "<a href=\"D2\"><button>D2</button></a>";
  String d3 = "<a href=\"D3\"><button>D3</button></a>";
  String d4 = "<a href=\"D4\"><button>D4</button></a>";
  String d5 = "<a href=\"D5\"><button>D5</button></a>";
  String d6 = "<a href=\"D6\"><button>D6</button></a>";
  String d7 = "<a href=\"D7\"><button>D7</button></a>";
  String d8 = "<a href=\"D8\"><button>D8</button></a>";

  String d_1 = d1 + d2 + d3 + d4;
  String d_2 = d5 + d6 + d7 + d8;

  String off = "<a href=\"LEDOff\"><button>OFF</button></a>";
  
  String s = "<p>" + d_1 + "</p><p>" + d_2 + "</p><p>" + off + "</p>";
  
  String pageTemplate = "<html><body><h1>Simple NodeMCU Web Server</h1>" + s + "<p>#LED_STATE_KEY#</p></body></html>";

  pageTemplate.replace(LED_STATE_KEY, ledState);
  String page = pageTemplate;
  
  digitalWrite(pin_D1, LOW);
  digitalWrite(pin_D2, LOW);
  digitalWrite(pin_D3, LOW);
  digitalWrite(pin_D4, LOW);
  digitalWrite(pin_D5, LOW);
  digitalWrite(pin_D6, LOW);
  digitalWrite(pin_D7, LOW);
  //digitalWrite(pin_D8, LOW);

       if (ledState == "D1") { digitalWrite(pin_D1, HIGH); }
  else if (ledState == "D2") { digitalWrite(pin_D2, HIGH); }
  else if (ledState == "D3") { digitalWrite(pin_D3, HIGH); }
  else if (ledState == "D4") { digitalWrite(pin_D4, HIGH); }
  else if (ledState == "D5") { digitalWrite(pin_D5, HIGH); }
  else if (ledState == "D6") { digitalWrite(pin_D6, HIGH); }
  else if (ledState == "D7") { digitalWrite(pin_D7, HIGH); }
  //else if (ledState == "D8") { digitalWrite(pin_D8, HIGH); }
  else if (ledState == "D8")
  {
    String paletteOutput = PalettePicker();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }

  server.send(200, "text/html", page);
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
