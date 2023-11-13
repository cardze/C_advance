// #include "ui.h"
// #include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOTAL 200

int comp_inc(char a, char b)
{
    return (int)a - (int)b;
}

int comp_dec(char a, char b)
{
    return (int)b - (int)a;
}

void bubble_sort(char *buf, int len, int (*comp)(char, char))
{
    int i, j;
    char tmp;

    for (i = 0; i < (len - 1); i++)
    {
        for (j = i; j < len; j++)
        {
            // judge the two bit by sub  
            if (comp(buf[i], buf[j])>0)
            {
                tmp = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }
}

void print_result(char *buf)
{
    int i;
    printf("    Result: %s\n", buf);
}

int main(void)
{
    int i, flag, length;
    char *buf = malloc(TOTAL * sizeof(char));
    memset(buf, 0, TOTAL * sizeof(char));
    while (1)
    {
        printf("Please enter (0) increasing or (1) decreasing sort: ");
        scanf("%d", &flag);
        if (flag < 0 || flag > 1)
        {
            printf("ERROR: no such option! \n\n");
            continue;
        }

        printf("  Please enter a string: ");
        scanf("%s", buf);
        length = strlen(buf);
        bubble_sort(buf, length, (flag == 0) ? comp_inc : comp_dec);
        print_result(buf);
    }
}