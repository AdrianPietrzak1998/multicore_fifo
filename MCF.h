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

typedef struct{
    uint16_t msgID;
    union{
        float f32;
        uint16_t u16;
        uint32_t u32;
        int16_t i16;
        int32_t i32;
    };
}MCF_Message_t;

typedef struct{
	MCF_Message_t *msgBuf;
	uint16_t *head;
	uint16_t *tail;
	uint16_t msgBufSize;
	void (*msgParser)(MCF_Message_t *msgBuf);
}MCF_t;

void MCF_send_u16(MCF_t *Instance, uint16_t msgID, uint16_t value);
void MCF_send_i16(MCF_t *Instance, uint16_t msgID, int16_t value);
void MCF_send_u32(MCF_t *Instance, uint16_t msgID, uint32_t value);
void MCF_send_i32(MCF_t *Instance, uint16_t msgID, int32_t value);
void MCF_send_f32(MCF_t *Instance, uint16_t msgID, float value);
void MCF_receive(MCF_t *Instance);



#endif /* MULTICORE_FIFO_MCF_H_ */
