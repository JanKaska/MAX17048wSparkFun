/*
 * EXAMPLE CODE FOR MAX17048 and OLED display with SH1106 driver IC 
 * REading data from MAX17048 using SparkFun library and displaying them on the OLED.
 *
 * https://github.com/LasKKit/
 * laskarduino.cz
 * 2022
 *
 * Compile it as "ESP32-WROOM-DA"
 *
 *  Produkt jeste neni.
 *  Produkt jeste neni.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> //Nutné stáhnout knihovnu - https://github.com/adafruit/Adafruit_SH110X
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h> 
//Nutné stáhnout knihovnu MAX17048 -  http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library

SFE_MAX1704X lipo(MAX1704X_MAX17048);

#define i2c_Address 0x3c //Na této adrese je displej, pokud nebude fungoval zkuste vyměnit za 0x3d
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1); //Přiřadí displej, tloušťku a výšku

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    lipo.enableDebugging();
    lipo.begin();
    lipo.quickStart();
    lipo.setThreshold(20);
    delay(250);
    display.begin(i2c_Address, true); // Address 0x3C default
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE); //Nastaví barvu displeje
    display.setTextSize(1); //Nastaví velikost písma
    
}

void loop()
{
  
   display.setCursor(0,0); //Nastaví kurzor na základní pozici. 
   display.println((String)"Napeti na beterii:"+lipo.getVoltage()+"V"); //Vypíše na display napětí baterie
   display.println((String)"Nabiti baterie:"+lipo.getSOC()+" \%"); //Vypíše na display příblyžné nabití baterie v procentech
   if (lipo.getAlert()){
    display.println("Baterie temer vybita!");
    }
    else{
    display.println("Baterie v poratku.");
      }
   display.display(); 
   Serial.println((String)"VCELL V   : "+lipo.getVoltage()+"V");
   Serial.println((String)"VCELL SOC : "+lipo.getSOC()+" \%");
   Serial.println((String)"Alltert : "+lipo.getAlert());
   Serial.println();
   delay(500);
   display.clearDisplay();
}
