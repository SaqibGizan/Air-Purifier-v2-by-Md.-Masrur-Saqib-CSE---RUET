/*
 * Author: Md. Masrur Saqib, CSE-18, RUET
 * Organization: Gizan-Tech
 * Date of creation: 05-Nov-20
 * Project Name: Low Cost Air Purifier
 * Last Modification: 13-Dec-20
 * Modified by: Md. Masrur Saqib
 */

#include"Display.h"
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

Display :: Display()
{

}

void Display :: begin()
{
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Low cost AirPurifier");
  lcd.setCursor(0, 1);
  lcd.print("         by         ");
  lcd.setCursor(0, 2);
  lcd.print("  Md. Masrur Saqib  ");
  lcd.setCursor(0, 3);
  lcd.print("       Gizan        ");
  delay(5000);
}

void Display :: show(int x, int y, String text)
{
  lcd.setCursor(x, y);
  lcd.print(text);
}

void Display :: show(int x, int y, float num)
{
  num *= 100;
  int ver = num;
  num = ver / 100.0;
  lcd.setCursor(x, y);
  lcd.print(num);
}

void Display :: show(int x1, int x2, int y, float num)
{
  String numt = String(num);
  int size = numt.length();
  int x = x2 - size;
  lcd.setCursor(x1, y);
  for (int i = 0 ; i < x - x1; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(x, y);
  lcd.print(num);

}

void Display :: show(int x, int y, double num)
{
  lcd.setCursor(x, y);
  num *= 100;
  int ver = num;
  num = ver / 100.0;
  lcd.print(num);
}

void Display :: show(int x, int y, int num)
{
  lcd.setCursor(x, y);
  lcd.print(num);
}

void Display :: legend()
{
  lcd.setCursor(0, 0);
  lcd.print("DustLvL        ug/m3");
  lcd.setCursor(0, 1);
  lcd.print("Humidity        %   ");
  lcd.setCursor(0, 2);
  lcd.print("Temper          C   ");
  lcd.setCursor(0, 3);
  lcd.print("AirQuality          ");
  delay(500);
}
