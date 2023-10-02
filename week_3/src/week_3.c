#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct num_list
{
    int counts;
    int *p_list;
} Num_list;

void fill_list(Num_list *list);
void bubble_sort(Num_list *list);
void merge(Num_list *list_1, Num_list *list_2);
void print_list(Num_list *list);

int main(int argc , char ** argv){
    // get the list data and count
    Num_list *list_1, *list_2;
    list_1 = (Num_list*)malloc(sizeof(Num_list));
    list_2 = (Num_list*)malloc(sizeof(Num_list));
    printf("Please enter how many numbers in list1:");
    fill_list(list_1);
    bubble_sort(list_1);
    printf("Please enter how many numbers in list1:");
    fill_list(list_2);
    bubble_sort(list_2);
    printf("sorted list1: ");
    print_list(list_1);
    printf("sorted list2: ");
    print_list(list_2);

    printf("merge list : ");
    merge(list_1, list_2);

    free(list_1);
    free(list_2);
    return 0;
}

void fill_list(Num_list *list)
{
    scanf("%d", &(list->counts));
    int tmp_count = list->counts;
    list->p_list = (int*)malloc(sizeof(int)*tmp_count);
    int *mod_ptr = list->p_list;
    printf("\tPlease input %d numbers : ", tmp_count);
    for(int i = 0; i<tmp_count;i++){
        scanf("%d", (mod_ptr+i));
    }
}

void swap(int * ptr1, int * ptr2){
    int tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void bubble_sort(Num_list *list)
{
    for(int i = 0 ; i< list->counts-1 ;i ++){
        for(int j = 0; j<list->counts -i -1 ; j++){
            if(list->p_list[j] > list->p_list[j+1]){
                swap(list->p_list+j, list->p_list+j+1);
            }
        }
    }
}

void merge(Num_list *list_1, Num_list *list_2)
{
    int * arr1, * arr2;
    arr1 = list_1->p_list;
    arr2 = list_2->p_list;
    int c1, c2;
    c1 = c2 = 0;
    while(c1<list_1->counts && c2<list_2->counts){
        if(*arr1 < *arr2){
            printf("%d ", *arr1);
            arr1++;
            c1++;
        }else{
            printf("%d ", *arr2);
            arr2++;
            c2++;
        }
    }
    while(c1 < list_1->counts){
        printf("%d ", *arr1);
        arr1++;
        c1++;
    }
    while(c2 < list_2->counts){
        printf("%d ", *arr2);
        arr2++;
        c2++;
    }
    printf("\n");
}

void print_list(Num_list *list)
{
    int *temp_ptr = list->p_list;
    
    for(int i =0 ; i < list->counts; i++){
        printf("%d ", *temp_ptr);
        temp_ptr++;
    }
    printf("\n");
}
