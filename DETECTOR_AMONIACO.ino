#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include "config.h"                           // Networking Data 
#include "Server.hpp"                         // URI Handler
#include "ESP8266_Utils.hpp"                  // Wifi Conection Handler

void setup(void) {
   Serial.begin(9600);
   SPIFFS.begin();
   
   ConnectWiFi_STA();

   InitServer();
}

void loop(void) {
  
}
