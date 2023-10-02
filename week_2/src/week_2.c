#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc , char ** argv){
    // know how many data will we gonna input
    int count = atoi(*(argv+1)); 
    printf("count = %d\n", count);
    int len = sqrt(count);
    int **mat = (int**)malloc(sizeof(int*)*len);
    for(int i =0;i<len; i++){
        *(mat+i) = (int*)calloc(0, sizeof(int)*len);
    }

    for(int row =0 ; row< len; row++){
        for(int col =0 ; col <len ; col++){
            *(*(mat+row)+col) = atoi(*(argv+2+row*len+col));
        }
    }

    for(int row =0 ; row< len; row++){
        for(int col =0 ; col <len ; col++){
            printf("%3d ",*(*(mat+row)+col));
        }
        printf("\n");
    }

    // change first row and third row
    int * tmp = *(mat + 0);
    *(mat + 0) = *(mat+2);
    *(mat+2)  = tmp;

    printf("// change first row and third row\n");
    for(int row =0 ; row< len; row++){
        for(int col =0 ; col <len ; col++){
            printf("%3d ",*(*(mat+row)+col));
        }
        printf("\n");
    }

    for(int i =0 ; i<len ;i++){
        int tmp_int=*(*(mat+i)+0);
        *(*(mat+i)+0) = *(*(mat+i)+2);
        *(*(mat+i)+2) = tmp_int;
    }

    printf("// change first col and third col\n");
    for(int row =0 ; row< len; row++){
        for(int col =0 ; col <len ; col++){
            printf("%3d ",*(*(mat+row)+col));
        }
        printf("\n");
    }

    return 0;
}