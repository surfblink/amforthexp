ENTRY (_start)

MEMORY {
    FLASH (rwx) : ORIGIN = 0x00010000, LENGTH = 1M
    RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 1M
    RAM2 (rwx) : ORIGIN = 0x10100000, LENGTH = 1M
}

INCLUDE amforth32.ld

SECTIONS {

    uname_buf_size = 512;

    amramlo2 : {

        PROVIDE(RAM_lower_uname_buf = . ) ;
        . = . + uname_buf_size ; 
        PROVIDE(RAM_upper_uname_buf = . ) ;
        . = . + 4 ;
    } > RAM2
}