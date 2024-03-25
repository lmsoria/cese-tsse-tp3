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

#include <assert.h>
#include <stdlib.h>

#include "ring_buffer.h"

/* === Macros definitions ====================================================================== */
/* === Private data type declarations ========================================================== */

///
/// @brief Structure representing a ring buffer.
///
/// The ring buffer maintains a fixed-size circular buffer with read and write indices.
///
struct ring_buf_t
{
    uint8_t* buffer;  ///< Pointer to the underlying buffer.
    size_t capacity;  ///< Length of the buffer.
    size_t tail;      ///< Index pointing to the next element to be read.
    size_t head;      ///< Index pointing to the next element to be written.
    bool is_full;     ///< Whether is full or not
};

/* === Private variable declarations =========================================================== */
/* === Private function declarations =========================================================== */

static void advance_head_pointer(ring_buffer_t rb);

/* === Public variable definitions ============================================================= */
/* === Private variable definitions ============================================================ */
/* === Private function implementation ========================================================= */

static inline size_t advance_headtail_value(size_t value, size_t capacity) { return (value + 1) % capacity; }

static void advance_head_pointer(ring_buffer_t rb)
{
    assert(rb);

    if (ring_buffer_is_full(rb)) { rb->tail = advance_headtail_value(rb->tail, rb->capacity); }

    rb->head = advance_headtail_value(rb->head, rb->capacity);
    rb->is_full = (rb->head == rb->tail);
}

/* === Public function implementation ========================================================== */

ring_buffer_t ring_buffer_init(uint8_t* buffer, size_t size)
{
    assert(buffer && size);

    ring_buffer_t rb = malloc(sizeof(ring_buf_t));
    assert(rb);

    rb->buffer = buffer;
    rb->capacity = size;
    ring_buffer_reset(rb);

    assert(ring_buffer_is_empty(rb));

    return rb;
}

void ring_buffer_deinit(ring_buffer_t* rb)
{
    assert(rb != NULL);
    free(*rb);
    *rb = NULL;
}

void ring_buffer_reset(ring_buffer_t rb)
{
    assert(rb);

    rb->head = 0;
    rb->tail = 0;
    rb->is_full = false;
}

size_t ring_buffer_size(ring_buffer_t rb)
{
    assert(rb);

    size_t size = rb->capacity;

    if (!ring_buffer_is_full(rb)) {
        if (rb->head >= rb->tail) {
            size = (rb->head - rb->tail);
        } else {
            size = (rb->capacity + rb->head - rb->tail);
        }
    }

    return size;
}

size_t ring_buffer_capacity(ring_buffer_t rb)
{
    assert(rb);
    return rb->capacity;
}

bool ring_buffer_is_empty(ring_buffer_t rb)
{
    assert(rb);

    return (!ring_buffer_is_full(rb) && (rb->head == rb->tail));
}

bool ring_buffer_is_full(ring_buffer_t rb)
{
    assert(rb);

    return rb->is_full;
}

void ring_buffer_write_byte(ring_buffer_t rb, uint8_t data)
{
    assert(rb && rb->buffer);

    rb->buffer[rb->head] = data;

    advance_head_pointer(rb);
}

int ring_buffer_read_byte(ring_buffer_t rb, uint8_t* data)
{
    assert(rb && data && rb->buffer);

    int r = -1;

    if (!ring_buffer_is_empty(rb)) {
        *data = rb->buffer[rb->tail];
        rb->tail = advance_headtail_value(rb->tail, rb->capacity);
        rb->is_full = false;
        r = 0;
    }

    return r;
}

/* === End of documentation ==================================================================== */
