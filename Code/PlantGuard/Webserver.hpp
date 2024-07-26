class Webserver {
public:
  Webserver();
  void begin();
private:
  void wifi_init();
  void server_init();
  void fs_init();
};
