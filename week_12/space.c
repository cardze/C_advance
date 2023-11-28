#include "space.h"

unsigned char buffer[ELEMENT_SIZE * NUM_BYTE_BUF];
unsigned char byte_buf_mask = 0;

void print_buffer_status(void)
{
    int i;
    unsigned char mask = 0x80;

    printf("      byte_buf_mask: ");
    for (i = 0; i < NUM_BYTE_BUF; i++)
    {
        printf("%d ", (byte_buf_mask & mask) >> (7 - i));
        mask = mask >> 1;
    }

    printf("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;

    if (byte_buf_mask == FULL)
    {
        return;
    }
    else if (type == TYPE_SMALL)
    {
        location = test_single_location(byte_buf_mask, NUM_BYTE_BUF);
        set_single_bit(&byte_buf_mask, location);
        *target = &buffer[location * ELEMENT_SIZE];
        *mem_location = location;
    }
    else
    {

        location = test_dual_location(byte_buf_mask, NUM_BYTE_BUF);
        if (location >= 0)
        {
            set_dual_bit(&byte_buf_mask, location);
            *target = &buffer[location * ELEMENT_SIZE];
            *mem_location = location;
        }
        else
        {
            return;
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
    printf("seg not here \n");
}

int test_dual_location(unsigned char mask, int mask_length)
{
    for (int i = 0; i < mask_length-1; i++)
    {
        if ((((mask >> i) & 1) == 0) && ((mask >> (i+1)) & 1) == 0)
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
        for(int i =ELEMENT_SIZE * mem_location ; i< ELEMENT_SIZE * (mem_location+1); i++){
            buffer[i] = 0;
        }
        clear_single_bit(&byte_buf_mask, mem_location);
    }
    else if (type == TYPE_LARGE)
    {
        for(int i =ELEMENT_SIZE * mem_location ; i< ELEMENT_SIZE * (mem_location+2); i++){
            buffer[i] = 0;
        }
        clear_dual_bit(&byte_buf_mask, mem_location);
    }
}
