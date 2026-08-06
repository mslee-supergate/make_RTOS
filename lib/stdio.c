#include "stdio.h"
#include "HalUart.h"
#include <stddef.h>

#define PRINTF_BUF_SIZE 1024U

static char printf_buf[PRINTF_BUF_SIZE];

uint32_t putstr(const char* s)
{
    uint32_t c = 0;
    while(*s)
    {
        Hal_uart_put_char(*s++);
        c++;
    }
    return c;
    
}

uint32_t debug_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(printf_buf, format, args);
    va_end(args);

    return putstr(printf_buf);
}

uint32_t vsprintf(char* buf, const char* format, va_list args)
{
    uint32_t c = 0;

    char ch;
    char* str;
    uint32_t uint;
    uint32_t hex;

    for(uint32_t i = 0; format[i]; i ++)
    {
        if(format[i] == '%')
        {
            i++;
            switch(format[i])
            {
                case 'c':
                    ch =(char)va_arg(args, int32_t);
                    buf[c++] = ch;
                    break;

                case 's':
                    str = (char*)va_arg(args, char*);
                    if(str == NULL)
                    {
                        str = "(null)";
                    }
                    while(*str)
                    {
                        buf[c++] = *str++;
                    }
                    break;

                case 'u':
                    uint = (uint32_t)va_arg(args, uint32_t);
                    c += utoa(&buf[c], uint, utoa_dec);
                    break;

                case 'x':
                    hex = (uint32_t)va_arg(args, uint32_t);
                    c += utoa(&buf[c], hex, utoa_hex);
                    break;
            }       
        }    
        else
        {
            buf[c++] = format[i];
        }
    }

    if(c >= PRINTF_BUF_SIZE)
    {
        buf[0] = '\0';
        return 0;
    }

    buf[c] = '\0';
    return c;
    
}

uint32_t utoa(char* buf, uint32_t value, utoa_t base)
{
    uint32_t c = 0;
    int32_t idx = 0;
    char tmp[11];

    do{
        uint32_t t = value % (uint32_t)base;
        if (t >= 10)
        {
            t += 'A' - '0' - 10;
        }
        tmp[idx++] = (char)(t + '0');
        value /= (uint32_t)base;
    } while(value);

    for(int32_t i = idx - 1; i >= 0; i--)
    {
        buf[c++] = tmp[i];
    }

    return c;
}