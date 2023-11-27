#pragma once
#include "space.h"

typedef struct node
{
    tTypeScore *data_ptr;
    struct node *next;
}tNode;

typedef struct nodeInfo
{
    int count;
    tNode *head;
}tStack;

tStack *create_stack(void);
void handle_push_operation(tStack *stack_ptr);
void handle_pop_operation(tStack *stack_ptr);
void print_stack_content(tStack *stack_ptr);
