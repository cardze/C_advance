#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define N 5

typedef struct Score
{
    int score;
    int loc;
    int used;
}tTypeScore;

void get_score_space(tTypeScore **pp_score);
void return_score_space(int location );

