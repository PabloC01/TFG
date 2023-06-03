// Pablo Cantón Ruiz - TFG

#ifndef GRAFOS_H
#define GRAFOS_H

#include <vector>

using namespace std;

// Función que crea y devuelve la lista de adyacencia de un grafo a partir de la matriz de adyacencia
vector<vector<int> > matriz_a_lista(vector<vector<int> > matriz);

// Clase para representar un grafo
class Grafo{
    public:
        vector<vector<int> > matriz;
        vector<vector<int> > lista;
        int n_nodos;
        bool ponderado;
        bool dirigido;
        int min;
        int max;

        Grafo();
        Grafo(vector<vector<int> > mat, int num_nodos, bool peso, bool dir, int m, int M);
        Grafo(char* path);
        void mostrar_grafo();
};

// Funciones para generar grafos aleatorios
Grafo grafo_aleatorio(int n_nodos, float densidad, int semilla, bool dirigido, bool ponderado, int min, int max);
Grafo grafo_aleatorio(int n_nodos, float densidad, int semilla, bool dirigido, bool ponderado);

#endif