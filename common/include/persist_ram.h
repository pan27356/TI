//#############################################################################
//
// FILE:   persist_ram.h
//
// TITLE:  8-byte exclusive NOINIT RAM at the end of GS3 (F28003x).
//
// Soft-reset and watchdog-reset safe: linker section ".persist" is not
// cleared by cinit.  Full power-on reset leaves RAM undefined.
//
//#############################################################################

#ifndef PERSIST_RAM_H
#define PERSIST_RAM_H

#include <stdint.h>

//
// Fixed address: last 8 usable bytes of RAMGS3 (0xFFF8..0xFFFF reserved).
//
#define PERSIST_RAM_ADDR         0x0000FFF0U
#define PERSIST_RAM_SIZE_BYTES   8U
#define PERSIST_RAM_WORD_COUNT   4U

//
// Exclusive 8-byte buffer in NOINIT section ".persist".
// Four uint16_t words hold eight 8-bit bytes (low byte first in each word).
//
extern volatile uint16_t PersistRam_buf[PERSIST_RAM_WORD_COUNT];

//
// Optional byte helpers (index 0..7).  Each value uses only the low 8 bits.
//
extern uint16_t PersistRam_getByte(uint16_t index);
extern void PersistRam_setByte(uint16_t index, uint16_t value);

#endif // PERSIST_RAM_H
