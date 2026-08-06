#ifndef LIB_STDIO_H_
#define LIB_STDIO_H_

#include <stdint.h>
#include "stdarg.h"

typedef enum utoa_t {
    utoa_dec = 10,
    utoa_hex = 16
} utoa_t;

uint32_t putstr(const char* s);
uint32_t debug_printf(const char* format, ...);
uint32_t vsprintf(char* buffer, const char* format, va_list args);
uint32_t utoa(char* buf, uint32_t value, utoa_t base);

#endif /* LIB_STDIO_H_ */
