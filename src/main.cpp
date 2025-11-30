#include <Arduino.h>
#include "const.h"

#include "tasks/available/task.h"
#include "tasks/camera/task.h"
// #include "tasks/light/task.h"
#include "tasks/network/task.h"
// #include "tasks/power/task.h"
#include "tasks/uptime/task.h"
#include "tasks/wifi_strength/task.h"

std::list<Task *> tasks;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

AvailableTask availableTask(&client);
// PowerTask powerTask(&client);
UptimeTask uptimeTask(&client);
WifiStrengthTask wifiStrengthTask(&client);

CameraTask cameraTask(&client);

bool alreadyPublished = false;

void networkConnected()
{
  unsigned long ms = millis();
  Serial.printf("Network connected - %lu\n", ms);
  if (!alreadyPublished)
  {
    for (auto &task : tasks)
    {
      task->publishDiscovery();
    }

    alreadyPublished = true;
  }

  cameraTask.subscribe();
  // powerTask.subscribe();
}

void subscribeHandler(char *topic, byte *payload, unsigned int length)
{
  std::string message(reinterpret_cast<char *>(payload), length);

  for (auto &task : tasks)
  {
    if (task->matchTopic(topic))
    {
      task->msgHandler(topic, message);
    }
  }
}

NetworkTask networkTask(
    &client,
    networkConnected,
    subscribeHandler);

void setup()
{
  Serial.begin(115200);
  Serial.println("Testing - v0.0.1");

  // tasks.push_back(&powerTask);
  tasks.push_back(&availableTask);
  tasks.push_back(&uptimeTask);
  tasks.push_back(&networkTask);
  tasks.push_back(&wifiStrengthTask);
  tasks.push_back(&cameraTask);

  for (auto &task : tasks)
  {
    task->setup();
  }
}

void loop()
{
  unsigned long ms = millis();

  for (auto &task : tasks)
  {
    task->loop(&ms);
  }

  delay(LOOP_INTERVAL_MS - (millis() % LOOP_INTERVAL_MS));
}