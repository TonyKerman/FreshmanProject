
#ifndef __USER_MAIN_H
#define __USER_MAIN_H

#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * middle val
 * servo_start_sem 790 ,S2 505; S3 415
 *
 *
 */
extern SemaphoreHandle_t data_mutex;
extern SemaphoreHandle_t sync_mutex;
void StartServoTask(void *argument);
//void StartSensorTask(void  * argument);
#ifdef __cplusplus
}
#endif

#endif
