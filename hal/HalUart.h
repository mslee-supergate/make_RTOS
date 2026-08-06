#ifndef HAL_HARLUART_H_
#define HAL_HARLUART_H_

#include <stdint.h>

void Hal_uart_init(void);
void Hal_uart_put_char(uint8_t ch);
uint8_t Hal_uart_get_char(void);

#endif /* HAL_HARLUART_H_ */
