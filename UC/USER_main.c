
#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "USER_main.h"
#include "usart.h"
#include "tim.h"
#include "Serial_Servo.h"
#include "mapping.h"
#include "Mpu6050.h"
#include "i2c.h"
#include "moving_average_filter.h"
#define SERVO_NUM 4

enum arm_modes{ARM_DISABLE,ARM_ENABLE}arm_mode;
Serial_Servo * Servo[SERVO_NUM];
Mpu6050 mpu1;
mapping_param_t servo_mapping[SERVO_NUM];
float flitered_gyro[2];
MovingAverageFilter mpu_roll_filter;
MovingAverageFilter mpu_pitch_filter;
uint8_t uart6_rxbuf[10];
uint8_t uart6_rxindex=0;

union v16{
    int16_t int16;
    uint8_t uint8[2];
}object_xy[2];


static inline void Servos_ReadPos();
static inline void arm_disable_executor();
static inline void arm_enable_executor();


void StartServoTask(void *argument)
{
    arm_mode = ARM_ENABLE;

    for (int i = 0; i < SERVO_NUM; i++) {
        Servo[i] = Serial_Servo_Create(&huart2,i+1);
        Serial_Servo_SetLoadOrUnload(Servo[i],1);
        Serial_Servo_Set_Mode(Servo[i],0);
        int8_t s=1;
        do {
            vTaskDelay(1);
            s=Serial_Servo_ReadPosition(Servo[i]);
            if(s==-1){
                printf("Servo %d init failed\r\n",i);
                HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                vTaskDelay(200/ portTICK_RATE_MS);
            }

        } while (s);
        //pos_feedback.data.data[i]=Servo[i]->currentPostion;
    }
    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
    mapping_param_init(&servo_mapping[0],900,500,900,0,90,0);
    mapping_limit_i(&servo_mapping[0],0,1000);
    Serial_Servo_SetLimit(Servo[0],0,1000);
    vTaskDelay(50);
    mapping_param_init(&servo_mapping[1],430,750,430,0,90,0);
    mapping_limit_i(&servo_mapping[1],430,1000);
    Serial_Servo_SetLimit(Servo[1],430,1000);
    vTaskDelay(50);
    mapping_param_init(&servo_mapping[2],50,400,50,0,90,0);
    Serial_Servo_SetLimit(Servo[2],0,500);
    vTaskDelay(50);
    mapping_param_init(&servo_mapping[3],320,1075,700,-90,90,0);

    //Serial_Servo_SetLimit(Servo[3],0,1000);
//    vTaskDelay(50);
//    Serial_Servo_Move(Servo[0], mapping_o2i(&servo_mapping[0],90),3000);
//    vTaskDelay(500);
//    Serial_Servo_Move(Servo[1],mapping_o2i(&servo_mapping[1],90),3000);
//    vTaskDelay(50);
//    Serial_Servo_Move(Servo[2],mapping_o2i(&servo_mapping[2],0),3000);
//    vTaskDelay(50);
//    Serial_Servo_Move(Servo[3],mapping_o2i(&servo_mapping[3],-45),3000);
//    vTaskDelay(50);

    for(;;)
    {
        Servos_ReadPos();
        //printf("roll:%f\r\n",MAF_update(&mpu_roll_filter,mpu1.roll));
        //printf("target pos:%f \n",mapping_o2i(&servo_mapping[3],mpu1.roll*180/3.14-45));
        if(arm_mode==ARM_DISABLE)
            arm_disable_executor();
        else if(arm_mode==ARM_ENABLE)
            arm_enable_executor();

        vTaskDelay(200/portTICK_RATE_MS);
    }
}


void StartSensorTask(void *argument)
{
    float last_roll=0;
    float last_pitch=0;
    HAL_UART_Receive_IT(&huart6,uart6_rxbuf,5);
    while (Mpu6050_Init(&mpu1,&hi2c1,0,Afsr_2g,Gfsr_250LSB,50)!=0)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        printf("mpu6050 init failed\r\n");
        vTaskDelay(200/portTICK_RATE_MS);
    }
    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
    MAF_init(&mpu_roll_filter,5);
    MAF_init(&mpu_pitch_filter,5);
    for(;;)
    {
        Mpup6050_update(&mpu1);

        flitered_gyro[0]=MAF_update(&mpu_roll_filter,mpu1.roll)*180/3.14;
        flitered_gyro[1]=MAF_update(&mpu_pitch_filter,mpu1.pitch)*180/3.14;
        printf("/*%f,%f*/\n",flitered_gyro[1],flitered_gyro[0]);
        vTaskDelay(20/portTICK_RATE_MS);
    }

}


void Servos_ReadPos(){
    for (int i = 0; i < SERVO_NUM; i++) {
        Serial_Servo_ReadPosition(Servo[i]);
    }
}


static inline void arm_disable_executor()
{
    Serial_Servo_Move(Servo[0], mapping_o2i(&servo_mapping[0],170),2000);
    Serial_Servo_Move(Servo[1], mapping_o2i(&servo_mapping[1],0),2000);
    Serial_Servo_Move(Servo[2], mapping_o2i(&servo_mapping[2],0),2000);
    Serial_Servo_Move(Servo[3], mapping_o2i(&servo_mapping[3],0),2000);
}


static inline void arm_enable_executor()
{
    if (xSemaphoreTake(data_mutex, 100 / portTICK_RATE_MS) == pdTRUE){
        for(int i=0;i<SERVO_NUM;i++){
            Serial_Servo_Move(Servo[0], mapping_o2i(&servo_mapping[0],15-flitered_gyro[1]),200);
            vTaskDelay(50);
            Serial_Servo_Move(Servo[1],mapping_o2i(&servo_mapping[1],75-flitered_gyro[1]),200);
            vTaskDelay(50);
            Serial_Servo_Move(Servo[2], mapping_o2i(&servo_mapping[2],-flitered_gyro[1]),200);
            vTaskDelay(50);
            Serial_Servo_Move(Servo[3],mapping_o2i(&servo_mapping[3],flitered_gyro[0]-45),200);
        }
        xSemaphoreGive(data_mutex);
//        printf("pos_raw:\t%d %d %d %d\r\n",Servo[0]->currentPostion,Servo[1]->currentPostion,Servo[2]->currentPostion,Servo[3]->currentPostion);
//            printf("pos:\t\t%d %3f %3f %3f\r\n",
//                   Servo[0]->currentPostion,
//                   mapping_i2o(&servo_mapping[1],Servo[1]->currentPostion),
//                   mapping_i2o(&servo_mapping[2],Servo[2]->currentPostion),
//                   mapping_i2o(&servo_mapping[3],Servo[3]->currentPostion));
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance==USART6)
    {

        if(uart6_rxbuf[uart6_rxindex]==0x33)
        {
            if(uart6_rxindex>=4)
            {
                *(uart6_rxbuf-4) = object_xy[0].uint8[0];
                *(uart6_rxbuf-3) = object_xy[0].uint8[1];
                *(uart6_rxbuf-2) = object_xy[1].uint8[0];
                *(uart6_rxbuf-1) = object_xy[0].uint8[1];
                HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                uart6_rxindex=0;
            }
            uart6_rxindex+=1;
            if(uart6_rxindex>9)
                uart6_rxindex=0;
        }

        HAL_UART_Receive_IT(&huart6,uart6_rxbuf+uart6_rxindex,5);
    }

}