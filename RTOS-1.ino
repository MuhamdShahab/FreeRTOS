/* DESCRIPTION 
 *  IN the below program i have created a task for ESP32 using Arduino IDE 
 *  first the tast configure how many cores we have in the controller aftetr that a task or thread is created in setup and with priority 1, 
 *  A local variable was also passed for better inderstanidng as arg1 to the the task else only Write NULL.
 *  LED blinks with the value of arg1 as passes in setup
 *  
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


// Pins
static const int led_pin = 19;

// Our task: blink an LED
void toggleLED(void *ptr) {
  int index = (int)ptr;
  
  Serial.println(index);
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(index / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(index / portTICK_PERIOD_MS);
  }
}

void setup() {
    Serial.begin(9600);
  // Configure pin
  pinMode(led_pin, OUTPUT);

 int arg1 =200;
  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              toggleLED,    // Function to be called
              "Toggle LED", // Name of task
              1024,         // Stack size (768 + usage)
              (void*) arg1, // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

             vTaskDelete(NULL); // Delete setup and Loop tasks
}

void loop() {
 //Task Deleted via vTaskDelate(NULL);
}
