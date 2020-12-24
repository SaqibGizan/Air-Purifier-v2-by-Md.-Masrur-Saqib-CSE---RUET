/*
 * Author: Md. Masrur Saqib, CSE-18, RUET
 * Organization: Gizan-Tech
 * Date of creation: 05-Nov-20
 * Project Name: Low Cost Air Purifier
 * Last Modification: 13-Dec-20
 * Modified by: Md. Masrur Saqib
 */

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
#define DHTTYPE DHT11
#define DustLed_pin 4
#define DustOut_pin A7
#define HV 12
#define LV 3
#define Auto 1 
#define Manual 2
#define dustID "D"
#define humID "H"
#define tempID "T"


dustSensor dust(DustLed_pin, DustOut_pin);
Controll fan1(Fan1_pin, HV);
Controll fan2(Fan2_pin, HV);
Controll fan3(Fan3_pin, HV);
Controll fan4(Fan4_pin, HV);
Controll led(Backlit_pin);
DHT dht(Dht_pin, DHTTYPE);
Display dis;
SoftwareSerial blu(BluRx_pin, BluTx_pin); //RX, TX


uint8_t MODE = 1;
String quality;
float dst;
float hum;
float temp;
int count = 0;

void setup()
{
  dust.begin();
  dht.begin();
  fan1.begin();
  fan2.begin();
  fan3.begin();
  fan4.begin();
  led.begin();
  All_ON();
  dis.begin();
  blu.begin(115200);
  dis.legend();
}

void loop()
{
  dst = dust.avgDensity();
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  quality = dust.airHealth();
  dis.show(8, 15, 0, dst);
  dis.show(9, 15, 1, hum);
  dis.show(9, 15, 2, temp);
  dis.show(11, 3, quality);
  dataSend(dustID, dst);
  dataSend(humID, hum);
  dataSend(tempID, temp);
  if (blu.available())
  {
    Bluetooth();
  }
  MODE_CONTROL();
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
      count = 0;
    }
    else {
      count++;
      if(count > 4)
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

  if (rBlu == 'G') {
    fan3.highSpd();
    MODE = 0;
  }
  if (rBlu == 'H') {
    fan3.midSpd();
    MODE = 0;
  }
  if (rBlu == 'J') {
    fan3.lowSpd();
    MODE = 0;
  }
  if (rBlu == 'K') {
    fan4.highSpd();
    MODE = 0;
  }
  if (rBlu == 'L') {
    fan4.midSpd();
    MODE = 0;
  }
  if (rBlu == 'Z') {
    fan4.lowSpd();
    MODE = 0;
  }
  if (rBlu == 'X') {
    fan3.on();
    MODE = 0;
  }
  if (rBlu == 'C') {
    fan3.off();
    MODE = 0;
  }
  if (rBlu == 'V') {
    fan4.on();
    MODE = 0;
  }
  if (rBlu == 'B') {
    fan4.off();
    MODE = 0;
  }
}

void dataSend(String id, float num)
{
  String text = id + " " + (String)num + " ";
  blu.print(text);
  delay(50);
}
