#include "task.h"

AvailableTask::AvailableTask(PubSubClient *client) : Task(client) {};

void AvailableTask::loop(unsigned long *ms)
{
    if (isSameInterval(lastPublishedAt, *ms, AVAILABLE_PUBLISH_INTERVAL_MS))
        return;

    if (Task::isConnected())
    {
        publishOnline();
        lastPublishedAt = *ms;
    }
}
void AvailableTask::cleanup()
{
    publishOffline();
}

void AvailableTask::publishDiscovery()
{
    Task::publish((AVAILABLE_ENTITY + DISCOVERY_TOPIC), AVAILABLE_DISCOVERY_PAYLOAD);
    publishOnline();
}

void AvailableTask::publishOnline()
{
    Task::publish((AVAILABLE_ENTITY + STATE_TOPIC), AVAILABLE_STATE_PAYLOAD_ONLINE);
}

void AvailableTask::publishOffline()
{
    Task::publish((AVAILABLE_ENTITY + STATE_TOPIC), AVAILABLE_STATE_PAYLOAD_OFFLINE);
}
