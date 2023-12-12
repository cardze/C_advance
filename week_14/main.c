#include "main.h"
#include "queue.h"
#include "space.h"


int main (void)
{
    tQueue *queue;
    int operation =1;
    tQueueNode *target_node;
    int id, score=0, ret, size;
    queue = createQueue();

    while (operation)
    {
        printf("Remaining memory space %d\n", check_remaining_space());
        printf("Which type you are going to operate? \n");
        printf("1. Add an item\n");
        printf("2. remove an item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1)
        {
            printf("  enter id: \n");
            scanf("%d", &id);
            printf("  specify data type (units) you want: \n");
            scanf("%d", &size);
            ret = enqueue_node(queue, id, score, size);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 2)
        {
            printf ("  enter an ID to remove \n");
            scanf("%d", &id);
            target_node = find_target_node(queue, id, (operation == 3 ? TYPE_SMALL : TYPE_LARGE));
            if (target_node == NULL)
            {
                printf ("    Cannot find the target node \n");
            }
            else
            {
                dequeue_node(queue, target_node, target_node->data_type);
            }
            print_buffer_status();
        }
        else 
        {
            printf ("    No such operation \n");   
        }
        print_queue(queue);
    }

}
