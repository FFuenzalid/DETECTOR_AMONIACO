void ConnectWiFi_STA(bool useStaticIP = false)
{
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   if(useStaticIP) WiFi.config(ip, gateway, subnet);
   Serial.println("Conecting...\n");
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(300);
     Serial.print('.'); 
   }
 
   Serial.println("");
   Serial.print("Connected at SSID:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t\t\t");
   Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP = false)
{ 
   Serial.println("");
   WiFi.mode(WIFI_AP);
   while(!WiFi.softAP(ssid, password))
   {
     Serial.println(".");
     delay(100);
   }
   if(useStaticIP) WiFi.softAPConfig(ip, gateway, subnet);

   Serial.println("");
   Serial.print("Iniciado AP:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.softAPIP());
}
