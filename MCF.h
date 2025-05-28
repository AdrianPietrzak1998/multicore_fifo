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
 * It includes a message identifier and a payload, represented as a union of several common types.
 * The union allows for efficient transmission of a single value of a known type.
 *
 * The interpretation of the union contents depends on the message ID and the context of use.
 */
typedef struct{
	/** Message identifier, used to distinguish message types or destinations. */
    uint16_t msgID;

    /**
     * @brief Union of supported payload types.
     *
     * Only one of these fields is valid at a time. The sender and receiver must agree
     * on the type associated with a given msgID.
     */
    union{
        float    f32;  /**< 32-bit floating-point value. */
        uint16_t u16;  /**< 16-bit unsigned integer. */
        uint32_t u32;  /**< 32-bit unsigned integer. */
        int16_t  i16;  /**< 16-bit signed integer. */
        int32_t  i32;  /**< 32-bit signed integer. */
    };
}MCF_Message_t;

/**
 * @brief MCF queue instance for inter-core communication.
 *
 * This structure represents a single instance of the MCF (Multi-Core FIFO) message queue.
 * It encapsulates the buffer and state required for circular message handling between cores.
 */
typedef struct{
    /**
     * @brief Pointer to the message buffer.
     *
     * This is a circular buffer containing messages exchanged between cores.
     * The buffer must be externally allocated and capable of holding `msgBufSize` elements.
     */
	MCF_Message_t *msgBuf;

    /**
     * @brief Pointer to the head index.
     *
     * This index is incremented when new messages are inserted into the buffer.
     * It must be shared between cores and stored in a memory location visible to all participants.
     */
	uint16_t *head;

    /**
     * @brief Pointer to the tail index.
     *
     * This index is incremented when messages are read from the buffer.
     * Like the head, it must be stored in a shared memory location.
     */
	uint16_t *tail;

    /**
     * @brief Size of the message buffer (in number of messages).
     *
     * Defines the capacity of the circular buffer. It must be greater than zero
     * and match the actual size of the allocated `msgBuf` array.
     */
	uint16_t msgBufSize;

    /**
     * @brief Callback for parsing or handling received messages.
     *
     * This function is invoked when a message is retrieved from the buffer.
     * It should implement logic specific to the message type, based on `msgID`.
     */
	void (*msgParser)(MCF_Message_t *msgBuf);
}MCF_t;

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
