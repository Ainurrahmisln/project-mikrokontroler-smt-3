#include "GY521.h"
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

char IdNya[] = "Vpd8Ry0rYJt4orKK_ANbhgXG6GuwsUz6";
char Wifi[] = "amy";
char Pass[] = "amyapp12";

void setup() {

  Serial.begin(9600);
  pinMode(D10, OUTPUT);
  Blynk.begin(IdNya, Wifi, Pass, "blynk-cloud.com", 8080);

}

void loop() {
  Blynk.run();

}