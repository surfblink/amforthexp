# SPDX-License-Identifier: GPL-3.0-only





# MFD wrong chip .include "mcu-words/pll.s"

.if WANT_QEM_BUILD
    .include "mcu-words/serial.qem"        
.else
    .include "mcu-words/usart.s"
    .include "mcu-words/gpio.s"     
.endif

# MFD wrong chip .include "mcu-words/qspidiv.s"

# MFD include "mcu-words/flash.s" as in dict_prims
.include "mcu-words/led.s"

.include "mcu-words/env-board.s"
#include "mcu-words/build-info.s"
.include "mcu-words/applturnkey.s"

.include "mcu-words/type0.s" # not sure 

# MFD .include "mcu-words/qtest.s"
.if WANT_SYSTICK
.include "mcu-words/systick.s"
.endif

.include "mcu-words/reset.s"

.if WANT_TIMER6
.include "mcu-words/t6.s"
.include "mcu-words/t8.s"
.include "mcu-words/t9.s"
.endif

#.include "mcu-words/temp6.s"
.include "mcu-words/usb.s"
#.include "mcu-words/debug.s"
#.include "mcu-words/frag.s"

.if WANT_FLOAT
    .include "mcu-words/float.s"
.endif

.include "mcu-words/mlc.s"