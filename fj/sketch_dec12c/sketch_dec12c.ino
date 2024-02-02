#include <CTBot.h>

CTBot myBot;

String ssid = "amy";
String password = "amyapp12";

String token = "6354371750:AAGoGCW7mnT7NlMsckta5WiFgRYgQtyg0Ek";
const int id = 1395759591;

void setup() {
  Serial.begin(9600);

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

  myBot.sendMessage(id, "Target Terjatuh");

}

void loop() {
  // put your main code here, to run repeatedly:

}
