// src/nodos.h

#ifndef NODOS_H
#define NODOS_H

typedef struct {
    int** adjacencyMatrix;
    int numVertices;
} Graph;

Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void printDegrees(Graph* graph);
int isRegular(Graph* graph);
int isRegularComplete(Graph* graph);
void findCutVertices(Graph* graph);
void freeGraph(Graph* graph);

#endif // NODOS_H
