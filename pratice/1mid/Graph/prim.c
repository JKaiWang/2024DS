#include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define INF  100000
int matrix[MAX][MAX];
void findMinSpanningTree(int n, int *cost , int *edgeCount , int edges[MAX][2]) {
    int inMST[MAX] = {0};
    int minWeight[MAX];
    int parent[MAX];

    for(int i=0 ; i<n ; i++){
        minWeight[i] = INF;
        parent[i] = -1;
    }

    minWeight[0] = 0;
    *cost = 0;
    *edgeCount = 0;
    for(int i=0 ; i<n ; i++){
        int minW = INF;
        int u = -1;
        for(int j=0 ; j<n ; j++){
            if(!inMST[j] && minWeight[j] < minW){
                minW = minWeight[j];
                u=j;
            }
        }
        inMST[u] = 1;
        *cost += minW;

        if(parent[u]!=-1){
            edges[*edgeCount][1] = parent[u];
            edges[*edgeCount][0] = u;
            (*edgeCount)++;
        }

        for(int j=0 ; j<n ; j++){
            if(!inMST[j] && matrix[u][j]>0 &&matrix[u][j] < minWeight[j]){
                minWeight[j] = matrix[u][j];
                parent[j] = u;
            }
        }
    }

    
}
int main(){
    // input
    int n;
    scanf("%d" , &n);
    //int matrix[MAX][MAX];
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            scanf("%d" , &matrix[i][j]);
        }
    }

    int totalCost = 0;
    int edgeCount = 0;
    int edges[MAX][2];
    findMinSpanningTree(n , &totalCost , &edgeCount , edges);
    //output
    printf("%d" , totalCost);
    for(int i=0 ; i<n-1 ; i++){
        printf(", (%d,%d)" , edges[i][1] , edges[i][0]);
    }
    printf("\n");
}