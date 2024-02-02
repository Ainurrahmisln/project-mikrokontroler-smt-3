#include <LiquidCrystal_I2C.h>

#include <dummy.h>

#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define BLYNK_TEMPLATE_ID "TMPL6knOLM0YX"
#define BLYNK_TEMPLATE_NAME "Digital Ruler Pengukur Tinggi Badan"
#define BLYNK_AUTH_TOKEN "ioK2P_L8mZwYX0OlcrNrgRaWgDE-wjZu"

#define TRIG_PIN D6
#define ECHO_PIN D5

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "amy";
const char* password = "amyapp12";
 
int ledPin1 = D4;
int ledPin2 = D3;
int ledPin3 = D2;

WiFiServer server(80);
 
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);  
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW); 
  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }  

  Serial.begin(115200);
  
  server.begin(); 

  lcd.init();                     
  lcd.backlight();
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("Server Address:");
  lcd.setCursor(0,1);
  lcd.println(WiFi.localIP());

  Serial.print("Server Address:");
  Serial.println(WiFi.localIP());

}
 
void loop() {  
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate distance in centimeters using the speed of sound (343 meters per second)
  distance = (duration * 0.0343) / 2;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(distance);
  lcd.print("cm");

  delay(500);

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  while(!client.available())
  {
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  client.flush();
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    value = LOW;
  } 

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Status LED : ");
 
  if(value == HIGH) {
    client.print("On");
  } 
  else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>"); 
  delay(1);
}