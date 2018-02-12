
//Wiring (Photon ⇒ OLED screen):
// D4 ⇒ CS
// D3 ⇒ DC
// D5 ⇒ RST
// A5 ⇒ D1
// A3 ⇒ D0
// 3V3 ⇒ VCC
// GND ⇒ GND

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

String level = "";

void setup() {

    display.begin(SSD1306_SWITCHCAPVCC);

    display.setTextSize(2);       // text size
    display.setTextColor(WHITE); // text color

}

char publishString_WiFiData[40];


void loop() {

    updateLevel();
    
    int n = -WiFi.RSSI();
    sprintf (publishString_WiFiData,"Wifi Strength is %d.",n);
    
    Particle.publish("Wifi Strength", publishString_WiFiData, PRIVATE);

    display.clearDisplay();
    display.setCursor(1, 1);
    display.print("WiFi: ");
    display.print(String(-WiFi.RSSI()));
    display.setCursor(1, 20);
    display.print("By: Lucas");
    display.setCursor(1, 41);
    display.setTextSize(1);
    display.print("-The Best TA");
    display.setCursor(1, 51);
    display.print("your WiFi is: "+level);
    display.setTextSize(2);
    display.display();
    delay(500);
    
}

void updateLevel(){
   
   if((-WiFi.RSSI()) < 20 && (-WiFi.RSSI()) > 0){
       level = "AHH!!!";
   } 
   else if((-WiFi.RSSI()) < 40 && (-WiFi.RSSI()) >= 20){
       level = "amazing";
   }
     else if((-WiFi.RSSI()) < 60 && (-WiFi.RSSI()) >= 40){
       level = "great";
   }
     else if((-WiFi.RSSI()) < 80 && (-WiFi.RSSI()) >= 60){
       level = "alright";
   }
    else if((-WiFi.RSSI()) < 100 && (-WiFi.RSSI()) >= 80){
       level = "bad";
   }
     else if((-WiFi.RSSI()) >= 100){
       level = "crap";
   }
   
   
}