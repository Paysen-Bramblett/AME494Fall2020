#include <Arduino.h>
#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

const int ledPin1 = 25;
const int ledPin2 = 26;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

char * HOSTNAME = "test12345";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>



WebServer server(80);


void setup() {
    Serial.begin(115200);

    pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
 // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin1, ledChannel);
  ledcAttachPin(ledPin2, ledChannel);

  
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

    
    server.on("/", []() {
      digitalWrite(21, 1);
      String v = server.arg("v");
      int slider = v.toInt();
      Serial.println(v);

      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString(v,  5, 10); 
      ledcWrite(ledChannel, slider);

       
      server.send(200, "text/html", "<html><head><script>function foo(v){window.location.href=\"./?v=\" + v}</script></head><body><input type='range' max='100' min=\"0\" onchange='foo(this.value)' id='theText'></body><script>document.getElementById(\"theText\").value=parseInt(window.location.search.replace(\"?v=\",\"\"))</script><html>");
    });

    
    server.begin();
    
}

void loop() {
    server.handleClient();  
}
