#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

#include "Webserver.hpp"
/* Put your SSID & Password */
#include "WifiCreds.hpp"

/* Put IP Address details */
IPAddress local_ip(192,168,1,254);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

Webserver::Webserver(): server(80) {}

void Webserver::wifi_init(){
  WiFi.mode(WIFI_STA);
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
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
