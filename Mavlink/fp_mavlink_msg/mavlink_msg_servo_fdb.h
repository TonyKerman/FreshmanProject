#pragma once
// MESSAGE SERVO_FDB PACKING

#define MAVLINK_MSG_ID_SERVO_FDB 3


typedef struct __mavlink_servo_fdb_t {
 float servo_pos[6]; /*<  y 舵机位置*/
} mavlink_servo_fdb_t;

#define MAVLINK_MSG_ID_SERVO_FDB_LEN 24
#define MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN 24
#define MAVLINK_MSG_ID_3_LEN 24
#define MAVLINK_MSG_ID_3_MIN_LEN 24

#define MAVLINK_MSG_ID_SERVO_FDB_CRC 89
#define MAVLINK_MSG_ID_3_CRC 89

#define MAVLINK_MSG_SERVO_FDB_FIELD_SERVO_POS_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SERVO_FDB { \
    3, \
    "SERVO_FDB", \
    1, \
    {  { "servo_pos", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_servo_fdb_t, servo_pos) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SERVO_FDB { \
    "SERVO_FDB", \
    1, \
    {  { "servo_pos", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_servo_fdb_t, servo_pos) }, \
         } \
}
#endif

/**
 * @brief Pack a servo_fdb message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param servo_pos  y 舵机位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_servo_fdb_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *servo_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SERVO_FDB_LEN];

    _mav_put_float_array(buf, 0, servo_pos, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SERVO_FDB_LEN);
#else
    mavlink_servo_fdb_t packet;

    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SERVO_FDB_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SERVO_FDB;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
}

/**
 * @brief Pack a servo_fdb message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param servo_pos  y 舵机位置
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_servo_fdb_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *servo_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SERVO_FDB_LEN];

    _mav_put_float_array(buf, 0, servo_pos, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SERVO_FDB_LEN);
#else
    mavlink_servo_fdb_t packet;

    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SERVO_FDB_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SERVO_FDB;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
}

/**
 * @brief Encode a servo_fdb struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param servo_fdb C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_servo_fdb_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_servo_fdb_t* servo_fdb)
{
    return mavlink_msg_servo_fdb_pack(system_id, component_id, msg, servo_fdb->servo_pos);
}

/**
 * @brief Encode a servo_fdb struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param servo_fdb C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_servo_fdb_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_servo_fdb_t* servo_fdb)
{
    return mavlink_msg_servo_fdb_pack_chan(system_id, component_id, chan, msg, servo_fdb->servo_pos);
}

/**
 * @brief Send a servo_fdb message
 * @param chan MAVLink channel to send the message
 *
 * @param servo_pos  y 舵机位置
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_servo_fdb_send(mavlink_channel_t chan, const float *servo_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SERVO_FDB_LEN];

    _mav_put_float_array(buf, 0, servo_pos, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SERVO_FDB, buf, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
#else
    mavlink_servo_fdb_t packet;

    mav_array_memcpy(packet.servo_pos, servo_pos, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SERVO_FDB, (const char *)&packet, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
#endif
}

/**
 * @brief Send a servo_fdb message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_servo_fdb_send_struct(mavlink_channel_t chan, const mavlink_servo_fdb_t* servo_fdb)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_servo_fdb_send(chan, servo_fdb->servo_pos);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SERVO_FDB, (const char *)servo_fdb, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
#endif
}

#if MAVLINK_MSG_ID_SERVO_FDB_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_servo_fdb_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *servo_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, servo_pos, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SERVO_FDB, buf, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
#else
    mavlink_servo_fdb_t *packet = (mavlink_servo_fdb_t *)msgbuf;

    mav_array_memcpy(packet->servo_pos, servo_pos, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SERVO_FDB, (const char *)packet, MAVLINK_MSG_ID_SERVO_FDB_MIN_LEN, MAVLINK_MSG_ID_SERVO_FDB_LEN, MAVLINK_MSG_ID_SERVO_FDB_CRC);
#endif
}
#endif

#endif

// MESSAGE SERVO_FDB UNPACKING


/**
 * @brief Get field servo_pos from servo_fdb message
 *
 * @return  y 舵机位置
 */
static inline uint16_t mavlink_msg_servo_fdb_get_servo_pos(const mavlink_message_t* msg, float *servo_pos)
{
    return _MAV_RETURN_float_array(msg, servo_pos, 6,  0);
}

/**
 * @brief Decode a servo_fdb message into a struct
 *
 * @param msg The message to decode
 * @param servo_fdb C-struct to decode the message contents into
 */
static inline void mavlink_msg_servo_fdb_decode(const mavlink_message_t* msg, mavlink_servo_fdb_t* servo_fdb)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_servo_fdb_get_servo_pos(msg, servo_fdb->servo_pos);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SERVO_FDB_LEN? msg->len : MAVLINK_MSG_ID_SERVO_FDB_LEN;
        memset(servo_fdb, 0, MAVLINK_MSG_ID_SERVO_FDB_LEN);
    memcpy(servo_fdb, _MAV_PAYLOAD(msg), len);
#endif
}
