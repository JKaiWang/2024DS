#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#define MAX 20
#define INF 10000
int matrix[MAX][MAX];
typedef struct Edge{
    int src ; 
    int dest;
    int weight;
}Edge;
int find(int parent[] , int x){
    if(parent[x] != x){
        parent[x] = find(parent , parent[x]);
    }
    return parent[x];
}
void unionSet(int parent[] , int rank[] , int x , int y){
    int rootX = find(parent ,x);
    int rootY = find(parent ,y);
    if(rootX == rootY) return ;
    if(rootX != rootY){
        if(rank[rootX] > rank[rootY]){
            parent[rootY] = rootX;
        }
        if(rank[rootY] > rank[rootX]){
            parent[rootX] = rootY;
        }
        else{
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
int compareEdge(const void* a , const void* b){
    return ((Edge*)a)->weight -((Edge*)b)->weight;
}
void findSpanningTree(int n , int *cost , int *edgeCount , int edges[MAX][2]){
    Edge edgeList[MAX*MAX] ;
    int edgeListSize = 0;
    for(int i=0 ; i<n ; i++){
        for(int j=i ; j<n ; j++){
            if(matrix[i][j] != 0 && matrix[i][j] != INF){
                edgeList[edgeListSize++]= (Edge){i , j , matrix[i][j]};
            }
        }
    }
    qsort(edgeList , edgeListSize , sizeof(Edge) , compareEdge);
    int parent[MAX] ; int rank[MAX];
    for(int i=0 ; i<n ; i++){
        parent[i] = i;
        rank[i] = 0;
    }
    *cost =0 ; *edgeCount=0;
    for(int i=0 ; i< edgeListSize && *edgeCount < n-1; i++){
        Edge e = edgeList[i];
        int rootSrc = find(parent , e.src);
        int rootDest = find(parent ,e.dest);
        if(rootSrc == rootDest) continue;
        if(rootSrc != rootDest){
            unionSet(parent , rank , rootSrc , rootDest);
            //printf("src:%d , rootsrc: %d, dest:%d , rootDest %d\n" , e.src , rootSrc ,e.dest , rootDest);
            int temp1 ; int temp2; 
            if(e.src > e.dest){
                temp1 = e.dest;
                temp2 = e.src;
            }
            else{
                temp1 = e.src ; 
                temp2 = e.dest;
            }
            edges[*edgeCount][0] = temp1;
            edges[*edgeCount][1] = temp2;
            (*edgeCount)++;
            *cost += e.weight;
        }
    }
}

int main() {
    // Input
    int n;
    scanf("%d", &n);  // Read the number of nodes
    
    // Read adjacency matrix
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int totalCost = 0;      // Storing the total cost of the minimum spanning tree
    int mst[MAX][2];  // Store the edges of the minimum spanning tree. 
                            // If the i-th edge is (u, v), then mst[i-1][0] = u,mst[i-1][1] = v
    int edgeCount= 0;
    findSpanningTree(n , &totalCost , &edgeCount , mst);
    // OutPut
    printf("%d", totalCost);
    for (int i = 0; i < n-1; i++) {
        printf(",(%d,%d)", mst[i][0], mst[i][1]);  
    }
    printf("\n");
    
    return 0;
}