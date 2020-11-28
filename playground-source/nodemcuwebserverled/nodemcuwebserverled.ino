//  Pick a LEDs connected to digital pins
//    Connect to WiFi
//    Start Web Server
//    Show page with buttons to pick LED pattern
//
//  Reference Links
//    Creating a Simple NodeMCU Web Server: https://www.teachmemicro.com/simple-nodemcu-web-server/
//    Add boards to IDE: http://arduino.esp8266.com/stable/package_esp8266com_index.json
//      Install Boards Manager - ESP8266
//      Reference NodeMCU 1.0 ESP-12E

// ------------------------------------------------------------------------------------------------------------------------
//  INCLUDES

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// ------------------------------------------------------------------------------------------------------------------------
// GLOBAL

// Network contants
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

// Digital pin setup
int _digitalPin = 0;

int D_OFF = -1;
int D_0 = 0;
int D_1 = 1;
int D_2 = 2;
int D_3 = 3;
int D_4 = 4;
int D_5 = 5;
int D_6 = 6;
int D_7 = 7;
int D_8 = 8;

int totalPinOptions = 10;
int pinOptions[] = { D_OFF, D_0, D_1, D_2, D_3, D_4, D_5, D_6, D_7, D_8 };

//  NodeMCU Dev Kit IO pins and ESP8266 internal GPIO pins mapping: https://www.electronicwings.com/nodemcu/nodemcu-gpio-with-arduino-ide
int pin_0 = 16;
int pin_1 = 5;
int pin_2 = 4;
int pin_3 = 0;
int pin_4 = 2;
int pin_5 = 14;
int pin_6 = 12;
int pin_7 = 13;
int pin_8 = 15;

// ------------------------------------------------------------------------------------------------------------------------
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
    GetHtmlPage(0);
  });

  delay(1000);
  
  ConfigureRoutes();
  
  server.begin();
  Serial.println("Web server started!");

  //  Setup digital pins
  pinMode(pin_0, OUTPUT);
  
  pinMode(pin_1, OUTPUT);
  pinMode(pin_2, OUTPUT);
  pinMode(pin_3, OUTPUT);
  pinMode(pin_4, OUTPUT);
  
  pinMode(pin_5, OUTPUT);
  pinMode(pin_6, OUTPUT);
  pinMode(pin_7, OUTPUT);
  pinMode(pin_8, OUTPUT);
}

//  ------------------------------------------------------------------------------------------------------------------------
void loop(void){
  server.handleClient();
}

//  ------------------------------------------------------------------------------------------------------------------------
void GetHtmlPage(int digitalPin){
  _digitalPin = digitalPin;

  ConfigureRoutes();

  SetDigitalPin(digitalPin);

  String pinButtons = "";
  Serial.println("Total Buttons: " + String(totalPinOptions));
  for(int i = 0; i < totalPinOptions; i++) {
    String buttonTag = GetButtonTag(pinOptions[i], digitalPin);

    Serial.println("Added: " + String(buttonTag));
    
    pinButtons += buttonTag;
  }

  String headerTags = "<header><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/mini.css/3.0.1/mini-default.min.css\"></header>";
  String title = "<title>LEDs</title>";
  String body = "<body>" + pinButtons + "<p>#LED_STATE_KEY#</p></body>";
  String pageTemplate = "<html>" + headerTags + title + body + "</html>";

  pageTemplate.replace(LED_STATE_KEY, String(digitalPin));
  String page = pageTemplate;
  
  server.send(200, "text/html", page);
}

//  ------------------------------------------------------------------------------------------------------------------------
void ConfigureRoutes() {
  /*
  for(int i = 0; i < totalPinOptions; i++) {
    int pinOption = pinOptions[i];
    server.on(("/" + String(pinOption)), [](){ GetHtmlPage(pinOption); } );
  }
  */
  server.on(("/" + String(D_OFF)), [](){ GetHtmlPage(D_OFF); } );
  
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

//  ------------------------------------------------------------------------------------------------------------------------
void SetDigitalPin(int digitalPin) {
  digitalWrite(pin_0, HIGH);
  
  digitalWrite(pin_1, HIGH);
  digitalWrite(pin_2, HIGH);
  digitalWrite(pin_3, HIGH);
  digitalWrite(pin_4, HIGH);

  digitalWrite(pin_5, HIGH);
  digitalWrite(pin_6, HIGH);
  digitalWrite(pin_7, HIGH);
  digitalWrite(pin_8, HIGH);

  if(digitalPin == D_0) { digitalWrite(pin_0, LOW); Serial.println("Digital 0"); }
  if(digitalPin == D_1) { digitalWrite(pin_1, LOW); Serial.println("Digital 1"); }
  if(digitalPin == D_2) { digitalWrite(pin_2, LOW); Serial.println("Digital 2"); }
  if(digitalPin == D_3) { digitalWrite(pin_3, LOW); Serial.println("Digital 3"); }
  if(digitalPin == D_4) { digitalWrite(pin_4, LOW); Serial.println("Digital 4"); }
  
  if(digitalPin == D_5) { digitalWrite(pin_5, LOW); Serial.println("Digital 5"); }
  if(digitalPin == D_6) { digitalWrite(pin_6, LOW); Serial.println("Digital 6"); }
  if(digitalPin == D_7) { digitalWrite(pin_7, LOW); Serial.println("Digital 7"); }
  if(digitalPin == D_8) { digitalWrite(pin_8, LOW); Serial.println("Digital 8"); }
}

//  ------------------------------------------------------------------------------------------------------------------------
String GetButtonTag(int route, int selectedRoute) {
  String SELECTED_BUTTON_KEY = "#SELECTED_BUTTON_KEY#";
  String text = "LED " + String(route);

  String buttonTag = "<a href=\"" + String(route) + "\"><button #SELECTED_BUTTON_KEY#>" + text + "</button></a>";
  
  if(selectedRoute == route) { buttonTag.replace(SELECTED_BUTTON_KEY, "class=\"inverse\""); }
  
  return buttonTag;
}

//EOL
