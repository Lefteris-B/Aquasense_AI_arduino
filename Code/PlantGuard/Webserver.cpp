#include "Webserver.hpp"
/* Put your SSID, Password, and IP address details */
#include "WiFiInfo.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

Webserver::Webserver(): server(80) {}

void Webserver::wifi_init(){
  IPAddress ip, subnet, gateway;
  ip.fromString(IP_ADDRESS);
  subnet.fromString(SUBNET_MASK);
  gateway.fromString(GATEWAY_ADDRESS);
  
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println(WiFi.localIP());
}
void Webserver::server_init(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
         request->send(SPIFFS, "/index.html", "text/html");
    });
  server.serveStatic("/assets", SPIFFS, "/assets/");
  server.begin();
  Serial.println("HTTP server started");
}
void Webserver::fs_init(){
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}
void Webserver::begin(){
    fs_init();
    wifi_init();
    server_init();
  }
