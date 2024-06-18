# Práctica 4 parte 2

## Código:

```c++

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
    // No hay necesidad de hacer nada en el bucle principal
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

 ```

## Descripción

En este código se crean dos tareas para encender y apagar un LED.

Se define el pin en el que estará conectado el LED. En la funcón **setup()** este es configurado como salida. Se crea un semáforo binario, una vez se ha creado con éxito se da el semáforo, se permite que la tarea de encendido comienze; y acto seguido se crean las tareas.

Ambas tareas están en un bucle infinito que se ejecuta continuamente, cada tarea intenta tomar el semáforo y espera hasta que esté disponible. Una vez recibe el semáforo cada una ejecuta su acción, en el caso de la tarea **TaskTurnOn** enciende el LED y en el caso de la tarea **TaskTurnOff** apaga el LED.

## Diagrama de flujos

```mermaid

graph LR;
    inicio[Inicio del programa] --> configurar[Configurar pin de LED];
    configurar --> crear_sem[Crear semáforo];
    crear_sem --> dar_sem[Dar semáforo inicial];
    dar_sem --> crear_turnon[Crear tarea TurnOn];
    crear_turnon --> crear_turnoff[Crear tarea TurnOff];
    crear_turnoff --> bucle[Bucle principal];
    bucle --> fin[Fin del programa];

```

## Conclusión

En conclusión, este codigo muestra el uso de dos tareas distintas para apagar y encender un LED y estas son sincronizadas mediante un semáforo.
