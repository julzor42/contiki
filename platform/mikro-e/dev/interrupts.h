/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its
 * affiliated group companies.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <pic32_gpio.h>

#define INTERRUPT_IRQ_INIT() __INTERRUPT_IRQ_INIT()
#define __INTERRUPT_IRQ_INIT()                                          \
  do {                                                                  \
    GPIO_CONFIGURE_AS_INPUT(D, 0);                                      \
    CNCONDSET = _CNCOND_ON_MASK;                                        \
    IEC1SET = _IEC1_CNDIE_MASK;                                         \
    IFS1CLR = _IFS1_CNDIF_MASK;                                         \
    IPC8SET = (6 << _IPC8_CNIP_POSITION) | (0 << _IPC8_CNIS_POSITION);  \
    (void)PORTD;                                                        \
  } while(0)





#define INTERRUPT_IRQ_ENABLE() __INTERRUPT_IRQ_ENABLE()
#define __INTERRUPT_IRQ_ENABLE()                                       \
  do {                                                                 \
    CNENDSET = _CNEND_CNIED0_MASK;                                     \
  } while(0)




#define INTERRUPT_IRQ_DISABLE() __INTERRUPT_IRQ_DISABLE()
#define __INTERRUPT_IRQ_DISABLE()                                      \
  do {                                                                 \
    CNENDCLR = _CNEND_CNIED0_MASK;                                     \
  } while(0)


#define INTERRUPT_CHECK_IRQ() __INTERRUPT_CHECK_IRQ()
#define __INTERRUPT_CHECK_IRQ()                                        \
  (IFS1bits.CNDIF & CNSTATDbits.CNSTATD0)



#define INTERRUPT_CLEAR_IRQ() __INTERRUPT_CLEAR_IRQ()
#define __INTERRUPT_CLEAR_IRQ()                                        \
  do {                                                                 \
    (void)PORTD;                                                       \
    IFS1CLR = _IFS1_CNDIF_MASK;                                        \
    CNSTATDCLR = _CNSTATD_CNSTATD0_MASK;                               \
  } while(0)


extern void (*interrupt_isr)(void);

#endif
