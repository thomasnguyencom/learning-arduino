//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

// for DHT11,
//      VCC: 5V or 3V
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

  Serial.print(celcius); Serial.print("\t\t");
  Serial.print(fahrenheit); Serial.print("\t\t");
  Serial.print(kelvin); Serial.print("\t\t");
  Serial.print(humidity); Serial.print("\t\t");
  
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
