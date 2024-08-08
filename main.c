//codigo basico de calculo de grafos
//compilacion           gcc main2.c src/nodos.c -o graph -lgdi32 -luser32
//ejecucion             graph.exe

#include <stdio.h>
#include <stdlib.h>
#include "src/nodos.h"

int main() {
    int numVertices, numEdges, src, dest;

    printf("Ingrese el numero de vertices: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);

    printf("Ingrese el numero de aristas: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Ingrese la arista %d (formato: origen destino): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Matriz de adyacencia:\n");
    printGraph(graph);

    printf("\nGrados:\n");
    printDegrees(graph);

    printf("\nEl grafo es regular? %s\n", isRegular(graph) ? "Si" : "No");
    printf("El grafo es regular completo? %s\n", isRegularComplete(graph) ? "Si" : "No");

    printf("\nPuntos de corte:\n");
    findCutVertices(graph);

    freeGraph(graph);

    return 0;
}

