#ifndef WIFI_HEADERFILE_H
#define WIFI_HEADERFILE_H

//wifi
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#define WIFI_SSID "guest"    // "300"//"WIFISD300""guest"//
#define WIFI_PASS "#Knowledge-Pool@"   	//"123123123"//"91389596""#Knowledge-Pool@"//
#define EXAMPLE_ESP_MAXIMUM_RETRY  5

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static EventGroupHandle_t  s_wifi_event_group;
static int s_retry_num = 0;

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data);

void wifi_init(void);

void wifi_start();

#endif
