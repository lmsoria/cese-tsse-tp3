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
#include <stdint.h>

/* === C++ Guard =============================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

///
/// @brief Structure representing a ring buffer.
///
/// The ring buffer maintains a fixed-size circular buffer with read and write indices.
///
typedef struct ring_buffer_t
{
    uint8_t* buffer;       ///< Pointer to the underlying buffer.
    uint32_t mask;         ///< Mask used for wrapping indices.
    uint32_t read_index;   ///< Index pointing to the next element to be read.
    uint32_t write_index;  ///< Index pointing to the next element to be written.
} ring_buffer_t;

/* === Public data type declarations =========================================================== */
/* === Public variable declarations ============================================================ */
/* === Public function declarations ============================================================ */

///
/// @brief Initializes a ring buffer with the given parameters.
///
/// This function initializes a ring buffer with the provided buffer and size. The buffer
/// must be pre-allocated by the caller. Additionally, the size parameter should be a power
/// of two as per the API assumption.
///
/// @param rb Pointer to the ring buffer structure to initialize.
/// @param buffer Pointer to the pre-allocated buffer.
/// @param size Size of the buffer. Must be a power of two.
///
void ring_buffer_init(ring_buffer_t* rb, uint8_t* buffer, uint32_t size);

///
/// @brief Checks if the ring buffer is empty.
///
/// This function checks whether the ring buffer is empty by comparing the read and write indices.
///
/// @param rb Pointer to the ring buffer structure to check.
/// @return true if the ring buffer is empty, false otherwise.
///
bool ring_buffer_is_empty(ring_buffer_t* rb);

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
bool ring_buffer_write_byte(ring_buffer_t* rb, uint8_t data);

///
/// @brief Reads a byte of data from the ring buffer.
///
/// This function reads a byte of data from the ring buffer. If the buffer is empty, it returns false.
///
/// @param rb Pointer to the ring buffer structure to read from.
/// @param data Pointer to a variable to store the read data.
/// @return true if data was successfully read, false if the buffer is empty.
///
bool ring_buffer_read_byte(ring_buffer_t* rb, uint8_t* data);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif
