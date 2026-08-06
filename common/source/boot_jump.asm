;//###########################################################################
;//
;// FILE:   boot_jump.asm
;//
;// TITLE:  Long-branch jump for boot chain (avoids ILLEGAL on APP codestart)
;//
;// C prototype:
;//   void Boot_jumpTo(uint32_t entryPoint);
;//
;// C28x C compiler passes the 32-bit argument in ACC.
;//
;//###########################################################################

    .def _Boot_jumpTo
    .sect ".TI.ramfunc"

_Boot_jumpTo:
    SETC    OBJMODE
    NOP
    MOVL    XAR7, ACC
    LB      *XAR7

    .end
