#ifndef WEATHER_HPP
#define WEATHER_HPP
#include <HTTPClient.h>
class Weather {
  public:
    Weather();
    void request();
    double latitude = 0;
    double longtitude = 0;
    int weatherCode;
    double windSpeed;
    
  private:
    HTTPClient http;
    int convertCode(int code);
    String url = "https://api.open-meteo.com/v1/forecast?latitude={latitude}&longitude={longitude}&current=weather_code,wind_speed_10m&wind_speed_unit=ms";
};

#endif
