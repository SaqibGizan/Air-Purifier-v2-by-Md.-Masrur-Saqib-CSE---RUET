/*
 * Author: Md. Masrur Saqib, CSE-18, RUET
 * Organization: Gizan-Tech
 * Date of creation: 05-Nov-20
 * Project Name: Low Cost Air Purifier
 * Last Modification: 13-Dec-20
 * Modified by: Md. Masrur Saqib
 */
 
#ifndef __CONTROLL_H__
#define __CONTROLL_H__
#include<Arduino.h>

class Controll{
    uint8_t fanPin;
    uint8_t volt;
  public:
    Controll(uint8_t Pin, uint8_t Volt);
    Controll(uint8_t Pin);
    void begin();
    void on();
    void highSpd();
    void midSpd();
    void lowSpd();
    void off();
};

#endif
