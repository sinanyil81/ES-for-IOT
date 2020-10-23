#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// configure buttons P1.1 and P1.4
	P1->DIR = ~(uint8_t) (BIT1 | BIT4 );
	P1->OUT = BIT1 | BIT4;
    P1->REN = BIT1 | BIT4;
    P1->SEL0 = 0;
    P1->SEL1 = 0;

    //set port as output (for LED)
    P2->DIR = BIT0 | BIT1;
    P2->OUT = 0;
    P2->SEL0 = 0;
    P2->SEL1 = 0;

    // Interrupt high-to-low
    P1->IES = BIT1 | BIT4;
    // clear interrupt flags
    P1->IFG = 0;
    // enable interrupt for P1.1 and P1.4
    P1->IE = BIT1 | BIT4;

    //enable interrupt for port 1
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);

    while(1){
        __sleep();
        __no_operation();                   // For debugger
    }
}


/* Port1 interrupt */
void PORT1_IRQHandler(void)
{
    //Button 1 red led
    if (P1->IFG & BIT1)
    {
        //toggle led
        P2->OUT ^= BIT0;
        //clear the interrupt flag
        P1->IFG &= ~BIT1;
    }

    //Button 2 green light
    if (P1->IFG & BIT4)
    {
        //toggle led
        P2->OUT ^= BIT1;
        //clear the interrupt flag
        P1->IFG &= ~BIT4;
    }
}
