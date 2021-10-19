
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp32/rom/uart.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>
#include <string.h>


#define ECHO_TEST_TXD_0  (GPIO_NUM_1)
#define ECHO_TEST_RXD_0  (GPIO_NUM_3)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)

static void IRAM_ATTR uart_intr_handle(void *arg);

typedef struct {
    char** arr;
    size_t cnt;
} array_t;

#define array_init(a)  (a).arr = NULL, (a).cnt = 0
void array_clear(array_t* a);
int  array_resize(array_t* a, size_t n);
void array_strtok(array_t* a, char* s, const char* delim);

void uart_config();
void console_start();

void array_strtok(array_t* a, char* s, const char* delim);
void array_clear(array_t* a);
int array_resize(array_t* a, size_t n);
void clearBuffer();
