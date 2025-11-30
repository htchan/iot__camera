#ifndef AVAILABLE_TASK_H
#define AVAILABLE_TASK_H

#include "../task.h"
#include "const.h"

class AvailableTask : public Task
{
public:
    AvailableTask(PubSubClient *);
    void loop(unsigned long *) override;
    void cleanup() override;
    void publishDiscovery() override;

private:
    unsigned long lastPublishedAt = 0;
    void publishOnline();
    void publishOffline();
};

#endif