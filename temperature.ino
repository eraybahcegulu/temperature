#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <FirebaseESP8266.h>

#define firebase_erisim_linki ""
#define firebase_sifre ""
#define FIREBASE_PATH ""

FirebaseData firebaseData;

const int oneWireBus = 4;     

OneWire oneWire(oneWireBus);

DallasTemperature sensors(&oneWire);

char ssid[] = "";
char pass[] = ""; 

void setup() {

  Serial.begin(115200);
  
   WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("Bağlantı kuruluyor");
    while (WiFi.status() != WL_CONNECTED) 
    { 
      delay(500); 
      Serial.print(".");
    }
  Serial.println(""); 
  Serial.println("Bağlantı sağlandı...");

  Firebase.begin(firebase_erisim_linki, firebase_sifre);  
  sensors.begin();
}

void loop() {
  WiFiClient istemci;
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("Sıcaklık: ");
  Serial.print(temperatureC);
  Serial.println("ºC");
  Firebase.setFloat(firebaseData, FIREBASE_PATH, temperatureC);
  delay(5000);
}