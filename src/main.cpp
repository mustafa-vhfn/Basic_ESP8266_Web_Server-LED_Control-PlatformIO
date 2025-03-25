/*********
  mustafa-vhfn
  https://github.com/mustafa-vhfn

*********/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char *ssid = "Your_SSID";       // Replace with your network's SSID
const char *password = "Your_Password";   // Replace with your network's password

const int led1 = D1; // GPIO5
const int led2 = D2; // GPIO4

AsyncWebServer server(80);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");


  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - startAttemptTime >= 10000) { 
      Serial.println("Failed to connect to Wi-Fi.");
      return;
    }
  }

  Serial.println("Connected to Wi-Fi");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!LittleFS.begin()) {
    Serial.println("Error mounting LittleFS!");
    return;
  }

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");

  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(led1, HIGH);
    request->send(200, "text/plain", "LED 1 is ON");
  });

  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(led1, LOW);
    request->send(200, "text/plain", "LED 1 is OFF");
  });

  server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(led2, HIGH);
    request->send(200, "text/plain", "LED 2 is ON");
  });

  server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(led2, LOW);
    request->send(200, "text/plain", "LED 2 is OFF");
  });

  server.begin();
  Serial.println("Server started!");
}

void loop() {}
