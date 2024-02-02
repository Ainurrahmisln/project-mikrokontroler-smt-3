//
//    FILE: GY521_angle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read angleX, angleY, angleZ
//     URL: https://github.com/RobTillaart/GY521

#include <SPI.h>
#include "GY521.h"

GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  SPI.begin();

  Serial.println("CLEARSHEET");
  Serial.println("LABEL, DATA");

  pinMode(D10, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s

  sensor.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor.axe = 0.002;
  sensor.aye = 0.002;
  sensor.aze = 0.002;
  sensor.gxe = 0.002;
  sensor.gye = 0.002;
  sensor.gze = 0.002;
}


void loop()
{
  sensor.read();
  float x = sensor.getAngleX();
  float y = sensor.getAngleY();
  float z = sensor.getAngleZ();

  if (counter % 10 == 0)
  {
    //  Serial.println("\nCNT\tX\tY\tZ");
  }

  //  Serial.print(counter);
  //  Serial.print('\t');
  // Serial.print(x, 1);
  // Serial.print('\t');
  // Serial.print(y, 1);
  // Serial.print('\t');
  // Serial.print(z, 1);
  // Serial.println();

  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(" ");


  counter++;

  if(x > 75 || x < -75 || y > 75 || y < -75)
  {
    digitalWrite(D10, HIGH);
    delay(50);
    digitalWrite(D10, LOW);
    delay(50);
  }
}