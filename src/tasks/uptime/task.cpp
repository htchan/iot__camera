#include "task.h"

#define UPTIME_PUBLISH_INTERVAL_MS 5000

UptimeTask::UptimeTask(PubSubClient *client) : Task(client) {};

void UptimeTask::cleanup()
{
    unsigned long ms = millis();
    publishState(&ms);
}

void UptimeTask::publishDiscovery()
{
    Task::publish((UPTIME_ENTITY + DISCOVERY_TOPIC), UPTIME_DISCOVERY_PAYLOAD);
    unsigned long ms = millis();
    publishState(&ms);
}

void UptimeTask::loop(unsigned long *ms)
{
    if (isSameInterval(*ms, uptimePublishedAt, UPTIME_PUBLISH_INTERVAL_MS))
    {
        return;
    }

    publishState(ms);
}

void UptimeTask::publishState(unsigned long *ms)
{
    if (!Task::isConnected())
    {
        return;
    }

    uptimePublishedAt = *ms;

    Task::publish((UPTIME_ENTITY + STATE_TOPIC), std::to_string(*ms));
}