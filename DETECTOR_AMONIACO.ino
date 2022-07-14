#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include "config.h"          // Networking Data
#include "Server.hpp"        // URI Handler (#DEBUG: AQUI ESTAN TODOS LOS PROBLEMAS)
#include "ESP8266_Utils.hpp" // Wifi Conection Handler

void setup(void)
{

   if (!SPIFFS.begin())
   {
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
   }

   Serial.begin(9600);
   SPIFFS.begin();

   ConnectWiFi_STA();

   InitServer();
}

void loop()
{
   // To access your stored values on inputString, inputInt, inputFloat
   String numero_1 = readFile(SPIFFS, "/numero_1.txt");
   Serial.print("*** numero_1: ");
   Serial.println(numero_1);

   String numero_2 = readFile(SPIFFS, "/numero_2.txt");
   Serial.print("*** numero_2: ");
   Serial.println(numero_2);

   String numero_3 = readFile(SPIFFS, "/numero_3.txt");
   Serial.print("*** numero_3: ");
   Serial.println(numero_3);
   delay(5000);
}
