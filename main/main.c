#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "wifi.h"
#include "http_request.h"
const char* TAG = "SERG";


void app_main(void){
	//wifi
		wifi_start();
	//http request
		https_get_request();
		https_post_request();

}
