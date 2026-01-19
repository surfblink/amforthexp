OUTPUT_ARCH( "riscv" )

ENTRY( PFA_COLD )

/* .equ datastack_size, 128  # (32*cellsize)
.equ returnstack_size, 128 # 32*cellsize
.equ refill_buf_size, 96
.equ appl_userarea_size, 2*cellsize
.equ leavestack_size, 8*cellsize */

MEMORY
{
   FLASH(RX)   : ORIGIN = 0x20400000, LENGTH = 0x8000
   RAM(WAIXL) : ORIGIN = 0x80000000, LENGTH = 0x4000
}

INCLUDE amforth32.ld