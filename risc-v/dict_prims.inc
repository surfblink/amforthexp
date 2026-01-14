# SPDX-License-Identifier: GPL-3.0-only
.global DO_EXECUTE , XT_WAZ


#
# all primitves / code words
# they are placed close together to
# maximize cache usage
#

    

.include "pri-words/drop.s"
.include "pri-words/over.s"
.include "pri-words/swap.s"
.include "pri-words/xor.s"
.include "pri-words/umstar.s"

.include "pri-words/plus.s"
.include "pri-words/2drop.s"
.include "pri-words/2dup.s"
.include "pri-words/rot.s"
.include "pri-words/invert.s"
.include "pri-words/negate.s"
.include "pri-words/minus.s"
.include "pri-words/dnegate.s"
.include "pri-words/d-plus.s"
.include "pri-words/d-minus.s"
.include "pri-words/star.s"


.include "mcu-words/flash.s"
.include "pri-words/exit.s"
.include "pri-words/exiti.s"

.include "pri-words/dup.s"
.include "pri-words/nip.s"

.include "pri-words/q-dup.s"
.include "pri-words/tuck.s"
.include "pri-words/m-rot.s"
.include "pri-words/pick.s"

.include "pri-words/to-r.s"
.include "pri-words/r-from.s"
.include "pri-words/r-fetch.s"
.include "pri-words/rp.s"
.include "pri-words/sp.s"

.include "pri-words/fetch.s"
.include "pri-words/store.s"

#.include "pri-words/negate.s"
.include "pri-words/abs.s"
.include "pri-words/muldiv.s"
.include "pri-words/stack.s"
.include "pri-words/logic.s"
.include "pri-words/memory.s"

DOCOLON: 
        push s2   # IP
        mv s2,s1  # W->IP
DO_NEXT:
        lw s1, 0(s2) # @IP -> W 
        addi s2,s2,4 # INC IP
DO_EXECUTE:
        lw a0, 0(s1) # @W, address of some executable code
        addi s1,s1,4 # INC W, points now to PFA
        jalr zero,a0,0 # jump to code
#DO_EXECUTE:
#        lw   s10, 0(s1) # @W, address of some executable code
#        addi s1,s1,4 # INC W, points now to PFA
#        jalr zero,s10,0 # jump to code

.include "pri-words/comp.s"

.include "pri-words/2swap.s"
.include "pri-words/2nip.s"
#.include "pri-words/2drop.s"
.include "pri-words/2over.s"
.include "pri-words/2r-fetch.s"
.include "pri-words/2to-r.s"
.include "pri-words/2r-from.s"
.include "pri-words/d-2star.s"
.include "pri-words/d-2slash.s"
#.include "pri-words/dabs.s"
#.include "pri-words/dnegate.s"
#.include "pri-words/d-plus.s"
#.include "pri-words/d-minus.s"
#.include "pri-words/2dup.s"
.include "pri-words/double.s"


#.include "pri-words/umplus.s"
#.include "pri-words/minus.s"
.include "pri-words/1-plus.s"
.include "pri-words/1-minus.s"
.include "pri-words/2-plus.s"
.include "pri-words/2-minus.s"
.include "pri-words/2-star.s"
.include "pri-words/2-slash.s"
.include "pri-words/cell-plus.s"
.include "pri-words/cells.s"


.include "pri-words/tib.s"
.include "pri-words/cold.s"

.include "pri-words/execute.s"

#.include "pri-words/pause.s"
.include "pri-words/nop.s"


.include "pri-words/do-do.s"
.include "pri-words/do-loop.s"
.include "pri-words/unloop.s"
.include "pri-words/i.s"
.include "pri-words/j.s"

.include "pri-words/do-aligned.s"
.include "sec-words/aligned.s"
#.include "pri-words/aligned.s"
#.include "pri-words/do-sliteral.s"
.include "pri-words/do-variable.s"
.include "pri-words/do-data.s"
.include "pri-words/do-value.s"
.include "pri-words/do-defer.s"
.include "pri-words/do-user.s"
.include "pri-words/do-does.k"
.include "pri-words/up.s"

.include "pri-words/1ms.s"
.include "pri-words/dobranch.s"
.include "pri-words/docondbranch.s"
.include "pri-words/doliteral.s"
.include "pri-words/doxliteral.s"
.include "pri-words/compare.s"
.include "pri-words/n_to_r.s"
.include "pri-words/n_r_from.s"
.include "pri-words/ashift.s"
.include "pri-words/cell-minus.s"
#.include "pri-words/areg.s"

.include "pri-words/2rot.s"
#.include "pri-words/pc.s"
.include "pri-words/move.s"
.include "pri-words/usb.s"
.include "pri-words/wordswap.s"
