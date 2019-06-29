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
int pin_D8 = 15;

void setup(void){
  //make the LED pin output and initially turned off
  pinMode(pin_D1, OUTPUT);
  pinMode(pin_D2, OUTPUT);
  pinMode(pin_D3, OUTPUT);
  pinMode(pin_D4, OUTPUT);
  pinMode(pin_D5, OUTPUT);
  pinMode(pin_D6, OUTPUT);
  pinMode(pin_D7, OUTPUT);
  pinMode(pin_D8, OUTPUT);
  digitalWrite(pin_D1, LOW);
  digitalWrite(pin_D2, LOW);
  digitalWrite(pin_D3, LOW);
  digitalWrite(pin_D4, LOW);
  digitalWrite(pin_D5, LOW);
  digitalWrite(pin_D6, LOW);
  digitalWrite(pin_D7, LOW);
  digitalWrite(pin_D8, LOW);
  
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
}
 
void loop(void){
  server.handleClient();
}

void GetHtmlPage(String ledState){
  String d1 = "<a href=\"D1\"><button>ON</button></a>";
  String d2 = "<a href=\"D2\"><button>ON</button></a>";
  String d3 = "<a href=\"D3\"><button>ON</button></a>";
  String d4 = "<a href=\"D4\"><button>ON</button></a>";
  String d5 = "<a href=\"D5\"><button>ON</button></a>";
  String d6 = "<a href=\"D6\"><button>ON</button></a>";
  String d7 = "<a href=\"D7\"><button>ON</button></a>";
  String d8 = "<a href=\"D8\"><button>ON</button></a>";

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
  digitalWrite(pin_D8, LOW);

       if (ledState == "D1") { digitalWrite(pin_D1, HIGH); }
  else if (ledState == "D2") { digitalWrite(pin_D2, HIGH); }
  else if (ledState == "D3") { digitalWrite(pin_D3, HIGH); }
  else if (ledState == "D4") { digitalWrite(pin_D4, HIGH); }
  else if (ledState == "D5") { digitalWrite(pin_D5, HIGH); }
  else if (ledState == "D6") { digitalWrite(pin_D6, HIGH); }
  else if (ledState == "D7") { digitalWrite(pin_D7, HIGH); }
  else if (ledState == "D8") { digitalWrite(pin_D8, HIGH); }

  server.send(200, "text/html", page);
}
