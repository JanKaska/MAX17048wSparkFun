/*
 * EXAMPLE CODE FOR MAX17048
 * Reading data from MAX17048 module using SparkFuns library
 *
 * https://github.com/LasKKit/
 * laskarduino.cz
 * 2022
 *
 * Compile it as "ESP32-WROOM-DA"
 *
 *  Produkt jeste neni.
 */

#include <Wire.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
// Nutné stáhnout tuto knihovnu: http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library
//SFE_MAX1704X lipo;
//SFE_MAX1704X lipo(MAX1704X_MAX17043); // Create a MAX17043
//SFE_MAX1704X lipo(MAX1704X_MAX17044); // Create a MAX17044
SFE_MAX1704X lipo(MAX1704X_MAX17048); // Create a MAX17048
//SFE_MAX1704X lipo(MAX1704X_MAX17049); // Create a MAX17049

double voltage = 0; // Proměná pro kontorlování napětí baterie
double soc = 0; // Proměná pro kontorlování stavu nabití baterie i.e. state-of-charge (SOC)
bool alert; // Proměná která kontroluje jestly se baterie dostala pod určitou hranici

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lipo.begin()
  lipo.enableDebugging();
  lipo.quickStart();
  // Lze nastavit přerušení pokud napětí baterie klesne pod určitou hodnotu
  // Můžeme nastavit kdekoliv mezi 1% - 32%:
  lipo.setThreshold(20); // Nastavý hodnotu pod kterou baterie spustí alarm jako 20%.
  
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage = lipo.getVoltage();
  soc = lipo.getSOC();
  alert = lipo.getAlert();
  Serial.println((String)"Napětí: "+voltage+" V"); //Vypíše napětí baterie
  Serial.println((String)"Percentage: "+soc+" %"); //Vypíše momentální stav baterie
  Serial.println((String)"Alert: "+alert); //Vypíše jesty napětí baterie kleslo pod určenou hodnotu
  Serial.println();
  delay(500);
}
