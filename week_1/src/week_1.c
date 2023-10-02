#include <stdio.h>
#include <stdlib.h>

int main(){
    int iter;
    int row, col;
    // the testcase won'
    int mat[10][10]={0};
    scanf("%d", &iter);
    for(row=0;row<iter;row++){
        for(col=0; col<iter; col ++){
            scanf("%d", &mat[row][col]);
        }
    }

    int ret = 1;
    for(row=0;row<iter;row++){
        for(col=0; col<iter; col ++){
            if(mat[row][col]!=mat[col][row]) ret=0;
            if(ret==0) break;
        }
    }
    if(ret ==0 ) printf("No\n");
    else printf("Yes\n");

    return 0;
}