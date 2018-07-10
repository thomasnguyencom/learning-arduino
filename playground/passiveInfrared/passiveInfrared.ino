// ------------------------------------------------------------------------------------------------------------------------
// http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
// ------------------------------------------------------------------------------------------------------------------------
// VCC Power (5V)
// OUT inputPin
// GND Ground
// ------------------------------------------------------------------------------------------------------------------------
// When the dials are facing you
// Left: sensitivity
// Right: time delay

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
int pirState = LOW;            // we start, assuming no motion detected
int val = 0;                   // variable for reading the pin status

String pirStatus = "OFF";

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================
// ------------------------------------------------------------------------------------------------------------------------
// INIT : SR501 Sensor
// ------------------------------------------------------------------------------------------------------------------------
int pirPin = 7;               // choose the input pin (for PIR sensor)
// ------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------
// INIT : LED
// ------------------------------------------------------------------------------------------------------------------------
int ledPin = 8;                // choose the pin for the LED
// ------------------------------------------------------------------------------------------------------------------------

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop(){
  boolean showChange = false;
  uint8_t secondHand = (millis() / 1000) % 60;
  uint8_t minuteHand = ((millis() / 1000) / 60) % 60;
  uint8_t hourHand = ((millis() / 1000) / 60 / 60) % 60;
  
// ------------------------------------------------------------------------------------------------------------------------
  
  val = digitalRead(pirPin);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      pirStatus = "ON";

      showChange = true;
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      pirStatus = "OFF";
      
      showChange = true;
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  if(showChange)
  {
    Serial.println("[" + String(hourHand) + " hour(s), " + String(minuteHand) + " minute(s), " + String(secondHand) + " second(s)] " + pirStatus);
    showChange = false;
  }
  
  delay(1000);
}
