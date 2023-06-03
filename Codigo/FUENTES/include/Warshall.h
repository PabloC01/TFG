// Pablo Cantón Ruiz - TFG

#ifndef WARSHALL_H
#define WARSHALL_H

#include "Grafos.h"

using namespace std;

// Función para mostrar un camino a partir de la matriz de predecesores
void Mostrar_Camino(vector<vector<int> > &Pi, int i, int j);

// Función para mostrar una matriz
void Mostrar_Matriz(vector<vector<int> > &L);
void Mostrar_Matriz(vector<vector<bool> > &L);

// Implementación del proceso de extender caminos mínimos
vector<vector<int> > Extender_Caminos_Minimos(vector<vector<int> > &L, vector<vector<int> > &d);

// Implementación de los algoritmos de cálculo de caminos mínimos entre todas las parejas de nodos
vector<vector<int> > Caminos_Minimos_Todas_Parejas_Lento(vector<vector<int> > &d);
vector<vector<int> > Caminos_Minimos_Todas_Parejas_Rapido(vector<vector<int> > &d);

// Implementación del algoritmo Floyd-Warshall
pair<vector<vector<int> >, vector<vector<int> > > Floyd_Warshall(Grafo G);

// Implementación del algoritmo de clausura transitiva
vector<vector<bool> > Clausura_Transitiva(Grafo G);

#endif