/* DESCRIPTION 
 *  using vTaskDelayUntil()
 *  https://www.freertos.org/vtaskdelayuntil.html
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
    Serial.println("I AM HERE 1");

   TickType_t xLastWakeTime;
 const TickType_t xFrequency = 1000;
     xLastWakeTime = xTaskGetTickCount();
  while(1) {
    digitalWrite(led_pin, HIGH);
     Serial.println("I AM HERE 2");
   vTaskDelayUntil( &xLastWakeTime, xFrequency );
    digitalWrite(led_pin, LOW);
      Serial.println("I AM HERE 4");
   vTaskDelayUntil( &xLastWakeTime, xFrequency );
  }
}
void printmsg(void *ptr) {
    Serial.println("I AM HERE 6");
  while(1) {
    Serial.println("I AM HERE 7");
  }
}


void setup() {
    Serial.begin(115200);
  // Configure pin
  pinMode(led_pin, OUTPUT);
  delay(5000);
    Serial.println("----READING STARTED----");
 int arg1 =1000;
  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              toggleLED,    // Function to be called
              "Toggle LED", // Name of task
              1024,         // Stack size (768 + usage)
              (void*) arg1, // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

   xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              printmsg,    // Function to be called
              "Print Msg", // Name of task
              1024,         // Stack size (768 + usage)
              NULL, // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

             vTaskDelete(NULL); // Delete setup(after task creation) and Loop tasks
}

void loop() {
  //Will be delete after calling vTaskDelete(NULL) in Setup
}
