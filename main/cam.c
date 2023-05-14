#include <stdio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_camera.h"

char * TAG="FUCKJ";
//WROVER-KIT PIN Map
#define CAM_PIN_PWDN    -1
#define CAM_PIN_RESET   18
#define CAM_PIN_XCLK    32
#define CAM_PIN_SIOD    22
#define CAM_PIN_SIOC    23

#define CAM_PIN_D7      39
#define CAM_PIN_D6      33
#define CAM_PIN_D5      25
#define CAM_PIN_D4      27
#define CAM_PIN_D3      12
#define CAM_PIN_D2      15
#define CAM_PIN_D1      2
#define CAM_PIN_D0      14
#define CAM_PIN_VSYNC   5
#define CAM_PIN_HREF    37
#define CAM_PIN_PCLK    26

static camera_config_t camera_config = {
        .pin_pwdn  = CAM_PIN_PWDN,
        .pin_reset = CAM_PIN_RESET,
        .pin_xclk = CAM_PIN_XCLK,
        .pin_sscb_sda = CAM_PIN_SIOD,
        .pin_sscb_scl = CAM_PIN_SIOC,

        .pin_d7 = CAM_PIN_D7,
        .pin_d6 = CAM_PIN_D6,
        .pin_d5 = CAM_PIN_D5,
        .pin_d4 = CAM_PIN_D4,
        .pin_d3 = CAM_PIN_D3,
        .pin_d2 = CAM_PIN_D2,
        .pin_d1 = CAM_PIN_D1,
        .pin_d0 = CAM_PIN_D0,
        .pin_vsync = CAM_PIN_VSYNC,
        .pin_href = CAM_PIN_HREF,
        .pin_pclk = CAM_PIN_PCLK,
//idf.py flash -p /dev/ttyUSB0 -b 115200 monitor
        .xclk_freq_hz = 10000000,//EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode
        .ledc_timer = LEDC_TIMER_0,
        .ledc_channel = LEDC_CHANNEL_0,

        .pixel_format = PIXFORMAT_RGB565,//YUV422,GRAYSCALE,RGB565,JPEG
        .frame_size =  FRAMESIZE_QQVGA,//QQVGA-QXGA Do not use sizes above QVGA when not JPEG

        .jpeg_quality = 20, //0-63 lower number means higher quality
        .fb_count = 1, //if more than one, i2s runs in continuous mode. Use only with JPEG
        .grab_mode = CAMERA_GRAB_WHEN_EMPTY//CAMERA_GRAB_LATEST. Sets when buffers should be filled
};






esp_err_t camera_init(){


    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t camera_capture(){
    //acquire a frame
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }
    //replace this with your own function
//    process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);

ESP_LOGE("fuck","%d   %d     %d     %d",fb->width,fb->height,fb->format,fb->len);
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ESP_OK;
}
void app_main(void)
{
    camera_init();
    while (1){
        camera_capture();
        vTaskDelay(200);
    }
}
