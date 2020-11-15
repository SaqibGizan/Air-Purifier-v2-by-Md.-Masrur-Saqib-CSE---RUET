#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include<Arduino.h>

class Display {

  public:
    Display();
    void begin();
    void legend();
    void show(int x, int y, int num);
    void show(int x, int y, double num);
    void show(int x, int y, float num);
    void show(int x, int y, String text);
    void show(int x1, int x2, int y, float num);
    void legendVal(float dust, float hum, float temp, String quality);


};

#endif
