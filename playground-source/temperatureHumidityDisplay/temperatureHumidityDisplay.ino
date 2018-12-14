//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

/* Tech Specs
3 to 5V power and I/O
2.5mA max current use during conversion (while requesting data)
Good for 20-80% humidity readings with 5% accuracy
Good for 0-50°C temperature readings ±2°C accuracy
No more than 1 Hz sampling rate (once every second)
Body size 15.5mm x 12mm x 5.5mm
4 pins with 0.1" spacing
*/

// for DHT11,
//      VCC: 5V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);

  Serial.print("Celcius"); Serial.print("\t\t");
  Serial.print("Fahrenheit"); Serial.print("\t");
  Serial.print("Kelvin"); Serial.print("\t\t");
  Serial.print("Humidity"); Serial.print("\t");
  Serial.print("Raw Data");
  Serial.println("");
}

void loop() {
  // read with raw sample data.
  byte rawTemperature = 0;
  byte rawHumidity = 0;
  byte data[40] = {0};

  if (dht11.read(pinDHT11, &rawTemperature, &rawHumidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }

  int temperature = (int) rawTemperature;
  int humidity = (int) rawHumidity;

  int celcius = temperature;
  float fahrenheit = (celcius * 9 / 5) + 32;
  float kelvin = ((float) celcius) + 273.15;

  Serial.print(celcius); Serial.print(" C"); Serial.print("\t\t");
  Serial.print(fahrenheit); Serial.print(" F"); Serial.print("\t\t");
  Serial.print(kelvin); Serial.print(" K"); Serial.print("\t\t");
  Serial.print(humidity); Serial.print(" %"); Serial.print("\t\t");
  
  //raw data output
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' '); //output each four set of bits
    }
  }
  Serial.println("");
  
  // DHT11 sampling rate is 1HZ.
  delay(1000 * 5);
}
