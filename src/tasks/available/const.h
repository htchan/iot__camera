#ifndef AVAILABLE_TASK_CONST
#define AVAILABLE_TASK_CONST

#include "../../const.h"

#define AVAILABLE_STATE_PAYLOAD_ONLINE "online"
#define AVAILABLE_STATE_PAYLOAD_OFFLINE "offline"

#define AVAILABLE_PUBLISH_INTERVAL_MS 60000

const std::string AVAILABLE_ENTITY = "homeassistant/binary_sensor/" + DEVICE_ID + "/sensor_status";
const std::string AVAILABLE_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__sensor_status",
    "name":"Sensor Status",
    "state_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_on":")" +
    AVAILABLE_STATE_PAYLOAD_ONLINE + R"(",
    "payload_off":")" +
    AVAILABLE_STATE_PAYLOAD_OFFLINE + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "expire_after":90,
    "entity_category":"diagnostic",
    "device_class":"connectivity"
})";

#endif