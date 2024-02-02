#define BLYNK_TEMPLATE_ID "TMPL61XuFOYZq"
#define BLYNK_TEMPLATE_NAME "Wheel chair"
#define BLYNK_AUTH_TOKEN "HTOoCrzfBqaYGBWTK_5S79nT1YxmiRuh"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "GY521.h"
#include <Wire.h> 
#include <CTBot.h>

char auth[] = "HTOoCrzfBqaYGBWTK_5S79nT1YxmiRuh";
char ssid[] = "amy";
char pass[] = "amyapp12";

GY521 sensor(0x68);

uint32_t counter = 0;

CTBot myBot;

String token = "6354371750:AAGoGCW7mnT7NlMsckta5WiFgRYgQtyg0Ek";
const int id = 1395759591;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D10, OUTPUT);
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
  sensor.axe = 0.0;
  sensor.aye = 0.0;
  sensor.aze = 0.0;
  sensor.gxe = 0.0;
  sensor.gye = 0.0;
  sensor.gze = -10.0;

  Serial.println("Bot is starting ...");

  //koneksi wifi
  myBot.wifiConnect(ssid, pass);

  //set token telegram
  myBot.setTelegramToken(token);

  if (myBot.testConnection())
  {
    Serial.println("Connection Success");
  }
  else
    {
      Serial.println("Connection failed");
    }
}


void loop()
{
  Blynk.run();
  sensor.read();
  float x = sensor.getAngleX();
  float y = sensor.getAngleY();
  float z = sensor.getAngleZ();

  Serial.print(x, 1);
  Serial.print('\t');
  Serial.print(y, 1);
  Serial.print('\t');
  Serial.print(z, 1);
  Serial.println();
  Blynk.virtualWrite(V0, x);
  delay(100);

  if(x > 70 || x < -70 || y > 70 || y < -70)
  {
    Serial.print("TARGET TERJATUH");
    for(int i = 0; i < 10; i++)
    {
      digitalWrite(D10, HIGH);
      delay(50);
      digitalWrite(D10, LOW);
      delay(25);
    }
    myBot.sendMessage(id, "TARGET TERJATUH");
    delay(3000);
  }
}
