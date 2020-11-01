#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#define DHTTYPE DHT11

char auth[] = "9CRUqB_4d0xOCrFdQ2m6KUxs_Nrz2hjZ"; //token dari email
char ssid[] = "MUSTIKA B8"; //nama wifi
char pass[] = "**********"; //password

const int ledHijau = 26;
const int ledKuning = 27;
const int ldrPin = 36;
const int dhtPin = 4;
float sensorSuhu;
int sensorCahaya;
int sliderSuhu;
int sliderCahaya;
int buttonState;

DHT dht(dhtPin, DHTTYPE);

BlynkTimer timer; 

BLYNK_WRITE(V4){
  int TH_Cahaya = param.asInt();
  sliderCahaya = TH_Cahaya;
}

BLYNK_WRITE(V5){
  int TH_Suhu = param.asInt();
  sliderSuhu = TH_Suhu;
}

BLYNK_WRITE(V8){
  int button = param.asInt();
  buttonState = button;
}

void sendSensor(){ 
  sensorCahaya = analogRead(ldrPin);
  int cahaya = 0.009768*sensorCahaya +10;
  Blynk.virtualWrite(V0, cahaya);
  Blynk.virtualWrite(V2, cahaya);

  sensorSuhu = dht.readTemperature();
  Blynk.virtualWrite(V1, sensorSuhu);
  Blynk.virtualWrite(V3, sensorSuhu);

  WidgetLED ledSuhu(V7);
  if(sensorSuhu>sliderSuhu){
    Blynk.setProperty(V7, "color", "#FF0000");
    ledSuhu.on();
  }else{
    Blynk.setProperty(V7, "color", "#00FF00");
    ledSuhu.on();
  }

  WidgetLED ledCahaya(V6);
  if(sensorCahaya>sliderCahaya){
    Blynk.setProperty(V6, "color", "#FF0000");
    ledCahaya.on();
  }else{
    Blynk.setProperty(V6, "color", "#00FF00");
    ledCahaya.on();
  }
  
}



void setup(){
  // Debug console
  Serial.begin(9600);

  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,73), 8080);

  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop(){
    Blynk.run();
    if(buttonState == 1){
      if(sensorCahaya>sliderCahaya){
        digitalWrite(ledKuning, HIGH);
      }else{
        digitalWrite(ledKuning, LOW);
      }

      if(sensorSuhu>sliderSuhu){
        digitalWrite(ledHijau, HIGH);
      }else{
        digitalWrite(ledHijau, LOW);
      }
      Serial.println(buttonState);
      timer.run();
    }
      
  
}
