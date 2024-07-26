#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <ESPAsyncWebServer.h>

class Webserver {
public:
  Webserver();
  void begin();
private:

  AsyncWebServer server;

  void wifi_init();
  void server_init();
  void fs_init();
};

#endif
