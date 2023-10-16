#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage
{
    int number;
    struct num_storage *next;
} tNumStorage;

typedef struct num_stor_head
{
    struct num_storage *head;
    struct num_storage *tail;
    int counts;
} tNumStorHead;

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
            tNumStorage *prev,*tmp = list->head;
            while (tmp->number < data)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            prev ->next = new_node;
            new_node ->next = tmp;
        }else if(data <= list->head->number){
            new_node->next = list->head;
            list->head = new_node;
        }else{
            list->tail->next = new_node;
            list->tail = new_node;
        }
    }
    list->counts++;
}

void get_input(tNumStorHead *list)
{
    int data;
    printf("Input a number: ");
    scanf("%d", &data);
    if (data == -1)
    {
        return;
    }
    sort_list(list, data);
    printf("\tlist->count: %d\n", list->counts);
    print_list(list);
    get_input(list);
}

int main(int argc, char **argv)
{
    int i;
    tNumStorHead *list = (tNumStorHead *)malloc(sizeof(tNumStorHead));
    init_list(list);
    get_input(list);
    return 0;
}