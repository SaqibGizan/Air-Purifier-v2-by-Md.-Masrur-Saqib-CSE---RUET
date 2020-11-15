#include<Arduino.h>
#include "dustSensor.h"
#define N 100

dustSensor :: dustSensor(uint8_t ledPin, uint8_t voPin)
{
  LEDPin = ledPin;
  VoPin = voPin;
}

void dustSensor :: begin()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(VoPin, OUTPUT);
}

int dustSensor :: dustRead()
{
  digitalWrite(LEDPin, LOW);
  delayMicroseconds(280);
  int VoRaw = analogRead(VoPin);
  digitalWrite(LEDPin, HIGH);
  delayMicroseconds(9620);
  return VoRaw;
}

float dustSensor :: dustLvl()
{
  float Vo = dustRead();
  VoRawCount = 0;
  VoRawTotal = 0;
  while (1) {
    Vo = dustRead();
    VoRawTotal += Vo;
    VoRawCount++;
    if ( VoRawCount >= N ) {
      Vo = 1.0 * VoRawTotal / VoRawCount;
      VoRawCount = 0;
      VoRawTotal = 0;
      break;
    }
  }

  Vo = Vo / 1024.0 * 5.0;
  dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  dustDensity = dV / K * 100.0;
  return dustDensity;
}

float dustSensor :: avgDensity()
{
  //avgDensityTotal += dustLvl();
  averageDensity = dustLvl();//avgDensityTotal / 2.0;
  //avgDensityTotal = averageDensity;
  return averageDensity;
}

String dustSensor :: airHealth()
{
  String health;
  if (averageDensity < 10) {
    health = "Healthy  ";
  }
  else if (averageDensity < 30) {
    health = "Modarate ";
  }
  else if (averageDensity < 50) {
    health = "Sensitive";
  }
  else if (averageDensity < 145) {
    health = "Unhealthy";
  }
  else {
    health = "Hazardous";
  }
  return health;
}
