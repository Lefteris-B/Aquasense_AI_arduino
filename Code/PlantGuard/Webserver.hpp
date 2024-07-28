#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <ESPAsyncWebServer.h>
#include "Weather.hpp"

class Webserver {
public:
  Webserver(Weather* weather);
  Weather* weather;
  void begin();
private:
  AsyncWebServer server;
  
  void wifi_init();
  void server_init();
  void fs_init();
  static String mainProcessor(const String& var);
};

#endif
