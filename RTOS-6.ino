/*
 * Queues are a source to transfer data or copy data between two variables of different tasks safely without any premption
 * Just like TCS or Bykea Parcel service.
 * Task#1 takes data from local variable and send it to Queue. If There are any available indexes in Queues it will succesfuly copy to that particular index and returns 
 * pdTRUE, and pdFALSE if there are not available slots and queue is full. In task2, it will recieve the value on FIFO bases and make that place vacant, Queue will automaticlaly bring second last value to the top.
 * if success occurs in cuting and pasting value to the local variable of Task#2 it will return pdTRUE else pdFALSE. Usually, we donot block the ticks to wait for data to get ready on recieving side.
 *
 *
 */


static const BaseType_t esp_core=0;

/*#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
*/ 

static const uint8_t queue_length = 6; //length of queue created
static QueueHandle_t msg_queue;

void task1(void *parameter)
{
  int datas;
  while(1)
  {
    //recieve message in a queue (donot block)
    if(xQueueReceive(msg_queue, (void*)&datas, 0) == pdTRUE)
    {
      Serial.print("Added Data: "); Serial.println(datas);
    }
    Serial.println(datas);
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}


void setup() {
  Serial.begin(115200);
  vTaskDelay(3000/portTICK_PERIOD_MS);
  Serial.println("----> FREEERTOS QUEUE DEMO <----");

  msg_queue = xQueueCreate(queue_length, sizeof(int));

  xTaskCreatePinnedToCore(task1, "Task 1", 1024, NULL, 1,NULL, esp_core);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  static int num =0;
  if(xQueueSend(msg_queue, (void*)&num,0) == pdFALSE)
  {
    Serial.println("Queue full");
  }
  num++;
  vTaskDelay(1000/portTICK_PERIOD_MS);

}
