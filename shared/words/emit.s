# SPDX-License-Identifier: GPL-3.0-only
.if WANT_USB_OPERATOR
DEFER "emit", EMIT, XT_USB_EMIT_PAUSE
.else
DEFER "emit", EMIT, XT_SERIAL_EMIT_PAUSE
.endif 
