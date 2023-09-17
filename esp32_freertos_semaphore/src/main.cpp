#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include <stdio.h>

SemaphoreHandle_t xSemaphore = NULL;

TaskHandle_t myTaskHandle1 = NULL;
TaskHandle_t myTaskHandle2 = NULL;

// function for task1
void Demo_Task(void *arg) {

  while (1) {
    printf("Message Sent! [%ld] \n", xTaskGetTickCount());
    xSemaphoreGive(xSemaphore);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// functin for task2
void Demo_Task2(void *arg) {

  while (1) {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
      printf("Received Message [%ld] \n", xTaskGetTickCount());
    }
  }
}

extern "C" {
void app_main(void) {
  xSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(Demo_Task, "Demo_Task", 2098, NULL, 10, &myTaskHandle1);
  xTaskCreate(Demo_Task2, "Demo_Task2", 2098, NULL, 10, &myTaskHandle2);
}
}
