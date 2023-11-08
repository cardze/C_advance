// #include "ui.h"
// #include "list.h"

#include <stdio.h>

#define check_bit(target, bit) ((target >> bit) & (0x01))

typedef unsigned int Int32;

int check_range_loop(Int32 input, Int32 high, Int32 low)
{
    int ret = 0;
    // return value should be 1(true) or 0(false)
    // trivial : check bit one by one.
    for (Int32 i = low; i <= high && ret == 0; i++)
    {
        ret |= check_bit(input, i);
    }
    return ret != 0;
}

int check_range_no_loop(Int32 input, Int32 high, Int32 low)
{
    // return value should be 1(true) or 0(false)
    // 30 ~ 1 bit checking
    Int32 mask = 0xffffffff;
    mask = mask >> (32 - (high - low + 1)); // concate mask's length to (high - low + 1)
    mask = mask << low; // move the posistion to the right place.

    return (mask & input) > 0;
}

int main(void)
{
    Int32 input;
    Int32 high, low;
    int result = 0;
    while (1)
    {
        printf("Please specify the input in HEX format : ");
        scanf("%x", &input);
        printf("\tPlease specify the high : ");
        scanf("%d", &high);
        if (high > 31)
            continue;
        printf("\tPlease specify the low : ");
        scanf("%d", &low);
        if (low < 0)
            continue;
        result = check_range_loop(input, high, low);
        printf("check_range_loop : %d\n", result);
        result = check_range_no_loop(input, high, low);
        printf("check_range_no_loop : %d\n", result);
    }
}