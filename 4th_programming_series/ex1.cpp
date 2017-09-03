// Dijkstra taken from http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/  


#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  
  

  
// A structure to represent a node in adjacency list  
struct Node  
{  
int dest;  
int weight;  
char valid;   
struct Node* next;  
};  
   
// A structure to represent an adjacency list  
struct AdjList  
{  
struct Node *head;  // pointer to head node of list  
};  
   
// A structure to represent a graph. A graph is an array of adjacency lists.  
// Size of array will be V (number of vertices in graph)  
struct Graph  
{  
int V;  
struct AdjList* array;  
};  
   
// A utility function to create a new adjacency list node  
struct Node* CreateNewNode(int dest, int weight)  
{  
struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));  
newNode->dest = dest;  
newNode->weight = weight;  
newNode->valid = 0;    
newNode->next = NULL;  
return newNode;  
}  
  
// A utility function that creates a graph of V vertices  
struct Graph* createGraph(int V)  
{  
    int i;  
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));  
    graph->V = V;  
   
    // Create an array of adjacency lists.  Size of array will be V  
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));  
   
     // Initialize each adjacency list as empty by making head as NULL  
    for (i = 0; i < V; ++i)  
        graph->array[i].head = NULL;  
   
    return graph;  
}  
   
// Adds an edge to an undirected graph  
void addEdge(struct Graph* graph, int src, int dest, int weight)  
{  
    // Add an edge from src to dest.  A new node is added to the adjacency  
    // list of src.  The node is added at the begining  
    struct Node* newNode = CreateNewNode(dest, weight);  
    newNode->next = graph->array[src].head;  
    graph->array[src].head = newNode;  
   
    // Since graph is undirected, add an edge from dest to src also  
    newNode = CreateNewNode(src, weight);  
    newNode->next = graph->array[dest].head;  
    graph->array[dest].head = newNode;  
}  
  
// Structure to represent a min heap node  
struct MinHeapNode  
{  
    int  v;  
    long long dist;  
};  
   
// Structure to represent a min heap  
struct MinHeap  
{  
    int size;      // Number of heap nodes present currently  
    int capacity;  // Capacity of min heap  
    int *pos;     // This is needed for decreaseKey()  
    struct MinHeapNode **array;  
};  
   
// A utility function to create a new Min Heap Node  
struct MinHeapNode* newMinHeapNode(int v, long long dist)  
{  
    struct MinHeapNode* minHeapNode =  
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));  
    minHeapNode->v = v;  
    minHeapNode->dist = dist;  
    return minHeapNode;  
}  
   
// A utility function to create a Min Heap  
struct MinHeap* createMinHeap(int capacity)  
{  
    struct MinHeap* minHeap =  
         (struct MinHeap*) malloc(sizeof(struct MinHeap));  
    minHeap->pos = (int *)malloc(capacity * sizeof(int));  
    minHeap->size = 0;  
    minHeap->capacity = capacity;  
    minHeap->array =  
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));  
    return minHeap;  
}  
  
// A utility function to swap two nodes of min heap. Needed for min heapify  
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)  
{  
    struct MinHeapNode* t = *a;  
    *a = *b;  
    *b = t;  
}  
   
// A standard function to heapify at given idx  
// This function also updates position of nodes when they are swapped.  
// Position is needed for decreaseKey()  
void minHeapify(struct MinHeap* minHeap, int idx)  
{  
    int smallest, left, right;  
    smallest = idx;  
    left = 2 * idx + 1;  
    right = 2 * idx + 2;  
   
    if (left < minHeap->size &&  
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )  
      smallest = left;  
   
    if (right < minHeap->size &&  
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )  
      smallest = right;  
   
    if (smallest != idx)  
    {  
        // The nodes to be swapped in min heap  
        struct MinHeapNode* smallestNode = minHeap->array[smallest];  
        struct MinHeapNode* idxNode = minHeap->array[idx];  
   
        // Swap positions  
        minHeap->pos[smallestNode->v] = idx;  
        minHeap->pos[idxNode->v] = smallest;  
   
        // Swap nodes  
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);  
   
        minHeapify(minHeap, smallest);  
    }  
}  
  
// A utility function to check if the given minHeap is ampty or not  
int isEmpty(struct MinHeap* minHeap)  
{  
    return minHeap->size == 0;  
}  
   
// Standard function to extract minimum node from heap  
struct MinHeapNode* extractMin(struct MinHeap* minHeap)  
{  
    if (isEmpty(minHeap))  
        return NULL;  
   
    // Store the root node  
    struct MinHeapNode* root = minHeap->array[0];  
   
    // Replace root node with last node  
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];  
    minHeap->array[0] = lastNode;  
   
    // Update position of last node  
    minHeap->pos[root->v] = minHeap->size-1;  
    minHeap->pos[lastNode->v] = 0;  
   
    // Reduce heap size and heapify root  
    --minHeap->size;  
    minHeapify(minHeap, 0);  
   
    return root;  
}  
  
// Function to decreasy dist value of a given vertex v. This function  
// uses pos[] of min heap to get the current index of node in min heap  
void decreaseKey(struct MinHeap* minHeap, int v, long long dist)  
{  
    // Get the index of v in  heap array  
    int i = minHeap->pos[v];  
   
    // Get the node and update its dist value  
    minHeap->array[i]->dist = dist;  
   
    // Travel up while the complete tree is not hepified.  
    // This is a O(Logn) loop  
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)  
    {  
        // Swap this node with its parent  
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;  
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;  
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);  
   
        // move to parent index  
        i = (i - 1) / 2;  
    }  
}  
   
// A utility function to check if a given vertex  
// 'v' is in min heap or not  
char isInMinHeap(struct MinHeap *minHeap, int v)  
{  
   if (minHeap->pos[v] < minHeap->size)  
     return 1;  
   return 0;  
}  
  
long long *H;  
  
// The main function that calulates distances of shortest paths from src to all  
// vertices. It is a O(ELogV) function  
long long dijkstra(struct Graph* graph, int src, int dest, int offset)  
{  
    int V = graph->V, v;// Get the number of vertices in graph  
    long long dist[V], res = 0, k;      // dist values used to pick minimum weight edge in cut  
   
    // minHeap represents set E  
    struct MinHeap* minHeap = createMinHeap(V);  
   
    // Initialize min heap with all vertices. dist value of all vertices   
    for (v = 0; v < V; ++v)  
    {  
        dist[v] = LLONG_MAX;  
        minHeap->array[v] = newMinHeapNode(v, dist[v]);  
        minHeap->pos[v] = v;  
    }  
   
    // Make dist value of src vertex as 0 so that it is extracted first  
    minHeap->array[src] = newMinHeapNode(src, dist[src]);  
    minHeap->pos[src]   = src;  
    dist[src] = offset;  
    decreaseKey(minHeap, src, dist[src]);  
   
    // Initially size of min heap is equal to V  
    minHeap->size = V;  
  
    // In the followin loop, min heap contains all nodes  
    // whose shortest distance is not yet finalized.  
    while (!isEmpty(minHeap))  
    {  
        // Extract the vertex with minimum distance value  
        struct MinHeapNode* minHeapNode = extractMin(minHeap);  
        int u = minHeapNode->v; // Store the extracted vertex number  
    if (u == dest){  
        res = minHeapNode->dist;  
        break;  
    }     
        // Traverse through all adjacent vertices of u (the extracted  
        // vertex) and update their distance values  
        struct Node* pCrawl = graph->array[u].head;  
        while (pCrawl != NULL)  
        {  
            int v = pCrawl->dest;  
        if (isInMinHeap(minHeap, v) && dist[u] != LLONG_MAX) {  
            if (pCrawl->valid == 0) {      
                    // If shortest distance to v is not finalized yet, and distance to v  
                    // through u is less than its previously calculated distance  
                    if (pCrawl->weight + dist[u] < dist[v]) {  
                        dist[v] = dist[u] + pCrawl->weight;  
                        // update distance value in min heap also  
                        decreaseKey(minHeap, v, dist[v]);  
                    }  
            }  
            else {  
            if (H[u] <= dist[u] && dist[u] < H[v])  
                k = H[v];   
            else if (H[v] <= dist[u] && dist[u] < H[u])  
                k = H[u];  
            else  
                k = dist[u];  
            if (pCrawl->weight + k < dist[v]) {  
                dist[v] = pCrawl->weight + k;  
                decreaseKey(minHeap, v, dist[v]);  
            }  
        }  
        }  
        pCrawl = pCrawl->next;  
        }  
    }     
    return res;  
}  
  
struct TourNode {  
    int v;  
    struct TourNode* next;  
};        
  
int main() {  
    int N , M , K;  
    long long res;  
    int T , A , B , i , u , v , c;
    struct Graph* G;  
    struct Node* temp2;  
    struct TourNode *head, *curr, *t;  
    scanf("%d %d", &N, &M);  
    scanf("%d %d %d %d", &A, &B, &T, &K);  
    H = (long long*) malloc(N*sizeof(long long));     
    head = (struct TourNode*) malloc(sizeof(struct TourNode));  
    scanf("%d", &c);  
    head->v = c - 1;  
    head->next = NULL;  
    curr = head;      
    for (i = 1; i < K; i++) {  
        scanf("%d", &c);  
        t = (struct TourNode*) malloc(sizeof(struct TourNode));  
        t->v = c - 1;  
        t->next = NULL;  
        curr->next = t;  
        curr = t;          
    }  
    G = createGraph(N);  
    for (i = 0; i < M; i++) {  
        scanf("%d %d %d", &u, &v, &c);  
        addEdge(G, u - 1, v - 1, c);      
    }  
    H[head->v] = 0;  
    for (curr = head->next, t = head; curr != NULL; curr = curr->next, t = t->next) {  
        for (temp2 = G->array[t->v].head; temp2 != NULL; temp2 = temp2->next)  
            if (temp2->dest == curr->v){  
                temp2->valid = 1;  
                H[curr->v] = H[t->v] + temp2->weight;  
                break;  
            }  
        for (temp2 = G->array[curr->v].head; temp2 != NULL; temp2 = temp2->next)  
                        if (temp2->dest == t->v){  
                               temp2->valid = 1;  
                               break;  
                        }  
    }  
    res = dijkstra(G, A - 1, B - 1, T);  
    printf("%lld\n", res - T);   
    return 0;     
}
