//#############################################################################
//
// FILE:   persist_ram.h
//
// TITLE:  Soft-reset retained RAM (NOINIT section) for C28x.
//
//#############################################################################

#ifndef PERSIST_RAM_H
#define PERSIST_RAM_H

#include <stdint.h>
#include <stdbool.h>

//
// Number of 8-bit payload bytes stored across NOINIT RAM.
//
#define PERSIST_RAM_PAYLOAD_BYTES    8U

//
// PersistRam_Block lives in linker section ".persist" (type = NOINIT).
// Payload is packed as four uint16_t words (low byte first, then high byte).
//
typedef struct
{
    uint16_t magic;
    uint16_t crc16;
    uint16_t data[4];
} PersistRam_Block;

//
// Returns true when magic and CRC match (data survived a soft reset).
//
extern bool PersistRam_isValid(void);

//
// Clears metadata so the block is treated as invalid on next boot.
//
extern void PersistRam_invalidate(void);

//
// Reads up to PERSIST_RAM_PAYLOAD_BYTES bytes.
// Returns false and zero-fills out[] when the block is invalid.
//
extern bool PersistRam_read(uint16_t out[PERSIST_RAM_PAYLOAD_BYTES]);

//
// Writes up to PERSIST_RAM_PAYLOAD_BYTES bytes and updates magic/CRC.
//
extern void PersistRam_write(const uint16_t in[PERSIST_RAM_PAYLOAD_BYTES]);

//
// Read/write a single 8-bit byte (index 0..7).
//
extern uint16_t PersistRam_readByte(uint16_t index);
extern void PersistRam_writeByte(uint16_t index, uint16_t value);

//
// Direct pointer to the NOINIT block (for debuggers only).
//
extern volatile PersistRam_Block PersistRam_block;

#endif // PERSIST_RAM_H
