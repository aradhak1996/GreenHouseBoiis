// #define PHOTO_POWER A5
// #define PHOTO_PIN   A0

int PHOTO_POWER = A5;
int PHOTO_PIN = A0;
char PhotoData[40];
int analogValue;
int pVal;

void setup() {

    pinMode(PHOTO_POWER, OUTPUT);
    pinMode(PHOTO_PIN, INPUT);

    digitalWrite(PHOTO_POWER, HIGH);
    Particle.variable("analogValue", &analogValue, INT);
    Particle.variable("powerVal", &pVal, INT);

}



void loop() {

    // int sensorVal = analogRead(PHOTO_PIN);
    analogValue = analogRead(PHOTO_PIN);
    pVal = analogRead(PHOTO_POWER);
    // sprintf (PhotoData, "Sensor Value is %d.", sensorVal);

    // Particle.publish("Sensor Value", PhotoData, PRIVATE);
    delay(1000);


}