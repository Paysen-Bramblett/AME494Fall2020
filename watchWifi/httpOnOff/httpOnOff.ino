#include <Arduino.h>
#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

char * HOSTNAME = "test";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);



void setup() {
    Serial.begin(115200);


  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);

    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_WHITE);
    ttgo->tft->setTextColor(TFT_BLACK, TFT_WHITE);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("Ready",  5, 10);
    
    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);
    // handle index -- HTTP Server
    
    server.on("/on", []() {
      Serial.println(1);
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("ON",  5, 10);  
       server.send(200, "");
       digitalWrite(25, HIGH);
       digitalWrite(26, HIGH);
    });

    server.on("/off", []() {
      Serial.println(0);
      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString("OFF",  5, 10);  
       server.send(200, "");
       digitalWrite(25, LOW);
       digitalWrite(26, LOW);
    });
 
    server.begin();
    
}

void loop() {
    server.handleClient();
}
