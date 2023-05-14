#include <stdio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_camera.h"

char * TAG="FUCKJ";

#define S002_SPI1_CLK_IO                    GPIO_NUM_18
#define S002_SPI1_MISO_IO                   GPIO_NUM_19
#define S002_SPI1_MOSI_IO                   GPIO_NUM_23

// SD Card
#define S002_SD_CLK_IO                      S002_SPI1_CLK_IO
#define S002_SD_DAT0_IO                     S002_SPI1_MISO_IO
#define S002_SD_CMD_IO                      S002_SPI1_MOSI_IO
#define S002_SD_CD_IO                       GPIO_NUM_4

// Camera
#define S002_CAMERA_RESET_IO                GPIO_NUM_5
#define S002_CAMERA_XCLK_IO                 GPIO_NUM_15
#define S002_CAMERA_SIOD_IO                 GPIO_NUM_21
#define S002_CAMERA_SIOC_IO                 GPIO_NUM_22
#define S002_CAMERA_D7_IO                   GPIO_NUM_2
#define S002_CAMERA_D6_IO                   GPIO_NUM_13
#define S002_CAMERA_D5_IO                   GPIO_NUM_12
#define S002_CAMERA_D4_IO                   GPIO_NUM_32
#define S002_CAMERA_D3_IO                   GPIO_NUM_25
#define S002_CAMERA_D2_IO                   GPIO_NUM_27
#define S002_CAMERA_D1_IO                   GPIO_NUM_26
#define S002_CAMERA_D0_IO                   GPIO_NUM_33
#define S002_CAMERA_VSYNC_IO                GPIO_NUM_17
#define S002_CAMERA_HREF_IO                 GPIO_NUM_16
#define S002_CAMERA_PCLK_IO                 GPIO_NUM_14
//WROVER-KIT PIN Map
#define CAM_PIN_PWDN        -1  //power down is not used
#define CAM_PIN_RESET       S002_CAMERA_RESET_IO //software reset will be performed
#define CAM_PIN_XCLK        S002_CAMERA_XCLK_IO
#define CAM_PIN_SIOD        S002_CAMERA_SIOD_IO
#define CAM_PIN_SIOC        S002_CAMERA_SIOC_IO

#define CAM_PIN_D7          S002_CAMERA_D7_IO
#define CAM_PIN_D6          S002_CAMERA_D6_IO
#define CAM_PIN_D5          S002_CAMERA_D5_IO
#define CAM_PIN_D4          S002_CAMERA_D4_IO
#define CAM_PIN_D3          S002_CAMERA_D3_IO
#define CAM_PIN_D2          S002_CAMERA_D2_IO
#define CAM_PIN_D1          S002_CAMERA_D1_IO
#define CAM_PIN_D0          S002_CAMERA_D0_IO
#define CAM_PIN_VSYNC       S002_CAMERA_VSYNC_IO
#define CAM_PIN_HREF        S002_CAMERA_HREF_IO
#define CAM_PIN_PCLK        S002_CAMERA_PCLK_IO

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
        .fb_location = CAMERA_FB_IN_DRAM,
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
