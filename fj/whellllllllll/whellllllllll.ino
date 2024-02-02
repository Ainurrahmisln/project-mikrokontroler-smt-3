
#include <CTBot.h>
#include <Wire.h>
#include "GY521.h"



GY521 sensor(0x68);

uint32_t counter = 0;

CTBot myBot;

String ssid = "amy";
String pass = "amyapp12";

String token = "6354371750:AAGoGCW7mnT7NlMsckta5WiFgRYgQtyg0Ek";
const int id = 1395759591;

void setup()
{
  Serial.begin(115200);

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
  sensor.read();
  float x = sensor.getAngleX();
  float y = sensor.getAngleY();
  float z = sensor.getAngleZ();

  if (counter % 10 == 0)
  {
    //Serial.println("\nCNT\tX\tY\tZ");
  }

  // Serial.print(counter);
  // Serial.print('\t');
  Serial.print(x, 1);
  Serial.print('\t');
  Serial.print(y, 1);
  Serial.print('\t');
  Serial.print(z, 1);
  Serial.println();

  counter++;
  delay(100);

  if(x > 70 || x < -70 || y > 70 || y < -70)
  {
    Serial.print("TARGET TERJATUH   ");
    for(int i = 0; i < 10; i++)
    {
       digitalWrite(D10, HIGH);
      delay(50);
      digitalWrite(D10, LOW);
      delay(25);
    }
    myBot.sendMessage(id, "TARGET TERJATUH, LALU MENGALAMI STROKE");
    delay(3000);
  }
}
