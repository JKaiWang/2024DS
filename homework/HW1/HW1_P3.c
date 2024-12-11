#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int queue[MAX];
int front=0;
int rear =0;

void Enqueue(int value){
    queue[rear++ ] = value;
}

int Dequeue(){
    return queue[front++];
}

int isEmpty(){
    if(front == rear){
        front = rear =0;
        return 1;
    }
    else{
        return 0;
    }
}

void BFS(int m , int A[m][m]){
    int visited[MAX] ={0};
    int traveledOrdered[MAX] , orderIndex =0;

    Enqueue(1);
    visited[1] = 1;

    while(!isEmpty()){
        int temp = Dequeue();
        traveledOrdered[orderIndex++] = temp;

        for(int i=2 ; i<=m ; i++){
            if(A[temp-1][i-1] == 1 && !visited[i]){
                Enqueue(i);
                visited[i] = 1;
            }
        }
        
    }

    for(int i=0 ; i<orderIndex ; i++){
        printf("%d ", traveledOrdered[i]);
    }
    printf("\n");
}

int main(){
    int size;
    scanf("%d" , &size);

    int array[size][size];

    for(int i=0 ; i<size ; i++){
        for(int j=0 ; j<size ; j++){
            scanf("%d" , &array[i][j]);
        }
    }

    BFS(size , array);

    return 0;
}
