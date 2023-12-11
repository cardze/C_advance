#include "space.h"

unsigned char buffer[SMALL_ELEMENT_SIZE * NUM_SMALL_BYTE_BUF + LARGE_ELEMENT_SIZE * NUM_LARGE_BYTE_BUF];
unsigned char byte_small_buf_mask = 0;
unsigned char byte_large_buf_mask = 0;

void print_buffer_status(void)
{
    int i;
    unsigned char mask = 0x80;

    printf("\n      byte_small_buf_mask: ");
    for (i = 0; i < NUM_SMALL_BYTE_BUF; i++)
    {
        printf("%d ", (byte_small_buf_mask & mask) >> (7 - i));
        mask = mask >> 1;
    }

    printf("\n");

    mask = 0x80;
    printf("      byte_large_buf_mask: ");
    for (i = 0; i < NUM_LARGE_BYTE_BUF; i++)
    {
        printf("%d ", (byte_large_buf_mask & mask) >> (7 - i));
        mask = mask >> 1;
    }

    printf("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;

    if (type == TYPE_SMALL)
    {
        if (byte_small_buf_mask == FULL)
        {
            // small buf is full, check large buf
            if (byte_large_buf_mask == FULL)
                return; // both no space
            location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);
            set_single_bit(&byte_large_buf_mask, location);
            *target = &buffer[LARGE_START + location * LARGE_ELEMENT_SIZE];
            *mem_location = location + (LARGE_START / SMALL_ELEMENT_SIZE);
        }
        else
        {
            // small buf has enough space
            location = test_single_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);
            set_single_bit(&byte_small_buf_mask, location);
            *target = &buffer[location * SMALL_ELEMENT_SIZE];
            *mem_location = location;
        }
    }
    else
    {
        // TYPE_large
        if (byte_large_buf_mask == FULL)
        {
            // large buf full, check small buf
            if (byte_small_buf_mask == FULL)
                return; // both full
            location = test_dual_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);
            if (location < 0)
                return; // no continous space for large in small buf
            set_dual_bit(&byte_small_buf_mask, location);
            *target = &buffer[location * SMALL_ELEMENT_SIZE];
            *mem_location = location;
        }
        else
        {
            // large buf is enough
            location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);
            set_single_bit(&byte_large_buf_mask, location);
            *target = &buffer[LARGE_START + location * SMALL_ELEMENT_SIZE];
            *mem_location = location + (LARGE_START / SMALL_ELEMENT_SIZE);
        }
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
    if (type == TYPE_SMALL)
    {
        if (mem_location >= (LARGE_START / SMALL_ELEMENT_SIZE))
        {
            // small ele in large buf
            for (int i = SMALL_ELEMENT_SIZE * mem_location; i < SMALL_ELEMENT_SIZE * (mem_location + 1); i++)
            {
                buffer[i] = 0;
            }
            clear_single_bit(&byte_large_buf_mask, mem_location - (LARGE_START / SMALL_ELEMENT_SIZE));
        }
        else
        {
            // normal case
            for (int i = SMALL_ELEMENT_SIZE * mem_location; i < SMALL_ELEMENT_SIZE * (mem_location + 1); i++)
            {
                buffer[i] = 0;
            }
            clear_single_bit(&byte_small_buf_mask, mem_location);
        }
    }
    else if (type == TYPE_LARGE)
    {
        if (mem_location < (LARGE_START / SMALL_ELEMENT_SIZE))
        {
            // special case, large ele in small buf
            // printf("\nDEBUG: special case, large ele in small buf\n");
            for (int i = SMALL_ELEMENT_SIZE * mem_location; i < SMALL_ELEMENT_SIZE * (mem_location + 2); i++)
            {
                buffer[i] = 0;
            }
            clear_dual_bit(&byte_small_buf_mask, mem_location);
        }
        else
        {
            // normal case large ele in large buf
            for (int i = LARGE_ELEMENT_SIZE * mem_location + LARGE_START; i < LARGE_ELEMENT_SIZE * (mem_location + 1) + LARGE_START; i++)
            {
                buffer[i] = 0;
            }
            clear_single_bit(&byte_large_buf_mask, mem_location - (LARGE_START / SMALL_ELEMENT_SIZE));
        }
    }
}
