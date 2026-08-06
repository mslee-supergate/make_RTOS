#include <stdint.h>
#include "Uart.h"
#include "HalUart.h"
#include "HalInterrupt.h"

extern volatile PL011_t *const Uart;

static void interrupt_handler(void);

void Hal_uart_init(void)
{
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;

    //Enable UART interrupt in GIC
    Uart->uartimsc.bits.RXIM = 1;

    //Register UART interrupt handler
    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);
}

void Hal_uart_put_char(uint8_t ch)
{
    while (Uart->uartfr.bits.TXFF == 1) {
    }
    Uart->uartdr.all = ch;
}

uint8_t Hal_uart_get_char(void)
{
    uint8_t data;

    while(Uart->uartfr.bits.RXFE);

    data = Uart->uartdr.all;

    //Check for errors
    if(data & 0xFFFFFF00)
    {
        Uart->uartrsr.all = 0; //Clear the error flags
        return 0;
    }

    data = (uint8_t)(data & 0xFF);
    return data;
}

static void interrupt_handler(void)
{
    uint8_t data = Hal_uart_get_char();
    Hal_uart_put_char(data);
}