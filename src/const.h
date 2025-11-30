#ifndef CONST_H
#define CONST_H

#include <string>
#include <WiFi.h>

std::string uint32ToHex(uint32_t value);

const std::string DEVICE_NAME_VIEW = "Camera";
const std::string DEVICE_NAME = "camera";
const std::string DEVICE_ID = DEVICE_NAME + "-" + uint32ToHex(ESP.getEfuseMac());
const std::string DEVICE_PAYLOAD =
    R"({
    "identifiers":[")" +
    DEVICE_ID + R"("],
    "name":")" +
    DEVICE_NAME_VIEW + R"(",
    "model":"D1 Mini",
    "manufacturer":"Espressif"
})";

const std::string STATE_TOPIC = "/state";
const std::string COMMAND_TOPIC = "/command";
const std::string DISCOVERY_TOPIC = "/config";

#define LOOP_INTERVAL_MS 100

#endif