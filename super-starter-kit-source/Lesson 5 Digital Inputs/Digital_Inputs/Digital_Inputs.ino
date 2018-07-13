//www.elegoo.com
//2016.12.08

//int ledPin = 4;
//int buttonApin = 13;

const int buttonPin = 13;     // the number of the pushbutton pin
const int ledPin =  4;      // the number of the LED pin
int count = 0;               // Count the button presses

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);    
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    // turn LED on:   
    digitalWrite(ledPin, HIGH); 
    count++;               // add 1 to the count
    if (count >= 8) {
      count = 0;
    } 
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
