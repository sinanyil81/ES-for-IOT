#include "msp.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

int main(void)
{
    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_holdTimer();

    // Set P1.0 to output direction
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);

    while(1){
        // Toggle P1.0 output
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);

        // Delay
        for(i=100000; i>0; i--);
    }
}
