;//###########################################################################
;//
;// FILE:   boot_jump.asm
;//
;// TITLE:  Boot jump to APP (assembly implementation)
;//
;//###########################################################################

APP_ENTRY_POINT .set  0x092000

    .def _JumpToApp
    .sect ".TI.ramfunc"

_JumpToApp:
    DINT
    AND     IER, #0x0000
    AND     IFR, #0x0000
    SETC    OBJMODE
    NOP
    MOVL    XAR7, #APP_ENTRY_POINT
    LB      *XAR7

    .end
