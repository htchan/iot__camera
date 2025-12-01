#ifndef CAMERA_TASK_H
#define CAMERA_TASK_H

#include "../task.h"
#include "const.h"

#include "esp_camera.h"
#include "esp_http_server.h"

class CameraTask : public Task
{
public:
    CameraTask(PubSubClient *);
    void setup() override;
    void loop(unsigned long *) override;
    void cleanup() override;
    void publishDiscovery() override;

private:
    camera_config_t config;
    int periodMs = 1000;
    bool enabled = false;
    unsigned long lastImagePublishAt = 0;
    bool horizontalFlip = false;
    bool verticalFlip = false;
    void stopCamera();
    void startCamera();
    void publishImage();
    void applyFlipSettings();
    void handleEnableCommand(std::string);
    void handleFpsCommand(std::string);
    void handleVFlipCommand(std::string);
    void handleHFlipCommand(std::string);
};

#endif