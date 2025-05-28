/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Author: Adrian Pietrzak
 * GitHub: https://github.com/AdrianPietrzak1998
 * Created: May 20, 2025
 */

#ifndef MULTICORE_FIFO_MCF_H_
#define MULTICORE_FIFO_MCF_H_

#include <stdint.h>

/**
 * @brief Message structure used in the MCF inter-core ring buffer.
 *
 * This structure represents a single message element that can be stored in the circular buffer.
 * It includes:
 * - `msgID`: Message identifier, used to distinguish message types or destinations.
 * - A union payload, which can represent a single value of one of several common types:
 *   - `f32`: 32-bit floating-point value.
 *   - `u16`: 16-bit unsigned integer.
 *   - `u32`: 32-bit unsigned integer.
 *   - `i16`: 16-bit signed integer.
 *   - `i32`: 32-bit signed integer.
 *
 * The interpretation of the union contents depends on the message ID and the context of use.
 */
typedef struct
{
    uint16_t msgID;
    union {
        float f32;
        uint16_t u16;
        uint32_t u32;
        int16_t i16;
        int32_t i32;
    };
} MCF_Message_t;

/**
 * @brief MCF queue instance for inter-core communication.
 *
 * This structure represents a single instance of the MCF (Multi-Core FIFO) message queue.
 * It encapsulates the buffer and state required for circular message handling between cores.
 *
 * - `msgBuf`: Pointer to the externally allocated circular buffer holding messages.
 * - `head`: Pointer to the shared head index, incremented on message insertion.
 * - `tail`: Pointer to the shared tail index, incremented on message retrieval.
 * - `msgBufSize`: Size (capacity) of the circular message buffer (number of messages).
 * - `msgParser`: Callback function to handle or parse messages when read.
 */
typedef struct
{
    MCF_Message_t *msgBuf;
    uint16_t *head;
    uint16_t *tail;
    uint16_t msgBufSize;
    void (*msgParser)(MCF_Message_t *msgBuf);
} MCF_t;

/**
 * @brief Initializes the MCF instance for transmission (TX) only.
 *
 * Sets up the circular buffer, head and tail pointers, and buffer size
 * for transmitting messages. No parser function is assigned in this mode.
 *
 * @param Instance Pointer to the MCF instance to initialize.
 * @param head     Pointer to the head index variable.
 * @param tail     Pointer to the tail index variable.
 * @param MsgBuf   Pointer to the message buffer array.
 * @param BufSize  Size of the message buffer (number of messages).
 */
void MCF_init_TX(MCF_t *Instance, uint16_t *head, uint16_t *tail, MCF_Message_t *MsgBuf, uint16_t BufSize);

/**
 * @brief Initializes the MCF instance for reception (RX) only.
 *
 * Sets up the circular buffer, head and tail pointers, buffer size,
 * and assigns a message parser callback for processing received messages.
 *
 * @param Instance   Pointer to the MCF instance to initialize.
 * @param head       Pointer to the head index variable.
 * @param tail       Pointer to the tail index variable.
 * @param MsgBuf     Pointer to the message buffer array.
 * @param BufSize    Size of the message buffer (number of messages).
 * @param msgParser  Callback function to parse received messages.
 */
void MCF_init_RX(MCF_t *Instance, uint16_t *head, uint16_t *tail, MCF_Message_t *MsgBuf, uint16_t BufSize,
                 void (*msgParser)(MCF_Message_t *msgBuf));

/**
 * @brief Initializes the MCF instance for both transmission (TX) and reception (RX).
 *
 * Sets up the circular buffer, head and tail pointers, buffer size,
 * and assigns a message parser callback for processing received messages.
 * Intended for use when the same core handles both sending and receiving.
 *
 * @param Instance   Pointer to the MCF instance to initialize.
 * @param head       Pointer to the head index variable.
 * @param tail       Pointer to the tail index variable.
 * @param MsgBuf     Pointer to the message buffer array.
 * @param BufSize    Size of the message buffer (number of messages).
 * @param msgParser  Callback function to parse received messages.
 */
void MCF_init_RXTX(MCF_t *Instance, uint16_t *head, uint16_t *tail, MCF_Message_t *MsgBuf, uint16_t BufSize,
                   void (*msgParser)(MCF_Message_t *msgBuf));

/**
 * @brief Sends a uint16_t message to the MCF queue.
 *
 * This function inserts a message with the given ID and 16-bit unsigned value
 * into the circular buffer associated with the specified MCF instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 * @param msgID    Identifier of the message to send.
 * @param value    16-bit unsigned value to include in the message payload.
 */
void MCF_send_u16(MCF_t *Instance, uint16_t msgID, uint16_t value);

/**
 * @brief Sends an int16_t message to the MCF queue.
 *
 * Inserts a message with the specified ID and 16-bit signed integer payload
 * into the circular buffer for the given MCF instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 * @param msgID    Identifier of the message to send.
 * @param value    16-bit signed integer to include in the message payload.
 */
void MCF_send_i16(MCF_t *Instance, uint16_t msgID, int16_t value);

/**
 * @brief Sends a uint32_t message to the MCF queue.
 *
 * Inserts a message with the specified ID and 32-bit unsigned integer payload
 * into the circular buffer for the given MCF instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 * @param msgID    Identifier of the message to send.
 * @param value    32-bit unsigned integer to include in the message payload.
 */
void MCF_send_u32(MCF_t *Instance, uint16_t msgID, uint32_t value);

/**
 * @brief Sends an int32_t message to the MCF queue.
 *
 * Inserts a message with the specified ID and 32-bit signed integer payload
 * into the circular buffer for the given MCF instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 * @param msgID    Identifier of the message to send.
 * @param value    32-bit signed integer to include in the message payload.
 */
void MCF_send_i32(MCF_t *Instance, uint16_t msgID, int32_t value);

/**
 * @brief Sends a float (float32) message to the MCF queue.
 *
 * Inserts a message with the specified ID and 32-bit floating-point value
 * into the circular buffer for the given MCF instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 * @param msgID    Identifier of the message to send.
 * @param value    32-bit floating-point value to include in the message payload.
 */
void MCF_send_f32(MCF_t *Instance, uint16_t msgID, float value);

/**
 * @brief Receives and parses the next message from the MCF queue.
 *
 * This function checks whether a new message is available in the queue.
 * If so, it retrieves the message and passes it to the user-defined parser function
 * provided in the `msgParser` field of the `MCF_t` instance.
 *
 * This function should be called continuously in the main loop of the application.
 *
 * @note The `msgParser` callback must be set before calling this function.
 *       If `msgParser` is `NULL`, this function must not be used with the instance.
 *
 * @param Instance Pointer to the MCF queue instance.
 */
void MCF_receive(MCF_t *Instance);

#endif /* MULTICORE_FIFO_MCF_H_ */
