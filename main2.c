//codigo basico de calculo de grafos con representacion grafica del grafo 
//compilacion           gcc main2.c src/nodos.c -o graph -lgdi32 -luser32
//ejecucion             graph.exe

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "src/nodos.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Función para dibujar el grafo usando GDI
void drawGraphGDI(HDC hdc, Graph* graph) {
    int centerX = 320, centerY = 240;
    int radius = 100;
    int vertexX[graph->numVertices];
    int vertexY[graph->numVertices];

    // Calcular la posición de los vértices en un círculo
    for (int i = 0; i < graph->numVertices; i++) {
        double angle = 2.0 * M_PI * i / graph->numVertices;
        vertexX[i] = centerX + radius * cos(angle);
        vertexY[i] = centerY + radius * sin(angle);
    }

    // Dibujar aristas
    HPEN hPenOld;
    HPEN hLinePen;
    COLORREF qLineColor;
    qLineColor = RGB(0, 0, 0);
    hLinePen = CreatePen(PS_SOLID, 2, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = i + 1; j < graph->numVertices; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                MoveToEx(hdc, vertexX[i], vertexY[i], NULL);
                LineTo(hdc, vertexX[j], vertexY[j]);
            }
        }
    }

    SelectObject(hdc, hPenOld);
    DeleteObject(hLinePen);

    // Dibujar vértices
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

    for (int i = 0; i < graph->numVertices; i++) {
        Ellipse(hdc, vertexX[i] - 5, vertexY[i] - 5, vertexX[i] + 5, vertexY[i] + 5);
    }

    SelectObject(hdc, hBrushOld);
    DeleteObject(hBrush);
}

// Función de ventana para manejar eventos
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Llamada a la función que dibuja el grafo
            Graph* graph = (Graph*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (graph != NULL) {
                drawGraphGDI(hdc, graph);
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    int numVertices, numEdges, src, dest;

    printf("Ingrese el numero de vertices: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);

    printf("Ingrese el numero de aristas: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Ingrese la arista %d (formato: src dest): ", i + 1);
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

    // Crear una ventana de Windows
    const char CLASS_NAME[] = "GrafoWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Grafo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)graph);

    ShowWindow(hwnd, SW_SHOW);

    // Bucle de mensajes de Windows
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    freeGraph(graph);

    return 0;
}
