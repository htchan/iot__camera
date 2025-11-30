#ifndef WIFI_STRENGTH_TASK_H
#define WIFI_STRENGTH_TASK_H

#include "../task.h"
#include "const.h"
#include <WiFi.h>

class WifiStrengthTask : public Task
{
public:
    WifiStrengthTask(PubSubClient *client);
    void loop(unsigned long *) override;
    void publishDiscovery() override;

private:
    unsigned long wifiStrengthPublishedAt = 0;
    int8_t readData();
};

#endif