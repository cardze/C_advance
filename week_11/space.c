#include "space.h"

tTypeScore score_buf[N];

void get_score_space(tTypeScore **pp_score)
{
    int index;
    for(int i =0 ; i<N; i++){
        if(score_buf[i].used == 0){
            index = i;
            break;
        }
    }
    (*pp_score)=&score_buf[index];
    (*pp_score)->used = 1;
    (*pp_score)->loc = index;
    printf("\t\tget_score_space(): giving space numbered %d\n", index);
    return;
}

void return_score_space(int loc)
{
    score_buf[loc].score = 0;
    score_buf[loc].used = 0;
    printf("\t\treturn_score_space(): returning space numbered %d\n", loc);
}