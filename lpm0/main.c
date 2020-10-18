#include "msp.h"

int main(void)
{
    // Hold the watchdog

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // GPIO Port Configuration for lowest power configuration
    P1->OUT = 0x00; P1->DIR = 0xFF;
    P2->OUT = 0x00; P2->DIR = 0xFF;
    P3->OUT = 0x00; P3->DIR = 0xFF;
    P4->OUT = 0x00; P4->DIR = 0xFF;
    P5->OUT = 0x00; P5->DIR = 0xFF;
    P6->OUT = 0x00; P6->DIR = 0xFF;
    P7->OUT = 0x00; P7->DIR = 0xFF;
    P8->OUT = 0x00; P8->DIR = 0xFF;
    P9->OUT = 0x00; P9->DIR = 0xFF;
    P10->OUT = 0x00; P10->DIR = 0xFF;
    PJ->OUT = 0x00; PJ->DIR = 0xFF;

    P1->OUT = BIT1;    // Set pull-up mode
    P1->REN = BIT1;    // Enable pull-up resistor
    P1->SEL0 = 0;      // Select GPIO
    P1->SEL1 = 0;      // Select GPIO

    P1->DIR |= BIT0;    // P1.0 set as input

    P1->IES = BIT1; // Interrupt on high-to-low transition
    P1->IFG = 0;    // Clear all P1 interrupt flags
    P1->IE = BIT1;  // Enable interrupt for P1.1

    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);

    while(1){
        __sleep();        // Enter LPM0 mode. Execution stops here.
        __no_operation(); // Just added here to have a line (to step over during debugging)
    }

}

/* Port1 ISR */
void PORT1_IRQHandler(void)
{
    // Check if P1.1 interrupt triggered
    if(P1->IFG & BIT1){
        // Toggle the output on the LED
        P1->OUT ^= BIT0;
    }

    // clear the flag
    P1->IFG &= ~BIT1;
}

