#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 100

void readInput(int *n , int matrix[MAX][MAX]){
    scanf("%d" , n);
    for(int i=0  ; i<*n ; i++){
        for(int j=0 ; j<*n ; j++){
            scanf("%d" , &matrix[i][j]);
        }
    }
}

void output(int cost , int edgeCount , int edges[MAX][2]){
    printf("%d ", cost);
    for(int i=edgeCount-1 ; i>=0 ; i--){
        printf("(%d,%d)" , edges[i][0] , edges[i][1]);
    }
    printf("\n");
}

int main(){
    int n;
    int matrix[MAX][MAX];
    int edges[MAX][2];
    int edgeCount = 0;
    int cost =0;

    readInput(&n , matrix);

    bool inTree[MAX] = {false};
    inTree[0] = true;

    for(int count =0 ; count < n-1 ; count++){
        int maxEdge = -1;
        int u = -1 , v = -1;

        for(int i=0 ; i<n ; i++){
            if(inTree[i]){
                for(int j=0 ; j<n ; j++){
                    if(!inTree[j] && matrix[i][j] > maxEdge){
                        maxEdge = matrix[i][j];
                        u=i;v=j;
                    }
                }
            }
        }

        if(u != -1 && v != -1){
            cost+= maxEdge;
            inTree[v] = true;

            if(u>v){
                int temp= u;
                u = v;
                v = temp;
            }
            edges[edgeCount][0] = u;
            edges[edgeCount][1] = v;
            edgeCount ++;
        }
    }
    output(cost, edgeCount , edges);
    return 0;
}