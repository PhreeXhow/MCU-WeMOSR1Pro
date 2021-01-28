#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

const char* host = "ESP";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Booting Sketch...");
  WiFiManager wifiManager;
  Serial.println("Starting WiFi OR Starting WiFi Config Manager...");
  wifiManager.autoConnect("ConfigESP");
  Serial.println("Starting mDNS Service...");
  MDNS.begin(host);
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n\n\n", host);
}

void loop(void) {
  httpServer.handleClient();
  MDNS.update();
}
