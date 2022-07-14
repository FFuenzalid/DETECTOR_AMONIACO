AsyncWebServer server(80);

// GET request will be sent to <ESP_IP>/get?PARAM_INPUT_X=<PARAM_INPUT_XMessage>
String PARAM_INPUT_1 = "numero_1";
String PARAM_INPUT_1 = "numero_2";
String PARAM_INPUT_1 = "numero_3";

String readFile(fs::FS &fs, const char *path)
{
   Serial.printf("Reading file: %s\r\n", path);
   File file = fs.open(path, "r");
   if (!file || file.isDirectory())
   {
      Serial.println("- empty file or failed to open file");
      return String();
   }
   Serial.println("- read from file:");
   String fileContent;
   while (file.available())
   {
      fileContent += String((char)file.read());
   }
   file.close();
   Serial.println(fileContent);
   return fileContent;
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
   Serial.printf("Writing file: %s\r\n", path);
   File file = fs.open(path, "w");
   if (!file)
   {
      Serial.println("- failed to open file for writing");
      return;
   }
   if (file.print(message))
   {
      Serial.println("- file written");
   }
   else
   {
      Serial.println("- write failed");
   }
   file.close();
}

String processor(const String &var)
{
   if (var == "numero_1")
   {
      return readFile(SPIFFS, "/numero_1.txt");
   }
   else if (var == "numero_2")
   {
      return readFile(SPIFFS, "/numero_2.txt");
   }
   else if (var == "numero_3")
   {
      return readFile(SPIFFS, "/numero_3.txt");
   }
   return String();
}

const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html><head>
   <title>Formulario de configuracion</title>
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <script>
   function submitMessage() {
     alert("Saved value to ESP SPIFFS");
     setTimeout(function(){ document.location.reload(false); }, 500);   
   }
   </script>
    </head>
    <body style="background-color:#f3ecd7;">
      <h1> Formulario de configuracion. </h1>

      <form action="/get"> 
        Mensaje actual: "numero_1" <br>
        inputString (current value %numero_1%): <br>
        <input type="text" name="numero_1" required pattern="[\w\s]{2,80}" title="Mensaje entre 2 y 80 caracteres">
        <input type="submit" value="Cambiar">
      </form>

      <h4> Formato de numero ejem: +82337656321</h4>

      <form action="/get">
        Telefono 1 actual: "numero_2" <br>
        <input type="text" name="numero_2" required pattern="^\+[0-9]{11}">
        <input type="submit" value="Cambiar">
      </form><br>

      <form action="/get">
        Telefono 2 actual: "numero_3" <br>
        <input type="text" name="numero_3>" required pattern="^\+[0-9]{11}">
        <input type="submit" value="Cambiar">
      </form><br>

</body></html>)rawliteral";

String telefono[10] = {"+56993025767", "+56958941206", "+56973787352"};

void InitServer()
{
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/html", index_html); });

   server.onNotFound([](AsyncWebServerRequest *request)
                     { request->send(400, "text/plain", "Not found"); });

   // ############### WORKING ON THIS ################
   // este GET debe insertar el dato en la SPIFFS

   server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
             {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      Serial.println(inputMessage);

      writeFile(SPIFFS, "/numero_1.txt", inputMessage.c_str());
    }
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      writeFile(SPIFFS, "/numero_2.txt", inputMessage.c_str());
    }
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      writeFile(SPIFFS, "/numero_3.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage); });

   // ############# END WORKING ################

   server.begin();
   Serial.println("HTTP server started");
}
