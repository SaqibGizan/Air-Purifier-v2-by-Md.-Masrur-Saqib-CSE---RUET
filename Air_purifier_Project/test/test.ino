#include <SoftwareSerial.h>
#include <DHT.h>
#include "Controll.h"
#include "dustSensor.h"
#include "Display.h"


#define Fan1_pin 5
#define Fan2_pin 6
#define Fan3_pin 9
#define Fan4_pin 10
#define Backlit_pin 13
#define BluRx_pin 3
#define BluTx_pin 2
#define Dht_pin 1
#define DHTTYPE DHT22
#define DustLed_pin 4
#define DustOut_pin A7
#define HV 12
#define LV 3
#define Auto 1 
#define Manual 2


dustSensor dust(DustLed_pin, DustOut_pin);
Controll fan1(Fan1_pin, HV);
Controll fan2(Fan2_pin, HV);
Controll fan3(Fan3_pin, LV);
Controll fan4(Fan4_pin, LV);
Controll led(Backlit_pin);
DHT dht(Dht_pin, DHTTYPE);
Display dis;
SoftwareSerial blu(BluRx_pin, BluTx_pin); //RX, TX


uint8_t MODE = 1;
String quality;
float dst;
float hum;
float temp;

void setup()
{
  blu.begin(115200);
  Serial.begin(115200);
}

void loop()
{
      
      if (Serial.available())
      {
           char data = Serial.read();
           blu.print(data);
      }
      if (blu.available())
      {
           char data = blu.read();
           Serial.print(data);
      }
}


void All_ON() {
  fan1.on();
  fan2.on();
  fan3.on();
  fan4.on();
  led.on();
}

void All_OFF() {
  fan1.off();
  fan2.off();
  fan3.off();
  fan4.off();
  //led.off();
}

void MODE_CONTROL() {
  if (MODE == 1) {
    if (dust.averageDensity < 5) {
      All_OFF();
    }
    else {
      All_ON();
    }
  }
}

void Bluetooth() {

  char rBlu = blu.read();

  if (rBlu == 'A') {
    All_ON();
    MODE = 1;
  }
  if (rBlu == 'S') {
    All_OFF();
    MODE = 0;
  }
  if (rBlu == 'M') {
    All_ON();
    MODE = 0;
  }
  if (rBlu == 'Q') {
    fan1.highSpd();
    MODE = 0;
  }
  if (rBlu == 'W') {
    fan1.midSpd();
    MODE = 0;
  }
  if (rBlu == 'E') {
    fan1.lowSpd();
    MODE = 0;
  }
  if (rBlu == 'R') {
    fan2.highSpd();
    MODE = 0;
  }
  if (rBlu == 'T') {
    fan2.midSpd();
    MODE = 0;
  }
  if (rBlu == 'Y') {
    fan2.lowSpd();
    MODE = 0;
  }
  if (rBlu == 'U') {
    fan1.on();
    MODE = 0;
  }
  if (rBlu == 'I') {
    fan1.off();
    MODE = 0;
  }
  if (rBlu == 'O') {
    fan2.on();
    MODE = 0;
  }
  if (rBlu == 'P') {
    fan2.off();
    MODE = 0;
  }
  if (rBlu == 'D') {
    led.on();
    MODE = 0;
  }
  if (rBlu == 'F') {
    led.off();
    MODE = 0;
  }
}
