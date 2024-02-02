#include "GY521.h"
#include <CTBot.h>

CTBot myBot;

String ssid = "amy";
String password = "amyapp12";

String token = "6354371750:AAGoGCW7mnT7NlMsckta5WiFgRYgQtyg0Ek";
const int id = 1395759591;

GY521 sensor(0x68);

uint32_t counter = 0;


void setup()
{
  Serial.println("Starting Bot ...");
  
  myBot.wifiConnect(ssid, password);

  myBot.setTelegramToken(token);

  if(myBot.testConnection())
  {
    Serial.print("Koneksi berhasil");
  }
  else
  {
    Serial.print("Koneksi gagal");
  }

  
  pinMode(D13, OUTPUT);
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
  Serial.print(x, 1);
  Serial.print('\t');
  Serial.print(y, 1);
  Serial.print('\t');
  Serial.print(z, 1);
  Serial.println();

  counter++;

  if(x > 40 || x < -40 && y < 25 || y > -65)
  {
    for (int i =  0; i < 10; i++)
    {
      digitalWrite(D13, HIGH);
      delay(50);
      digitalWrite(D13, LOW);
      delay(50);
    } 
    myBot.sendMessage(id, "Target Terjatuh");
    
  }
   
}
