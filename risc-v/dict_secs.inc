# SPDX-License-Identifier: GPL-3.0-only
#
# all secondaries / colon sec-words
# they represend data instead of code
#

.include "sec-words/quit.s"     
.include "sec-words/interpret.s"

.include "sec-words/recognize.s"
.include "sec-words/rec-null.s"
.include "sec-words/rec-find.s"
.include "sec-words/rec-intnum.s"
.include "sec-words/rec-split.s"
.include "sec-words/forth-recognizer.s"

# these move from pri-
.include "sec-words/dabs.s"
.include "sec-words/base.s"
.include "sec-words/state.s"
.include "sec-words/key.s"
.include "sec-words/keyq.s"
.include "sec-words/emit.s"
.include "sec-words/emitq.s"

.include "sec-words/pause.s"
.include "sec-words/bounds.s"
.include "sec-words/do-sliteral.s"
# end move

.include "sec-words/num-constants.s"
#.include "sec-words/dicthelp.s"

.if WANT_QEM_BUILD
    .include "sec-words/warm.qem"
.else
    .include "sec-words/warm.s"
.endif

.include "sec-words/ms.s"
.include "sec-words/cr.s"
.include "sec-words/bl.s"
.include "sec-words/space.s"
.include "sec-words/spaces.s"
.include "sec-words/left-bracket.s"
.include "sec-words/l-paren.s"
.include "sec-words/decimal.s"
.include "sec-words/hex.s"
.include "sec-words/binary.s"

.include "sec-words/pad.s"
.include "sec-words/here.s"
.include "sec-words/ramhere.s"
.include "sec-words/align.s"
.include "sec-words/allot.s"

.include "sec-words/hold.s"
.include "sec-words/sharp.s"
.include "sec-words/sign.s"
.include "sec-words/dot.s"
.include "sec-words/d-dot-r.s"
.include "sec-words/d-dot.s"
.include "sec-words/u-dot.s"
.include "sec-words/ud-dot.s"
.include "sec-words/ud-dot-r.s"

.include "sec-words/dot-s.s"
.include "sec-words/dot-k.s"

.include "sec-words/refill.s"
.include "sec-words/accept.s"
.include "sec-words/prompt-error.s"
.include "sec-words/prompt-input.s"
.include "sec-words/prompt-ok.s"
.include "sec-words/prompt-ready.s"

.include "sec-words/catch.s"
.include "sec-words/throw.s"
.include "sec-words/source.s"
.include "sec-words/q-stack.s"
.include "sec-words/cscan.s"
.include "sec-words/cskip.s"
.include "sec-words/parse-name.s"
.include "sec-words/parse.s"
.include "sec-words/slash-string.s"

.include "sec-words/2literal.s"
.include "sec-words/literal.s"
.include "sec-words/xliteral.s"
.include "sec-words/compile.s"
.include "sec-words/comma.s"
.include "sec-words/immediate-q.s"
.include "sec-words/order.s"
.include "sec-words/find-xt.s"
.include "sec-words/xt2nfa.s"
.include "sec-words/xt2ffa.s"
.include "sec-words/nfa2lfa.s"
.include "sec-words/nfa2cfa.s"
.include "sec-words/traverse-wordlist.s"
.include "sec-words/show-wordlist.s"
.include "sec-words/current.s"
.include "sec-words/search-wordlist.s"
.include "sec-words/name2string.s"
.include "sec-words/name2flags.s"

.include "sec-words/mplus.s"
.include "sec-words/ud-star.s"
.include "sec-words/within.s"
.include "sec-words/to-upper.s"
.include "sec-words/digit-q.s"
.include "sec-words/to-number.s"
.include "sec-words/number.s"
.include "sec-words/q-sign.s"
.include "sec-words/set-base.s"

.include "sec-words/map-stack.s"
.include "sec-words/qdo.s"

.include "sec-words/init-ram.s"
.include "sec-words/ver.s"

.include "sec-words/count.s"
.include "sec-words/type.s"
.include "sec-words/squote.s"
.include "sec-words/dot-quote.s"
.include "sec-words/scomma.s"
.include "sec-words/sliteral.s"
.include "sec-words/words.s"

.include "sec-words/l-mark.s"
.include "sec-words/l-resolve.s"
.include "sec-words/g-mark.s"
.include "sec-words/g-resolve.s"
.include "sec-words/ahead.s"
.include "sec-words/begin.s"
.include "sec-words/then.s"
.include "sec-words/until.s"
.include "sec-words/while.s"
.include "sec-words/if.s"
.include "sec-words/else.s"
.include "sec-words/again.s"
.include "sec-words/repeat.s"
.include "sec-words/leave.s"
.include "sec-words/immediate.s"
.include "sec-words/turnkey.s"

.include "sec-words/tick.s"
.include "sec-words/abort.s"

.include "sec-words/abort-string.s"
.include "sec-words/backslash.s"
.include "sec-words/bracketchar.s"
.include "sec-words/bracketcompile.s"
.include "sec-words/brackettick.s"
.include "sec-words/char.s"
.include "sec-words/colon-noname.s"
.include "sec-words/constant.s"
.include "sec-words/create.s"
.include "sec-words/defer.s"
.include "sec-words/defer-fetch.s"
.include "sec-words/defer-store.s"
.include "sec-words/do-create.s"
.include "sec-words/do.s"
.include "sec-words/endloop.s"
.include "sec-words/header.s"
.include "sec-words/latest.s"
.include "sec-words/loop.s"
.include "sec-words/newest.s"
.include "sec-words/plusloop.s"
.include "sec-words/postpone.s"
.include "sec-words/q-abort.s"
.include "sec-words/recurse.s"
.include "sec-words/reveal.s"
.include "sec-words/right-bracket.s"
.include "sec-words/colon.s"
.include "sec-words/semicolon.s"
.include "sec-words/semicoloni.s"
.include "sec-words/variable.s"
.include "sec-words/wlscope.s"
.include "sec-words/to-body.s"
.include "sec-words/get-current.s"
.include "sec-words/greater-zero.s"
.include "sec-words/to-in.s"
.include "sec-words/dp.s"
.include "sec-words/udefer.s"
.include "sec-words/wordlist.s"
.include "sec-words/ramwordlist.s"
.include "sec-words/flag.s"
.include "sec-words/search.s"
.include "sec-words/cloak.s"
#.include "sec-words/freeze.s"


# TW testing 

.include "sec-words/show.s"
.include "sec-words/value.s"
.include "sec-words/mop.s"
.include "sec-words/traps.s"
.include "sec-words/forget.s"
.include "sec-words/memmode.s"
.include "sec-words/private.s"
.include "sec-words/find.s"

.include "sec-words/dump.s"
.include "sec-words/testing.s"

.if WANT_SEE 
.include "sec-words/dis-asm.s"
.include "sec-words/see.s"
.include "sec-words/dicthelp.s"
.endif

.if WANT_MATCH
.include "sec-words/match.s"
.endif

.if WANT_CASE
.include "sec-words/case.s"
.endif

.if WANT_FORNEXT
.include "sec-words/for-next.s"
.endif

.if WANT_SAVE
.include "sec-words/save.s"
.endif 

.if WANT_FLOAT
.include "sec-words/float.s"
.endif 

.if WANT_TABLE
.include "sec-words/table.s"
.endif

.include "sec-words/empty.s"
.include "sec-words/blink.s"
.include "sec-words/barbar.s"
#.include "sec-words/does.s"
#.include "sec-words/code.s"


.include "sec-words/is.s"
.include "sec-words/alto.s"
#.include "sec-words/to.s"
.include "mcu-words/eeprom.s"
.include "sec-words/xt2string.s"
.include "sec-words/dictopt.s"

.include "sec-words/dallot.s"
.include "sec-words/dalign.s"

