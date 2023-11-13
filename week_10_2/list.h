#ifndef __LIST_H__
#define __LIST_H__

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

tNumStorHead* init_list();
tNumStorage *find_node(tNumStorHead *list, int pos);
void add_node(tNumStorHead *list, int data, int pos, int is_add_front);
void delete_node(tNumStorHead *list, int pos);



#endif