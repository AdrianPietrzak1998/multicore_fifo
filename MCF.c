/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Author: Adrian Pietrzak
 * GitHub: https://github.com/AdrianPietrzak1998
 * Created: May 20, 2025
 */

#include "MCF.h"
#include "assert.h"
#include <stddef.h>

/**
 * @brief Sends a uint16_t message to the buffer.
 *
 * Inserts a 16-bit unsigned integer value with the given message ID
 * into the queue associated with the specified instance.
 *
 * @param Instance Pointer to the MCF instance.
 * @param msgID    Message identifier.
 * @param value    16-bit unsigned value.
 */
void MCF_send_u16(MCF_t *Instance, uint16_t msgID, uint16_t value)
{

	assert(Instance != NULL);

	uint16_t head = *(Instance->head);

	if(head >= Instance->msgBufSize - 1)
	{
		head = 0;
	}
	else
	{
		head++;
	}

	Instance->msgBuf[head].u16 = value;
	Instance->msgBuf[head].msgID = msgID;
	*(Instance->head) = head;
}

/**
 * @brief Sends an int16_t message to the buffer.
 *
 * Inserts a 16-bit signed integer value with the given message ID
 * into the queue associated with the specified instance.
 *
 * @param Instance Pointer to the MCF instance.
 * @param msgID    Message identifier.
 * @param value    16-bit signed value.
 */
void MCF_send_i16(MCF_t *Instance, uint16_t msgID, int16_t value)
{
	assert(Instance != NULL);

	uint16_t head = *(Instance->head);

	if(head >= Instance->msgBufSize - 1)
	{
		head = 0;
	}
	else
	{
		head++;
	}

	Instance->msgBuf[head].i16 = value;
	Instance->msgBuf[head].msgID = msgID;
	*(Instance->head) = head;
}

/**
 * @brief Sends a uint32_t message to the buffer.
 *
 * Inserts a 32-bit unsigned integer value with the given message ID
 * into the queue associated with the specified instance.
 *
 * @param Instance Pointer to the MCF instance.
 * @param msgID    Message identifier.
 * @param value    32-bit unsigned value.
 */
void MCF_send_u32(MCF_t *Instance, uint16_t msgID, uint32_t value)
{
	assert(Instance != NULL);

	uint16_t head = *(Instance->head);

	if(head >= Instance->msgBufSize - 1)
	{
		head = 0;
	}
	else
	{
		head++;
	}

	Instance->msgBuf[head].u32 = value;
	Instance->msgBuf[head].msgID = msgID;
	*(Instance->head) = head;
}

/**
 * @brief Sends an int32_t message to the buffer.
 *
 * Inserts a 32-bit signed integer value with the given message ID
 * into the queue associated with the specified instance.
 *
 * @param Instance Pointer to the MCF instance.
 * @param msgID    Message identifier.
 * @param value    32-bit signed value.
 */
void MCF_send_i32(MCF_t *Instance, uint16_t msgID, int32_t value)
{
	assert(Instance != NULL);

	uint16_t head = *(Instance->head);

	if(head >= Instance->msgBufSize - 1)
	{
		head = 0;
	}
	else
	{
		head++;
	}

	Instance->msgBuf[head].i32 = value;
	Instance->msgBuf[head].msgID = msgID;
	*(Instance->head) = head;
}

/**
 * @brief Sends a float (float32) message to the buffer.
 *
 * Inserts a 32-bit floating-point value with the given message ID
 * into the queue associated with the specified instance.
 *
 * @param Instance Pointer to the MCF instance.
 * @param msgID    Message identifier.
 * @param value    32-bit float value.
 */
void MCF_send_f32(MCF_t *Instance, uint16_t msgID, float value)
{
	assert(Instance != NULL);

	uint16_t head = *(Instance->head);

	if(head >= Instance->msgBufSize - 1)
	{
		head = 0;
	}
	else
	{
		head++;
	}

	Instance->msgBuf[head].f32 = value;
	Instance->msgBuf[head].msgID = msgID;
	*(Instance->head) = head;
}

/**
 * @brief Receives and parses a message from the buffer.
 *
 * Retrieves the next message (if available) from the circular buffer and
 * passes it to the parser function defined in the MCF instance.
 *
 * This function must only be called if the `msgParser` callback is set.
 * Should be invoked regularly in the application main loop.
 *
 * @param Instance Pointer to the MCF instance.
 */
void MCF_receive(MCF_t *Instance)
{
	assert(Instance != NULL);

	while(*(Instance->head) != *(Instance->tail))
	{
		(*(Instance->tail))++;
		if(*(Instance->tail) >= Instance->msgBufSize)
		{
			*(Instance->tail) = 0;
		}
		Instance->msgParser(&(Instance->msgBuf[*(Instance->tail)]));
	}
}
