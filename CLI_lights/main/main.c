/*
Author: Samuel Gathemia
This program is provided with no warranties
Program under GNU license
Done on 24/5/2026
Enjoy!
*/

#include <stdio.h>
#include <string.h> // for strlen
#include <ctype.h> // for toupper cmd
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;

#define LED1_GPIO GPIO_NUM_2
#define LED2_GPIO GPIO_NUM_4
#define LED3_GPIO GPIO_NUM_16

#define UART_PORT UART_NUM_0
#define TXD_PIN GPIO_NUM_1 //GPIO 1 and 3 are the gpios used for the uart of the converter
#define RXD_PIN GPIO_NUM_3

void init(){
    //uart config
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
        //gpio config
   gpio_config_t led_conf = {
        .pin_bit_mask = ((1ULL << LED1_GPIO) | (1ULL << LED2_GPIO) | (1ULL << LED3_GPIO)),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };


    //install uart driver
    uart_driver_install(UART_PORT, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    // Configure UART parameters
    uart_param_config(UART_PORT, &uart_config);
    //configure uart pins
    uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    //configure gpio
    gpio_reset_pin(LED1_GPIO);
    gpio_reset_pin(LED2_GPIO);
    gpio_reset_pin(LED3_GPIO);
    gpio_config(&led_conf);
}

//led states
typedef enum{
    LED_ON,
    LED_OFF,
    LED_BLINK
}led_mode_t;
// define a tructure for the leds
typedef struct {
    int led_gpio;
    led_mode_t led_mode;
}led_config_t;
//innitialize the led configs
led_config_t led1 = {
        .led_gpio = LED1_GPIO,
        .led_mode = LED_OFF
};
led_config_t led2 = {
        .led_gpio = LED2_GPIO,
        .led_mode = LED_OFF
};
led_config_t led3 = {
        .led_gpio = LED3_GPIO,
        .led_mode = LED_OFF
};

void led1_func(){
    const char* querry = "Choose led task (1 - 3):\n 1. on\n 2. off\n 3. blink\n";
    uart_write_bytes(UART_NUM_0, (const char*)querry, strlen(querry));

    uint8_t data[RX_BUF_SIZE];
    int state = 1;
    while (state){
        int length = uart_read_bytes(UART_PORT, data, RX_BUF_SIZE - 1, pdMS_TO_TICKS(1000));

        if (length > 0){
            data[length] = '\0';
            uart_write_bytes(UART_PORT,"Function: ",strlen("Function: "));
            uart_write_bytes(UART_NUM_0, (char *)data, length);
            uart_write_bytes(UART_PORT, "\n", 1);

            if (strncmp((char*)data, "1", 1) == 0){
                led1.led_mode = LED_ON;
                uart_write_bytes(UART_NUM_0, "led on\n", strlen("led on\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "2", 1) == 0){
                led1.led_mode = LED_OFF;
                uart_write_bytes(UART_NUM_0, "led off\n", strlen("led off\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "3", 1) == 0){
                led1.led_mode = LED_BLINK;
                uart_write_bytes(UART_NUM_0, "led blinking\n", strlen("led blinking\n"));
                state = 0;

            }
            else{
                uart_write_bytes(UART_NUM_0, "Invalid function\n", strlen("Invalid function\n"));

            }
        }
    }
}
void led2_func(){
    const char* querry = "Choose led task (1 - 3):\n 1. on\n 2. off\n 3. blink\n";
    uart_write_bytes(UART_NUM_0, (const char*)querry, strlen(querry));

    uint8_t data[RX_BUF_SIZE];
    int state = 1;
    while (state){
        int length = uart_read_bytes(UART_PORT, data, RX_BUF_SIZE - 1, pdMS_TO_TICKS(1000));

        if (length > 0){
            data[length] = '\0';
            uart_write_bytes(UART_PORT,"Function: ",strlen("Function: "));
            uart_write_bytes(UART_NUM_0, (char *)data, length);
            uart_write_bytes(UART_PORT, "\n", 1);

            if (strncmp((char*)data, "1", 1) == 0){
                led2.led_mode = LED_ON;
                uart_write_bytes(UART_NUM_0, "led on\n", strlen("led on\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "2", 1) == 0){
                led2.led_mode = LED_OFF;
                uart_write_bytes(UART_NUM_0, "led off\n", strlen("led off\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "3", 1) == 0){
                led2.led_mode = LED_BLINK;
                uart_write_bytes(UART_NUM_0, "led blinking\n", strlen("led blinking\n"));
                state = 0;

            }
            else{
                uart_write_bytes(UART_NUM_0, "Invalid function\n", strlen("Invalid function\n"));

            }
        }
    }
}
void led3_func(){
    const char* querry = "Choose led task (1 - 3):\n 1. on\n 2. off\n 3. blink\n";
    uart_write_bytes(UART_NUM_0, (const char*)querry, strlen(querry));

    uint8_t data[RX_BUF_SIZE];
    int state = 1;
    while (state){
        int length = uart_read_bytes(UART_PORT, data, RX_BUF_SIZE - 1, pdMS_TO_TICKS(1000));

        if (length > 0){
            data[length] = '\0';
            uart_write_bytes(UART_PORT,"Function: ",strlen("Function: "));
            uart_write_bytes(UART_NUM_0, (char *)data, length);
            uart_write_bytes(UART_PORT, "\n", 1);

            if (strncmp((char*)data, "1", 1) == 0){
                led3.led_mode = LED_ON;
                uart_write_bytes(UART_NUM_0, "led on\n", strlen("led on\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "2", 1) == 0){
                led3.led_mode = LED_OFF;
                uart_write_bytes(UART_NUM_0, "led off\n", strlen("led off\n"));
                state = 0;

            }
            else if (strncmp((char*)data, "3", 1) == 0){
                led3.led_mode = LED_BLINK;
                uart_write_bytes(UART_NUM_0, "led blinking\n", strlen("led blinking\n"));
                state = 0;

            }
            else{
                uart_write_bytes(UART_NUM_0, "Invalid function\n", strlen("Invalid function\n"));

            }
        }
    }
}

//rx data to lowercase
void str_to_lower(char *str)
{
    while (*str)
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
void uart_task(void *arg){
     uint8_t data[RX_BUF_SIZE];

    while (1){

        int length = uart_read_bytes(UART_PORT, data, RX_BUF_SIZE - 1, pdMS_TO_TICKS(1000));

        if (length > 0){
            data[length] = '\0';
            str_to_lower((char*)data);
            //printf("Received: %s\n", data);
            //echo data recieved, but printf works just fine
            uart_write_bytes(UART_PORT,"Received: ",strlen("Received: "));
            uart_write_bytes(UART_NUM_0, (char *)data, length);
            uart_write_bytes(UART_PORT, "\n", 1);

            if (strncmp((char*)data, "1", 1) == 0){
                led1_func();
            }
            else if (strncmp((char*)data, "2", 1) == 0){
                led2_func();
            }
            else if (strncmp((char*)data, "3", 1) == 0){
                led3_func();
            }
            else{
                uart_write_bytes(UART_NUM_0, "Unknown command\n", strlen("Unknown command\n"));
            }

        }
    }
}

//led task
void led1_task(void *arg){
    while(1){
        switch(led1.led_mode){
            case LED_ON:
            gpio_set_level(led1.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_OFF:
            gpio_set_level(led1.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_BLINK:
            gpio_set_level(led1.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(led1.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void led2_task(void *arg){
    while(1){
        switch(led2.led_mode){
            case LED_ON:
            gpio_set_level(led2.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_OFF:
            gpio_set_level(led2.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_BLINK:
            gpio_set_level(led2.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(led2.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void led3_task(void *arg){
    while(1){
        switch(led3.led_mode){
            case LED_ON:
            gpio_set_level(led3.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_OFF:
            gpio_set_level(led3.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(50));
            break;

            case LED_BLINK:
            gpio_set_level(led3.led_gpio, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(led3.led_gpio, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    init(); //configs for UART and GPIO
    //create the rx task
    xTaskCreate(uart_task, "uart_task", 4096, NULL, 5, NULL);
    //create the led task
    xTaskCreate(led1_task, "led1_task", 2048, NULL, 5, NULL);
    xTaskCreate(led2_task, "led2_task", 2048, NULL, 5, NULL);
    xTaskCreate(led3_task, "led3_task", 2048, NULL, 5, NULL);

}
