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

// LED pin definitions
int ledPin = 13;

void setup(void){
  //make the LED pin output and initially turned off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   
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
    server.send(200, "text/html", GetHtmlPage(""));
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", GetHtmlPage("ON"));
    digitalWrite(ledPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", GetHtmlPage("OFF"));
    digitalWrite(ledPin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}

String GetHtmlPage(String ledState){
  String pageTemplate = "<html><body><h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><p>#LED_STATE_KEY#</p></body></html>";

  pageTemplate.replace(LED_STATE_KEY, ledState);
  String page = pageTemplate;
  
  return page;

}
