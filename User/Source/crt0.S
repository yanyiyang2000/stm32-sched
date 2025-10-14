    .text
    .syntax unified
    .thumb

    .align 0
    .global	_start
    .thumb_func
_start:
    movs    r0, #0	/* no argc */
    movs    r1, #0	/* no argv */
    bl      main
    bl      _exit
