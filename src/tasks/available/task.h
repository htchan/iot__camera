#ifndef AVAILABLE_TASK_H
#define AVAILABLE_TASK_H

#include "../task.h"
#include "const.h"

class AvailableTask : public Task
{
public:
    AvailableTask(PubSubClient *);
    void cleanup() override;
    void publishDiscovery() override;

private:
    void publishOnline();
    void publishOffline();
};

#endif