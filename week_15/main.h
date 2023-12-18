#ifndef __MAIN__
#define __MAIN__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4
typedef char My_int[MAX];

void my_add(My_int answer, My_int input_1, My_int input_2);
void my_number_print(My_int input);
void trans_from_string(My_int res, char *user_input);
#endif