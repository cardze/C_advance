#include "list.h"

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


tNumStorHead *init_list()
{
    tNumStorHead *list = (tNumStorHead *)malloc(sizeof(tNumStorHead));
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}