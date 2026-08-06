#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

static void Hw_init(void);
static void Debug_printf_test(void);

void main(void)
{
    Hw_init();

    uint32_t i = 100;
    while(i--)
    {
        Hal_uart_put_char('N');
    }
    Hal_uart_put_char('\n');

    putstr("Hello, World!\n");

    //c, s, u, x
    Debug_printf_test();


    i = 100;
    while(i--)
    {
        uint8_t ch = Hal_uart_get_char();
        Hal_uart_put_char(ch);
    }
    
}

static void Hw_init(void)
{
    Hal_uart_init();
}

static void Debug_printf_test(void)
{
    debug_printf("=== debug_printf test ===\n");

    debug_printf("c: %c\n", 'A');
    debug_printf("s: %s\n", "Hello RTOS");
    debug_printf("u: %u\n", (uint32_t)123456789U);
    debug_printf("x: 0x%x\n", (uint32_t)0xDEADBEEFU);

    debug_printf("all: %c, %s, %u, 0x%x\n",
                 'Z',
                 "TEST",
                 (uint32_t)1234U,
                 (uint32_t)0xABCDU);
}