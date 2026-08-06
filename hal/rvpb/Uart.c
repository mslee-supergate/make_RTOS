#include <stdint.h>
#include "Uart.h"
#include "HalUart.h"

static volatile PL011_t *const Uart =
    (volatile PL011_t *)UART_BASE_ADDRESS0;

void Hal_uart_init(void)
{
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;
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