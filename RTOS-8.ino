const int led_pin = 19;

static TimerHandle_t auto_reload = NULL;

void takesinput(void *parameters) {

  char c;

  while (1) {
    // See if there are things in the input serial buffer
    if (Serial.available() > 0) {

      // If so, echo everything back to the serial port
      c = Serial.read();
      Serial.print(c);

      // Turn on the LED
      digitalWrite(led_pin, HIGH);
    if( xTimerReset(auto_reload, 0 ) != pdPASS ) 
           Serial.println("5 Sec LED TImer Could'nt Reset Properly.");
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void backlight(TimerHandle_t xTimer)
{
  if((uint32_t)pvTimerGetTimerID(xTimer) == 1)
  {
  Serial.println("No Input From 5 Seconds");
  digitalWrite(led_pin, LOW);
  }
}

void setup() 
{
  Serial.begin(115200);
  vTaskDelay(2000/ portTICK_PERIOD_MS);
  Serial.println("---- Free RTOS Software Timers Demo ----");

  pinMode(led_pin, OUTPUT);

auto_reload = xTimerCreate("Auto-timer", //Name of the timers
                        5000/portTICK_PERIOD_MS, //Timer period in ticks
                        pdTRUE, // Auto Reload on
                        (void*)1, // Timer ID
                        backlight);  //timer expiry interrupt triger function

if(auto_reload == NULL )
{
    Serial.println("5 Sec Led TimerTimer Not Created Properly.");
}
else 
{
    if( xTimerStart(auto_reload, 0 ) != pdPASS ) 
      Serial.println("5 Sec Led Timer Couldn't Start properly.");
}

xTaskCreatePinnedToCore(takesinput, //task name
                        "Task 1", //task get name
                        1024, //stacj size
                        NULL, // parameter to pass to function
                        1, // priority
                        NULL, // task handle
                        0); //runs on core 0
                        
    vTaskDelete(NULL);
}
void loop()
{
    //Task Deleted
}
