
#ifndef __USER_MAIN_H
#define __USER_MAIN_H

#include "semphr.h"
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>
#include <sensor_msgs/msg/joint_state.h>
#include <std_msgs/msg/float32_multi_array.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
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
void StartDefaultTask(void *argument);
void StartControllerTask(void  * argument);
#ifdef __cplusplus
}
#endif

#endif
