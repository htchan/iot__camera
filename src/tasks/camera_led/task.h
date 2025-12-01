#ifndef CAMERA_LED_TASK_H
#define CAMERA_LED_TASK_H

#include "../task.h"
#include "const.h"

class CameraLedTask : public Task
{
public:
    CameraLedTask(PubSubClient *);
    void setup() override;
    void cleanup() override;
    void publishDiscovery() override;

private:
    bool enabled = false;
    void turnOn();
    void turnOff();
    void handleLedCommand(std::string payload);
};

#endif