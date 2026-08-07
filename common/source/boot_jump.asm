;//###########################################################################
;//
;// FILE:   boot_jump.asm
;//
;// TITLE:  Boot jump to APP (assembly implementation)
;//
;//###########################################################################

APP_ENTRY_POINT .set  0x092000

    .if __TI_EABI__
    .asg JumpToApp, _JumpToApp
    .endif

    .global _JumpToApp
    .sect ".TI.ramfunc"
    .retain

_JumpToApp:
    DINT
    AND     IER, #0x0000
    AND     IFR, #0x0000
    SETC    OBJMODE
    NOP
    MOVL    XAR7, #APP_ENTRY_POINT
    LB      *XAR7

    .end
