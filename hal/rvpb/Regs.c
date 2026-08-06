#include "Uart.h"
#include "Interrupt.h"

volatile PL011_t *const Uart =
    (volatile PL011_t *)UART_BASE_ADDRESS0;
volatile GicCput_t *const GicCpu =
    (volatile GicCput_t *)GIC_CPU_BASE;
volatile GicDist_t *const GicDist =
    (volatile GicDist_t *)GIC_DIST_BASE;
