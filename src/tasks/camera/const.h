#ifndef CAMERA_TASK_CONST
#define CAMERA_TASK_CONST

#include "../../const.h"
#include "../available/const.h"

// Camera pins for ESP32-CAM
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#define IMG_PUBLISH_INTERVAL_MS 200

#define CAMERA_COMMAND_ON "ON"
#define CAMERA_COMMAND_OFF "OFF"

#define LED_PIN 33

const std::string CAMERA_ENABLED_ENTITY = "homeassistant/switch/" + DEVICE_ID + "/camera_enabled";
const std::string CAMERA_ENABLED_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_enabled",
    "name":"Enabled",
    "state_topic":")" +
    CAMERA_ENABLED_ENTITY + STATE_TOPIC + R"(",
    "command_topic":")" +
    CAMERA_ENABLED_ENTITY + COMMAND_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "payload_on":")" +
    CAMERA_COMMAND_ON + R"(",
    "payload_off":")" +
    CAMERA_COMMAND_OFF + R"(",
    "retain":true,
    "command_retain":true
})";

const std::string CAMERA_IMAGE_ENTITY = "homeassistant/image/" + DEVICE_ID + "/camera_image";
const std::string CAMERA_IMAGE_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_image",
    "name":"Camera Image",
    "image_topic":")" +
    CAMERA_IMAGE_ENTITY + STATE_TOPIC + R"(",
    "content_type":"image/jpeg"
})";

const std::string CAMERA_V_FLIP_ENTITY = "homeassistant/switch/" + DEVICE_ID + "/camera_vertical_flip";
const std::string CAMERA_V_FLIP_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_vertical_flip",
    "name":"Vertical Flip",
    "state_topic":")" +
    CAMERA_V_FLIP_ENTITY + STATE_TOPIC + R"(",
    "command_topic":")" +
    CAMERA_V_FLIP_ENTITY + COMMAND_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "payload_on":")" +
    CAMERA_COMMAND_ON + R"(",
    "payload_off":")" +
    CAMERA_COMMAND_OFF + R"(",
    "retain":true,
    "command_retain":true
})";

const std::string CAMERA_H_FLIP_ENTITY = "homeassistant/switch/" + DEVICE_ID + "/camera_horizontal_flip";
const std::string CAMERA_H_FLIP_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_horizontal_flip",
    "name":"Horizontal Flip",
    "state_topic":")" +
    CAMERA_H_FLIP_ENTITY + STATE_TOPIC + R"(",
    "command_topic":")" +
    CAMERA_H_FLIP_ENTITY + COMMAND_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "payload_on":")" +
    CAMERA_COMMAND_ON + R"(",
    "payload_off":")" +
    CAMERA_COMMAND_OFF + R"(",
    "retain":true,
    "command_retain":true
})";

const std::string CAMERA_FPS_ENTITY = "homeassistant/select/" + DEVICE_ID + "/camera_fps";
const std::string CAMERA_FPS_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_fps",
    "name":"Camera FPS",
    "state_topic":")" +
    CAMERA_FPS_ENTITY + STATE_TOPIC + R"(",
    "command_topic":")" +
    CAMERA_FPS_ENTITY + STATE_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "options":[
        "0.1",
        "0.2",
        "0.5",
        "1",
        "2",
        "5",
        "10"
    ],
    "retain":true,
    "command_retain":true
})";
#endif