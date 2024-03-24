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

#pragma once

///
/// @file ring_buffer.h
/// @brief Defines a ring buffer data structure and associated functions in C.
///
/// A ring buffer, also known as a circular buffer, is a data structure that uses a fixed-size
/// buffer which wraps around itself. It is particularly useful in scenarios where you need
/// to efficiently manage a continuous stream of data with a fixed buffer size.
///
/// This file provides the definition of the ring buffer structure and functions to initialize,
/// read from, and write to the buffer.
///

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* === C++ Guard =============================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/// Opaque circular buffer structure
typedef struct ring_buf_t ring_buf_t;

/// Handle type, the way users interact with the API
typedef ring_buf_t* ring_buffer_t;

/* === Public variable declarations ============================================================ */
/* === Public function declarations ============================================================ */

///
/// @brief Initializes a ring buffer with the given parameters.
///
/// This function initializes a ring buffer with the provided buffer and size. The buffer
/// must be pre-allocated by the caller. Additionally, the size parameter should be a power
/// of two as per the API assumption.
///
/// @param buffer Pointer to the pre-allocated buffer.
/// @param size Size of the buffer. Must be a power of two.
///
ring_buffer_t ring_buffer_init(uint8_t* buffer, size_t size);

///
/// @brief Free a ring buffer structure. Data is not free'd, since it's owner's responsibility.
/// @param rb Ring buffer to free
///
void ring_buffer_deinit(ring_buffer_t rb);

///
/// @brief Resets the ring buffer state to empty (ie tail == head). Data is not cleared.
/// @param rb Ring buffer to reset.
///
void ring_buffer_reset(ring_buffer_t rb);

///
/// @brief Returns the number of elements stored on the ring buffer.
/// @param rb Ring buffer to check.
/// @return Size of the buffer.
///
size_t ring_buffer_size(ring_buffer_t rb);

///
/// @brief Returns the ring buffer capacity.
/// @param rb Ring buffer to check.
/// @return Maximum size of the buffer.
///
size_t ring_buffer_capacity(ring_buffer_t rb);

///
/// @brief Checks if the ring buffer is empty.
///
/// @param rb Pointer to the ring buffer structure to check.
/// @return true if the ring buffer is empty, false otherwise.
///
bool ring_buffer_is_empty(ring_buffer_t rb);

///
/// @brief Checks if the ring buffer is full.
///
/// @param rb Pointer to the ring buffer structure to check.
/// @return true if the ring buffer is full, false otherwise.
///
bool ring_buffer_is_full(ring_buffer_t rb);

///
/// @brief Writes a byte of data to the ring buffer.
///
/// This function writes a byte of data to the ring buffer. If the buffer is full, it discards
/// the oldest data to make space for the new data.
///
/// @param rb Pointer to the ring buffer structure to write to.
/// @param data The byte of data to write to the buffer.
/// @return true if the data was successfully written, false if the buffer is full and data was discarded.
///
void ring_buffer_write_byte(ring_buffer_t rb, uint8_t data);

///
/// @brief Reads a byte of data from the ring buffer.
///
/// This function reads a byte of data from the ring buffer. If the buffer is empty, it returns false.
///
/// @param rb Pointer to the ring buffer structure to read from.
/// @param data Pointer to a variable to store the read data.
/// @return 0 on success, or -1 if the buffer is empty.
///
int ring_buffer_read_byte(ring_buffer_t rb, uint8_t* data);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif
