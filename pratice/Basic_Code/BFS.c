#include<stdio.h>
#include<stdlib.h> 
#define MAX 5
int queue[100];
int front = -1; int rear = -1;

void BFS(int graph[MAX][MAX] , int visited[MAX] , int start , int n){
    queue[++rear] = start;
    visited[start] = 1;
    while(front < rear){
        int temp = queue[++front];
        printf("%d " , temp);
        for(int i=0 ; i<n ; i++){
            if(graph[temp][i] == 1 && !visited[i]){
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}
int main() {
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int visited[MAX] = {0};  // 初始化為未訪問
    int n = 5;               // 節點數量

    printf("BFS Traversal starting from node 0:\n");
    BFS(graph, visited, 0, n);

    return 0;
}