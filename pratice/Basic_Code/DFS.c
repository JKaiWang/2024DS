#include<stdio.h>
#include<stdlib.h>
#define MAX 5
void DFS(int matrix[MAX][MAX] , int visited[MAX]  , int start , int n){
    printf("%d " , start);
    visited[start] = 1;
    for(int i=0 ; i< n ; i++){
        if(matrix[start][i] == 1 && !visited[i]){
            //printf("%d " , i);
            DFS(matrix, visited , i , n);
        }
    }
}

int main(){
    int graph[MAX][MAX]={
    {0,1,1,0,0},
    {1,0,1,1,0},
    {1,1,0,1,1},
    {0,1,1,0,1},
    {0,0,1,1,0}};
    int visited[MAX] = {0};
    DFS(graph , visited , 0 , MAX);
}