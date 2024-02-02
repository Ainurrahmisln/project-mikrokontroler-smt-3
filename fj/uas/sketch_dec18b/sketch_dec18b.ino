#include "GY521.h"
#include <CTBot.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>

CTBot myBot;

char auth[] = "Vpd8Ry0rYJt4orKK_ANbhgXG6GuwsUz6";
char ssid[] = "amy";
char pass[] = "amyapp12";

BlynkTimer timer;

GY521 sensor(0x68);

uint32_t counter = 0;

void sendTelegramMessage(const char* message)
{

  myBot.sendMessage(1395759591, message);
}

void setup()
{
  Serial.println("Starting Bot ...");

  myBot.wifiConnect(ssid, password);

  myBot.setTelegramToken(token);

  if (myBot.testConnection())
  {
    Serial.println("Koneksi berhasil");
  }
  else
  {
    Serial.println("Koneksi gagal");
  }

  Blynk.begin(auth, ssid, pass);

  pinMode(D10, OUTPUT);
  Serial.begin(115200);
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
  sensor.axe = 0.574;
  sensor.aye = -0.002;
  sensor.aze = -1.043;
  sensor.gxe = 10.702;
  sensor.gye = -6.436;
  sensor.gze = -0.676;

  timer.setInterval(1000L, checkOrientation); // Check orientation every second
}

void loop()
{
  Blynk.run();
  timer.run();
}

void checkOrientation()
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
  Serial.print(x, 1);
  Serial.print('\t');
  Serial.print(y, 1);
  Serial.print('\t');
  Serial.print(z, 1);
  Serial.println();

  counter++;

  if (x > 40 || x < -40 && y < 25 || y > -65)
  {
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(D10, HIGH);
      delay(50);
      digitalWrite(D10, LOW);
      delay(50);
    }
    sendTelegramMessage("Target Terjatuh");
    Blynk.notify("Target Terjatuh");
  }
}
