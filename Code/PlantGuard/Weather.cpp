#include "Weather.hpp"
#include <ArduinoJson.h>

Weather::Weather() {}

void Weather::request() {
  url.replace("{latitude}", String(latitude));
  url.replace("{longitude}", String(longtitude));
  http.begin(url);
  int httpResponseCode = http.GET();
  String payload = http.getString();
  JsonDocument doc;
  deserializeJson(doc, payload);
  int code = doc["current"]["weather_code"];
  weatherCode = Weather::convertCode(code);
  windSpeed = doc["current"]["wind_speed_10m"];
  Serial.println(weatherCode);
}

int Weather::convertCode(int code) {
  if (code <= 45) {
    return 0;
  }
  else if (code >= 51) {
    return 1;
  }
  else if (code >= 95) {
    return 2;
  }
}
