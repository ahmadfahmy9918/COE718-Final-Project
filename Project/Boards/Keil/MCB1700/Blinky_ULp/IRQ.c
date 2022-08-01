/*------------------------------------------------------------------------------
 * Copyright (c) 2004-2020 Arm Limited (or its affiliates). All
 * rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1.Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   2.Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   3.Neither the name of Arm nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *------------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: IRQ Handler
 *----------------------------------------------------------------------------*/

#include "projectMain.h"

#include "LPC17xx.h"                    // LPC17xx Definitions
#include "Board_LED.h"
#include "Board_ADC.h"


volatile uint8_t clock_1s;              // Flag activated each second

void SysTick_HandlerIRQ (void);

/*------------------------------------------------------------------------------
  SysTick IRQ Handler (occurs every 10 ms)
 *----------------------------------------------------------------------------*/
void SysTick_HandlerIRQ (void) {
  static uint32_t ticks = 0U;
  static uint32_t timetick = 0U;
  static uint32_t leds = 0x01U;

  if (++ticks == 100U) {                // Set Clock1s to 1 every second
    ticks    = 0U;
    clock_1s = 1U;
  }

  // Blink the LEDs depending on ADC_Converted Value
  if (++timetick >= ADC_last) {
    timetick = 0U;
    LED_SetOut(leds);
    leds <<= 1;
    if (leds == (1U << LED_GetCount())) {
      leds = 0x01U;
    }
  }

  ADC_StartConversion();                // Start ADC conversion
}
