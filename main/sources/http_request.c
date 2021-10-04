#include <http_request.h>

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            //ESP_LOGI("http", "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
           // ESP_LOGI("http", "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            //ESP_LOGI("http", "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
           // ESP_LOGI("http", "HTTP_EVENT_ON_HEADER");
            printf("%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            if (!esp_http_client_is_chunked_response(evt->client)) {
                printf("%.*s", evt->data_len, (char*)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
           // ESP_LOGI("http", "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            //ESP_LOGI("http", "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}


void https_post_request(char* site, char* data)
{
    char local_response_buffer[1000] = {0};
	esp_http_client_config_t config = {
       // .url = "http://httpbin.org/post",
        .event_handler = _http_event_handle,
        .user_data = local_response_buffer,
    };

	esp_http_client_handle_t client = esp_http_client_init(&config);
	//strcat(site, "/post");
	esp_http_client_set_url(client,site);
    const char *post_data = data;

    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI("SERG", "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE("SERG", "HTTP POST request failed: %s", esp_err_to_name(err));
    }
}


void https_get_request(char* site)
{
	 char local_response_buffer[1000] = {0};

	    esp_http_client_config_t config = {
	        .event_handler = _http_event_handle,
	        .user_data = local_response_buffer,
	    };

	    esp_http_client_handle_t client = esp_http_client_init(&config);
	    esp_http_client_set_url(client,site);
	    esp_err_t err = esp_http_client_perform(client);
	    if (err == ESP_OK) {
	        ESP_LOGI("SERG", "HTTP GET Status = %d, content_length = %d",
	                esp_http_client_get_status_code(client),
	                esp_http_client_get_content_length(client));
	    } else {
	        ESP_LOGE("SERG", "HTTP GET request failed: %s", esp_err_to_name(err));
	    }
	    ESP_LOG_BUFFER_HEX("SERG", local_response_buffer, strlen(local_response_buffer));
}

