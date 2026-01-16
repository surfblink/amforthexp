# SPDX-License-Identifier: GPL-3.0-only
# Helper word for returning from interrupt handler. Used by ;i.
# TODO: this likely needs more work
CODEWORD "(exiti)", EXITI
    bx lr

