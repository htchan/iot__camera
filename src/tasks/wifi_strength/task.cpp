#include "task.h"
#include <algorithm>

WifiStrengthTask::WifiStrengthTask(PubSubClient *client) : Task(client) {};

void WifiStrengthTask::loop(unsigned long *ms)
{
    if (*ms / WIFI_STRENGTH_PUBLISH_INTERVAL_MS <= wifiStrengthPublishedAt / WIFI_STRENGTH_PUBLISH_INTERVAL_MS)
    {
        return;
    }

    if (!Task::isConnected())
    {
        return;
    }

    int8_t wifiStrength = readData();
    if (wifiStrength != 0)
    {
        Task::publish((WIFI_STRENGTH_ENTITY + STATE_TOPIC), std::to_string(static_cast<int>(wifiStrength)));
        wifiStrengthPublishedAt = *ms;
    }
}

void WifiStrengthTask::publishDiscovery()
{
    Task::publish((WIFI_STRENGTH_ENTITY + DISCOVERY_TOPIC), WIFI_STRENGTH_DISCOVERY_PAYLOAD);
}

int8_t WifiStrengthTask::readData()
{
    int8_t strength = 2 * (WiFi.RSSI() + 100);
    if (strength < 0)
        strength = 0;
    if (strength > 100)
        strength = 100;

    return strength;
}
