// 按权合并
void unionByWeight(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);

    if (rootI != rootJ) {
        if (size[rootI] < size[rootJ]) {
            parent[rootI] = rootJ;
            size[rootJ] += size[rootI];
        } else {
            parent[rootJ] = rootI;
            size[rootI] += size[rootJ];
        }
    }
}

// Kruskal算法
void kreskal(struct Heap* heap, int n) {
    int resultCount = 0;
    Edge result[100];
    numEdge = 0;

    while (numEdge < n - 1 && !Empty(heap)) {
        Edge minEdge = DeleteMin(heap);
        int rootU = find(minEdge.u);
        int rootV = find(minEdge.v);

        if (rootU != rootV) {
            result[resultCount++] = minEdge;
            unionByWeight(minEdge.u, minEdge.v);
            numEdge++;
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < resultCount; i++) {
        printf("%d -- %d == %d\n", result[i].u, result[i].v, result[i].weight);
    }
}

int main() {
    struct Heap heap;
    heap.num = 0;
    
    int n, m;  // n 为节点数量，m 为边数量
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);
    
    initialize(n);
    
    printf("Enter edges (u, v, weight):\n");
    for (int i = 0; i < m; i++) {
        Edge edge;
        scanf("%d %d %d", &edge.u, &edge.v, &edge.weight);
        Insert(&heap, edge);
    }
    
    kreskal(&heap, n);
    
    return 0;
}