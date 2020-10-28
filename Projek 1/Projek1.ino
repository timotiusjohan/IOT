
const int ledHijau = 23;
const int ledMerah = 26;
const int ledKuning = 27;

int ledMerahState = LOW;
int ledKuningState = LOW;
int ledHijauState = LOW;

long StartTime = 0;


long interval = 10000;

void setup() {
    pinMode(ledMerah, OUTPUT);  
    pinMode(ledKuning, OUTPUT);      
    pinMode(ledHijau, OUTPUT);      
}

void loop(){
  unsigned long CheckTime = millis();
  unsigned long elapsedTime = CheckTime - StartTime;

 if(elapsedTime > interval) {
    StartTime = CheckTime;
 }

  if (elapsedTime < 4000){
    ledMerahState = HIGH;             
    ledKuningState = LOW;            
    ledHijauState = LOW ; 
  }

   if (elapsedTime > 4000 && elapsedTime < 7000 ){
    ledMerahState = LOW;             
    ledKuningState = LOW;            
    ledHijauState = HIGH;
  }

  if (elapsedTime > 7000  ){ 
    ledMerahState = LOW;             
    ledKuningState = HIGH;            
    ledHijauState = LOW ;
  }

  digitalWrite(ledMerah,ledMerahState);
  digitalWrite(ledKuning,ledKuningState);
  digitalWrite(ledHijau,ledHijauState);

}
                       
