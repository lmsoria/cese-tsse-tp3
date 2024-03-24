/************************************************************************************************
Copyright (c) 2024, Leandro Soria <leandromsoria@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

///
/// @file ring_buffer.c
/// @brief Defines a ring buffer data structure and associated functions in C (implementation).
///

/* === Headers files inclusions ================================================================ */

#include "ring_buffer.h"

/* === Macros definitions ====================================================================== */
/* === Private data type declarations ========================================================== */
/* === Private variable declarations =========================================================== */
/* === Private function declarations =========================================================== */
/* === Public variable definitions ============================================================= */
/* === Private variable definitions ============================================================ */
/* === Private function implementation ========================================================= */
/* === Public function implementation ========================================================== */

void ring_buffer_init(ring_buffer_t* rb, uint8_t* buffer, uint32_t size)
{
    rb->buffer = buffer;
    rb->read_index = 0;
    rb->write_index = 0;
    rb->mask = size - 1;  // API assumption: the size is a power of two.
}

bool ring_buffer_is_empty(ring_buffer_t* rb) { return (rb->read_index == rb->write_index); }

bool ring_buffer_write_byte(ring_buffer_t* rb, uint8_t data)
{
    // First we make a local copy to keep track of the value during the call time (in case an ISR happens)
    uint32_t read_index = rb->read_index;
    uint32_t write_index = rb->write_index;

    uint32_t next_write_index = (write_index + 1) & rb->mask;
    // Avoid having write_index equal to read_index (and therefore making the ring buffer "empty")
    // by discarding the newer incoming data.
    if (next_write_index == read_index) { return false; }

    rb->buffer[write_index] = data;
    rb->write_index = next_write_index;

    return true;
}

bool ring_buffer_read_byte(ring_buffer_t* rb, uint8_t* data)
{
    // First we make a local copy to keep track of the value during the call time (in case an ISR happens)
    uint32_t read_index = rb->read_index;
    uint32_t write_index = rb->write_index;

    if (read_index == write_index) { return false; }

    *data = rb->buffer[read_index];
    read_index = (read_index + 1) & rb->mask;
    rb->read_index = read_index;

    return true;
}

/* === End of documentation ==================================================================== */
