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

/** @file test_ring_buffer.c
 ** @brief Test suite for the Ring Buffer data structure.
 **/

/* === Headers files inclusions ================================================================ */

#include <stddef.h>
#include <unity.h>

#include <utils/ring_buffer/ring_buffer.h>

/* === Macros definitions ====================================================================== */

#define BUFFER_SIZE 16

/* === Private data type declarations ========================================================== */

static ring_buffer_t ring_buffer;
static uint8_t ring_buffer_container[BUFFER_SIZE] = {0};

/* === Private variable declarations =========================================================== */
/* === Private function declarations =========================================================== */
/* === Public variable definitions ============================================================= */
/* === Private variable definitions ============================================================ */
/* === Private function implementation ========================================================= */
/* === Public function implementation ========================================================== */

void setUp(void) { ring_buffer_init(&ring_buffer, ring_buffer_container, BUFFER_SIZE); }

/// @test This test verifies that the ring buffer is initialized correctly with the expected properties
/// when no data has been written to or read from it. It sets up a ring buffer with a specified
/// size and checks that the size matches the expected buffer size, and both the read and write
/// indices are at their initial positions (0).
void test_initial_state(void)
{
    ring_buffer_t rb;
    uint8_t container[BUFFER_SIZE];

    ring_buffer_init(&rb, container, BUFFER_SIZE);

    TEST_ASSERT_EQUAL_UINT(BUFFER_SIZE, ring_buffer_size(&rb));
    TEST_ASSERT_EQUAL_UINT(0, rb.read_index);
    TEST_ASSERT_EQUAL_UINT(0, rb.write_index);
}

/// @test Ensure that the ring buffer reports as empty when no data has been written to it and that attempting to read
/// from it returns an appropriate error or indication of emptiness.
void test_buffer_empty(void)
{
    TEST_ASSERT(ring_buffer_is_empty(&ring_buffer));
    TEST_ASSERT(!ring_buffer_is_full(&ring_buffer));
}

/// @test This test verifies the behavior of the ring_buffer_is_full() function by filling the ring buffer to its
/// maximum capacity and then checking whether the function correctly returns true. It initializes a ring buffer with a
/// specified size and fills it with data up to its capacity. After filling the buffer, the test asserts that the buffer
/// is not empty and that the ring_buffer_is_full() function returns true, indicating that the buffer is indeed full.
void test_buffer_full(void)
{
    for (size_t i = 0; i < BUFFER_SIZE; i++) { ring_buffer_write_byte(&ring_buffer, (uint8_t)i); }

    TEST_ASSERT(!ring_buffer_is_empty(&ring_buffer));
    TEST_ASSERT(ring_buffer_is_full(&ring_buffer));
}

/// @test This test verifies the behavior of the ring buffer when performing a series of write and read operations
/// without reaching the wraparound condition.
void test_buffer_read_and_write_no_wrapping(void)
{
    const uint8_t A = 'a';
    const uint8_t B = 'b';
    const uint8_t C = 'c';
    uint8_t data = 0;

    // First case. Write A and Read A.
    TEST_ASSERT(ring_buffer_write_byte(&ring_buffer, A));
    TEST_ASSERT(ring_buffer_read_byte(&ring_buffer, &data));
    TEST_ASSERT_EQUAL_UINT8(data, A);

    // Second case. Write A, B and C in order.
    TEST_ASSERT(ring_buffer_write_byte(&ring_buffer, A));
    TEST_ASSERT(ring_buffer_write_byte(&ring_buffer, B));
    TEST_ASSERT(ring_buffer_write_byte(&ring_buffer, C));

    // First read operation should return A
    TEST_ASSERT(ring_buffer_read_byte(&ring_buffer, &data));
    TEST_ASSERT_EQUAL_UINT8(data, A);

    // Second read operation should return B
    TEST_ASSERT(ring_buffer_read_byte(&ring_buffer, &data));
    TEST_ASSERT_EQUAL_UINT8(data, B);

    // Third read operation should return C
    TEST_ASSERT(ring_buffer_read_byte(&ring_buffer, &data));
    TEST_ASSERT_EQUAL_UINT8(data, C);

    // After reading all the data the buffer should be empty.
    TEST_ASSERT(ring_buffer_is_empty(&ring_buffer));
}

/* === End of documentation ==================================================================== */
