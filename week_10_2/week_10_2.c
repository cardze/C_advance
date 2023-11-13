// #include "ui.h"
// #include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOTAL 200

void hex_to_dec(char hex, int *res)
{
    (*res) *= 16;
    if ((int)hex - 'A' < 0)
    {
        (*res) += ((int)hex - (int)'0');
    }
    else
    {
        if((int)hex - (int)'A' < 6) (*res) += ((int)hex - (int)'A'+10);
        else (*res) += ((int)hex - (int)'a'+10);
    }
    // every time after calling this fuction, 
    // the value of res should multiple by 16 
    // and add the actual value of this bit.
}

void bin_to_dec(char bin, int *res)
{
    (*res) *= 2;
    (*res) += ((int)bin - (int)'0');
}

void print_result(int result)
{
    printf("    Result: %d\n", result);
}

int to_dec(char *buf, int len, int (*from)(char, int *))
{
    int ret = 0;
    for (int i = 1; i < len; i++)
    {
        from(buf[i], &ret);
    }
    return ret;
}

int main(void)
{
    int result=0, flag, length;
    char *buf = malloc(TOTAL * sizeof(char));
    memset(buf, 0, TOTAL * sizeof(char));
    while (1)
    {
        printf("Please enter number: ");
        scanf("%s", buf);
        length = strlen(buf);
        if(buf[0] == 'h'){
            result = to_dec(buf, length, hex_to_dec);
        }else if(buf[0] == 'b'){
            result = to_dec(buf, length, bin_to_dec);
        }else{
            printf("ERROR\n");
        }
        print_result(result);
    }
}