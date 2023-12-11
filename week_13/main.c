#include "main.h"
#include "queue.h"
#include "space.h"


int main (void)
{
    tQueue *queue;
    int operation=1;
    tQueueNode *target_node;
    int id, score=0, ret;
    queue = createQueue();

    while (operation)
    {

        printf("\nWhich type you are going to operate? \n");
        printf("1. Add a type 1 item\n");
        printf("2. Add a type 2 item\n");
        printf("3. remove a type 1 item with a specific Id\n");
        printf("4. remove a type 2 item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1 || operation == 2)
        {
            printf("  Enter id and score: ");
            scanf("%d", &id);
            scanf("%d", &score);

            ret = tqeueu_enqueue(queue, id, score, (operation == 1 ? TYPE_SMALL : TYPE_LARGE));
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 3 || operation == 4)
        {
            printf ("  Enter an ID to remove ");
            scanf("%d", &id);
            target_node = find_target_node(queue, id, (operation == 3 ? TYPE_SMALL : TYPE_LARGE));
            if (target_node == NULL)
            {
                printf ("    Cannot find the target node \n");
            }
            else
            {
                print_target_info(target_node);
                dequeue_node(queue, target_node, (operation == 3 ? TYPE_SMALL : TYPE_LARGE));
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
