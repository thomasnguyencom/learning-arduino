// https://randomnerdtutorials.com/getting-started-with-esp8266-wifi-transceiver-review/
// https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

// ========================================================================================================================
// [01] Installing the ESP8266 Board
// ------------------------------------------------------------------------------------------------------------------------
// 1) Open the preferences window from the Arduino IDE.
//         Go to File > Preferences
// 2) Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json
//         into the “Additional Board Manager URLs” field as shown in the figure below. 
//         Then, click the “OK” button.
// 3) Open boards manager.
//         Go to Tools > Board > Boards Manager…
//         Arduino IDE boards manager
// 4) Scroll down, select the ESP8266 board menu and install “esp8266”
// 5) Choose your ESP8266 board from Tools > Board > Generic ESP8266 Module
// 6) Finally, re-open your Arduino IDE
// ========================================================================================================================

// ========================================================================================================================
// [02] Testing the Installation
// ------------------------------------------------------------------------------------------------------------------------
// 1) Download and install
//         https://www.ftdichip.com/Drivers/VCP.htm (2.12.28 as executable)
// 
// ========================================================================================================================

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// INIT : ESP8266
//   AT version:1.2.0.0(Jul  1 2016 20:04:45)
//   SDK version:1.5.4.1(39cb9a32)
//   Ai-Thinker Technology Co. Ltd.
//   Dec  2 2016 14:21:16
// ------------------------------------------------------------------------------------------------------------------------
//  Chip layout
//  /--------------------------------\
//  | [TX    ] [GND   ] /----------\  |
//  | [CH_PD ] [GPIO 2] |   /------/  |
//  | [RST   ] [GPIO 0] |   \------\  |
//  | [VCC   ] [RX    ]            |  |
//  \--------------------------------/

// ------------------------------------------------------------------------------------------------------------------------
// INIT : FTD1232
// ------------------------------------------------------------------------------------------------------------------------
//  Chip layout
//  /--------------------------------\
//  |                          [DTR] |
//  |                          [RX ] |
//  |                          [TX ] |
//  |                          [VCC] |
//  |                          [CTS] |
//  |                          [GND] |
//  \--------------------------------/

// ------------------------------------------------------------------------------------------------------------------------
// Schematic : ESP8266 and FTD1232
// ------------------------------------------------------------------------------------------------------------------------
//  FTD1232 Schematic                   [mapping ->]  ESP8266 Schematic
//  /--------------------------------\
//  |                          [DTR] | -              /--------------------------------\
//  |                          [RX ] | [TX ]          | [TX    ] [GND   ] /----------\  |
//  |                          [TX ] | [RX ]          | [CH_PD ] [GPIO 2] |   /------/  |
//  |                          [VCC] | [VCC][CH_PD]   | [RST   ] [GPIO 0] |   \------\  |
//  |                          [CTS] | -              | [VCC   ] [RX    ]            |  |
//  |                          [GND] | [GND][GPIO 0]  \--------------------------------/
//  \--------------------------------/                

/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

int pin = 2;

void setup() {
  // initialize GPIO 2 as an output.
  pinMode(pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}

//EOL
