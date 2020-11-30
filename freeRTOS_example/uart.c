#include <stdint.h>
#include <stdio.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "uart.h"

/**
 * UCxBRS config lookup table (see Ref. Manual p.721, Table 22-4)
 */
const uint_fast16_t UCxBRS[] = {
       0,  529,  715,  835, 1001, 1252, 1430, 1670, 2147, 2224, 2503, 3000, 3335, 3575, 3753, 4003, 4286, 4378, 5002, 5715, 6003, 6254, 6432, 6667, 7001, 7147, 7503, 7861, 8004, 8333, 8464, 8572, 8751, 9004, 9170, 9288,
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x11, 0x21, 0x22, 0x44, 0x25, 0x49, 0x4A, 0x52, 0x92, 0x53, 0x55, 0xAA, 0x6B, 0xAD, 0xB5, 0xB6, 0xD6, 0xB7, 0xBB, 0xDD, 0xED, 0xEE, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE,
};

/**
 * UART peripheral configuration (with baudrate configuration placeholder).
 * To manually calculate and set clock configuration of these values with the
 * online calculator at: http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
 */
 eUSCI_UART_Config uart_config = {
    .selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK,    // SMCLK Clock Source
    .clockPrescalar = 0,                                    // BRDIV default
    .firstModReg = 0,                                       // UCxBRF default
    .secondModReg = 0,                                      // UCxBRS default
    .parity = EUSCI_A_UART_NO_PARITY,                       // No Parity
    .msborLsbFirst = EUSCI_A_UART_LSB_FIRST,                // MSB First
    .numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT,          // One stop bit
    .uartMode = EUSCI_A_UART_MODE,                          // UART mode
    .overSampling = 0,                                      // Over sampling default
};


// configure EUSCI module for UART operation on pins P1.2 and P1.3
void uart_init(uint32_t baudrate)
{
    // initialize GPIO first
    uart_init_gpio();

    // baudrate settings calculation from TI demo
    float N = (float) CS_getSMCLK() / (float) baudrate;

    if (N > 16)
    {
        uart_config.clockPrescalar = (uint_fast16_t) (N / 16);
        uart_config.firstModReg = (uint_fast16_t) (((N / 16.0f) - (float)uart_config.clockPrescalar) * 16);
        uart_config.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
    }
    else
    {
        uart_config.clockPrescalar = (uint_fast16_t) N;
        uart_config.firstModReg = 0;
        uart_config.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    }

    // fractional portion calculation
    uint_fast16_t frac = (N - (uint_fast16_t) N) * 10000;
    uart_config.secondModReg = 0;
    for (int_fast8_t i = 35; i >= 0; i--)
    {
        if (frac >= UCxBRS[i])
        {
            uart_config.secondModReg = UCxBRS[36 + i];
            break;
        }
    }

    // initialize using driverlib
    UART_initModule(UART_INTERFACE, &uart_config);

    // interrupt setup
    // -- none --

    // enable module
    UART_enableModule(UART_INTERFACE);
}

/**
 * Initialize the GPIO pins used by the UART.
 */
void uart_init_gpio(void)
{
    // configure clock and data ports to connect to UART peripheral
    GPIO_setAsPeripheralModuleFunctionOutputPin(UART_TX_PORT, UART_TX_PIN, UART_GPIO_AF);
    GPIO_setAsPeripheralModuleFunctionOutputPin(UART_RX_PORT, UART_RX_PIN, UART_GPIO_AF);

    // interrupt setup
    // -- none --
}

/**
 * Send string via UART peripheral
 * @param str Pointer to the message to send
 * @param ... printf-style parameters
 */
void uart_println(const char* str, ...)
{
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
}




/*
 * If UART_PRINTF is enabled, override required system calls.
 */
#if UART_PRINTF > 0
int fputc(int c, register FILE *stream)
{
    UART_transmitData(UART_INTERFACE, (uint8_t) c);
    return c;
}

int fputs(const char *s, register FILE *stream)
{
    uart_println(s);
    return 0;
}

#endif

