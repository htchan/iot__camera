#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H

#include "../task.h"
#include "const.h"

class NetworkTask : public Task
{
public:
    NetworkTask(
        PubSubClient *client,
        void (*networkConnectedFunc)(),
        void (*subscribeHandlerFunc)(char *, byte *, unsigned int));
    void setup() override;
    void cleanup() override;
    void loop(unsigned long *ms) override;

private:
    bool isMqttConnected = false;
    unsigned long lastConnectTrialBeginAt = 0;
    void (*networkConnectedFunc)();
    void (*subscribeHandlerFunc)(char *, byte *, unsigned int);
    PubSubClient *client;
};

#endif