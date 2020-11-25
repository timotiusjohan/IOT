#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "https://simplesmarthome-1b41e.firebaseio.com/"
#define FIREBASE_AUTH "WB31Ak8BiihxblSgoMek3Oq70rktPMaunTTMzght"
#define WIFI_SSID "MUSTIKA B8"
#define WIFI_PASSWORD "evelyn2607"

#define relayPin 4
#define ldrPin 36

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;

String path = "/Node1";

int ldrRead;

void setup(){
  Serial.begin(115200);

  conWifi();
  pinMode(relayPin, OUTPUT);
  pinMode(ldrPin, INPUT);

}

void loop(){
  delay(500);

  ldrRead = analogRead(ldrPin);
  char cstr[16];
  itoa(ldrRead, cstr, 10);
  Firebase.setString(firebaseData, path + "/curValue", cstr);
  if(Firebase.getString(firebaseData, path + "/rangeValue")){
    String range = firebaseData.stringData();
    int rangeValue = range.toInt();
    if(ldrRead < rangeValue){
      digitalWrite(relayPin, LOW);
      Firebase.setString(firebaseData, path + "/state", "Lampu Menyala");
    }else{
      digitalWrite(relayPin, HIGH);
      Firebase.setString(firebaseData, path + "/state", "Lampu Mati");
    }
  }
}

void conWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
