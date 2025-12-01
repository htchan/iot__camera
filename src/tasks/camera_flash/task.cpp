
#include "task.h"
#include "const.h"

CameraFlashTask::CameraFlashTask(PubSubClient *client) : Task(client) {};

void CameraFlashTask::setup()
{
    // configure LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // configure LEDC channel
    ledc_channel_config_t ledc_channel = {
        .gpio_num = LEDC_OUTPUT_IO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    setFlashBrightness(0);
}

void CameraFlashTask::cleanup()
{
    setFlashBrightness(0);
}

void CameraFlashTask::publishDiscovery()
{
    Task::publish((CAMERA_FLASH_ENTITY + DISCOVERY_TOPIC), CAMERA_FLASH_DISCOVERY_PAYLOAD);
}

bool CameraFlashTask::matchTopic(char *topic)
{
    return strcmp(topic, (CAMERA_FLASH_ENTITY + COMMAND_TOPIC).c_str()) == 0 ||
           strcmp(topic, (CAMERA_FLASH_ENTITY + BRIGHTNESS_COMMAND_TOPIC).c_str()) == 0;
}

void CameraFlashTask::msgHandler(char *topic, std::string message)
{
    if (strcmp(topic, (CAMERA_FLASH_ENTITY + COMMAND_TOPIC).c_str()) == 0)
    {
        handleEnableCommand(message);
    }
    else if (strcmp(topic, (CAMERA_FLASH_ENTITY + BRIGHTNESS_COMMAND_TOPIC).c_str()) == 0)
    {
        handleBrightnessCommand(message);
    }
}

void CameraFlashTask::subscribe()
{
    Task::subscribe(CAMERA_FLASH_ENTITY + COMMAND_TOPIC);
    Task::subscribe(CAMERA_FLASH_ENTITY + BRIGHTNESS_COMMAND_TOPIC);
}

void CameraFlashTask::setFlashBrightness(uint32_t duty_percent)
{
    // Calculate duty based on the resolution.
    // For a 13-bit resolution, maximum duty is (2^13 - 1)
    uint32_t duty = (duty_percent * MAX_DUTY) / 100;

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}

void CameraFlashTask::handleEnableCommand(std::string message)
{
    if (message == CAMERA_FLASH_COMMAND_ON && !enabled)
    {
        enabled = true;
        if (brightness != 0)
            setFlashBrightness(brightness);
    }
    else if (message == CAMERA_FLASH_COMMAND_OFF && enabled)
    {
        enabled = false;
        setFlashBrightness(0);
    }

    Task::publish((CAMERA_FLASH_ENTITY + STATE_TOPIC), enabled ? CAMERA_FLASH_COMMAND_ON : CAMERA_FLASH_COMMAND_OFF);
}

void CameraFlashTask::handleBrightnessCommand(std::string message)
{
    brightness = atoi(message.c_str());
    if (enabled)
        setFlashBrightness(brightness);
    Task::publish((CAMERA_FLASH_ENTITY + BRIGHTNESS_STATE_TOPIC), message);
}
