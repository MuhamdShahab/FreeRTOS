#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/semphr.h"


static int global = 0;
static SemaphoreHandle_t mutex = NULL;


void task1(void *parameter)
{
    while(1)
    {
        if(xSemaphoreTake(mutex,0) == pdTRUE)
        {
            global ++;
            printf("Number 1 ::  %d\n", global);
            xSemaphoreGive(mutex);
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }
}
void task2(void *parameter)
{
    while(1)
    {
        if(xSemaphoreTake(mutex,0) == pdTRUE)
        {
            global ++;
            printf("Number 2 ::  %d\n", global);
            xSemaphoreGive(mutex);
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }
}


void app_main(void)
{


mutex = xSemaphoreCreateMutex(); 

xTaskCreatePinnedToCore(task1, "Task 1", 2048, NULL, 1, NULL, 0);  
xTaskCreatePinnedToCore(task2, "Task 2", 2048, NULL, 1, NULL, 0);

vTaskDelete(NULL);
}
s