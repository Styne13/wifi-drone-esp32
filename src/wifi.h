/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"
#include "ibus.h"
#include "index_html.h"
#include <WiFi.h>
#include <WebServer.h>

// wifi config, or defaults.
#if __has_include("secret.h")
    #include "secret.h"
#else
    #warning "Using Defaults: Copy secret.sample.h to secret.h and edit that to use your own settings"
    #define WIFI_SSID "replace-me"
    #define WIFI_PASSWORD "replace-me"
#endif

class Wifi {
  public:
    void begin(void (*controlCallback)(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2]));
    void loop();

  private:
    static const unsigned int WEBSERVER_PORT = 80;
    const char * CONTROL_PATH = "/control";
    const char * MDNS_DOMAIN_NAME = "quadcopter";
    WebServer * server;

    void beginWebServer(WebServer * server);
    static void onRoot();
    static void onControl();
    void (*controlCallback)(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2]);
};

extern Wifi wifi;

#endif