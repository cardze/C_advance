#include "queue.h"
#include "space.h"

tQueue *createQueue(void)
{
    tQueue *queue;
    queue = (tQueue *)malloc(sizeof(tQueue));

    if (queue)
    {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }

    return queue;
}

int enqueue_node(tQueue *queue, int id, int score, int data_type)
{
    tQueueNode *newptr = NULL;
    int mem_location;

    our_malloc(data_type, &newptr, &mem_location);
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
    // init
    newptr->data_type = data_type + 1;
    newptr->id = id;
    newptr->score = score;
    newptr->location = mem_location;
    newptr->next = NULL;
    newptr->prev = NULL;

    // mantain queue
    if (queue->count == 0)
    {
        queue->front = newptr;
        queue->rear = newptr;
    }
    else
    {
        newptr->prev = queue->rear;

        queue->rear->next = newptr;
        queue->rear = newptr;
    }

    queue->count++;

    return 1;
}

void dequeue_node(tQueue *queue, tQueueNode *target, int data_type)
{
    // maintain queue
    if (queue->count == 1)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }
    else if (target == queue->front)
    {
        queue->front = target->next;
        queue->front->prev = NULL;
    }else if(target == queue->rear){
        queue->rear = target->prev;
        queue->rear->next = NULL;
    }else{
        target->next->prev = target->prev;
        target->prev->next = target->next;
    }

    queue->count--;
    our_free(data_type, target->location);
}

tQueueNode *find_target_node(tQueue *queue, int id, int data_type)
{
    int i;
    tQueueNode *target = queue->front;
    while (target != NULL)
    {
        if (target->id == id)
            return target;
        else
            target = target->next;
    }

    return NULL;
}

void print_queue(tQueue *queue)
{
    int i;
    tQueueNode *target = queue->front;

    printf("      queue content: ");
    for (i = 0; i < queue->count; i++)
    {
        printf("%d(%d) ", target->id, target->data_type);
        target = target->next;
    }
    printf("\n");
}