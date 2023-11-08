#include "ui.h"

void ui_main_menu(tNumStorHead *list)
{
    int option;
    printf("1. Add a number or 2. Delete a number: ");
    scanf("%d", &option);
    if (option == 1)
    {
        add_number_to_list(list);
    }
    else if (option == 2)
    {
        delete_number_on_list(list);
    }
    else
    {
        printf("Wrong option, try again...\n");
    }
}

void add_number_to_list(tNumStorHead *list)
{
    printf(" Add a number: ");
    int data, pos, is_front;
    scanf("%d", &data);

    if (list->counts == 0)
    {
        add_node(list, data, 0, 1);
    }
    else
    {
        printf("  Specify a target location: ");
        scanf("%d", &pos);
        if (pos > list->counts || pos < 0)
        {
            printf("  Wrong position, try again...\n");
            return;
        }
        else
        {
            // valid pos
            printf("  1. Before or 2. After the location %d: ", pos);
            scanf("%d", &is_front);
            if (is_front == 1)
            {
                add_node(list, data, pos - 1, 1);
            }
            else if (is_front == 2)
            {
                add_node(list, data, pos - 1, 0);
            }
            else
            {
                printf("  Wrong option try again...\n");
                return;
            }
        }
    }
    print_list(list);
}

void delete_number_on_list(tNumStorHead *list)
{
    int pos;
    printf("  Specify a target location: ");
    scanf("%d", &pos);
    if (pos > list->counts || pos < 1)
    {
        printf("  Wrong position, try again...\n");
        return;
    }
    else
    {
        delete_node(list, pos - 1);
    }
    print_list(list);
}

void print_list(tNumStorHead *list)
{
    tNumStorage *tmp = list->head;
    printf("\n");
    printf("counts: %d \n", list->counts);
    printf("\tFrom head --> ");
    while (tmp != NULL)
    {
        printf("%d ", tmp->number);
        tmp = tmp->next;
    }
    tmp = list->tail;
    printf("\n");
    printf("\tFrom tail --> ");
    while (tmp != NULL)
    {
        printf("%d ", tmp->number);
        tmp = tmp->prev;
    }
    printf("\n");
}