
#include "main.h"
#include "cmsis_os.h"
#include "USER_main.h"
#include "usart.h"
#include "Serial_Servo.h"
#define SERVO_NUM 6
#ifdef __cplusplus
extern "C" {
#endif

//声明micro ros 组件
rclc_support_t support;
rcl_allocator_t allocator;
rclc_executor_t executor;
rcl_node_t node;
//声明  自定义组件
rcl_subscription_t pos_cmd_subscriber;
rcl_publisher_t debug_publisher;
rcl_publisher_t pos_feedback_publisher;
rcl_publisher_t angle_feedback_publisher;
rcl_timer_t timer1;
//声明自定义消息
std_msgs__msg__Float32MultiArray pos_feedback;
std_msgs__msg__Float32MultiArray angle_feedback;
std_msgs__msg__Float32MultiArray _pos_cmd;
std_msgs__msg__Float32MultiArray pos_cmd;
//std_msgs__msg__Int32 stm_time;
std_msgs__msg__String debugmsg;

bool cubemx_transport_open(struct uxrCustomTransport *transport);
bool cubemx_transport_close(struct uxrCustomTransport *transport);
size_t cubemx_transport_write(struct uxrCustomTransport *transport, const uint8_t *buf, size_t len, uint8_t *err);
size_t cubemx_transport_read(struct uxrCustomTransport *transport, uint8_t *buf, size_t len, int timeout, uint8_t *err);
void *microros_allocate(size_t size, void *state);
void microros_deallocate(void *pointer, void *state);
void *microros_reallocate(void *pointer, size_t size, void *state);
void *microros_zero_allocate(size_t number_of_elements, size_t size_of_element, void *state);
#ifdef __cplusplus
}
#endif
//声明函数
void pos_cmd_subCallback(const void *msgin);
void timer1_callback(rcl_timer_t *timer, int64_t last_call_time);
uint16_t filter(const int16_t lst_value,const int16_t new_value,const uint16_t A);
static void Servos_ReadPos();
void StartDefaultTask(void *argument);


const int16_t bis[SERVO_NUM] = {800,1155,400,700,0,0};
Serial_Servo * Servo[SERVO_NUM];

//定时器回调函数，用于发布消息
void timer1_callback(rcl_timer_t *timer, int64_t last_call_time)
{
//    stm_time.data = (int32_t)xTaskGetTickCount();
//    rcl_publish(&stm_time_publisher, &stm_time, NULL);
    if(xSemaphoreTake(data_mutex, 70/portTICK_RATE_MS)==pdTRUE)
    {
        rcl_publish(&pos_feedback_publisher, &pos_feedback, NULL);
        rcl_publish((&angle_feedback_publisher), &angle_feedback, NULL);
        xSemaphoreGive(data_mutex);
    }
}

//接收回调函数
void pos_cmd_subCallback(const void *msgin) {
    const std_msgs__msg__Float32MultiArray *_pos_cmd = (const std_msgs__msg__Float32MultiArray *) msgin;
    if (xSemaphoreTake(data_mutex, 10 / portTICK_RATE_MS) == pdTRUE) {
        std_msgs__msg__Float32MultiArray__copy(_pos_cmd, &pos_cmd);
        xSemaphoreGive(data_mutex);
    } else {
        return;
    }
    /*发送dubug topic
    debugmsg.data.capacity = 20;
    debugmsg.data.size = 20;
    debugmsg.data.data = (char *) pvPortMalloc(20 * sizeof(char));
    sprintf(debugmsg.data.data, "%f", msgj_in.position.data[2]);
    rcl_publish(&debug_publisher, &debugmsg, NULL);
    vPortFree(debugmsg.data.data);*/

}


void StartControllerTask(void *argument)
{

    const uint16_t dt = 100 ;
    //Mpu6050 * mpu1 = Mpu6050_Create(&hi2c1,0,Afsr_2g,Gfsr_250LSB,100);
//    while (Mpu6050_Init(mpu1)!=0)
//    {
//        HAL_GPIO_TogglePin(LDR_GPIO_Port,LDR_Pin);
//        osDelay(1000);
//    }
    HAL_GPIO_WritePin(LDR_GPIO_Port,LDR_Pin,GPIO_PIN_SET);
    for (int i = 0; i < SERVO_NUM; i++) {
        Servo[i] = Serial_Servo_Create(&huart2,i+1,bis[i]);
        Serial_Servo_SetLoadOrUnload(Servo[i],1);
        Serial_Servo_Set_Mode(Servo[i],0);
        int8_t s=1;
        do {
            osDelay(1);
            s=Serial_Servo_ReadPosition(Servo[i]);
            if(s==-1){
                HAL_GPIO_TogglePin(LDR_GPIO_Port,LDR_Pin);
                osDelay(100);
            }

        } while (s);
        pos_feedback.data.data[i]=Servo[i]->currentPostion;
    }
    HAL_GPIO_WritePin(LDR_GPIO_Port,LDR_Pin,GPIO_PIN_SET);
    Serial_Servo_SetLimit(Servo[0],0,1000);
    osDelay(5);
    Serial_Servo_SetLimit(Servo[1],0,1000);
    osDelay(5);
    Serial_Servo_SetLimit(Servo[2],0,1000);
    osDelay(5);
    Serial_Servo_SetLimit(Servo[3],0,1000);
    osDelay(5);
//    Serial_Servo_Move(Servo[0],350,3000);
//    osDelay(1000);
//    Serial_Servo_Move(Servo[1],440,3000);
//    Serial_Servo_Move(Servo[2],440,3000);
//    Serial_Servo_Move(Servo[3],452,3000);
//    osDelay(4000);
    Serial_Servo_Move(Servo[0],640,3000);
    Serial_Servo_Move(Servo[1],800,3000);
    Serial_Servo_Move(Servo[2],625,3000);
    Serial_Servo_Move(Servo[3],450,3000);
    osDelay(3000);
    //uint32_t  PreviousWakeTime = osKernelSysTick();
    while (1)
    {
        Servos_ReadPos();
        for(int i=0;i<SERVO_NUM;i++){
            pos_feedback.data.data[i]=filter(pos_feedback.data.data[i],Servo[i]->currentPostion,400);
            //servoPos[i]=Servo[i]->currentPostion;
        }
        //    Mpup6050_update(mpu1);

        osDelayUntil(dt);
    }

}

void StartDefaultTask(void *argument) {
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    if (rmw_uros_set_custom_transport(
            true,
            (void *) &huart1,
            cubemx_transport_open,
            cubemx_transport_close,
            cubemx_transport_write,
            cubemx_transport_read) == RMW_RET_ERROR)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);

    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = microros_allocate;
    freeRTOS_allocator.deallocate = microros_deallocate;
    freeRTOS_allocator.reallocate = microros_reallocate;
    freeRTOS_allocator.zero_allocate = microros_zero_allocate;

    if (!rcutils_set_default_allocator(&freeRTOS_allocator))
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    // micro-ROS app
    allocator = rcl_get_default_allocator();
    //create support
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_support_init(&support, 0, NULL, &allocator)
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    // create node
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_node_init_default(&node, "stm32_node", "", &support)
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    std_msgs__msg__String__init(&debugmsg);

    // create publisher angle_feedback
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_publisher_init_default(
            &debug_publisher,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
            "debug")
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_publisher_init_default(
            &angle_feedback_publisher,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg,Float32MultiArray ),
            "angle_feedback")
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_publisher_init_default(
            &pos_feedback_publisher,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg,Float32MultiArray ),
            "pos_feedback")
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
//    if (rclc_publisher_init_default(
//            &stm_time_publisher,
//            &node,
//            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
//            "stm32_time")
//        == RCL_RET_OK)
//        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    //create subscriber
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_subscription_init_default(
            &pos_cmd_subscriber,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
            "pos_cmd")
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    //create timer
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if( rclc_timer_init_default(
            &timer1,
            &support,
            RCL_MS_TO_NS(100),
            timer1_callback)
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    //create executor
    executor = rclc_executor_get_zero_initialized_executor();
    HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_RESET);
    if (rclc_executor_init(&executor, &support.context, 2, &allocator)
        == RCL_RET_OK)
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin, GPIO_PIN_SET);
    //add subscriber and timer to executor
    rclc_executor_add_subscription(
            &executor,
            &pos_cmd_subscriber,
            &_pos_cmd,
            &pos_cmd_subCallback,
            ON_NEW_DATA);

    rclc_executor_add_timer(&executor, &timer1);
    osDelay(300);
// 为数组型的msg分配空间
    pos_feedback.data.capacity=SERVO_NUM;
    pos_feedback.data.size=SERVO_NUM;
    pos_feedback.data.data=(float *)pvPortMalloc(SERVO_NUM*sizeof(float));
    angle_feedback.data.capacity=2;
    angle_feedback.data.size=2;
    angle_feedback.data.data=(float *)pvPortMalloc(2*sizeof(float));
    pos_cmd.data.capacity=SERVO_NUM;
    pos_cmd.data.size=SERVO_NUM;
    pos_cmd.data.data=(float *)pvPortMalloc(SERVO_NUM*sizeof(float));
    xSemaphoreGive(sync_mutex);
    osDelay(10);
    xSemaphoreTake(sync_mutex, portMAX_DELAY);
    rclc_executor_spin(&executor);
    for (;;) {}
}


/*
 * S0 0-->800
 * S1 0-->1155
 * S2 0-->400
 * S3 0-->700
 * 方向：右手定则x->y为增大方向
 */



void __(void *argument)
{
    int16_t targetPos[SERVO_NUM]={640,800,625,450};
    int16_t temp[SERVO_NUM]={0};
    while (1)
    {
        //Serial_Servo_Stop(Servo[3]);
//        BaseType_t state = xQueueReceive(targetPosQueue,temp,5000);
//        if(state == pdPASS) {
//            for (int i = 0; i < SERVO_NUM; i++) {
//                if (temp[i] != targetPos[i]) {
//                    targetPos[i] = temp[i];
//                    //Serial_Servo_Move(Servo[i],limit(targetPos[i],0,1000),4*dt);
//                    if(i==3){
//                        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//                        printf("2\n");
//                        Serial_Servo_Move(Servo[3],targetPos[3], dt);
//                    }
//                }
//            }
//           // printf("targetPos[%d]:%d\n", 3, targetPos[3]);
//        }
//        osDelay(4*dt);
        //printf("servoMoveTaskHandle %d\n",(int)uxTaskGetStackHighWaterMark(servoMoveTaskHandle));
    }
}

void Servos_ReadPos(){
    for (int i = 0; i < SERVO_NUM; i++) {

        Serial_Servo_ReadPosition(Servo[i]);

    }
}
uint16_t filter(const int16_t lst_value,const int16_t new_value,const uint16_t A){
    if((new_value - lst_value > A) || (lst_value - new_value > A)) {
        return lst_value;
    } else {
        return new_value;
    }
}

