//
// Created by tony on 23-12-19.
//

#ifndef UART_RX_IT_H
#define UART_RX_IT_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
#include "usart.h"

typedef struct uart_rx_it_handle
{
    UART_HandleTypeDef *huart;
    uint8_t head_size;
    uint8_t data_size;
    uint8_t index;
    uint8_t * head;
    uint8_t * buffer;
}uart_rx_it_handle;
HAL_StatusTypeDef uart_rx_it_start(uart_rx_it_handle * handle);
void UART_RxCpltCallback(UART_HandleTypeDef *huart,uart_rx_it_handle * handle);
#ifdef __cplusplus
}
#endif
#endif //FRESHMANPROJECT_STM32_UART_RX_IT_H
