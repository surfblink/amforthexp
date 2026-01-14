# SPDX-License-Identifier: GPL-3.0-only


# macros
#   s5/SP RSP Return Stack Pointer
#   s3 TOS Top Of Stack
#   s4 DSP Data Stack Pointer
#   t0 temp 
#   t1 temp
#   t2 temp
#   s7 loop index
#   s8 loop limit
#   a0..a5 temp
#   s2 IP  Forth VM IP register (ITC Instruction Pointer)
#   s1 W   Forth VM W register
#   s6 user pointer UP

.macro NEXT
    j DO_NEXT
.endm

.macro savetos
  addi s4, s4, -4
  sw s3, 0(s4)
.endm

.macro loadtos
  lw s3, 0(s4)
  addi s4,s4,4
.endm

.macro push register
  addi s5, s5, -4
  sw \register, 0(s5)
.endm

.macro pop register
  lw \register, 0(s5)
  addi s5, s5, 4
.endm

.macro pushdouble register1 register2
  addi s5, s5, -8  
  sw \register1, 4(s5)
  sw \register2, 0(s5)  
.endm

.macro popdouble register1 register2
  lw \register1, 4(s5)
  lw \register2, 0(s5)
  addi s4, s4, 8
.endm

.macro pushda register # Push register on Datastack
  savetos
  mv s3, \register    
.endm

.macro popda register # Pop register from Datastack
  mv \register, s3
  loadtos
.endm

.macro pushdadouble register1 register2 # Push register on Datastack
  addi s4, s4, -8
  sw s3, 4(s4)
  sw \register1, 0(s4)
  mv s3, \register2
.endm

.macro popdadouble register1 register2 # Pop register from Datastack
  mv \register1, s3
  lw \register2, 0(s4)
  lw s3, 4(s4)
  addi s4, s4, 8
.endm


# start of flash dictionary. The 0 is the stop marker
.macro STARTDICT
#.text should aready be in section amforth 
.word 0
97: # riscv-wordlist
98: # environment
99: # forth-wordlist
.endm

# save the beginning of the wordlists
.macro ENDDICT
VALUE "riscv-wordlist", RISCV_WORDLIST, 97b
VALUE "environment", ENVIRONMENT, 98b
VALUE "forth-wordlist", FORTH_WORDLIST, 99b
.set core_wordlist , 99b

.set DPSTART, 99b
# TRIAL
# .set rampointer , rampointer / 256
# .set rampointer , rampointer + 1
# .set rampointer , rampointer * 256
# .set rampointer , rampointer + 256 # space for Forth Interrupt table 
# .set reg_shadow , rampointer
# .set rampointer , rampointer + 256
# .set flash_buf  , rampointer       # space for 256B buffer for ...
# .set rampointer , rampointer + 256 # ... , ,, write to flash
# .set flash_alt  , rampointer       # space for 256B buffer for ...
# .set rampointer , rampointer + 256 # ... ! write to flash
# .set rom_buf    , rampointer
# .set rampointer , rampointer + 256
# .set ram_pool   , rampointer
# .set rampointer , rampointer + 1024
# .set ram_dict   , rampointer 
# # TRIAL
# .equ HERESTART, rampointer
.endm

.macro STRING string
    .word XT_DOSLITERAL
    .byte 8f - 7f
7:  .ascii "\string"
8:  .p2align 2,0x0f
.endm

# .macro ramallot Name, Length 
#   .equ RAM_lower_\Name, rampointer     # \Name at
#   .set rampointer, rampointer + \Length
#   .equ RAM_upper_\Name, rampointer     # \Name at
# .endm

.equ Flag_cloaked,    0x80000000
.equ Flag_visible,    0x00000000

.equ Flag_immediate,  0x0010
.equ Flag_value,      0x0020
.equ Flag_defer,      0x0040
.equ Flag_init,       0x0080
.equ Flag_table,      0x0100

.equ Flag_ramallot,   Flag_visible | 0x0100      # Ramallot means that RAM is reserved and initialised by catchflashpointers for this definition on startup
.equ Flag_variable,   Flag_ramallot| 1           # How many 32 bit locations shall be reserved ?
.equ Flag_2variable,  Flag_ramallot| 2

.equ Flag_colon   ,   Flag_visible | 4 
.equ Flag_constant,   Flag_visible | 8 

.macro HEADER Flags, Name, Label, PFA
    .p2align 2,0x55
VE_\Label:
    .word 99b         # Insert Link
99: .word \Flags      # Flag field
    .byte 8f - 7f     # Calculate length of name field
7:  .ascii "\Name"    # Insert name string
8:  .p2align 2,0xaa   # Realign
   XT_\Label: .word \PFA
   PFA_\Label: 
.endm

.macro CODEWORD Name, Label
    HEADER Flag_visible, "\Name", \Label, PFA_\Label
.endm

.macro CLOAKED_CODEWORD Name, Label
    HEADER Flag_visible | Flag_cloaked, "\Name", \Label, PFA_\Label
.endm

.macro STARTDICTFIX
#.text should aready be in section amforth
       .p2align 2,0x55
       .word 0
97:
98:
99:    .word 0
       .byte 8f-7f
7:     .ascii "nop"
8:     .p2align 2,0xAA
XT_NOP: .word PFA_NOP
PFA_NOP:
        NEXT 
.endm

# HIDEWORD is a CODEWORD with Flag_invisible
# suspect I have made this visible again as
# whatever I was trying did not work and I
# did not want to go an edit all the files
# again to replace HIDEWORD with CODEWORD 
.macro HIDEWORD Name, Label
    HEADER Flag_visible, "\Name", \Label, PFA_\Label
.endm

.macro HEADLESS Label
  .p2align 2,0x55
   XT_\Label: .word PFA_\Label
   PFA_\Label: 
.endm

.macro COLON Name, Label
    HEADER Flag_colon, "\Name", \Label, DOCOLON
.endm

.macro CLOAKED_COLON Name, Label
    HEADER Flag_colon | Flag_cloaked, "\Name", \Label, DOCOLON
.endm

.macro NONAME Label
  .p2align 2,0x55
   XT_\Label: .word DOCOLON
   PFA_\Label: 
.endm

.macro IMMED Name, Label
    HEADER Flag_visible|Flag_immediate, \Name, \Label, DOCOLON
.endm

.macro VARIABLE Name, Label
    HEADER Flag_visible|Flag_variable, "\Name", \Label, PFA_DOVARIABLE
    .section amramlo,"aw",@nobits
    .balign 4
    .set \Label\()_ram, .           # Capture current location counter
    .space 4
    .section amforth
    .word \Label\()_ram             # Write the captured address into flash
.endm

.macro CLOAKED_VARIABLE Name, Label
   HEADER Flag_visible|Flag_variable|Flag_cloaked, "\Name", \Label, PFA_DOVARIABLE
    .section amramlo,"aw",@nobits
    .balign 4
    .set \Label\()_ram, .           # Capture current location counter
    .space 4
    .section amforth
    .word \Label\()_ram             # Write the captured address into flash
.endm

.macro DVARIABLE Name, Label
   HEADER Flag_visible|Flag_variable, "\Name", \Label, PFA_DOVARIABLE
    .section amramlo,"aw",@nobits
    .balign 4
    .set \Label\()_ram, .           # Capture current location counter
    .space 8
    .section amforth
    .word \Label\()_ram             # Write the captured address into flash
.endm

.macro NVARIABLE Name, Label, N
  HEADER Flag_visible|Flag_variable, "\Name", \Label, PFA_DOVARIABLE
    .section amramlo,"aw",@nobits
    .balign 4
    .set \Label\()_ram, .          # Capture current location counter
    .space 4*\N
    .section amforth
    .word \Label\()_ram            # Write the captured address into flash
.endm

.macro CLOAKED_DVARIABLE Name, Label
   HEADER Flag_visible|Flag_variable|Flag_cloaked, "\Name", \Label, PFA_DOVARIABLE
    .section amramlo,"aw",@nobits
    .balign 4
    .set \Label\()_ram, .           # Capture current location counter
    .space 8
    .section amforth
    .word \Label\()_ram             # Write the captured address into flash
.endm

.macro USER Name, Label, UOffset
   HEADER Flag_visible|Flag_variable, "\Name", \Label, PFA_DOUSER
   .word \UOffset
   .equ USER_\Label,\UOffset # for listing
.endm

.macro VALUE Name, Label, Default
    HEADER Flag_visible|Flag_value|Flag_init, "\Name", \Label, PFA_DOVALUE
   .section amramlo,"aw",@nobits
   .balign 4
   .set \Label\()_ram, .           # Capture current location counter
   .space 4
   .section amforth
   .word \Label\()_ram             # Write the captured address into flash
   .word \Default
   .word XT_FETCH
   .word XT_STORE
.endm

.macro CLOAKED_VALUE Name, Label, Default
    HEADER Flag_visible|Flag_value|Flag_init|Flag_cloaked, "\Name", \Label, PFA_DOVALUE
   .section amramlo,"aw",@nobits
   .balign 4
   .set \Label\()_ram, .           # Capture current location counter
   .space 4
   .section amforth
   .word \Label\()_ram             # Write the captured address into flash
   .word \Default
   .word XT_FETCH
   .word XT_STORE
.endm

# .macro ALTVAL Name, Label, Default
#     HEADER Flag_visible|Flag_value|Flag_init, "\Name", \Label, PFA_DOVALUE
#    .word rampointer
#     .equ RAM_\Label,rampointer # for listing
#    .set rampointer, rampointer+4
#    .word rom_pointer
#    .section amrom,"ax"
#    .word \Default
#    .section amforth,"ax"
# #   .set keep , .
# #   .org rom_pointer
# #   .word \Default
# #   .org keep
#    .set rom_pointer , rom_pointer + 4
#    .word XT_FETCH
#    .word XT_STORE
# .endm

.macro DEFER Name, Label, XT
    HEADER Flag_visible|Flag_defer|Flag_init, "\Name", \Label, PFA_DODEFER
   .section amramlo,"aw",@nobits
   .balign 4
   .set \Label\()_ram, .           # Capture current location counter
   .space 4
   .section amforth
   .word \Label\()_ram             # Write the captured address into flash
   .word \XT
   .word XT_FETCH
   .word XT_STORE
.endm

.macro CLOAKED_DEFER Name, Label, XT
    HEADER Flag_visible|Flag_defer|Flag_init|Flag_cloaked, "\Name", \Label, PFA_DODEFER
   .section amramlo,"aw",@nobits
   .balign 4
   .set \Label\()_ram, .           # Capture current location counter
   .space 4
   .section amforth
   .word \Label\()_ram             # Write the captured address into flash
   .word \XT
   .word XT_FETCH
   .word XT_STORE
.endm

.macro CONSTANT Name, Label, NUM
#    HEADER Flag_visible, "\Name", \Label, PFA_DOVARIABLE
    HEADER Flag_constant, "\Name", \Label, PFA_DOVARIABLE
    .word \NUM
.endm

.macro CLOAKED_CONSTANT Name, Label, NUM
#    HEADER Flag_visible, "\Name", \Label, PFA_DOVARIABLE
    HEADER Flag_constant|Flag_cloaked, "\Name", \Label, PFA_DOVARIABLE
    .word \NUM
.endm

.macro CON Name, NUM
    CONSTANT "\Name" , "\Name" , \NUM
.endm

.macro DATA Name, Label
    HEADER Flag_visible, "\Name", \Label, PFA_DODATA
.endm


# ===================
# environment contains colon words only
# ===================

.macro ENVIRONMENT Name, Label
    .p2align 2,0xf0
VE_ENV_\Label:
    .word 98b          # Insert Link
98:
    .word Flag_visible      # Flag field

    .byte 8f - 7f     # Calculate length of name field
7:  .ascii "\Name"    # Insert name string
8:  .p2align 2,0xf0        # Realign

   XT_ENV_\Label: .word DOCOLON
   PFA_ENV_\Label:
.endm

# =====================
# CSR are RISC-V specific registers
# =====================

.macro CSR NUM, Name
    .p2align 2,0xf0
VE_CSR_\Name:
    .word 97b               # Insert Link
97: .word Flag_visible      # Flag field

    .byte 8f - 7f     # Calculate length of name field
7:  .ascii "\Name"    # Insert name string
8:  .p2align 2,0xf0   # Realign

   XT_CSR_\Name: .word PFA_CSR_\Name
   PFA_CSR_\Name:
     savetos
     csrr s3, \NUM
   NEXT
.endm


  