#include "task.h"

CameraTask::CameraTask(PubSubClient *cli) : Task(cli) {};

void CameraTask::setup()
{
    // setup camera config
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 1;

    // optionally power down the sensor if PWDN is defined in your config
    if (config.pin_pwdn >= 0)
    {
        pinMode(config.pin_pwdn, OUTPUT);
        digitalWrite(config.pin_pwdn, HIGH); // HIGH usually = power down
    }
}

void CameraTask::loop(unsigned long *ms)
{
    if (isSameInterval(*ms, lastImagePublishAt, periodMs) || !enabled)
    {
        return;
    }
    publishImage();
    lastImagePublishAt = *ms;
}

void CameraTask::cleanup()
{
    stopCamera();
}

void CameraTask::publishDiscovery()
{
    Task::publish((CAMERA_ENABLED_ENTITY + DISCOVERY_TOPIC), CAMERA_ENABLED_DISCOVERY_PAYLOAD);
    Task::publish((CAMERA_H_FLIP_ENTITY + DISCOVERY_TOPIC), CAMERA_H_FLIP_DISCOVERY_PAYLOAD);
    Task::publish((CAMERA_V_FLIP_ENTITY + DISCOVERY_TOPIC), CAMERA_V_FLIP_DISCOVERY_PAYLOAD);
    Task::publish((CAMERA_IMAGE_ENTITY + DISCOVERY_TOPIC), CAMERA_IMAGE_DISCOVERY_PAYLOAD);
    Task::publish((CAMERA_FPS_ENTITY + DISCOVERY_TOPIC), CAMERA_FPS_DISCOVERY_PAYLOAD);
}

bool CameraTask::matchTopic(char *topic)
{
    return strcmp(topic, (CAMERA_ENABLED_ENTITY + COMMAND_TOPIC).c_str()) == 0 ||
           strcmp(topic, (CAMERA_H_FLIP_ENTITY + COMMAND_TOPIC).c_str()) == 0 ||
           strcmp(topic, (CAMERA_V_FLIP_ENTITY + COMMAND_TOPIC).c_str()) == 0 ||
           strcmp(topic, (CAMERA_FPS_ENTITY + STATE_TOPIC).c_str()) == 0;
}

void CameraTask::msgHandler(char *topic, std::string msg)
{
    // TODO: implement message handling
    if (strcmp(topic, (CAMERA_ENABLED_ENTITY + COMMAND_TOPIC).c_str()) == 0)
    {
        if (msg == CAMERA_COMMAND_ON && !enabled)
            startCamera();
        else if (msg == CAMERA_COMMAND_OFF && enabled)
            stopCamera();
        Task::publish((CAMERA_ENABLED_ENTITY + STATE_TOPIC), enabled ? CAMERA_COMMAND_ON : CAMERA_COMMAND_OFF);
    }
    else if (strcmp(topic, (CAMERA_H_FLIP_ENTITY + COMMAND_TOPIC).c_str()) == 0)
    {
        if (msg == CAMERA_COMMAND_ON)
            horizontalFlip = 1;
        else if (msg == CAMERA_COMMAND_OFF)
            horizontalFlip = 0;

        applyFlipSettings();
        Task::publish((CAMERA_H_FLIP_ENTITY + STATE_TOPIC), horizontalFlip ? CAMERA_COMMAND_ON : CAMERA_COMMAND_OFF);
    }
    else if (strcmp(topic, (CAMERA_V_FLIP_ENTITY + COMMAND_TOPIC).c_str()) == 0)
    {
        if (msg == CAMERA_COMMAND_ON)
            verticalFlip = 1;
        else if (msg == CAMERA_COMMAND_OFF)
            verticalFlip = 0;

        applyFlipSettings();
        Task::publish((CAMERA_V_FLIP_ENTITY + STATE_TOPIC), verticalFlip ? CAMERA_COMMAND_ON : CAMERA_COMMAND_OFF);
    }
    else if (strcmp(topic, (CAMERA_FPS_ENTITY + STATE_TOPIC).c_str()) == 0)
    {
        float fps = std::stof(msg);
        fps = std::max(0.1f, std::min(fps, 10.0f));

        periodMs = 1000 / fps;
    }
}

void CameraTask::subscribe()
{
    Task::subscribe(CAMERA_ENABLED_ENTITY + COMMAND_TOPIC);
    Task::subscribe(CAMERA_H_FLIP_ENTITY + COMMAND_TOPIC);
    Task::subscribe(CAMERA_V_FLIP_ENTITY + COMMAND_TOPIC);
    Task::subscribe(CAMERA_FPS_ENTITY + STATE_TOPIC);
}

void CameraTask::stopCamera()
{
    camera_fb_t *fb = esp_camera_fb_get();
    if (fb)
    {
        esp_camera_fb_return(fb);
        fb = NULL;
    }

    esp_camera_deinit();

    // optionally power down the sensor if PWDN is defined in your config
    if (config.pin_pwdn >= 0)
    {
        digitalWrite(config.pin_pwdn, HIGH); // HIGH usually = power down
    }

    enabled = false;
    Task::publish((CAMERA_IMAGE_ENTITY + STATE_TOPIC), ""); // clear image state
}

void CameraTask::startCamera()
{
    // optionally power down the sensor if PWDN is defined in your config
    if (config.pin_pwdn >= 0)
        digitalWrite(config.pin_pwdn, LOW); // HIGH usually = power down

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
        return;

    enabled = true;
    applyFlipSettings();
    publishImage();
}

// Usage: if (hasSignificantChange(fb->buf, prev_fb->buf, fb->len)) { publish... }

void CameraTask::publishImage()
{
    if (!enabled)
        return;

    camera_fb_t *fb = esp_camera_fb_get();
    if (fb)
    {
        Task::publish((CAMERA_IMAGE_ENTITY + STATE_TOPIC), (const char *)fb->buf, fb->len);
        esp_camera_fb_return(fb);
    }
}

void CameraTask::applyFlipSettings()
{
    if (!enabled)
        return;

    sensor_t *s = esp_camera_sensor_get();
    if (s)
    {
        // Enable vertical flip (top <-> bottom)
        s->set_vflip(s, verticalFlip); // 1 is enable, 0 is disable
        // Enable horizontal mirror (left <-> right)
        s->set_hmirror(s, horizontalFlip); // 1 is enable, 0 is disable
    }
}