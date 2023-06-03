// Pablo Cantón Ruiz - TFG

#include <vector>
#include <random>
#include <iostream>
#include <fstream>

#include "Grafos.h"

using namespace std;

vector<vector<int> > matriz_a_lista(vector<vector<int> > matriz){
    vector<vector<int> > lista;
    for(int i=0; i<matriz.size(); i++){
        vector<int> aux;
        for(int j=0; j<matriz[i].size(); j++){
            if(matriz[i][j] != 0)
                aux.push_back(j);
        }
        lista.push_back(aux);
    }

    return lista;
}

Grafo::Grafo(){
    matriz = vector<vector<int> >();
    lista = vector<vector<int> >();
    n_nodos = 0;
    pesos = false;
    dirigido = false;
    min = 0;
    max = 0;
}

Grafo::Grafo(vector<vector<int> > mat, int num_nodos, bool peso, bool dir, int m, int M){
    matriz = mat;
    n_nodos = num_nodos;
    lista = matriz_a_lista(matriz);
    pesos = peso;
    dirigido = dir;
    min = m;
    max = M;
}

Grafo::Grafo(char* path){
    ifstream fin (path);

    if(!fin.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    fin >> n_nodos >> pesos >> dirigido >> min >> max;

    matriz = vector<vector<int> >(n_nodos, vector<int>(n_nodos, 0));

    for(int i=0; i<n_nodos; i++)
        for(int j=0; j<n_nodos; j++)
            fin >> matriz[i][j];

    lista = matriz_a_lista(matriz);
}

void Grafo::mostrar_grafo(){
    cout << "Número de nodos: " << n_nodos << ".\n";
    cout << "Matriz de adyacencia:\n";

    cout << "   ";
    for(int i=0; i<n_nodos; i++)
        cout << i << "  ";
    cout << endl;

    for(int i=0; i<n_nodos; i++){
        cout << i << " ";
        for(int j=0; j<n_nodos; j++){
            if(matriz[i][j] < 0)
                cout << "-" << -matriz[i][j] << " ";
            else
                cout << " " << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

Grafo grafo_aleatorio(int n_nodos, float densidad, int semilla, bool dirigido, bool pesos, int min, int max){
    int n_aristas = n_nodos*(n_nodos - 1)*densidad;

    srand(semilla);

    // Si no es dirigido hacemos una matriz triangular con la mitad de aristas
    if(!dirigido)
        n_aristas = n_aristas/2;

    vector<vector<int> > matriz(n_nodos, vector<int> (n_nodos, 0));

    int cont = 0;
    while(cont < n_aristas){
        int i = rand() % n_nodos;
        int j = rand() % n_nodos;

        while(i==j)
            j = rand() % n_nodos;

        int valor = 1;
        if(pesos)
            do{
                valor = min+rand()%(max+1-min);
            } while(valor == 0);

        if(matriz[i][j]==0 && (dirigido || (i<j  && !dirigido))){ // Si no es dirigido la hacemos triangular
            matriz[i][j] = valor;
            cont++;
        }
    }

    if(!dirigido){
        for(int i=0; i<n_nodos; i++){
            for(int j=0; j<i; j++){
                matriz[i][j]=matriz[j][i];
            }
        }
    }

    return Grafo(matriz, n_nodos, pesos, dirigido, min, max);
}

Grafo grafo_aleatorio(int n_nodos, float densidad, int semilla, bool dirigido, bool pesos){
    return grafo_aleatorio(n_nodos, densidad, semilla, dirigido, pesos, 1, 1);
}