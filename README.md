# Sorch

---

# 1. 介绍

Sorch 是一个为 RT-Thread 设计的排序与搜索算法库，提供高效的归并排序和二分查找算法。该模块使用泛型编程接口，支持任意数据类型的排序和查找操作，具有稳定的时间复杂度和优秀的性能表现。

## 1.1 主要特性

- 归并排序（Merge Sort）：
  - 时间复杂度 O(n log n)，空间复杂度 O(n)
  - 稳定排序算法，保持相等元素的相对顺序
  - 支持自定义比较函数，适用于任意数据类型
- 二分查找（Binary Search）：
  - 时间复杂度 O(log n)，适用于已排序数组
  - 快速查找元素位置
  - 支持自定义比较函数，适用于任意数据类型
- 基于 RT-Thread 内存管理（使用 rt_malloc/rt_free）
- 轻量级设计，占用资源少
- 简洁的 API 接口，易于集成和使用

## 1.2 适用场景

- 需要对动态数据进行排序的场景
- 需要在大量数据中快速查找元素的场景
- 需要稳定排序算法的应用
- 嵌入式系统中对内存敏感的排序需求

# 2. 使用

### 2.1 归并排序

```c
// 定义比较函数
int int_cmp(void *a, void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa - *pb);
}

// 对数组进行排序
int data[] = {5, 2, 8, 1, 9, 3};
size_t n = sizeof(data) / sizeof(data[0]);
int32_t ret = merge_sort(data, n, sizeof(int), int_cmp);
if (ret == 0) {
    rt_kprintf("Sort success!\n");
} else if (ret == -2) {
    rt_kprintf("Memory allocation failed!\n");
} else {
    rt_kprintf("Invalid parameters!\n");
}
```

### 2.2 二分查找

```c
// 定义比较函数（与排序使用相同的比较函数）
int int_cmp(void *a, void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa - *pb);
}

// 在已排序数组中查找元素
int target = 5;
int index = binary_search(data, n, sizeof(int), &target, int_cmp);
if (index != -1) {
    rt_kprintf("Found element %d at index %d\n", target, index);
} else {
    rt_kprintf("Element %d not found\n", target);
}
```

### 2.3 自定义数据类型排序

```c
// 定义结构体类型
typedef struct {
    int id;
    char name[16];
} student_t;

// 定义结构体比较函数
int student_cmp(void *a, void *b)
{
    student_t *pa = (student_t *)a;
    student_t *pb = (student_t *)b;
    return (pa->id - pb->id);
}

// 对结构体数组进行排序
student_t students[] = {
    {3, "Alice"},
    {1, "Bob"},
    {2, "Charlie"}
};
size_t n = sizeof(students) / sizeof(students[0]);
merge_sort(students, n, sizeof(student_t), student_cmp);
```

# 3. Demo

以下是一个完整的 Sorch 模块使用示例，展示了排序和查找功能：

```c
#include <rtthread.h>
#include "sorch.h"

// 整数比较函数
int int_cmp(void *a, void *b)
{
    return (*(int *)a - *(int *)b);
}

// 打印数组元素
void print_array(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        rt_kprintf("%d ", arr[i]);
    }
    rt_kprintf("\n");
}

int sorch_demo(void)
{
    // 准备测试数据
    int data[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    size_t n = sizeof(data) / sizeof(data[0]);

    // 打印原始数组
    rt_kprintf("Original array: ");
    print_array(data, n);

    // 执行归并排序
    int32_t ret = merge_sort(data, n, sizeof(int), int_cmp);
    if (ret != 0) {
        rt_kprintf("Sort failed with error code: %d\n", ret);
        return -1;
    }

    // 打印排序后的数组
    rt_kprintf("Sorted array:   ");
    print_array(data, n);

    // 执行二分查找
    int targets[] = {5, 10, 1, 8};
    for (size_t i = 0; i < sizeof(targets)/sizeof(targets[0]); i++) {
        int target = targets[i];
        int index = binary_search(data, n, sizeof(int), &target, int_cmp);
        if (index != -1) {
            rt_kprintf("Found %d at index %d\n", target, index);
        } else {
            rt_kprintf("Element %d not found\n", target);
        }
    }

    return 0;
}

MSH_CMD_EXPORT(sorch_demo, Sorch module demo);
```

# 4. API 说明

## 4.1 归并排序

```c
int32_t merge_sort(void *data_list, size_t n, size_t size, int (*cmp)(void *a, void *b));
```

**参数：**
- `data_list`: 待排序的数据数组
- `n`: 数组中元素的个数
- `size`: 每个元素的大小（字节）
- `cmp`: 比较函数指针，返回值含义：
  - < 0: a < b
  - = 0: a == b
  - > 0: a > b

**返回值：**
- `0`: 排序成功
- `-1`: 参数无效（NULL 指针或 n/size 为 0）
- `-2`: 内存分配失败

**时间复杂度：** O(n log n)
**空间复杂度：** O(n)

## 4.2 二分查找

```c
int binary_search(const void *data_list, size_t n, size_t size,
                  void *x, int (*cmp)(void *a, void *b));
```

**参数：**
- `data_list`: 已排序的数据数组
- `n`: 数组中元素的个数
- `size`: 每个元素的大小（字节）
- `x`: 要查找的目标值
- `cmp`: 比较函数指针（含义同归并排序）

**返回值：**
- >= 0: 找到的元素索引
- `-1`: 未找到或参数无效

**时间复杂度：** O(log n)
**前置条件：** 数据数组必须已按比较函数的顺序排序

**注意：** 二分查找要求数组必须是有序的，否则查找结果不可预测。


# 5. 注意事项

1. 归并排序会使用 RT-Thread 的内存管理函数（`rt_malloc` 和 `rt_free`）分配临时内存，确保在使用前已初始化 RT-Thread 内存管理。
2. 二分查找要求输入数组必须是已排序的，否则结果不可预测。
3. 比较函数必须满足传递性：若 a < b 且 b < c，则 a < c。
4. 排序过程会直接修改原始数组，如需保留原始数据，请先创建副本。
5. 内存分配失败时，归并排序会返回错误代码，但不会修改原始数组。

# 6. 许可

MIT Copyright (c) 2020-2026 Gary Zhang [cleancode@163.com]
