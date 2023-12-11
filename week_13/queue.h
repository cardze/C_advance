#ifndef __QUEUE__
#define __QUEUE__

typedef struct type_small {
    int id;
    int location;
    int score;
}tQueueSmall;

typedef struct type_large {
    int id;
    int location;
    int score[8];
}tQueueLarge;


typedef struct node_info {
    int data_type;
    void * content_ptr;
    struct node_info *next;
    struct node_info *prev;
}tQueueNode; 

typedef struct {
    tQueueNode *front;
    tQueueNode *rear;
    int count;
}tQueue;


tQueue* createQueue(void);

// int enqueue_node(tQueue *queue, int id, int score, int data_type);
int tqeueu_enqueue(tQueue *queue, int id, int score, int data_type);
void dequeue_node(tQueue *queue, tQueueNode *target, int data_type);
tQueueNode *find_target_node(tQueue *queue, int id, int data_type);
void print_target_info(tQueueNode* target);

void print_queue(tQueue *queue);

#endif