#include "Webserver.hpp"
#include "Weather.hpp"
/* Put your SSID, Password, and IP address details */
#include "WiFiInfo.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

Webserver::Webserver(Weather* weather):server(80) {
  this->weather=weather;
}


void Webserver::wifi_init() {
  IPAddress ip, subnet, gateway, primaryDns, secondDns;
  ip.fromString(IP_ADDRESS);
  subnet.fromString(SUBNET_MASK);
  gateway.fromString(GATEWAY_ADDRESS);
  primaryDns.fromString(PRIMARY_DNS);
  secondDns.fromString(SECONDARY_DNS);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet, primaryDns, secondDns);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println(WiFi.localIP());
}
void Webserver::server_init() {
  server.on("/", HTTP_GET, [this](AsyncWebServerRequest * request) {
    if (request->hasParam("cover")) {
      Serial.println("Cover on");
    }
    if (request->hasParam("latitude")) {
      AsyncWebParameter* p = request->getParam("latitude");
      Serial.println("Latitude: " + p->value());
      this->weather->latitude=p->value().toDouble();
    }
    if (request->hasParam("longtitude")) {
      AsyncWebParameter* p = request->getParam("longtitude");
      Serial.println("Longtitude: " + p->value());
      this->weather->longtitude=p->value().toDouble();
    }
    request->send(SPIFFS, "/index.html", String(), false, std::bind(&Webserver::mainProcessor, this, std::placeholders::_1));
  });
  server.serveStatic("/assets", SPIFFS, "/assets/");
  server.begin();
  Serial.println("HTTP server started");
}
String Webserver::mainProcessor(const String& var) {
  if (var == "temperature") {
    return F("20");
  } else if (var == "wind") {
    return String(weather->windSpeed);
  } else if (var == "humidity") {
    return F("70");
  } else if (var == "light") {
    return F("100");
  } else {
    return F("");
  }
}
void Webserver::fs_init() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}
void Webserver::begin() {
  fs_init();
  wifi_init();
  server_init();
}
