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

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//  ------------------------------------------------------------------------------------------------------------------------
//  GLOBAL

//  Network contants
const char* ssid = "gorideabike";
const char* pass = "tomisthebomb";

//  Find/Replace contants
const String LED_STATE_KEY = "#LED_STATE_KEY#";

//  ------------------------------------------------------------------------------------------------------------------------
//  INIT : WS2811
//  Wire configuration
//    [GND] Connects to ground
//    [DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and  
//      the strip data input pin to reduce noise on that line
//    [5V]  Connects to a +5V power supply
//  ------------------------------------------------------------------------------------------------------------------------

//  Palette set up
#define PIN        15

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 50

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

//  Blynk setup
#define BLYNK_PRINT Serial

char auth[] = "oIRYZXmQ-sCl2zPjU_UQfCH1wVldhdia";

int _colorR = 0;
int _colorG = 0;
int _colorB = 0;

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
  _colorR = param.asInt();
  
  Serial.println("V2 Slider value is: " + String(_colorR));
}

BLYNK_WRITE(V3)
{
  _colorG = param.asInt();
  
  Serial.println("V3 Slider value is: " + String(_colorG));
}

BLYNK_WRITE(V4)
{
  _colorB = param.asInt();
  
  Serial.println("V4 Slider value is: " + String(_colorB));
}


//  ------------------------------------------------------------------------------------------------------------------------
void setup(void){
  //  power-up safety delay
  delay(3000);

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); //WiFi.begin(ssid, password);
  Serial.println("Connected");

  /*  Wait for connection
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
  */

  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
  
  //  Setup WS2812B Strip
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}
 
//  ------------------------------------------------------------------------------------------------------------------------
void loop(void){
  Blynk.run();
  
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(_colorR, _colorG, _colorB));
  }
  
  pixels.show();
}

//  ------------------------------------------------------------------------------------------------------------------------
void GetHtmlPage(String paletteName){
  /*
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
   */
}

//  ------------------------------------------------------------------------------------------------------------------------
void ConfigureRoutes() {
  /*
  server.on(("/" + PALETTE_CANDYCANE), [](){ GetHtmlPage(PALETTE_CANDYCANE); } );
  server.on(("/" + PALETTE_GLOW)     , [](){ GetHtmlPage(PALETTE_GLOW); } );
  server.on(("/" + PALETTE_COLORFUL) , [](){ GetHtmlPage(PALETTE_COLORFUL); } );
  server.on(("/" + PALETTE_SPARKLES) , [](){ GetHtmlPage(PALETTE_SPARKLES); } );
  server.on(("/" + PALETTE_HOLIDAY)  , [](){ GetHtmlPage(PALETTE_HOLIDAY); } );
  server.on(("/" + PALETTE_CHASE)    , [](){ GetHtmlPage(PALETTE_CHASE); } );  
  server.on(("/" + PALETTE_MURCA)    , [](){ GetHtmlPage(PALETTE_MURCA); } );
  server.on(("/" + PALETTE_CANDYCANE), [](){ GetHtmlPage(PALETTE_CANDYCANE); } );
  
   */
}
