#ifndef CAMERA_LED_TASK_CONST
#define CAMERA_LED_TASK_CONST

#include "../../const.h"
#include "../available/const.h"

#define CAMERA_LED_PIN 33

#define CAMERA_LED_COMMAND_ON "ON"
#define CAMERA_LED_COMMAND_OFF "OFF"

const std::string CAMERA_LED_ENTITY = "homeassistant/switch/" + DEVICE_ID + "/camera_led";
const std::string CAMERA_LED_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_led",
    "name":"Camera LED",
    "state_topic":")" +
    CAMERA_LED_ENTITY + STATE_TOPIC + R"(",
    "command_topic":")" +
    CAMERA_LED_ENTITY + COMMAND_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "payload_on":")" +
    CAMERA_LED_COMMAND_ON + R"(",
    "payload_off":")" +
    CAMERA_LED_COMMAND_OFF + R"(",
    "retain":true,
    "command_retain":true
})";

#endif