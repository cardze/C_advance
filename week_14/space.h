#ifndef __SPACE__
#define __SPACE__

#include "main.h"

#define NUM_BYTE_BUF 23
#define ELEMENT_SIZE 32
#define FULL 255
#define MASK_ARR_SIZE ((NUM_BYTE_BUF % 8)?NUM_BYTE_BUF/8+1:NUM_BYTE_BUF/8)

void print_buffer_status(void);
void our_malloc(int type, void **target, int *mem_location);
void our_free(int type, int mem_location);
int test_single_location(unsigned char mask, int mask_length);
int test_location(unsigned char *mask, int mask_length, int size);
void set_single_bit(unsigned char *mask, int location);
// void set_bit(unsigned char **mask, int location, int size);
void set_bit(unsigned char * mask, int location, int size);
int test_dual_location(unsigned char mask, int mask_length);
void set_dual_bit(unsigned char *mask, int location);
void clear_single_bit(unsigned char *mask, int location);
void clear_dual_bit(unsigned char *mask, int location);
void clear_bit(unsigned char *mask, int location, int size);
int check_full(unsigned char *mask);
int check_remaining_space();

#endif