#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

static TimerHandle_t one_time = NULL;
static TimerHandle_t multiple_time = NULL;


void one_time_function(TimerHandle_t xTimer)
{
    if((uint32_t)pvTimerGetTimerID(xTimer) == 0)
  printf("One time Expired. \n");

      if((uint32_t)pvTimerGetTimerID(xTimer) == 1)
  printf("Auto Reload Expired. \n");
}

void app_main() 
{
vTaskDelay(2000/ portTICK_PERIOD_MS);
printf("---- Free RTOS Software Timers Demo ---- \n");

one_time = xTimerCreate("One-time-timer", //Name of the timers
                        2000/portTICK_PERIOD_MS, //Timer period in ticks
                        pdFALSE, // Auto Reload oof
                        (void*)0, // Timer ID
                        one_time_function);  //timer expiry interrupt triger function

multiple_time = xTimerCreate("One-time-timer", //Name of the timers
                        1000/portTICK_PERIOD_MS, //Timer period in ticks
                        pdTRUE, // Auto Reload on
                        (void*)1, // Timer ID
                        one_time_function);  //timer expiry interrupt triger function

if(one_time == NULL || multiple_time == NULL )
{
    printf("One of the Timer Not Created Properly. \n");
}
else 
{
    vTaskDelay(1000/portTICK_PERIOD_MS);
    printf("Timers Started \n");
    xTimerStart(one_time, portMAX_DELAY);
   xTimerStart(multiple_time, portMAX_DELAY);
}
    vTaskDelete(NULL);
}