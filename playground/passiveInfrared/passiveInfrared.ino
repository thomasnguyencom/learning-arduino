// http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
// 
// VCC Power
// OUT inputPin
// GND Ground

int ledPin = 8;                // choose the pin for the LED
int inputPin = 7;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

String pirStatus = "OFF";

void setup() {
  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirStatus = "ON";
      
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
    else {
      Serial.println("YYYYY");
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirStatus = "OFF";
      
      // We only want to print on the output change, not state
      pirState = LOW;
    }
    else {
      Serial.println("ZZZZZ");
    }
  }
  uint8_t secondHand = (millis() / 1000) % 60;
  uint8_t minuteHand = ((millis() / 1000) % 60) % 60;
  
  Serial.println("[" + String(minuteHand) + ":" + String(secondHand) + "] " + pirStatus);
  delay(1000);
}
