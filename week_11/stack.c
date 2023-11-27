#include "stack.h"

tStack *create_stack(void)
{
    tStack *tmp = (tStack *)malloc(sizeof(tStack));
    tmp->count = 0;
    tmp->head = NULL;
    return tmp;
}

void handle_push_operation(tStack *stack_ptr)
{
    if (stack_ptr->count == N)
    {
        printf("[Error] handle_push_operation(): space full.\n");
        return;
    }
    int score;
    printf("\thandle_push_operation(): enter score value: ");
    scanf("%d", &score);
    tNode *node = (tNode *)malloc(sizeof(tNode));
    get_score_space(&node->data_ptr);
    node->data_ptr->score = score; // assign user input
    tNode *prev_head = stack_ptr->head;
    stack_ptr->head = node;
    stack_ptr->head->next = prev_head;
    stack_ptr->count++;
}
void handle_pop_operation(tStack *stack_ptr)
{
    if (stack_ptr->count == 0)
    {
        printf("[Error] handle_pop_operation(): nothing to pop.\n");
        return;
    }
    int loc = stack_ptr->head->data_ptr->loc;
    printf("\thandle_pop_operation(): poped value: %d\n", stack_ptr->head->data_ptr->score);
    return_score_space(loc);
    tNode *prev_head=stack_ptr->head;
    stack_ptr->head = stack_ptr->head->next;
    stack_ptr->count--;
    free(prev_head);
}
void print_stack_content(tStack *stack_ptr)
{
    printf("\tprint_stack_content() stack item -> ");
    tNode *head_copy = stack_ptr->head;
    while (head_copy)
    {
        printf("%d(%d) ", head_copy->data_ptr->score, head_copy->data_ptr->loc);
        head_copy = head_copy->next;
    }
}