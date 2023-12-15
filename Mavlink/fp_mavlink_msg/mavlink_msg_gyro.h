#pragma once
// MESSAGE GYRO PACKING

#define MAVLINK_MSG_ID_GYRO 2


typedef struct __mavlink_gyro_t {
 float roll; /*<  x 方向角弧度*/
 float pith; /*<  y 方向角弧度*/
} mavlink_gyro_t;

#define MAVLINK_MSG_ID_GYRO_LEN 8
#define MAVLINK_MSG_ID_GYRO_MIN_LEN 8
#define MAVLINK_MSG_ID_2_LEN 8
#define MAVLINK_MSG_ID_2_MIN_LEN 8

#define MAVLINK_MSG_ID_GYRO_CRC 242
#define MAVLINK_MSG_ID_2_CRC 242



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GYRO { \
    2, \
    "GYRO", \
    2, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gyro_t, roll) }, \
         { "pith", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gyro_t, pith) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GYRO { \
    "GYRO", \
    2, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gyro_t, roll) }, \
         { "pith", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gyro_t, pith) }, \
         } \
}
#endif

/**
 * @brief Pack a gyro message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll  x 方向角弧度
 * @param pith  y 方向角弧度
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyro_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll, float pith)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GYRO_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pith);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GYRO_LEN);
#else
    mavlink_gyro_t packet;
    packet.roll = roll;
    packet.pith = pith;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GYRO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GYRO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
}

/**
 * @brief Pack a gyro message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll  x 方向角弧度
 * @param pith  y 方向角弧度
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gyro_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll,float pith)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GYRO_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pith);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GYRO_LEN);
#else
    mavlink_gyro_t packet;
    packet.roll = roll;
    packet.pith = pith;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GYRO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GYRO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
}

/**
 * @brief Encode a gyro struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyro_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gyro_t* gyro)
{
    return mavlink_msg_gyro_pack(system_id, component_id, msg, gyro->roll, gyro->pith);
}

/**
 * @brief Encode a gyro struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gyro_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gyro_t* gyro)
{
    return mavlink_msg_gyro_pack_chan(system_id, component_id, chan, msg, gyro->roll, gyro->pith);
}

/**
 * @brief Send a gyro message
 * @param chan MAVLink channel to send the message
 *
 * @param roll  x 方向角弧度
 * @param pith  y 方向角弧度
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gyro_send(mavlink_channel_t chan, float roll, float pith)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GYRO_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pith);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GYRO, buf, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
#else
    mavlink_gyro_t packet;
    packet.roll = roll;
    packet.pith = pith;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GYRO, (const char *)&packet, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
#endif
}

/**
 * @brief Send a gyro message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gyro_send_struct(mavlink_channel_t chan, const mavlink_gyro_t* gyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gyro_send(chan, gyro->roll, gyro->pith);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GYRO, (const char *)gyro, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
#endif
}

#if MAVLINK_MSG_ID_GYRO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gyro_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll, float pith)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pith);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GYRO, buf, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
#else
    mavlink_gyro_t *packet = (mavlink_gyro_t *)msgbuf;
    packet->roll = roll;
    packet->pith = pith;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GYRO, (const char *)packet, MAVLINK_MSG_ID_GYRO_MIN_LEN, MAVLINK_MSG_ID_GYRO_LEN, MAVLINK_MSG_ID_GYRO_CRC);
#endif
}
#endif

#endif

// MESSAGE GYRO UNPACKING


/**
 * @brief Get field roll from gyro message
 *
 * @return  x 方向角弧度
 */
static inline float mavlink_msg_gyro_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pith from gyro message
 *
 * @return  y 方向角弧度
 */
static inline float mavlink_msg_gyro_get_pith(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a gyro message into a struct
 *
 * @param msg The message to decode
 * @param gyro C-struct to decode the message contents into
 */
static inline void mavlink_msg_gyro_decode(const mavlink_message_t* msg, mavlink_gyro_t* gyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gyro->roll = mavlink_msg_gyro_get_roll(msg);
    gyro->pith = mavlink_msg_gyro_get_pith(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_GYRO_LEN? msg->len : MAVLINK_MSG_ID_GYRO_LEN;
        memset(gyro, 0, MAVLINK_MSG_ID_GYRO_LEN);
    memcpy(gyro, _MAV_PAYLOAD(msg), len);
#endif
}
