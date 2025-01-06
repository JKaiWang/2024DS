#include<stdio.h>
#define MAX 30
typedef struct edge{
    int u,v,weight;
} edge;
typedef struct edge_list{
    edge data[MAX];
    int n;
} edgeList;
edgeList elist;
int Graph[MAX][MAX] , n;
edgeList spanlist;

void kruskai(){
    int belongs[MAX] 

}