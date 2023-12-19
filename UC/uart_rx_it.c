//
// Created by tony on 23-12-19.
//

#include "uart_rx_it.h"
#include "usart.h"
#include "stdlib.h"
//不用FreeRTOS
//#include "stdlib.h"



int cmpare_uint8(const uint8_t *arr1,const uint8_t *arr2,int len)
{
    for(int i=0;i<len;i++)
        if(*(arr1+i) != *(arr2+i))
            return -1;
    return 0;

}

HAL_StatusTypeDef uart_rx_it_start(uart_rx_it_handle * handle)
{
    if(handle->head == NULL)
        return HAL_ERROR;
    handle->index=0;
    handle->buffer = (uint8_t*)malloc(sizeof(uint8_t)*(handle->head_size+handle->data_size));
    HAL_StatusTypeDef res =  HAL_UART_Receive_IT(handle->huart,handle->buffer,1);
//    if(res == HAL_OK)
//        handle->index+=1;
    return res;

}
void UART_RxCpltCallback(UART_HandleTypeDef *huart,uart_rx_it_handle * handle)
{
    if(huart==handle->huart)
    {
        uint8_t  get_data_frame = 0;
        if(handle->index<handle->head_size-1)
        {

        } else
        {
            if(cmpare_uint8(handle->head,handle->buffer+handle->index-handle->head_size,handle->head_size)==0)
            {}
        }
        handle->index+=1;
        if(handle->index == handle->data_size + handle->head_size)
            handle->index=0;
        HAL_UART_Receive_IT(handle->huart,handle->buffer+handle->index, 1);
    }

}