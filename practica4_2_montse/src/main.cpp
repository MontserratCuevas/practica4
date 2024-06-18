#include <Arduino.h>

    SemaphoreHandle_t semaphore;

    void TaskTurnOn(void *pvParameters);
    void TaskTurnOff(void *pvParameters);

    const int ledPin = 23;

    void setup() {
    pinMode(ledPin, OUTPUT);
    semaphore = xSemaphoreCreateBinary();
    if (semaphore != NULL) {
        xSemaphoreGive(semaphore); 
    }

    xTaskCreate(TaskTurnOn, "TurnOn", 1000, NULL, 1, NULL);
    xTaskCreate(TaskTurnOff, "TurnOff", 1000, NULL, 1, NULL);
    }

    void loop() {
    // No hay necesidad de hacer nada en el bucle
        }

    void TaskTurnOn(void *pvParameters) {
    (void) pvParameters;
    for (;;) {
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
        digitalWrite(ledPin, HIGH); 
        xSemaphoreGive(semaphore); 
        }
    }
    }

    void TaskTurnOff(void *pvParameters) {
     (void) pvParameters;
    for (;;) {
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
        digitalWrite(ledPin, LOW);
        xSemaphoreGive(semaphore); 
        }
         }
    }