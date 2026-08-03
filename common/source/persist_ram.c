//#############################################################################
//
// FILE:   persist_ram.c
//
// TITLE:  Soft-reset retained RAM (NOINIT section) for C28x.
//
//#############################################################################

#include "persist_ram.h"

#define PERSIST_RAM_MAGIC    0x5033U  // 'P3'

//
// Place in NOINIT linker section; startup code must not zero this region.
//
#pragma DATA_SECTION(PersistRam_block, ".persist")
#pragma RETAIN(PersistRam_block)
volatile PersistRam_Block PersistRam_block;

//*****************************************************************************
//
// CRC-16/CCITT-FALSE over an array of 16-bit words (low 8 bits are payload).
//
//*****************************************************************************
static uint16_t PersistRam_calcCrc16(const uint16_t *words, uint16_t count)
{
    uint16_t crc = 0xFFFFU;
    uint16_t i;
    uint16_t b;

    for(i = 0U; i < count; i++)
    {
        crc ^= (words[i] & 0x00FFU) << 8;
        for(b = 0U; b < 8U; b++)
        {
            if((crc & 0x8000U) != 0U)
            {
                crc = (uint16_t)((crc << 1) ^ 0x1021U);
            }
            else
            {
                crc = (uint16_t)(crc << 1);
            }
        }

        crc ^= (words[i] & 0xFF00U);
        for(b = 0U; b < 8U; b++)
        {
            if((crc & 0x8000U) != 0U)
            {
                crc = (uint16_t)((crc << 1) ^ 0x1021U);
            }
            else
            {
                crc = (uint16_t)(crc << 1);
            }
        }
    }

    return(crc);
}

//*****************************************************************************
//
// Pack/unpack helpers: two 8-bit bytes per uint16_t word.
//
//*****************************************************************************
static uint16_t PersistRam_unpackByte(uint16_t wordIndex, uint16_t byteIndex)
{
    uint16_t word;

    word = PersistRam_block.data[wordIndex];
    if(byteIndex == 0U)
    {
        return(word & 0x00FFU);
    }

    return((word >> 8) & 0x00FFU);
}

static void PersistRam_packByte(uint16_t wordIndex, uint16_t byteIndex,
                                uint16_t value)
{
    uint16_t word;
    uint16_t v;

    v = value & 0x00FFU;
    word = PersistRam_block.data[wordIndex];

    if(byteIndex == 0U)
    {
        word = (uint16_t)((word & 0xFF00U) | v);
    }
    else
    {
        word = (uint16_t)((word & 0x00FFU) | (v << 8));
    }

    PersistRam_block.data[wordIndex] = word;
}

//*****************************************************************************
//
// PersistRam_isValid
//
//*****************************************************************************
bool PersistRam_isValid(void)
{
    uint16_t crc;

    if(PersistRam_block.magic != PERSIST_RAM_MAGIC)
    {
        return(false);
    }

    crc = PersistRam_calcCrc16((const uint16_t *)PersistRam_block.data, 4U);
    return(crc == PersistRam_block.crc16);
}

//*****************************************************************************
//
// PersistRam_invalidate
//
//*****************************************************************************
void PersistRam_invalidate(void)
{
    PersistRam_block.magic = 0U;
    PersistRam_block.crc16 = 0U;
}

//*****************************************************************************
//
// PersistRam_read
//
//*****************************************************************************
bool PersistRam_read(uint16_t out[PERSIST_RAM_PAYLOAD_BYTES])
{
    uint16_t i;

    if(!PersistRam_isValid())
    {
        for(i = 0U; i < PERSIST_RAM_PAYLOAD_BYTES; i++)
        {
            out[i] = 0U;
        }
        return(false);
    }

    for(i = 0U; i < PERSIST_RAM_PAYLOAD_BYTES; i++)
    {
        out[i] = PersistRam_unpackByte(i >> 1, i & 1U);
    }

    return(true);
}

//*****************************************************************************
//
// PersistRam_write
//
//*****************************************************************************
void PersistRam_write(const uint16_t in[PERSIST_RAM_PAYLOAD_BYTES])
{
    uint16_t i;

    for(i = 0U; i < PERSIST_RAM_PAYLOAD_BYTES; i++)
    {
        PersistRam_packByte(i >> 1, i & 1U, in[i]);
    }

    PersistRam_block.crc16 =
        PersistRam_calcCrc16((const uint16_t *)PersistRam_block.data, 4U);
    PersistRam_block.magic = PERSIST_RAM_MAGIC;
}

//*****************************************************************************
//
// PersistRam_readByte
//
//*****************************************************************************
uint16_t PersistRam_readByte(uint16_t index)
{
    uint16_t bytes[PERSIST_RAM_PAYLOAD_BYTES];
    uint16_t i;

    (void)PersistRam_read(bytes);

    if(index >= PERSIST_RAM_PAYLOAD_BYTES)
    {
        return(0U);
    }

    return(bytes[index]);
}

//*****************************************************************************
//
// PersistRam_writeByte
//
//*****************************************************************************
void PersistRam_writeByte(uint16_t index, uint16_t value)
{
    uint16_t bytes[PERSIST_RAM_PAYLOAD_BYTES];
    uint16_t i;

    if(index >= PERSIST_RAM_PAYLOAD_BYTES)
    {
        return;
    }

    if(PersistRam_isValid())
    {
        (void)PersistRam_read(bytes);
    }
    else
    {
        for(i = 0U; i < PERSIST_RAM_PAYLOAD_BYTES; i++)
        {
            bytes[i] = 0U;
        }
    }

    bytes[index] = value & 0x00FFU;
    PersistRam_write(bytes);
}
