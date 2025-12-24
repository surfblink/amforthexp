# This should get autoloaded by GDB when started with `make gdb`
# Otherwise can also be loaded with source ./.gdbinit

# command dump the return stack
define .r
  set var $frame = $sp
  while $frame < 0x20000100
    # location of the next XT to run after EXIT
    x/a $frame
    # next XT to run after EXIT
    # x/a *(int)$frame
    set $frame = $frame + 4
  end
end

# command to dump the parameter stack
define .s
  # print TOS
  print $r6
  # grab the PSP
  set var $frame = $r7
  # rest of the parameter stack
  while $frame < 0x20000080
    print *(int)$frame
    set $frame = $frame + 4
  end
end

# to help stepping through colon words, put a breakpoint at DO_EXECUTE
# and add commands to step twice to get into the next word's code.
# You can then move to the next word with 'continue'.
# Use 'disable/enable' to (de)activate the breakpoint.
define bde
  hbreak DO_EXECUTE
  commands
    step 2
  end
end

# TUI for debugging
# ref: https://undo.io/resources/enhance-gdb-with-tui/

source ./gdb-amforth.py

# create a new tui layout for AmForth
# tui new-layout forth regs 15 {-horizontal src 1 asm 1} 20 status 0 cmd 20
# tui new-layout forth {-horizontal { {-horizontal src 2 asm 3 } 1 status 0 cmd 1 } 3 regs 1 } 1
tui new-layout forth {-horizontal { {-horizontal src 2 asm 3 } 1 status 0 cmd 1 } 3  { fregs 2 fps 1 frs 1 } 1 } 1
layout forth
focus cmd