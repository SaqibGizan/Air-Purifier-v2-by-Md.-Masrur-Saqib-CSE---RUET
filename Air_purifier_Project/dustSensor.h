/*
 * Author: Md. Masrur Saqib, CSE-18, RUET
 * Organization: Gizan-Tech
 * Date of creation: 05-Nov-20
 * Project Name: Low Cost Air Purifier
 * Last Modification: 13-Dec-20
 * Modified by: Md. Masrur Saqib
 */

#ifndef __DUSTSENSOR_H__
#define __DUSTSENSOR_H__
#include<Arduino.h>

class dustSensor {
    uint8_t LEDPin, VoPin;
    unsigned long VoRawTotal = 0;
    int VoRawCount = 0;
    float Voc = 0.6;
    const float K = 0.5;
    int sampleRate = 100;
    float dustDensity = 0;
    float dV;

  public:
    float averageDensity = 0;
    float avgDensityTotal = 0;
    dustSensor(uint8_t ledPin, uint8_t voPin);
    void begin();
    int dustRead();
    float dustLvl();
    float avgDensity();
    String airHealth();
};

#endif
