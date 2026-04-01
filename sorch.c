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

#include "sorch.h"

int binary_search(const void *data_list, size_t n, size_t size,
                  void *x, int (*cmp)(void *a, void *b))
{
    // check if any of the parameters are NULL or the size is 0
    if (NULL == data_list || NULL == x || NULL == cmp || 0 == n || 0 == size) {
        return -1;
    }

    // set up the left and right pointers to the beginning and end of the array
    char *left = (char *)data_list;
    char *right = left + (n - 1) * size;

    // loop until left is greater than right
    while (left <= right) {
        // set the mid pointer to the middle of the current range being searched
        size_t index = ((size_t)(right - left) / size) / 2;
        char *mid = left + index * size;

        // use the cmp function to compare the element at mid with the element being searched
        int cmp_res = cmp(mid, x);

        // if the element at mid is equal to x, return the index of mid
        if (cmp_res == 0) {
            return (int)((mid - (char *)data_list) / size);
        }
        // if the element at mid is less than x, shift the range to the right of mid
        else if (cmp_res < 0) {
            left = mid + size;
        }
        // if the element at mid is greater than x, shift the range to the left of mid
        else {
            right = mid - size;
        }
    }

    // element not found
    return -1;
}


int32_t merge_sort(void *data_list, size_t n, size_t size, int (* cmp)(void *a, void *b))
{
    // check if any of the inputs are invalid
    if (data_list == NULL || n <= 0 || size <= 0 || cmp == NULL) {
        return -1;
    }

    // cast the data list to a char pointer to allow easy memory arithmetic
    char *arr = (char *)data_list;
    char *mem_buf = (char *)rt_malloc(n * size);
    if (mem_buf == NULL) {
        return -2;
    }

    // Perform merge sort using a divide-and-conquer approach
    for (size_t step = 1; step < n; step <<= 1) {
        for (size_t i = 0; i < n; i += 2 * step) {
            size_t left = i;
            size_t mid = i + step;
            size_t right = i + 2 * step;

            if (mid > n) {
                mid = n;
            }

            if (right > n) {
                right = n;
            }

            size_t i1 = left;
            size_t i2 = mid;
            size_t j = 0;

            // merge the two sub-lists by comparing elements using the comparison function
            while (i1 < mid && i2 < right) {
                if (cmp(arr + i1 * size, arr + i2 * size) <= 0) {
                    rt_memcpy(mem_buf + j * size, arr + i1 * size, size);
                    i1++;
                } else {
                    rt_memcpy(mem_buf + j * size, arr + i2 * size, size);
                    i2++;
                }
                j++;
            }

            // copy any remaining elements from the left sub-list
            while (i1 < mid) {
                rt_memcpy(mem_buf + j * size, arr + i1 * size, size);
                i1++;
                j++;
            }

            // copy any remaining elements from the right sub-list
            while (i2 < right) {
                rt_memcpy(mem_buf + j * size, arr + i2 * size, size);
                i2++;
                j++;
            }

            // copy the sorted sub-list from the temporary buffer to the original list
            rt_memcpy(arr + left * size, mem_buf, (right - left) * size);
        }
    }

    rt_free(mem_buf);
    return 0;
}
