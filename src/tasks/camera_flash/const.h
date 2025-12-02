#ifndef CAMERA_FLASH_TASK_CONST
#define CAMERA_FLASH_TASK_CONST

#include "../../const.h"
#include "../available/const.h"

#define LEDC_TIMER LEDC_TIMER_3
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO (4) // Define the output GPIO
#define LEDC_CHANNEL LEDC_CHANNEL_3
#define LEDC_DUTY_RES LEDC_TIMER_11_BIT // Set duty resolution to 13 bits
#define MAX_DUTY ((1 << LEDC_DUTY_RES) - 1) / 10
#define LEDC_FREQUENCY (32000) // Frequency in Hertz. Set frequency at 4 kHz

#define CAMERA_FLASH_BRIGHTNESS_SCALE 20

#define CAMERA_FLASH_COMMAND_ON "ON"
#define CAMERA_FLASH_COMMAND_OFF "OFF"

const std::string CAMERA_FLASH_ENTITY = "homeassistant/light/" + DEVICE_ID + "/camera_flash";
const std::string BRIGHTNESS_COMMAND_TOPIC = "_brightness/command";
const std::string BRIGHTNESS_STATE_TOPIC = "_brightness/state";
const std::string CAMERA_FLASH_DISCOVERY_PAYLOAD =
    R"({
    "device":)" +
    DEVICE_PAYLOAD + R"(,
    "unique_id":")" +
    DEVICE_ID + R"(__camera_flash",
    "name":"Camera Flash",
    "command_topic":")" +
    CAMERA_FLASH_ENTITY + COMMAND_TOPIC + R"(",
    "state_topic":")" +
    CAMERA_FLASH_ENTITY + STATE_TOPIC + R"(",
    "brightness_scale":,)" +
    std::to_string(CAMERA_FLASH_BRIGHTNESS_SCALE) + R"(,
    "brightness_command_topic":")" +
    CAMERA_FLASH_ENTITY + BRIGHTNESS_COMMAND_TOPIC + R"(",
    "brightness_state_topic":")" +
    CAMERA_FLASH_ENTITY + BRIGHTNESS_STATE_TOPIC + R"(",
    "availability_topic":")" +
    AVAILABLE_ENTITY + STATE_TOPIC + R"(",
    "payload_not_available":"",
    "payload_on":")" +
    CAMERA_FLASH_COMMAND_ON + R"(",
    "payload_off":")" +
    CAMERA_FLASH_COMMAND_OFF + R"(",
    "retain":true,
    "command_retain":true,
    "effect_list":["flash"]
})";

#endif