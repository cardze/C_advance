#include <stdio.h>

typedef char buf[2];

int main(void){
    buf b[3];
    b[0][0] = 0x10;
    b[0][1] = 0x20;
    b[1][0] = 0x30;
    b[1][1] = 0x40;
    b[2][0] = 0x50;
    b[2][1] = 0x60;

    printf("%x", *(b)[1]);
}