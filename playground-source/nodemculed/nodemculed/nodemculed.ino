//https://www.teachmemicro.com/intro-nodemcu-arduino/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, LOW);
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(12, HIGH);
  delay(1000);              // wait for a second
}

/*
 * The chip model: CP2102
 * NodeMCU V1.0
 * https://frightanic.com/iot/comparison-of-esp8266-nodemcu-development-boards/
 * 
 *                                                                |---|
 *                                    [TOUT] -   [ADC0] - [A0]  - |---|
 *                                               [RSRV] - [RSV] - |---|
 *                                               [RSRV] - [RSV] - |---|
 *                                    [SDD3] - [GPIO10] - [SD3] - |---|
 *                                    [SDD2] -  [GPIO9] - [SD2] - |---|
 *                                    [SDD1] -   [MOSI] - [SD1] - |---|
 *                                   [SDCMD] -     [CS] - [CMD] - |---|
 *                                    [SDD0] -   [MISO] - [SD0] - |---|
 *                                   [SDCLK] -   [SCLK] - [CLK] - |---|
 *                                                [GND] - [GND] - |---|
 *                                               [3.3V] - [3V3] - |---|
 *                                                 [EN] - [EN]  - |---|
 *                                                [RST] - [RST] - |---|
 *                                                [GND] - [GND] - |---|
 *                                                [VIN] - [VIN] - |---|
 *                                                                |---|
 * 
 * 
 * |---|
 * |---| - [D0] - [GPIO16] - [USER] - [WAKE]
 * |---| - [D1] - [GPIO5]
 * |---| - [D2] - [GPIO4]
 * |---| - [D3] - [GPIO0] - [FLASH]
 * |---| - [D4] - [GPIO2] - [TXD1]
 * |---| - [3V3] - [3.3V]
 * |---| - [GND] - [GND]
 * |---| - [D5] - [GPIO14] -         - [HSCLK]
 * |---| - [D6] - [GPIO12] -         - [HMISO]
 * |---| - [D7] - [GPIO13] - [RXD2]  - [HMOSI]
 * |---| - [D8] - [GPIO15] - [TXD2]  - [HCS]
 * |---| - [RX] - [GPIO3]  - [RXD0]
 * |---| - [TX] - [GPIO1]  - [TXD0]
 * |---| - [GND] - [GND]
 * |---| - [3V3] - [3.3V]
 * |---|
 * 
 */


/* Manufacturer information
 * 
 * https://www.amazon.com/gp/product/B01IK9GEQG/
 * MakerFocus 2pcs ESP8266 NodeMCU LUA CP2102 ESP-12E 
 * Internet WiFi Development Board Serial Wireless Module Internet for Arduino IDE/Micropython 
 * with Free Adapter Board for ESP8266 ESP-01 and nRF24L01+ 
 * 
 * 
 * There is the way to guide you to use the new version: 
 * The command you needed to use is: esptool.py --baud 115200 --port /dev/tty.SLAB_USBtoUART write_flash -fs 32m -ff 80m --flash_mode dio 0x00000 boot_v1.7.bin 0x1000 user1.bin 0x37c000 esp_init_data_default.bin 0x37e000 blank.bin 
 * The important part is “—flash mode dio” 
 * https://github.com/espressif/esptool/wiki/SPI-Flash-Modes;
 * 
 * Firmware link: https://github.com/nodemcu/nodemcu-firmware; 
 * Data download access to the website: http://www.nodemcu.com; 
 * Test Video: https://www.youtube.com/watch?v=Gh_pgqjfeQc; 
 * Makerfocus nRF24L01+ and ESP8266 ESP-01 Breadboard Breakout Adapter Board is come for free, 
 * it can compatible with "nRF24L01+ " and ESP8266 ESP-01. If you need more information about it, 
 * pls refer to: https://www.amazon.com/dp/B01N5AK6E1;
 * 
 * ESP8266 is a highly integrated chip designed for the needs of a new connected world. It offers a 
 * complete and self-contained Wi-Fi networking solution, allowing it to either host the application 
 * or to offload all Wi-Fi networking functions from another application processor.
 * 
 * ESP8266 has powerful on-board processing and storage capabilities that allow it to be integrated 
 * with the sensors and other application specific devices through its GPIOs with minimal development 
 * up-front and minimal loading during runtime. Its high degree of on-chip integration allows for 
 * minimal external circuitry, and the entire solution, including front-end module, is designed to 
 * occupy minimal PCB area;
 * 
 * We Have a Strong After-sales Service Team: 
 * As long as you have any questions about the product, we will resolve your issue immediately if 
 * received your email, your satisfactory purchase experience is our greatest hope! How to email us? 
 * Plz click “MakerFocus” and click “Ask a question” to email us! Looking forward to your consultation!
 * 
 * 
 * 
 */
