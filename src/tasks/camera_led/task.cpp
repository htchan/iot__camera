#include "task.h"

CameraLedTask::CameraLedTask(PubSubClient *client) : Task(
                                                         client,
                                                         {{CAMERA_LED_ENTITY + COMMAND_TOPIC, [this](std::string message)
                                                           { handleLedCommand(message); }}}) {};

void CameraLedTask::setup()
{
    pinMode(CAMERA_LED_PIN, OUTPUT);
    turnOff();
}

void CameraLedTask::cleanup()
{
    turnOff();
}

void CameraLedTask::publishDiscovery()
{
    Task::publish((CAMERA_LED_ENTITY + DISCOVERY_TOPIC), CAMERA_LED_DISCOVERY_PAYLOAD);
}

void CameraLedTask::turnOn()
{
    digitalWrite(CAMERA_LED_PIN, LOW);
    enabled = true;
}

void CameraLedTask::turnOff()
{
    digitalWrite(CAMERA_LED_PIN, HIGH);
    enabled = false;
}

void CameraLedTask::handleLedCommand(std::string message)
{
    if (message == CAMERA_LED_COMMAND_ON && !enabled)
    {
        turnOn();
    }
    else if (message == CAMERA_LED_COMMAND_OFF && enabled)
    {
        turnOff();
    }

    Task::publish((CAMERA_LED_ENTITY + STATE_TOPIC), enabled ? CAMERA_LED_COMMAND_ON : CAMERA_LED_COMMAND_OFF);
}