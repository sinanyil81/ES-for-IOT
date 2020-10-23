#include "msp.h"


/**
 * main.c
 */
int main(void) {
    volatile unsigned int i;

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    // GPIO Setup
    P1->OUT &= ~BIT0;                       // Clear LED to start
    P1->DIR |= BIT0;                        // Set P1.0/LED to output

    // Configure P5.4 for ADC
    P5->SEL1 |= BIT4;
    P5->SEL0 |= BIT4;

    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);

    // Sampling time, S&H=16, ADC14 on
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    // Use sampling timer, 12-bit conversion results
    ADC14->CTL1 = ADC14_CTL1_RES_2;
    // A1 ADC input select; Vref=AVCC
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;
    // Enable ADC conv complete interrupt
    ADC14->IER0 |= ADC14_IER0_IE0;

    while (1)
    {
        // Start sampling/conversion
        ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
        __sleep();
        __no_operation();                   // For debugger
    }
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void) {
    // ADC12MEM0 = A1 > 0.5AVcc?
    if (ADC14->MEM[0] >= 0x7FF)
      P1->OUT |= BIT0;  // P1.0 = 1
    else
      P1->OUT &= ~BIT0; // P1.0 = 0
}

