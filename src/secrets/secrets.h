#ifndef SECRETS_H
#define SECRETS_H

#include <string>
#include <WiFi.h>

extern const std::string WIFI_CONN_SSID;
extern const std::string WIFI_CONN_PASSWORD;

extern const IPAddress STATIC_IP;
extern const IPAddress GATEWAY;
extern const IPAddress SUBNET;
extern const IPAddress DNS;

extern const std::string MQTT_SERVER;
extern const int MQTT_PORT;
extern const std::string MQTT_USER;
extern const std::string MQTT_PASSWORD;
extern const std::string MQTT_CLIENT_ID_PREFIX;

#endif