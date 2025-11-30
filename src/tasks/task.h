#ifndef META_TASK_H
#define META_TASK_H

#include <PubSubClient.h>
#include <string>
#include <list>

class Task
{
public:
    Task(PubSubClient *cli) : client(cli) {};
    virtual void setup() {};
    virtual void cleanup() {};
    virtual void loop(unsigned long *ms) {};
    virtual void publishDiscovery() {};
    virtual bool matchTopic(char *) { return false; };
    virtual void msgHandler(char *, std::string) {};
    virtual bool completed() { return true; };

protected:
    bool isConnected() { return client->connected(); }
    void publish(std::string topic, std::string payload) { client->publish(topic.c_str(), payload.c_str(), true); }
    void publish(std::string topic, const char *buf, unsigned int len) { client->publish(topic.c_str(), (const uint8_t *)buf, len); }
    void subscribe(std::string topic) { client->subscribe(topic.c_str()); }
    void unsubscribe(std::string topic) { client->unsubscribe(topic.c_str()); }
    PubSubClient *client;
};

inline bool isSameInterval(unsigned long time1, unsigned long time2, unsigned long interval)
{
    return time1 / interval == time2 / interval;
}

#endif