#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "nodos.h"

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjacencyMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
    graph->adjacencyMatrix[dest][src] = 1;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void printDegrees(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                degree++;
            }
        }
        printf("Vertice %d: Grado %d\n", i, degree);
    }
}

int isRegular(Graph* graph) {
    int degree = -1;
    for (int i = 0; i < graph->numVertices; i++) {
        int currentDegree = 0;
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                currentDegree++;
            }
        }
        if (degree == -1) {
            degree = currentDegree;
        } else if (degree != currentDegree) {
            return 0;
        }
    }
    return 1;
}

int isRegularComplete(Graph* graph) {
    int degree = graph->numVertices - 1;
    for (int i = 0; i < graph->numVertices; i++) {
        int currentDegree = 0;
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                currentDegree++;
            }
        }
        if (currentDegree != degree) {
            return 0;
        }
    }
    return 1;
}

void DFS(Graph* graph, int vertex, bool visited[], int disc[], int low[], int parent[], bool ap[]) {
    static int time = 0;
    int children = 0;
    visited[vertex] = true;
    disc[vertex] = low[vertex] = ++time;

    for (int v = 0; v < graph->numVertices; v++) {
        if (graph->adjacencyMatrix[vertex][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = vertex;
                DFS(graph, v, visited, disc, low, parent, ap);

                low[vertex] = (low[vertex] < low[v]) ? low[vertex] : low[v];

                if (parent[vertex] == -1 && children > 1)
                    ap[vertex] = true;
                if (parent[vertex] != -1 && low[v] >= disc[vertex])
                    ap[vertex] = true;
            } else if (v != parent[vertex]) {
                low[vertex] = (low[vertex] < disc[v]) ? low[vertex] : disc[v];
            }
        }
    }
}

void findCutVertices(Graph* graph) {
    bool *visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    int *disc = (int*)malloc(graph->numVertices * sizeof(int));
    int *low = (int*)malloc(graph->numVertices * sizeof(int));
    int *parent = (int*)malloc(graph->numVertices * sizeof(int));
    bool *ap = (bool*)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
        visited[i] = false;
        ap[i] = false;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i])
            DFS(graph, i, visited, disc, low, parent, ap);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (ap[i])
            printf("El vertice %d es un vertice de corte\n", i);
    }

    free(visited);
    free(disc);
    free(low);
    free(parent);
    free(ap);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph);
}
