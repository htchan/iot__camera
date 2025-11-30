#ifndef UPTIME_TASK_H
#define UPTIME_TASK_H

#include "../task.h"
#include "const.h"

class UptimeTask : public Task
{
public:
    UptimeTask(PubSubClient *);
    void cleanup() override;
    void loop(unsigned long *) override;
    void publishDiscovery() override;

private:
    unsigned long uptimePublishedAt = 0;
    void publishState(unsigned long *);
};

#endif