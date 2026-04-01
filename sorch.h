/**
 * @brief sorch is made from sort and search, it provides merge sort and binary search algorithms.
 *
 * @copyright Copyright (c) 2020-2026 Gary Zhang [cleancode@163.com]
 *
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __SORCH__
#define __SORCH__

#include <stdint.h>
#include "rtthread.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief merge sort
 *
 * @param data_list  the data list to be sorted
 * @param n           the number of elements
 * @param size        the size of each element
 * @param cmp         the comparison function
 */
int32_t merge_sort(void *data_list, size_t n, size_t size, int (* cmp)(void *a, void *b));

/**
 * @brief binary search
 *
 * @param data_list  the data list to be searched
 * @param n           the number of elements
 * @param size        the size of each element
 * @param x           the target value to search for
 * @param cmp         the comparison function
 * @return int        the index of the target value if found, otherwise -1
 */
int binary_search(const void *data_list, size_t n, size_t size,
                  void *x, int (*cmp)(void *a, void *b));

#ifdef __cplusplus
}
#endif

#endif // __SORCH__
