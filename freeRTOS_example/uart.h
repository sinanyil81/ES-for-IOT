#ifndef UART_H__
#define UART_H__

#include <stdio.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


// enable/disable the use of UART for printf output
#define UART_PRINTF     1

#define UART_INTERFACE  EUSCI_A0_BASE
#define UART_RX_PORT    GPIO_PORT_P1
#define UART_RX_PIN     GPIO_PIN2
#define UART_TX_PORT    GPIO_PORT_P1
#define UART_TX_PIN     GPIO_PIN3
#define UART_GPIO_AF    GPIO_PRIMARY_MODULE_FUNCTION


void uart_init(uint32_t);
void uart_init_gpio(void);
void uart_println(const char*, ...);

/*
 * If UART_PRINTF is enabled, override required system calls.
 */
#if UART_PRINTF > 0
#define uart_print printf
int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);
#endif

#endif /* UART_H__ */
