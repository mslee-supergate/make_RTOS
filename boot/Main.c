#include <stdbool.h>
#include "stdint.h"
#include "stdlib.h"
#include "HalInterrupt.h"
#include "HalUart.h"
#include "HalTimer.h"
#include "stdio.h"
#include "Kernel.h"

static void Hw_init(void);
static void Debug_printf_test(void);
static void Timer_test(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

static void Kernel_init(void)
{
    uint32_t taskId;

    Kernel_task_init();

    taskId = Kernel_task_create(User_task0);
    if(NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task0 creation fail\n");
    }

    taskId = Kernel_task_create(User_task1);
    if(NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task1 creation fail\n");
    }

    taskId = Kernel_task_create(User_task2);
    if(NOT_ENOUGH_TASK_NUM == taskId)
    {
        putstr("Task2 creation fail\n");
    }

    Kernel_start();
}

void User_task0(void)
{
    uint32_t local = 0;

    while(true)
    {
        debug_printf("User Task #0 SP=0x%x\n", &local);
        Kernel_yield();
    }
}

void User_task1(void)
{
    uint32_t local = 0;

    while(true)
    {
        debug_printf("User Task #1 SP=0x%x\n", &local);
        Kernel_yield();
    }
}
void User_task2(void)
{
    uint32_t local = 0;

    while(true)
    {
        debug_printf("User Task #2 SP=0x%x\n", &local);
        Kernel_yield();
    }
}

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
    //Timer_test();
    Timer_test();
    
    Kernel_init();
 
    while(true);
}

static void Hw_init(void)
{
    Hal_interrupt_init();
    Hal_uart_init();
    Hal_timer_init();
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

static void Timer_test(void)
{
    uint32_t i = 3;
    while(i--)
    {
        debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
        delay(1000);
    }
}
