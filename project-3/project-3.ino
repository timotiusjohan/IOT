#include <WiFi.h>
#include <MQTT.h>

int pinLDR = 36;
int pinRelay = 4;
int ldrRead;
int convertPayload;

const char ssid[] = "MUSTIKA B8";
const char pass[] = "evelyn2607";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

 
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ESP32 Johan", "0fce44e7", "8f9125c88d198b64")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/lamp");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(topic == "/lamp"){
    convertPayload = payload.toInt();
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  pinMode(pinRelay,OUTPUT);
  

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  ldrRead=analogRead(pinLDR);
  char cstr[16];
  itoa(ldrRead, cstr, 10);
  client.publish("/lamp/ldrRead",cstr);
  
;
  if(ldrRead < convertPayload){
    digitalWrite(pinRelay, LOW);
    client.publish("/lamp/state","Lampu Menyala");
  }else{
    digitalWrite(pinRelay, HIGH);
    client.publish("/lamp/state","Lampu Mati");
    
  }
}
