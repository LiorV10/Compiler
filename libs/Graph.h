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
    unsigned short info;
    BOOL isAccepting;
    BOOL visited;
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
} Graph;

void InitGraph(Graph *graph)
{
    InitLinearLinkedList(&graph->verticesManager);
}

Vertex *AddVertex(Graph *graph, void *info, BOOL isAccepting)
{
    Vertex *newVertex = malloc(sizeof(Vertex));
    InitLinearLinkedList(&newVertex->edgesManager);

    !graph->verticesManager ? 
        InsertLastCircularLinearLinkedList(&graph->verticesManager) :
        InsertEndCircularLinearLinkedList(&graph->verticesManager);

    newVertex->info = info;
    newVertex->isAccepting = isAccepting;
    newVertex->visited = FALSE;
    
    graph->verticesManager->info = newVertex;

    return (newVertex);
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