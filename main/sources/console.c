#include "console.h"
#include "http_request.h"

uint8_t rxbuf[256]={0};
int rx_len;
int flag_post = 0, flag_get = 0, flag=0;


static void IRAM_ATTR uart_intr_handle(void *arg)
{
	uint16_t rx_fifo_len, status;
	uint16_t i = 0;

	  status = UART0.int_st.val; // read UART interrupt Status
	  rx_fifo_len = UART0.status.rxfifo_cnt; // read number of bytes in UART buffer
	  while(rx_fifo_len)
	  {
	   rxbuf[i++] = UART0	.fifo.rw_byte; // read all bytes
	   rx_fifo_len--;
	  }

	  uart_clear_intr_status(UART_NUM_0, UART_RXFIFO_FULL_INT_CLR|UART_RXFIFO_TOUT_INT_CLR);

	  if (rxbuf[i-1] == '\n'|| rxbuf[i-1]=='\r')
	  {
		  flag = 1;
	  }
}

void uart_config(){
	uart_config_t uart_config_0 = {
		        .baud_rate = 115200,
		        .data_bits = UART_DATA_8_BITS,
		        .parity    = UART_PARITY_DISABLE,
		        .stop_bits = UART_STOP_BITS_1,
		        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		        .source_clk = UART_SCLK_APB,
		    };
	uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
	uart_param_config(UART_NUM_0, &uart_config_0);
	uart_set_pin(UART_NUM_0, ECHO_TEST_TXD_0, ECHO_TEST_RXD_0, ECHO_TEST_RTS, ECHO_TEST_CTS);

	ESP_ERROR_CHECK(uart_isr_free(UART_NUM_0));
	ESP_ERROR_CHECK(uart_isr_register(UART_NUM_0,uart_intr_handle, NULL, ESP_INTR_FLAG_IRAM, NULL));
	ESP_ERROR_CHECK(uart_enable_rx_intr(UART_NUM_0));
}


void console_start() {

	array_t a;

	while(1){
//		array_init(a);
//		array_strtok(&a,(char*) rxbuf, " \r\n\t,?!");
		if(flag==1){

		uart_write_bytes(UART_NUM_0, rxbuf, strlen((char*)rxbuf));

		array_init(a);
		array_strtok(&a,(char*) rxbuf, " \r\n\t,?!");

		if(rxbuf[0] == (int)'p' && rxbuf[1] == (int)'o' && rxbuf[2] == (int)'s' && rxbuf[3] == (int)'t')
		{
			uart_write_bytes(UART_NUM_0, a.arr[1], strlen((char*)a.arr[1]));
			uart_write_bytes(UART_NUM_0, "\n", 1);
			uart_write_bytes(UART_NUM_0, a.arr[2], strlen((char*)a.arr[2]));
			uart_write_bytes(UART_NUM_0, "\n", 1);

			https_post_request(a.arr[1], a.arr[2]);
		}else
			if(rxbuf[0] == (int)'g' && rxbuf[1] == (int)'e' && rxbuf[2] == (int)'t')
			{
				 uart_write_bytes(UART_NUM_0, a.arr[1], strlen((char*)a.arr[1]));
				 uart_write_bytes(UART_NUM_0, "\n", 1);

				 https_get_request(a.arr[1]);
			}
		clearBuffer();
		array_clear(&a);
		flag=0;
		}
		vTaskDelay( 100 / portTICK_PERIOD_MS);
	}
}

//		if(flag_post == 1){
//
//			uart_write_bytes(UART_NUM_0, "\npost", 5);
//			//https_post_request(a.arr[1], a.arr[2]);
//
//			flag_post = 0;
//		}
//
//		if(flag_get == 1){
//
//			uart_write_bytes(UART_NUM_0, "\nget", 4);
//			//https_get_request(a.arr[1]);
//
//			flag_get = 0;
//			}

// разбиение строки на слова
void array_strtok(array_t* a, char* s, const char* delim){
    char*  i, *j;
    size_t m,  n = 0;
    // подсчитываем кол-во слов
    for(i = s; *i; i = j){
        while(*i && (strchr(delim, *i) != NULL))
            ++i;

        j = i;
        while(*j && (strchr(delim, *j) == NULL))
            ++j;

        if(j > i)
            ++n;
    }

    if(! array_resize(a, n))
        return;

    m = 0;
    for(i = strtok(s, delim); i != NULL; i = strtok(NULL, delim))
        a->arr[m++] = strdup(i);
}

//удаление массива
void array_clear(array_t* a){
    size_t i;
    if(a->arr != NULL){
        for(i = 0; i < a->cnt; ++i)
            free(a->arr[i]);
        free(a->arr);
        a->arr = NULL;
        a->cnt = 0;
    }
}

//выделение памяти под массив
int array_resize(array_t* a, size_t n){
    size_t i;
    array_clear(a);
    a->arr = (char**)malloc(n * sizeof(char*));
    if(a->arr == NULL)
        return 0;

    for(i = 0; i < n; ++i)
        a->arr[i] = NULL;
    a->cnt = n;
    return 1;
}

void clearBuffer(){
   for(int i=256;i>=0;i--)
   {
	   rxbuf[i]='\0';
   }
}

