/* DESCRIPTION 
 *  Aborting a delay called by a function
 *  xTaskAbortDelay(task_Handle)
 *  
 */

//Run this 3rd line code if you dont know how many cores your ESP have otherwise 
static const BaseType_t app_cpu = 0; // my esp have two core with # 0  and 1 ;

/*#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
*/ 

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

// Pins
static const int led_pin = 19;

// Our task: blink an LED
void task__1(void *ptr) {
  while(1) 
  {
    Serial.println("I AM HERE 1");
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

void task__2(void *ptr) {
while(1) 
  {
    Serial.println("I AM HERE 7");
    vTaskDelay(200/portTICK_PERIOD_MS);
    xTaskAbortDelay(task_1);
  }
}


void setup() {
    Serial.begin(115200);
  // Configure pin
  pinMode(led_pin, OUTPUT);
  delay(5000);
    Serial.println("----READING STARTED----");

  Serial.print("Setup and loop task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  
  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              task__1,    // Function to be called
              "Task 1", // Name of task
              1024,         // Stack size (768 + usage)
              NULL, // Parameter to pass to function
              0,            // Task priority (0 to configMAX_PRIORITIES - 1)
              &task_1,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

   xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              task__2,    // Function to be called
              "Task 2", // Name of task
              1024,         // Stack size (768 + usage)
              NULL, // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              &task_2,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

             vTaskDelete(NULL); // Delete setup(after task creation) and Loop tasks
}

void loop() {
  //Will be delete after calling vTaskDelete(NULL) in Setup
}
