
# Delay processing busy waits on the Cortex-M4 system timer, SysTick
# RA4M1 provides external SYSTICCLK clock fixed at 32.768 kHz as an alternative to using the MCU clock 48Mhz.
# We're using SYSTICCLK here.
# Ref: Cortex-M4 User Guide: 4.4 System timer, SysTick
# Ref: Renesas RA4M1 User Manual: 2.9 SysTick System Timer

ARM_CONSTANT "SYST_CSR", SYST_CSR, 0xE000E010 
# SYST_CSR SysTick Control and Status Register
# Bits   | Name     | Function
# ----------------------------
# [31:17] | -         | Reserved
# [16]    | COUNTFLAG | Returns 1 if timer counted to 0 since last time this was read.
# [15:3]  | -         | Reseverd
# [2]     | CLKSOURCE | Clock source: 0 = external clock / 1 = processor clock.
# [1]     | TICKINT   | Enables SysTick exception request; Software can use COUNTFLAG to determine if SysTick has ever counted to zero.
# [0]     | ENABLE    | Enables the counterr
# When ENABLE is set to 1, the counter loads the RELOAD value from the SYST_RVR register
# and then counts down. On reaching 0, it sets the COUNTFLAG to 1 and optionally asserts the
# SysTick depending on the value of TICKINT. It then loads the RELOAD value again, and begins counting.

ARM_CONSTANT "SYST_RVR", SYST_RVR, 0xE000E014
# SYST_RVR SysTick Reload Value Register (lower 24 bits only)
# The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF. A start value of 0 is
# possible, but has no effect because the SysTick exception request and COUNTFLAG are activated when counting from 1 to 0.
# The RELOAD value is calculated according to its use. For example, to generate a multi-shot
# timer with a period of N processor clock cycles, use a RELOAD value of N-1. If the SysTick
# interrupt is required every 100 clock pulses, set RELOAD to 99.

ARM_CONSTANT "SYST_CVR", SYST_CVR, 0xE000E018
# SYST_CVR SysTick Current Value Register (lower 24 bits only)
# Reads return the current value of the SysTick counter.
# A write of any value clears the field to 0, and also clears the SYST_CSR COUNTFLAG bit to 0.

.equ TIMER_RELOAD_VALUE, 0x00FFFFFF

ARM_COLON "delay-init", DELAY_INIT
    @ Disable SysTick during setup
    .word XT_ZERO, XT_SYST_CSR, XT_STORE

    @ Maximum reload value for 24 bit timer
    .word XT_DOLITERAL, TIMER_RELOAD_VALUE, XT_SYST_RVR, XT_STORE

    @ Any write to current clears it
    .word XT_ZERO, XT_SYST_CVR, XT_STORE

    @ Enable SysTick with SYSTICCLK = 32.768kHz clock
    .word XT_ONE, XT_SYST_CSR, XT_STORE
.word XT_EXIT

# Wait for n ticks of the SysTick timer.
# tick = 1/32.768 kHz = 30.5 us
# TODO: doesn't seem to handle timer wrap-around
ARM_COLON "delay-ticks", DELAY_TICKS
@ ( n -- ) wait for n ticks of the timer, tick ~ 30 microseconds
    .word XT_SYST_CVR, XT_FETCH     @ ( n start-ticks )
DELAY_TICKS_LOOP:
      .word XT_PAUSE, XT_2DUP
      .word XT_SYST_CVR, XT_FETCH    @ ( n start-ticks n start-ticks current-ticks )
      # need to handle timer wrapping around zero
      .word XT_MINUS, XT_DUP, XT_ZEROLESS, XT_NOT, XT_DOCONDBRANCH, 1f
      # elapsed ticks are negative, timer wrapped, add the reload value
      .word XT_DOLITERAL, TIMER_RELOAD_VALUE, XT_PLUS
1:    .word XT_UGREATER, XT_DOCONDBRANCH, DELAY_TICKS_LOOP
    .word XT_2DROP
.word XT_EXIT

COLON "ms", MS
@ ( n -- ) wits n milliseconds, 1 ms = 1000/30.5 = 32.78 ticks
    .word XT_ZERO
    .word XT_QDOCHECK,XT_DOCONDBRANCH,MS_LEAVE, XT_DODO
MS_LOOP:
       .word XT_DOLITERAL, 33, XT_DELAY_TICKS, XT_DOLOOP, MS_LOOP
MS_LEAVE:
    .word XT_EXIT
