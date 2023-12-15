#pragma once
// MESSAGE CMD PACKING

#define MAVLINK_MSG_ID_CMD 1


typedef struct __mavlink_cmd_t {
 float servo_pos[4]; /*<  y 舵机目标位置（仅ENABLE时可用）*/
 int16_t target[2]; /*<  目标在相机中相对图像·中心的x,y位置*/
 uint8_t mod; /*<  模式*/
} mavlink_cmd_t;

#define MAVLINK_MSG_ID_CMD_LEN 21
#define MAVLINK_MSG_ID_CMD_MIN_LEN 21
#define MAVLINK_MSG_ID_1_LEN 21
#define MAVLINK_MSG_ID_1_MIN_LEN 21

#define MAVLINK_MSG_ID_CMD_CRC 153
#define MAVLINK_MSG_ID_1_CRC 153

#define MAVLINK_MSG_CMD_FIELD_SERVO_POS_LEN 4
#define MAVLINK_MSG_CMD_FIELD_TARGET_LEN 2

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CMD { \
    1, \
    "CMD", \
    3, \
    {  { "mod", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_cmd_t, mod) }, \
         { "servo_pos", NULL, MAVLINK_TYPE_FLOAT, 4, 0, offsetof(mavlink_cmd_t, servo_pos) }, \
         { "target", NULL, MAVLINK_TYPE_INT16_T, 2, 16, offsetof(mavlink_cmd_t, target) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CMD { \
    "CMD", \
    3, \
    {  { "mod", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_cmd_t, mod) }, \
         { "servo_pos", NULL, MAVLINK_TYPE_FLOAT, 4, 0, offsetof(mavlink_cmd_t, servo_pos) }, \
         { "target", NULL, MAVLINK_TYPE_INT16_T, 2, 16, offsetof(mavlink_cmd_t, target) }, \
         } \
}
#endif

/**
 * @brief Pack a cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mod  模式
 * @param servo_pos  y 舵机目标位置（仅ENABLE时可用）
 * @param target  目标在相机中相对图像·中心的x,y位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mod, const float *servo_pos, const int16_t *target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_LEN];
    _mav_put_uint8_t(buf, 20, mod);
    _mav_put_float_array(buf, 0, servo_pos, 4);
    _mav_put_int16_t_array(buf, 16, target, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_LEN);
#else
    mavlink_cmd_t packet;
    packet.mod = mod;
    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*4);
    mav_array_memcpy(packet.target, target, sizeof(int16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
}

/**
 * @brief Pack a cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mod  模式
 * @param servo_pos  y 舵机目标位置（仅ENABLE时可用）
 * @param target  目标在相机中相对图像·中心的x,y位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mod,const float *servo_pos,const int16_t *target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_LEN];
    _mav_put_uint8_t(buf, 20, mod);
    _mav_put_float_array(buf, 0, servo_pos, 4);
    _mav_put_int16_t_array(buf, 16, target, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CMD_LEN);
#else
    mavlink_cmd_t packet;
    packet.mod = mod;
    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*4);
    mav_array_memcpy(packet.target, target, sizeof(int16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
}

/**
 * @brief Encode a cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_cmd_t* cmd)
{
    return mavlink_msg_cmd_pack(system_id, component_id, msg, cmd->mod, cmd->servo_pos, cmd->target);
}

/**
 * @brief Encode a cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_cmd_t* cmd)
{
    return mavlink_msg_cmd_pack_chan(system_id, component_id, chan, msg, cmd->mod, cmd->servo_pos, cmd->target);
}

/**
 * @brief Send a cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param mod  模式
 * @param servo_pos  y 舵机目标位置（仅ENABLE时可用）
 * @param target  目标在相机中相对图像·中心的x,y位置
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_cmd_send(mavlink_channel_t chan, uint8_t mod, const float *servo_pos, const int16_t *target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CMD_LEN];
    _mav_put_uint8_t(buf, 20, mod);
    _mav_put_float_array(buf, 0, servo_pos, 4);
    _mav_put_int16_t_array(buf, 16, target, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD, buf, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
#else
    mavlink_cmd_t packet;
    packet.mod = mod;
    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*4);
    mav_array_memcpy(packet.target, target, sizeof(int16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD, (const char *)&packet, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
#endif
}

/**
 * @brief Send a cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_cmd_send_struct(mavlink_channel_t chan, const mavlink_cmd_t* cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cmd_send(chan, cmd->mod, cmd->servo_pos, cmd->target);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD, (const char *)cmd, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mod, const float *servo_pos, const int16_t *target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 20, mod);
    _mav_put_float_array(buf, 0, servo_pos, 4);
    _mav_put_int16_t_array(buf, 16, target, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD, buf, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
#else
    mavlink_cmd_t *packet = (mavlink_cmd_t *)msgbuf;
    packet->mod = mod;
    mav_array_memcpy(packet->servo_pos, servo_pos, sizeof(float)*4);
    mav_array_memcpy(packet->target, target, sizeof(int16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CMD, (const char *)packet, MAVLINK_MSG_ID_CMD_MIN_LEN, MAVLINK_MSG_ID_CMD_LEN, MAVLINK_MSG_ID_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE CMD UNPACKING


/**
 * @brief Get field mod from cmd message
 *
 * @return  模式
 */
static inline uint8_t mavlink_msg_cmd_get_mod(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field servo_pos from cmd message
 *
 * @return  y 舵机目标位置（仅ENABLE时可用）
 */
static inline uint16_t mavlink_msg_cmd_get_servo_pos(const mavlink_message_t* msg, float *servo_pos)
{
    return _MAV_RETURN_float_array(msg, servo_pos, 4,  0);
}

/**
 * @brief Get field target from cmd message
 *
 * @return  目标在相机中相对图像·中心的x,y位置
 */
static inline uint16_t mavlink_msg_cmd_get_target(const mavlink_message_t* msg, int16_t *target)
{
    return _MAV_RETURN_int16_t_array(msg, target, 2,  16);
}

/**
 * @brief Decode a cmd message into a struct
 *
 * @param msg The message to decode
 * @param cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_cmd_decode(const mavlink_message_t* msg, mavlink_cmd_t* cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cmd_get_servo_pos(msg, cmd->servo_pos);
    mavlink_msg_cmd_get_target(msg, cmd->target);
    cmd->mod = mavlink_msg_cmd_get_mod(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CMD_LEN? msg->len : MAVLINK_MSG_ID_CMD_LEN;
        memset(cmd, 0, MAVLINK_MSG_ID_CMD_LEN);
    memcpy(cmd, _MAV_PAYLOAD(msg), len);
#endif
}
