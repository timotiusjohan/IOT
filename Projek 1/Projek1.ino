#include "DHT.h"

const int DHTPIN = 0;
const int buttonPin = 4;
const int ledMerah = 27;
const int ledKuning = 26;
const int ledHijau = 23;

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int buttonState = 0;
boolean start = false;

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  pinMode(buttonPin, INPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  
  
  dht.begin();
}

void loop() {
  delay(200);
  buttonState = digitalRead(buttonPin);
  

  Serial.println(start);
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if(buttonState == HIGH){
    start = !start;
  }
  if(start==1){
    if(t<35){
        digitalWrite(ledMerah, LOW);
        digitalWrite(ledKuning, LOW);
        digitalWrite(ledHijau, HIGH);
      }else if(t>=35 && t<=50){
        digitalWrite(ledMerah, LOW);
        digitalWrite(ledHijau, HIGH);
        digitalWrite(ledKuning, HIGH);  
      }else if(t>50){
        digitalWrite(ledHijau, HIGH);
        digitalWrite(ledKuning, HIGH);
        digitalWrite(ledMerah, HIGH);  
      }
    Serial.print(t);
    Serial.print(F("°C "));
  }else{
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW); 
  }

  
}
