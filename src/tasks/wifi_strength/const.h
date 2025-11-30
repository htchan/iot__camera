#ifndef WIFI_STRENGTH_CONST
#define WIFI_STRENGTH_CONST

#include "../../const.h"
#include "../available/const.h"

#define WIFI_STRENGTH_PUBLISH_INTERVAL_MS 60000 // 60s

const std::string WIFI_STRENGTH_ENTITY = "homeassistant/sensor/" + DEVICE_ID + "/wifi_strength";
const std::string WIFI_STRENGTH_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__wifi_strength",
    "name":"Wifi Strength",
    "unit_of_measurement":"%",
    "state_topic":")" +
    WIFI_STRENGTH_ENTITY + STATE_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "entity_category":"diagnostic",
    "state_class":"measurement"
})";

#endif