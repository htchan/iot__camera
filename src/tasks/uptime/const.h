#ifndef UPTIME_TASK_CONST
#define UPTIME_TASK_CONST

#include "../../const.h"
#include "../available/const.h"

#define UPTIME_PUBLISH_INTERVAL_MS 60000

const std::string UPTIME_ENTITY = "homeassistant/sensor/" + DEVICE_ID + "/uptime";
const std::string UPTIME_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__uptime",
    "name":"Uptime",
    "unit_of_measurement":"ms",
    "state_topic":")" +
    UPTIME_ENTITY + STATE_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "entity_category":"diagnostic",
    "state_class":"total_increasing",
    "device_class":"duration"
})";

#endif