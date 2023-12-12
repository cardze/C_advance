#include "space.h"

unsigned char buffer[ELEMENT_SIZE * NUM_BYTE_BUF];
unsigned char byte_buf_masks[MASK_ARR_SIZE] = {0};

int check_remaining_space()
{
    int ret = NUM_BYTE_BUF;
    for (int i = 0; i < NUM_BYTE_BUF; i++)
    {
        if (((byte_buf_masks[i / 8] >> (i % 8)) & 1) == 1)
            ret--;
    }
    return ret;
}

void print_buffer_status(void)
{
    int i, shift;
    int remain_bits = NUM_BYTE_BUF;

    printf("      buffer_mask: ");
    for (int iter = MASK_ARR_SIZE - 1; iter >= 0; iter--)
    {
        shift = ((remain_bits % 8) ? (remain_bits % 8) : 8);
        for (i = 0; i < shift; i++)
        {
            printf("%d ", ((byte_buf_masks[iter]) >> (shift - i - 1)) & 1);
        }
        printf(", ");
        remain_bits -= shift;
    }
    // printf("\n");
    // for (i = 0; i < MASK_ARR_SIZE; i++)
    // {
    //     printf("%d ,", byte_buf_masks[i]);
    // }

    printf("\n");
}

int check_full(unsigned char *mask)
{

    int res = 1;
    for (int i = 0; i < MASK_ARR_SIZE; i++)
    {
        res &= ((*(mask + i)) == FULL);
    }
    return res;
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;

    if (check_full(byte_buf_masks))
    {
        return;
    }
    else
    {
        location = test_location(byte_buf_masks, NUM_BYTE_BUF, type);
        if (location == -1)
            return;
        set_bit(byte_buf_masks, location, type);
        *target = &buffer[location * ELEMENT_SIZE];
        *mem_location = location;
    }
}

int test_location(unsigned char *mask, int mask_length, int size)
{
    int start, end;
    unsigned char end_mask;
    for (int i = 0; i < NUM_BYTE_BUF - size + 1; i++)
    {
        start = i;
        if (((mask[start / 8] >> start % 8) & 1) == 1)
            continue;
        end = start + size - 1;
        while (start != end)
        {
            end_mask = mask[end / 8];
            if (((end_mask >> (end % 8)) & 1) != 0)
                break;
            else
            {
                end--;
            }
        }
        if (start == end)
            return start;
    }
    return -1;
}

void set_bit(unsigned char *mask, int location, int size)
{
    for (int i = location; i < location + size; i++)
    {
        mask[i / 8] |= (1 << (i % 8));
    }
}

int test_single_location(unsigned char mask, int mask_length)
{
    for (int i = 0; i < mask_length; i++)
    {
        if (((mask >> i) & 1) == 0)
        {
            return i;
        }
    }
    return -1;
}

void set_single_bit(unsigned char *mask, int location)
{
    *mask = *mask | (1 << location);
}

int test_dual_location(unsigned char mask, int mask_length)
{
    for (int i = 0; i < mask_length - 1; i++)
    {
        if ((((mask >> i) & 1) == 0) && ((mask >> (i + 1)) & 1) == 0)
        {
            return i;
        }
    }
    return -1;
}

void set_dual_bit(unsigned char *mask, int location)
{
    *mask = *mask | (3 << location);
}

void clear_single_bit(unsigned char *mask, int location)
{
    *mask = *mask & (~(1 << location));
}

void clear_dual_bit(unsigned char *mask, int location)
{
    *mask = *mask & (~(3 << location));
}

void our_free(int type, int mem_location)
{
    for (int i = ELEMENT_SIZE * mem_location; i < ELEMENT_SIZE * (mem_location + type); i++)
    {
        buffer[i] = 0;
    }
    clear_bit(byte_buf_masks, mem_location, type);
}

void clear_bit(unsigned char *mask, int location, int size)
{
    for (int i = location; i < location + size; i++)
    {
        mask[i / 8] &= (~(1 << (i % 8)));
    }
}
