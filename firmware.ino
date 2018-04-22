STARTUP(WiFi.selectAntenna(ANT_AUTO));

int valvePin = D4;
int moistureSensor1 = A0;
int moistureSensor2 = A1;
int moistureSensor3 = A2;
int moisturePower1 = D0;
int moisturePower2 = D1;
int moisturePower3 = D2;
float avgMoisture;
int actuationThreshold;
int isWatering = false;
int wetThreshold;


void setup() {

    Serial.begin(9600);
    pinMode(valvePin, OUTPUT);
    Particle.function("actuate", actuate);
    Particle.function("getState", getState);
    setupHardware();
    timerStart();
    Particle.subscribe("moisture", actuationController);


}
// turnValveTimerOff(){
//   valveTimer.stop();
//   actuate("close");
// }

//Timer valveTimer = timer(6000,turnValveTimerOff(),true);//6 seconds


void actuationController(const char *event, const char *data){
  String reading = String(data);
  int soilValue = reading.toInt();
  if(soilValue >= actuationThreshold){
    actuate("open");
    //valveTimer.start();
    isWatering = true;
  }
  else{
    isWatering = false;
    actuate("close");
  }
  

}

void valveOn(){
  digitalWrite(valvePin, LOW)
}

void valveOff(){
  digitalWrite(valvePin, HIGH);
}

void setupHardware(){
  digitalWrite(valvePin, HIGH); // close the valve
  pinMode(moistureSensor1, INPUT);
  pinMode(moistureSensor2, INPUT);
  pinMode(moistureSensor3, INPUT);
  pinMode(moisturePower1, OUTPUT);
  pinMode(moisturePower2, OUTPUT);
  pinMode(moisturePower3, OUTPUT);
  unPowerSensors();

}

void publishState(){
  powerSensors();
  int sensorVal1 = analogRead(moistureSensor1);
  int sensorVal2 = analogRead(moistureSensor2);
  int sensorVal3 = analogRead(moistureSensor3);
  avgMoisture = average(sensorVal1, sensorVal2, sensorVal3);
  String publishVal = String(avgMoisture);
  Particle.publish("moisture", publishVal);
  unPowerSensors();

}

Timer timer(60000, publishState);

void timerStart(){
  timer.start();
}

float average(int val1, int val2, int val3){
  int sum = val1 + val2 + val3;
  float average = sum/3;
  return average;
}

void powerSensors(){
  digitalWrite(moisturePower1, HIGH);
  digitalWrite(moisturePower2, HIGH);
  digitalWrite(moisturePower3, HIGH);
}

void unPowerSensors(){
  digitalWrite(moisturePower1, LOW);
  digitalWrite(moisturePower2, LOW);
  digitalWrite(moisturePower3, LOW);

}

void loop() {

  if(isWatering){
    int soilReading1 = analogRead(moistureSensor1);
    int soilReading2 = analogRead(moistureSensor2);
    int soilReading3 = analogRead(moistureSensor3);
    float avgValue = average(soilReading1, soilReading2, soilReading3);
    powerSensors();
    valveOn();
    if(avgValue <= wetThreshold){
      valveOff();
      unPowerSensors();
      isWatering = false;
      Particle.publish("status", "stopped");
    }
  }
  // actuate("open");

}


int getState(String command){
    int state = digitalRead(valvePin);
    Particle.publish("state", String(valvePin));
    return state;
}

int actuate(String command){
    //digitalWrite to Solenoid Valve based on which button was pushed on the UI
    if(command=="open"){
        valveOn(); //open the valve
        Particle.publish("state", "Open"); //send the state back to the UI
        return 1;
    }
    else if(command=="close"){
        valveOff(); // close the valve
        Particle.publish("state", "Closed"); //send the state back to the UI
        return 0;
    }
}
