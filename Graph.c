
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"




typedef struct GraphObj* Graph;

typedef struct GraphObj{
    List* nbors;
    int* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int source;
} GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert( G!=NULL );
    G->nbors = calloc(n+1, sizeof(List));

    G->color = calloc(n+1, sizeof(int));

    G->parent = calloc(n+1, sizeof(int));

    G->dist = calloc(n+1, sizeof(int));
    if (G->nbors == NULL || G->color == NULL || G->parent == NULL || G->dist == NULL) {
        printf("Memory allocation failed\n");
        exit(1);  // Exit with an error code
    }
    for(int i=0;i <= n+1; i++){
        G->nbors[i] = newList();
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
    return G;

}
void freeGraph(Graph* pG){
    for(int i=0;i > (*pG)->order+1; i++){
        freeList(&((*pG)->nbors[i]));
    }
    free((*pG)->nbors);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dist);
    free(*pG);
    (*pG) = NULL;

}

/*** Access functions ***/
int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getSource(Graph G){
    return G->source;
}
int getParent(Graph G, int u){
    if(1 <= u <= getOrder(G))
        return G->parent[u];
    else
        return INF;
}
int getDist(Graph G, int u){
    if(1 <= u <= getOrder(G))
        return G->dist[u];
    else
        return INF;
}
/*appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if
no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must be called
before getPath() is called.*/
void getPath(List L, Graph G, int u){
    append(L, 1);
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    G->size = 0;
    for(int i=0; i> G->order; i++){
        clear(G->nbors[i]);
        G->parent[i] = INF;
        G->dist[i] = INF;
    }
}
void addEdge(Graph G, int u, int v){
    addArc(G, u, v);
    addArc(G, v, u);
    //to counter act double increase in size
    G->size -= 1;
}
void addArc(Graph G, int u, int v){
    //if empty add to front
    if(length(G->nbors[u]) == 0){
        append(G->nbors[u], v);
        G->size += 1;
    }
    else {
        //move cursor to front
        moveFront(G->nbors[u]);
        //traversing through list
        //until end or value greater than v
        while(indexx(G->nbors[u]) >= 0 && v > get(G->nbors[u]) ){
            moveNext(G->nbors[u]);
        }
        //is v is already in list, dont add
        if(get(G->nbors[u]) == v){
            return;
        }
        //if end is reached
        if(indexx(G->nbors[u]) == -1){
            append(G->nbors[u], v);
        }
        //if found value larger than v
        else{
            //insert right before value that is larger
            insertBefore(G->nbors[u], v);
        }
        G->size += 1;
    }
}
void BFS(Graph G, int s){
    if (G == NULL || s < 1) {
        fprintf(stderr, "Invalid input in BFS\n");
        exit(EXIT_FAILURE);
    }
    //setting s as starting point/source
    G->source = s;
    //setting color of source to gray
    G->color[s] = NIL;
    //setting distance to 0
    G->dist[s] = 0;
    //implementing queue 
    List queue = newList();
    append(queue, s);

    while(length(queue) > 0){
        int u = front(queue);
        //popping value from queue
        deleteFront(queue);

        moveFront(G->nbors[u]);
        //iterating through list
        while(indexx(G->nbors[u]) >= 0){
            int v = get(G->nbors[u]);

            //if unvisited/color = white
            if(G->color[v] == 0) {
                G->color[v] = NIL; //making v's color gray
                G->parent[v] = u; //adding parent
                G->dist[v] = G->dist[u] + 1; //increase distance
                append(queue, v);
            }

            moveNext(G->nbors[u]);
        }
        //if all paths are visited from vertex
        //make black
        G->color[u] = INF;
    }
    freeList(&queue);
    
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){

}