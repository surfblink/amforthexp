
COLON "appl-turnkey", APPLTURNKEY
  .word XT_DECIMAL
  .word XT_DELAY_INIT
  .word XT_UART_INIT
  # give UART 10ms to initialize properly
  # .word XT_DOLITERAL, 100, XT_MS
  # SERIAL_EMITQ cannot work properly until the first character is emitted,
  # so as a workaround just emit a space right at the start without checking SERIAL_EMITQ.
  .word XT_DOLITERAL, 32, XT_SERIAL_EMIT

  .word XT_DOT_VER
  .word XT_SPACE,XT_ENV_BOARD,XT_TYPE, XT_CR
  .word XT_BUILD_INFO,XT_TYPE, XT_SPACE, XT_REV_INFO, XT_TYPE

  .word XT_LED_INIT
  
# for now just flash the LED forever
#LED_BLINK_LOOP:
#  .word XT_LED_ON, XT_DOLITERAL, 200, XT_MS
#  .word XT_LED_OFF, XT_DOLITERAL, 800, XT_MS
#  .word XT_DOLOOP, LED_BLINK_LOOP

.word XT_EXIT
