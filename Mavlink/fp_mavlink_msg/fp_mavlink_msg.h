/** @file
 *  @brief MAVLink comm protocol generated from fp_mavlink_msg.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_FP_MAVLINK_MSG_H
#define MAVLINK_FP_MAVLINK_MSG_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_FP_MAVLINK_MSG.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_FP_MAVLINK_MSG_XML_HASH -1526173315997505494

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{1, 153, 21, 21, 0, 0, 0}, {2, 242, 8, 8, 0, 0, 0}, {3, 89, 24, 24, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_FP_MAVLINK_MSG

// ENUM DEFINITIONS


/** @brief 机械臂工作模式 */
#ifndef HAVE_ENUM_ARM_MODE
#define HAVE_ENUM_ARM_MODE
typedef enum ARM_MODE
{
   DISABLE=0, /* 收起 | */
   ENABLE=1, /* 打开 | */
   ARM_MODE_ENUM_END=2, /*  | */
} ARM_MODE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_cmd.h"
#include "./mavlink_msg_gyro.h"
#include "./mavlink_msg_servo_fdb.h"

// base include



#if MAVLINK_FP_MAVLINK_MSG_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_CMD, MAVLINK_MESSAGE_INFO_GYRO, MAVLINK_MESSAGE_INFO_SERVO_FDB}
# define MAVLINK_MESSAGE_NAMES {{ "CMD", 1 }, { "GYRO", 2 }, { "SERVO_FDB", 3 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_FP_MAVLINK_MSG_H
