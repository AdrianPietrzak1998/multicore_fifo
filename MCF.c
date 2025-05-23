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
