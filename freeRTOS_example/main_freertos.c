#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "uart.h"

/**
 * UART baudrate configuration.
 */
const uint32_t uart_baudrate = 115200;


/***
 * Declaration of functions
 */
void vTaskFunction(void *pvParameters);

void vSimpleDelay();

/***
 * Function for printing to the UART terminal, using a mutex to avoid access conflicts.
 */
void uart_println_mutex(const char* str, ...);

//m2_1_1s//
/* The semaphore handle, which is used in uart_println_mutex() */
SemaphoreHandle_t xMutex;
//m2_1_1e//

/*-----------------------------------------------------------*/
int main(void)
{
    // Initialize UART
    uart_init(uart_baudrate);

    BaseType_t result = pdPASS;

    //m2_1_2s//
    xMutex = xSemaphoreCreateMutex();
    //m2_1_2e//

    /***
     * The first task will be created and the string to be printed will be passed as a parameter
     */
    uart_println_mutex("Creating TaskA.");
    char *pcParameters1 = "TaskA is running and running.";
    result =  xTaskCreate(vTaskFunction, "TaskA", 1000, (void*)pcParameters1, 1, NULL);
    if (result != pdPASS) {
        uart_println_mutex("Error creating TaskA.");
        return 0;
    }

    /***
     * The second task will be created and the string to be printed will be passed as a parameter.
     * Note: For Task 1.1. we could also use the same task function (i.e. vTask1Function) and only
     * change the parameter.
     */
    uart_println_mutex("Creating TaskB.");
    char *pcParameters2 = "TaskB is running and running.";
    result =  xTaskCreate(vTaskFunction, "TaskB", 1000, (void*)pcParameters2, 1, NULL);
    if (result != pdPASS) {
        uart_println_mutex("Error creating TaskB.");
        return 0;
    }

    // Start the tasks and timer running
    vTaskStartScheduler();

    /* The following line should never be reached.
     * Otherwise there was insufficient FreeRTOS heap
     * memory available for the task to be created.
     */
    return 0;
}
/*-----------------------------------------------------------*/


/**
 * Task function for TaskA and TaskB
 * @param pvParameters String with the task name
 */
void vTaskFunction(void *pvParameters)
{
    uart_println_mutex("Start task.");

    while (1) {
        uart_println_mutex(( char * ) pvParameters);
        // Uncomment the next line for solution to Task 2.2
//        vSimpleDelay();
        //   Comment the next line for solution to Task 2.3
        //m2_2s//
        vTaskDelay(pdMS_TO_TICKS(1000));
        //m2_2e//
    }
}

/***
 * Wait for a given amount of time
 */
void vSimpleDelay()
{
    for(uint32_t i=0; i < 100000;i++)
    {
    }
}

/***
 * A custom print function, which is extended to use a mutex to avoid access conflicts.
 * @param str Pointer to the message to send
 * @param ... printf-style parameters
 */
//m2_1_3s//
void uart_println_mutex(const char* str, ...)
{
    xSemaphoreTake(xMutex, portMAX_DELAY);

    // ======= DO NOT EDIT BELOW THIS LINE =======
    static char print_buffer[256];

    va_list lst;
    va_start(lst, str);
    vsnprintf(print_buffer, 256, str, lst);
    str = print_buffer;
    while (*str)
    {
        while (!(EUSCI_A_CMSIS(UART_INTERFACE)->IFG & EUSCI_A_IFG_TXIFG));
        EUSCI_A_CMSIS(UART_INTERFACE)->TXBUF = *str;
        str++;
    }
    while (!(EUSCI_A_CMSIS(UART_INTERFACE)->IFG & EUSCI_A_IFG_TXIFG));
    EUSCI_A_CMSIS(UART_INTERFACE)->TXBUF = '\r';
    while (!(EUSCI_A_CMSIS(UART_INTERFACE)->IFG & EUSCI_A_IFG_TXIFG));
    EUSCI_A_CMSIS(UART_INTERFACE)->TXBUF = '\n';
    // ======= DO NOT EDIT ABOVE THIS LINE =======

    xSemaphoreGive(xMutex);
}
//m2_1_3e//


/* -------------------------------------------------------------------------
 * Default FreeRTOS hooks
 * ------------------------------------------------------------------------- */

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/* ------------------------------------------------------------------------- */

void vApplicationIdleHook( void )
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}
/* ------------------------------------------------------------------------- */

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/* ------------------------------------------------------------------------- */

void *malloc( size_t xSize )
{
    /* There should not be a heap defined, so trap any attempts to call
    malloc. */
    Interrupt_disableMaster();
    for( ;; );
}
/* ------------------------------------------------------------------------- */


/*-----------------------------------------------------------*/

void vPreSleepProcessing(uint32_t ulExpectedIdleTime)
{

}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
     configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
     added here, but the tick hook is called from an interrupt context, so
     code must not attempt to block, and only the interrupt safe FreeRTOS API
     functions can be used (those that end in FromISR()). */

    /* The full demo includes a software timer demo/test that requires
     prodding periodically from the tick interrupt. */
    //vTimerPeriodicISRTests();
    /* Call the periodic event group from ISR demo. */
    //vPeriodicEventGroupsProcessing();
    /* Use task notifications from an interrupt. */
    //xNotifyTaskFromISR();
    /* Use mutexes from interrupts. */
    //vInterruptSemaphorePeriodicTest();
}
/*-----------------------------------------------------------*/
