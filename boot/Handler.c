#include <stdbool.h>
#include "HalInterrupt.h"

__attribute__ ((interrupt ("IRQ"))) void Irq_handler(void)
{
    Hal_interrupt_run_handler();
}

__attribute__ ((interrupt ("FIQ"))) void Fiq_handler(void)
{
    while(true);
}
