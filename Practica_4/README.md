# Práctica 4

## Código:

```c++
    void anotherTask( void * parameter );
    void setup()
    {
    Serial.begin(112500);
    /* we create a new task here */
    xTaskCreate(anotherTask, /* Task function. */
    "another Task", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
    }
    /* the forever loop() function is invoked by Arduino ESP32 loopTask */
    void loop()
    {
    Serial.println("this is ESP32 Task");
    delay(1000);
    }
    /* this function will be invoked when additionalTask was created */
    void anotherTask( void * parameter )
    {
    /* loop forever */
    for(;;)
    {
    Serial.println("this is another Task");
    delay(1000);
    }
    /* delete a task when finish,
    this will never happen because this is infinity loop */
    vTaskDelete( NULL );
    }

```

En este código se implementan dos tareas distintas.
 
En el **setup()** se crea una de ellas usando la función xTaskCreate()  y es llamada **anotherTask**, esta imprime un mensaje repetidamente 
por  el puerto serial.

En la función **loop()** se ejecuta repetidamente la tarea principal. 

Las tareas imprimen simultaneamente mensajes diferentes por el puerto serial cada segundo (1000ms).

Al final, hay una llamada a **vTaskDelete(NULL)** para la liberación de memoria, pero en este caso nunca va a llegar devido a que el bucle es 
infinito (for(;;)).

## Conclusión:

En conclusión, este código implementa multiples tareas simultaneamente, y esto nos permite aprovechar al máximo los recursos del microcontrolador, teniendo así una mayor eficiencia. 
