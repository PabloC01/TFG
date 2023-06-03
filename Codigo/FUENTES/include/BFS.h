// Pablo Cantón Ruiz - TFG

#ifndef BFS_H
#define BFS_H

#include "Grafos.h"

using namespace std;

// Implementación del algoritmo BFS
bool BFS(Grafo G, int ini, int fin, vector<vector<int> > &padre);

// Implementación del algoritmos BFS para cálculo de componentes conexas
int BFS_conexas(Grafo G);

#endif