#include "task.h"
#include "../../secrets/secrets.h"

NetworkTask::NetworkTask(
    PubSubClient *client,
    void (*networkConnectedFunc)(),
    void (*subscribeHandlerFunc)(char *, byte *, unsigned int)) : Task(client),
                                                                  networkConnectedFunc(networkConnectedFunc),
                                                                  subscribeHandlerFunc(subscribeHandlerFunc),
                                                                  client(client) {};

void NetworkTask::setup()
{
    // setup PubSubClient
    client->setBufferSize(16384);
    // client->setBufferSize(65536);
    client->setCallback(subscribeHandlerFunc);

    // setup Wifi
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(true);
    WiFi.disconnect();
    // WiFi.config(STATIC_IP, GATEWAY, SUBNET, DNS);
};

void NetworkTask::cleanup()
{
    client->disconnect();
    WiFi.disconnect();
};

void NetworkTask::loop(unsigned long *ms)
{
    // connect Wifi
    if (WiFi.status() != WL_CONNECTED)
    {
        if (lastConnectTrialBeginAt == 0)
        {
            // If not in connect trial, then start the connect trial
            WiFi.begin(WIFI_CONN_SSID.c_str(), WIFI_CONN_PASSWORD.c_str());
            lastConnectTrialBeginAt = *ms;
        }
        else if (lastConnectTrialBeginAt + WIFI_CONNECT_TIMEOUT < *ms)
        {
            // if connect trial timeout, disconnect wifi and set last_conn_trial to 0
            WiFi.disconnect();
            lastConnectTrialBeginAt = 0;
        }
    }

    // connect MQTT
    if (WiFi.status() == WL_CONNECTED && !client->connected())
    {
        isMqttConnected = false;
        // generate random client id
        char clientID[32];
        snprintf(clientID, sizeof(clientID), "%s%04X", MQTT_CLIENT_ID_PREFIX.c_str(), (uint16_t)(millis() & 0xFFFF));

        client->setServer(MQTT_SERVER.c_str(), MQTT_PORT);
        client->connect(clientID, MQTT_USER.c_str(), MQTT_PASSWORD.c_str());
    }

    if (client->connected())
    {
        if (!isMqttConnected)
        {
            // networkConnectedFunc will only be called at first connected
            isMqttConnected = true;
            networkConnectedFunc();
        }

        for (int i = 0; i < CONTINUE_SUBSCRIBE_COUNT; i++)
        {
            client->loop();
        }
    }
}
