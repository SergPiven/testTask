#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "wifi.h"
const char* TAG = "SERG";


void app_main(void){
	//wifi
		wifi_start();

}
