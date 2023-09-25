#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct reg
{
    int id;
    int score;
} tReg;


int main(int argc , char ** argv){
    tReg *stu_ptr;
    tReg *head;
    int i;
    stu_ptr = (tReg*)malloc(sizeof(tReg)*N);
    head = stu_ptr;

    stu_ptr -> id = 1; stu_ptr -> score = 99;
    stu_ptr ++;
    stu_ptr -> id = 2; stu_ptr -> score = 80;

    stu_ptr = head;
    stu_ptr[2].id = 40; stu_ptr[2].score = 60;

    stu_ptr = head;
    for(i =0 ; i< N ; i++){
        printf("id: %d, score:%d\n", stu_ptr->id, stu_ptr->score);
        stu_ptr++;
    }
    free(head);
    
    return 0;
}