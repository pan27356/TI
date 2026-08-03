//#############################################################################
//
// FILE:   persist_ram.c
//
// TITLE:  8-byte exclusive NOINIT RAM at the end of GS3 (F28003x).
//
//#############################################################################

#include "persist_ram.h"

//
// Link to the last 8 bytes of RAMGS3.  Do not place any other symbols in
// section ".persist".
//
#pragma DATA_SECTION(PersistRam_buf, ".persist")
#pragma RETAIN(PersistRam_buf)
volatile uint16_t PersistRam_buf[PERSIST_RAM_WORD_COUNT];

//*****************************************************************************
//
// PersistRam_getByte
//
//*****************************************************************************
uint16_t PersistRam_getByte(uint16_t index)
{
    uint16_t word;

    if(index >= PERSIST_RAM_SIZE_BYTES)
    {
        return(0U);
    }

    word = PersistRam_buf[index >> 1];
    if((index & 1U) == 0U)
    {
        return(word & 0x00FFU);
    }

    return((word >> 8) & 0x00FFU);
}

//*****************************************************************************
//
// PersistRam_setByte
//
//*****************************************************************************
void PersistRam_setByte(uint16_t index, uint16_t value)
{
    uint16_t word;
    uint16_t v;

    if(index >= PERSIST_RAM_SIZE_BYTES)
    {
        return;
    }

    v = value & 0x00FFU;
    word = PersistRam_buf[index >> 1];

    if((index & 1U) == 0U)
    {
        word = (uint16_t)((word & 0xFF00U) | v);
    }
    else
    {
        word = (uint16_t)((word & 0x00FFU) | (v << 8));
    }

    PersistRam_buf[index >> 1] = word;
}
