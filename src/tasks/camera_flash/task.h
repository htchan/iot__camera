#ifndef CAMERA_FLASH_TASK_H
#define CAMERA_FLASH_TASK_H

#include "../task.h"
#include "const.h"
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"

class CameraFlashTask : public Task
{
public:
    CameraFlashTask(PubSubClient *);
    void setup() override;
    void cleanup() override;
    void publishDiscovery() override;
    bool matchTopic(char *) override;
    void msgHandler(char *, std::string) override;
    void subscribe();

private:
    bool enabled = false;
    int brightness = 0;
    void setFlashBrightness(uint32_t);
    void handleEnableCommand(std::string);
    void handleBrightnessCommand(std::string);
};

#endif