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
void add_number_to_list(tNumStorHead *list);
void delete_number_on_list(tNumStorHead *list);
void add_node(tNumStorHead *list, int data, int pos, int is_add_front);
tNumStorage *find_node(tNumStorHead *list, int pos);

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
    printf("\n");
    printf("counts: %d \n", list->counts);
    printf("From head --> ");
    while (tmp != NULL)
    {
        printf("%d ", tmp->number);
        tmp = tmp->next;
    }
    tmp = list->tail;
    printf("\n");
    printf("From tail --> ");
    while (tmp != NULL)
    {
        printf("%d ", tmp->number);
        tmp = tmp->prev;
    }
    printf("\n");
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

// assume the pos is valid and 0-index.
tNumStorage *find_node(tNumStorHead *list, int pos)
{
    tNumStorage *found;
    // assume the pos is zero-indexed
    found = list->head;
    for (int i = 0; i < pos; i++)
    {
        found = found->next;
    }
    return found;
}

// assume the pos is valid.
void add_node(tNumStorHead *list, int data, int pos, int is_add_front)
{
    tNumStorage *new_node = (tNumStorage *)malloc(sizeof(tNumStorage));
    tNumStorage *assert_target;
    new_node->number = data;
    if (pos == 0 && list->counts == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else if (pos == 0 && is_add_front == 1)
    {
        // update old head's prev from NULL to new node
        // point new node's next to old head
        // and update the new head
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }
    else if (pos == list->counts - 1 && is_add_front == 0)
    {
        // same logic as add to head' front part
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    else
    {
        assert_target = find_node(list, pos);
        if (is_add_front == 1)
        {
            new_node->next = assert_target;
            new_node->prev = assert_target->prev;
            assert_target->prev->next = new_node;
            assert_target->prev = new_node;
        }
        else
        {
            new_node->prev = assert_target;
            new_node->next = assert_target->next;
            assert_target->next->prev = new_node;
            assert_target->next = new_node;
        }
    }
    list->counts++;
}

// 0-index pos
void delete_node(tNumStorHead *list, int pos)
{
    if (list->counts == 0)
    {
        return;
    }

    if (list->counts == 1)
    {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->counts--;

        return;
    }

    tNumStorage *target;
    // delete head
    if (pos == 0)
    {
        target = list->head;
        list->head = target->next;
        list->head->prev = NULL;
        free(target);
        list->counts--;

        return;
    }
    // delete tail
    if (pos == list->counts - 1)
    {
        target = list->tail;
        list->tail = target->prev;
        list->tail->next = NULL;
        free(target);
        list->counts--;

        return;
    }

    target = find_node(list, pos);
    target->next->prev = target->prev;
    target->prev->next = target->next;
    free(target);
    list->counts--;
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

// 1-index
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

void get_input(tNumStorHead *list)
{
    int option;
    while (1)
    {
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
}