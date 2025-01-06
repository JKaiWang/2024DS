#include<stdio.h>
#include<stdlib.h>

typedef struct unionSet{
    int *parent;
    int *rank;
    int n;
} Set;

Set* createSet(int n){
    Set* set = (Set*)malloc(sizeof(Set));
    set->parent = (int*)malloc(sizeof(int)*n);
    set->rank = (int*)malloc(sizeof(int) * n);
    set->n  = n;
    for(int i=0 ; i<n ; i++){
        set->parent[i]= 0;
        set->rank[i] = 0; 
    }
    return set;
}

int find(Set* set , int x){
    if(set->parent[x] != x){
        set->parent[x] = find(set , set->parent[x]);
    }
    return set->parent[x];
}

void unionSets(Set* set , int x , int y){
    int rootX = find(set, x);
    int rootY = find(set , y);
    if(rootX == rootY) return ;
    if(set->rank[rootX] > set->rank[rootY]){
        set->parent[rootY] = rootX;
    }
    else if(set->rank[rootX] < set->rank[rootY]){
        set->parent[rootX] = rootY;
    }else{
        set->parent[rootY] = rootX;
        set->rank[rootX]++;
    }
}

void printUnionStructure(Set* set){
    printf("Element -> root\n");
    for(int i=0 ; i<set->n ; i++){
        printf("#d->%d\n" , i , find(set , i));
    }
}

int main(){
    int n= 10 ;
    Set* set = createSet(n);

    unionSets(set, 0, 1);
    unionSets(set, 1, 2);
    unionSets(set, 3, 4);
    unionSets(set, 4, 5);
    unionSets(set, 6, 7);
    unionSets(set, 7, 8);
    unionSets(set, 8, 9);
    printf("Find(2): %d\n", find(set, 2));
    printf("Find(5): %d\n", find(set, 5));
    printf("Find(9): %d\n", find(set, 9));

    // Print the set structure
    printf("\nDisjoint Set Structure:\n");
    printUnionStructure(set);

    // Free allocated memory
    free(set->parent);
    free(set->rank);
    free(set);

    return 0;
}