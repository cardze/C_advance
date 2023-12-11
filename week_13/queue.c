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

// int enqueue_node(tQueue *queue, int id, int score, int data_type)
// {
//     tQueueNode *newptr = NULL;
//     int mem_location;

//     our_malloc(data_type, &newptr, &mem_location);
//     if (newptr == NULL)
//     {
//         printf("    Enqueue False!!! \n");
//         return 0;
//     }
//     // init
//     newptr->data_type = data_type + 1;
//     newptr->id = id;
//     newptr->score = score;
//     newptr->location = mem_location;
//     newptr->next = NULL;
//     newptr->prev = NULL;

//     // mantain queue
//     if (queue->count == 0)
//     {
//         queue->front = newptr;
//         queue->rear = newptr;
//     }
//     else
//     {
//         newptr->prev = queue->rear;

//         queue->rear->next = newptr;
//         queue->rear = newptr;
//     }

//     queue->count++;

//     return 1;
// }

int tqeueu_enqueue(tQueue *queue, int id, int score, int data_type)
{
    tQueueNode *queue_node;
    int mem_location;
    void *newptr = NULL;
    queue_node = (tQueueNode *)malloc(sizeof(tQueueNode));

    our_malloc(data_type, (void *)&newptr, &mem_location);
    if (newptr == NULL)
    {
        printf("\n    Enqueue False!!! \n");
        return 0;
    }
    // init node info
    queue_node->data_type = data_type;
    queue_node->content_ptr = newptr;
    queue_node->next = NULL;
    queue_node->prev = NULL;

    //  init node data
    if (data_type == TYPE_SMALL)
    {
        tQueueSmall *new_small = (tQueueSmall *)newptr;
        new_small->id = id;
        new_small->location = mem_location;
        new_small->score = score;
    }
    else
    { // large
        tQueueLarge *new_large = (tQueueLarge *)newptr;
        new_large->id = id;
        new_large->location = mem_location;
        new_large->score[0] = score;
    }

    // mantain queue
    if (queue->count == 0)
    {
        queue->front = queue_node;
        queue->rear = queue_node;
    }
    else
    {
        queue_node->prev = queue->rear;

        queue->rear->next = queue_node;
        queue->rear = queue_node;
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
    }
    else if (target == queue->rear)
    {
        queue->rear = target->prev;
        queue->rear->next = NULL;
    }
    else
    {
        target->next->prev = target->prev;
        target->prev->next = target->next;
    }

    queue->count--;
    if (data_type == TYPE_SMALL)
    {
        our_free(data_type, ((tQueueSmall *)target->content_ptr)->location);
    }
    else
    { // large
        our_free(data_type, ((tQueueLarge *)target->content_ptr)->location);
    }
}

tQueueNode *find_target_node(tQueue *queue, int id, int data_type)
{
    int i;
    tQueueNode *target = queue->front;
    while (target != NULL)
    {
        // check node info of its data type is match or not
        if (target->data_type == data_type)
        {
            if (data_type == TYPE_SMALL)
            {
                tQueueSmall *small_data = (tQueueSmall *)target->content_ptr;
                if (small_data->id == id)
                    return target;
                else
                    target = target->next;
            }
            else
            { // type large
                tQueueLarge *large_data = (tQueueLarge *)target->content_ptr;
                if (large_data->id == id)
                    return target;
                else
                    target = target->next;
            }
        }else{
            target = target->next;
        }
    }

    return NULL;
}
void print_target_info(tQueueNode *target)
{
    tQueueSmall *small_data;
    tQueueLarge *large_data;
    int loc, id;
    if (target->data_type == TYPE_SMALL)
    {
        small_data = (tQueueSmall *)target->content_ptr;
        loc = small_data->location;
        id = small_data->id;
    }
    else
    {
        // large data
        large_data = (tQueueLarge *)target->content_ptr;
        loc = large_data->location;
        id = large_data->id;
    }
    printf("\ntarget type: %d, location: %d, id: %d\n", target->data_type+1, loc, id);
}

void print_queue(tQueue *queue)
{
    int i;
    int id, score, type, loc;
    tQueueNode *target = queue->front;
    printf("      type mixed queue: ");
    for (i = 0; i < queue->count; i++)
    {
        if (target->data_type == TYPE_SMALL)
        {
            tQueueSmall *small_data = (tQueueSmall *)target->content_ptr;
            id = small_data->id;
            score = small_data->score;
            loc = small_data->location;
            type = TYPE_SMALL;
        }
        else
        {
            tQueueLarge *large_data = (tQueueLarge *)target->content_ptr;
            id = large_data->id;
            score = large_data->score[0];
            loc = large_data->location;
            type = TYPE_LARGE;
        }

        printf("%d,%d(%d,%d) ", id, score, type + 1, loc);
        target = target->next;
    }
    printf("\n");
}