#ifndef META_TASK_H
#define META_TASK_H

#include <PubSubClient.h>
#include <string>
#include <list>

class Task
{
public:
    Task(PubSubClient *cli) : client(cli) {};
    Task(PubSubClient *cli, std::list<std::pair<std::string, std::function<void(std::string)>>> pairs) : client(cli), msgHandlers(pairs) {};
    virtual void setup() {};
    virtual void cleanup() {};
    virtual void loop(unsigned long *ms) {};
    virtual void publishDiscovery() {};
    virtual bool matchTopic(char *topic)
    {
        for (auto &handlerPair : msgHandlers)
        {
            if (strcmp(topic, handlerPair.first.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    };
    virtual void msgHandler(char *topic, std::string msg)
    {
        for (auto &handlerPair : msgHandlers)
        {
            if (strcmp(topic, handlerPair.first.c_str()) == 0)
            {
                handlerPair.second(msg);
                return;
            }
        }
    };
    virtual void subscribe()
    {
        for (auto &handlerPair : msgHandlers)
        {
            subscribe(handlerPair.first);
        }
    }
    virtual bool completed() { return true; };

protected:
    bool isConnected() { return client->connected(); }
    void publish(std::string topic, std::string payload) { client->publish(topic.c_str(), payload.c_str(), true); }
    void publish(std::string topic, const char *buf, unsigned int len) { client->publish(topic.c_str(), (const uint8_t *)buf, len); }
    void subscribe(std::string topic) { client->subscribe(topic.c_str()); }
    void unsubscribe(std::string topic) { client->unsubscribe(topic.c_str()); }
    PubSubClient *client;
    std::list<std::pair<std::string, std::function<void(std::string)>>> msgHandlers;
};

inline bool isSameInterval(unsigned long time1, unsigned long time2, unsigned long interval)
{
    return time1 / interval == time2 / interval;
}

#endif