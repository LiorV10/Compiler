// Graph.h

#define _GRAPH_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

typedef struct
{
    void *info;
    CircularLinearLinkedListNode *edgesManager;
} Vertex;

typedef struct
{
    void *weight;
    Vertex *dest;
} Edge;

typedef struct
{
    CircularLinearLinkedListNode *verticesManager;
    BOOL (*Comapre)
    (void *, void *);
} Graph;

void InitGraph(Graph *graph, BOOL (*Compare)(void *, void *))
{
    InitLinearLinkedList(&graph->verticesManager);
    graph->Comapre = Compare;
}

Vertex *AddVertex(Graph *graph, void *info)
{
    Vertex *newVertex = malloc(sizeof(Vertex));
    InitLinearLinkedList(&newVertex->edgesManager);

    !graph->verticesManager ? 
        InsertLastCircularLinearLinkedList(&graph->verticesManager) :
        InsertEndCircularLinearLinkedList(&graph->verticesManager);

    newVertex->info = info;
    graph->verticesManager->info = newVertex;

    return (newVertex);
}

Vertex *FindVertex(Graph *graph, void *vertex)
{
    CircularLinearLinkedListNode *ptr = graph->verticesManager;

    do
    {
        ptr = ptr->nextNode;
    }
    while (ptr != graph->verticesManager && !graph->Comapre(((Vertex *)ptr->info)->info, vertex));

    return (ptr ? ptr->info : NULL);
}

CircularLinearLinkedListNode *Adjacents(Graph *graph, void *vertex)
{
    return (FindVertex(graph, vertex)->edgesManager);
}

void JoinWeight(Graph *graph, Vertex *source, Vertex *dest, void *weight)
{
    Edge *newEdge = malloc(sizeof(Edge));
    // Vertex *source = FindVertex(graph, sourceVertex);

    !source->edgesManager ? 
        InsertLastCircularLinearLinkedList(&source->edgesManager) :
        InsertEndCircularLinearLinkedList(&source->edgesManager);

    newEdge->dest = dest; // FindVertex(graph, destVertex);
    newEdge->weight = weight;
    source->edgesManager->info = newEdge;
}

// void JoinWeight_(Graph *graph, void *sourceVertex, void *destVertex, void *weight)
// {
//     Edge *newEdge = malloc(sizeof(Edge));
//     Vertex *source = FindVertex(graph, sourceVertex);

//     source->edgesManager ? 
//         InsertLastCircularLinearLinkedList(&source->edgesManager) :
//         InsertEndCircularLinearLinkedList(&source->edgesManager);

//     newEdge->dest = FindVertex(graph, destVertex);
//     newEdge->weight = weight;
//     source->edgesManager->info = newEdge;
// }
// --------------------------------------------------------------------------- //

#define DEFINE_GRAPH(WEIGHT_TYPE, VERTEX_TYPE, VERTICES_NUM, COMPARATOR)     \
    typedef VERTEX_TYPE VertexType;                                          \
    typedef WEIGHT_TYPE WeightType;                                          \
    typedef struct                                                           \
    {                                                                        \
        BOOL isExists;                                                       \
        WeightType weight;                                                   \
    } Weight;                                                                \
                                                                             \
    typedef struct                                                           \
    {                                                                        \
        unsigned short verticesNum;                                          \
        Weight adjacencyMatrix[VERTICES_NUM][VERTICES_NUM];                  \
        VertexType *vertices;                                                \
    } Graph;                                                                 \
                                                                             \
    void InitGraph(Graph *graph, VertexType *vertices)                       \
    {                                                                        \
        *graph = (Graph){                                                    \
            .adjacencyMatrix = {ZERO},                                       \
            .verticesNum = VERTICES_NUM,                                     \
            .vertices = vertices};                                           \
    }                                                                        \
                                                                             \
    unsigned short FindVertexOffset(Graph *graph, VertexType info)           \
    {                                                                        \
        unsigned short offset = ZERO;                                        \
                                                                             \
        while (!COMPARATOR(info, graph->vertices[offset++]))                 \
            ;                                                                \
                                                                             \
        return (--offset);                                                   \
    }                                                                        \
                                                                             \
    VertexType FindVertex(Graph *graph, unsigned offset)                     \
    {                                                                        \
        return graph->vertices[offset];                                      \
    }                                                                        \
                                                                             \
    void Join(Graph *graph, VertexType first, VertexType second)             \
    {                                                                        \
        unsigned short firstOffset = FindVertexOffset(graph, first);         \
        unsigned short secondOffset = FindVertexOffset(graph, second);       \
                                                                             \
        graph->adjacencyMatrix[firstOffset][secondOffset].isExists = TRUE;   \
    }                                                                        \
                                                                             \
    void JoinWeight(Graph *graph, VertexType first, VertexType second,       \
                    WEIGHT_TYPE weight)                                      \
    {                                                                        \
        unsigned short firstOffset = FindVertexOffset(graph, first);         \
        unsigned short secondOffset = FindVertexOffset(graph, second);       \
                                                                             \
        graph->adjacencyMatrix[firstOffset][secondOffset].isExists = TRUE;   \
        graph->adjacencyMatrix[firstOffset][secondOffset].weight = weight;   \
    }                                                                        \
                                                                             \
    void RemoveEdge(Graph *graph, VertexType first, VertexType second)       \
    {                                                                        \
        unsigned short firstOffset = FindVertexOffset(graph, first);         \
        unsigned short secondOffset = FindVertexOffset(graph, second);       \
                                                                             \
        graph->adjacencyMatrix[firstOffset][secondOffset].isExists = FALSE;  \
    }                                                                        \
                                                                             \
    BOOL IsAdjacent(Graph *graph, VertexType first, VertexType second)       \
    {                                                                        \
        unsigned short firstOffset = FindVertexOffset(graph, first);         \
        unsigned short secondOffset = FindVertexOffset(graph, second);       \
                                                                             \
        return (graph->adjacencyMatrix[firstOffset][secondOffset].isExists); \
    }