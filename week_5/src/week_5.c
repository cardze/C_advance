#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage
{
    int number;
    struct num_storage *next;
    struct num_storage *prev;
} tNumStorage;

typedef struct num_stor_head
{
    struct num_storage *head;
    struct num_storage *tail;
    int counts;
} tNumStorHead;

void init_list(tNumStorHead *list);
void print_list(tNumStorHead *list);
void sort_list(tNumStorHead *list, int data);
void get_input(tNumStorHead *list);
void delete_last(tNumStorHead *list);

int main(int argc, char **argv)
{
    int i;
    tNumStorHead *list = (tNumStorHead *)malloc(sizeof(tNumStorHead));
    init_list(list);
    get_input(list);
    return 0;
}

void init_list(tNumStorHead *list)
{
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void print_list(tNumStorHead *list)
{
    tNumStorage *tmp = list->head;
    printf("\tThe sorted list: ");
    while (tmp != NULL)
    {
        printf("%d ", tmp->number);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void sort_list(tNumStorHead *list, int data)
{
    tNumStorage *new_node = (tNumStorage *)malloc(sizeof(tNumStorage));
    new_node->number = data;

    if (list->counts == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        if (data > list->head->number && data < list->tail->number)
        {
            tNumStorage *prev, *tmp = list->head;
            while (tmp->number < data)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            new_node->prev = prev;
            prev->next = new_node;
            tmp->prev = new_node;
            new_node->next = tmp;
        }
        else if (data <= list->head->number)
        {
            new_node->next = list->head;
            list->head->prev = new_node;
            list->head = new_node;
        }
        else
        {
            new_node->prev = list->tail;
            list->tail->next = new_node;
            list->tail = new_node;
        }
    }
    list->counts++;
}

void delete_last(tNumStorHead *list)
{
    if (list->counts == 0)
    {
        printf("\tThere is nothing to delete.\n\n");
        return;
    }
    else
    {
        if (list->counts == 1)
        {
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            tNumStorage *pre = list->tail->prev;
            free(list->tail);
            pre->next = NULL;
            list->tail = pre;
        }
        list->counts--;
    }
}
void get_input(tNumStorHead *list)
{
    int data = 0;
    int tmp;
    while (data != -1)
    {
        printf("Input a number (-1 to exit, -2 to delete last): ");
        scanf("%d", &data);
        if (data == -1)
            break;
        else if (data == -2)
        {
            tmp = list->counts;
            delete_last(list);
            if (tmp - 1 >= 0)
            {
                printf("\tlist->count: %d\n", list->counts);
                print_list(list);
            }
        }
        else
        {
            sort_list(list, data);
            printf("\tlist->count: %d\n", list->counts);
            print_list(list);
        }
    }
}