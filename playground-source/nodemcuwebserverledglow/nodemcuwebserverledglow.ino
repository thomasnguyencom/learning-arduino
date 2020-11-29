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
#define PIN        15

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 50

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

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
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(255, 147, 41));
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
