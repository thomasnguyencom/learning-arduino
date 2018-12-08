// http://www.instructables.com/id/The-First-Usage-of-ESP8266-With-Arduino-Uno/
// https://www.itead.cc/wiki/ESP8266_Serial_WIFI_Module#AT_Commands

// ========================================================================================================================
// NOTE: this directly interacts with the Serial Monitor, no code
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
// Wire/Ribbon configuration
// ------------------------------------------------------------------------------------------------------------------------
// -{Green } [TX    ] (TX) Transmitter mode
// -{Blue  } [CH_PD ] (5V) Chip power down
// -{Purple} [RST   ] (-) Reset
// -{Gray  } [VCC   ] (5V) Voltage of Closed Circuit
// ------------------------------------------------------------------------------------------------------------------------
// -{Brown } [GND   ] (GND) Ground
// -{Red   } [GPIO 2] (-) General Port Input Output 2
// -{Orange} [GPIO 0] (-) General Port Input Output 0
// -{Yellow} [RX    ] (RX) Receive mode

// ------------------------------------------------------------------------------------------------------------------------
// Serial Monitor configuration
// ------------------------------------------------------------------------------------------------------------------------
// Set Both NL & CR
// Set baud rate 115200 (default)
// ------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------
// AT Command Format: 
// ------------------------------------------------------------------------------------------------------------------------
// SET  AT+<cmd>=<…>
// GET  AT+<cmd>?
// TEST AT+<cmd>=?
// EXEC AT+<cmd>

// ------------------------------------------------------------------------------------------------------------------------
// Basic Commands             Verb Behavior                      Notes
// ------------------------------------------------------------------------------------------------------------------------
// AT                         EXEC Check module status      
// AT+CIOBAUD=9600            SET  Update baud rate              Default: 115200
// AT+RST                     -    Reset the module
// AT+GMR                     EXEC Firmware version              AT version:1.2.0.0(Jul  1 2016 20:04:45)
//                                                               SDK version:1.5.4.1(39cb9a32)
//                                                               Ai-Thinker Technology Co. Ltd.
//                                                               Dec  2 2016 14:21:16

// ------------------------------------------------------------------------------------------------------------------------
// WiFi Commands              Verb Behavior                      Notes
// ------------------------------------------------------------------------------------------------------------------------
// AT+CWMODE?                 GET  Get network mode              1 = Sta
//                                                               2 = AP (AP is a normal mode for devices)
//                                                               3 = both (default mode of router)
// AT+CWLAP                   EXEC List WiFi
// AT+CWJAP?                  GET  Get connected WiFi
// AT+CWJAP                   EXEC Connect to the AP             AT+ CWJAP =<ssid>,<pwd>
// AT+CWQAP                   EXEC Disconnect to the AP
// AT+CWSAP                   EXEC Set params of AP              AT+ CWSAP= <ssid>,<pwd>,<chl>, <ecn>
// AT+CWLIF                   EXEC Check join device's IP

// ------------------------------------------------------------------------------------------------------------------------
// TCP/IP Commands            Verb Behavior                      Notes
// ------------------------------------------------------------------------------------------------------------------------
// AT+CIPSTATUS               EXEC                               <id>,<type>,<addr>,<port>,<tetype>= client or server mode
//                                                               status:
//                                                                 2: Got IP
//                                                                 3: Connected
//                                                                 4: Disconnected
//                                                               id： id of the connection (0~4), for multi-connect
//                                                               type： string, “TCP” or “UDP”
//                                                               addr： string, IP address.
//                                                               port： port number
//                                                               tetype：
//                                                                 0: ESP8266 runs as client
//                                                                 1: ESP8266 runs as server

void setup()
{
}

void loop()
{
}


//EOL
