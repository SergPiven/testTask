#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "wifi.h"
#include "http_request.h"
#include "console.h"
const char* TAG = "SERG";


void app_main(void){


	//wifi
		wifi_start();
	//http request
		//https_get_request();
		//https_post_request();

		uart_config();
		console_start();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
}
