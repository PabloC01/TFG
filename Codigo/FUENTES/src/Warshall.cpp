// Pablo Cantón Ruiz - TFG

#include <vector>
#include <iostream>

#include "Warshall.h"

using namespace std;

// Constante que actuará de infinito
const int MAX = 1000000;

// Implementación de la función para mostrar un camino a partir de la matriz de predecesores
void Mostrar_Camino(vector<vector<int> > &Pi, int i, int j){
    if(i==j)
        cout << i;
    else if(Pi[i][j] == -1)
        cout << "No existe camino entre " << i << " y " << j;
    else{
        Mostrar_Camino(Pi, i, Pi[i][j]);
        cout << " -> " << j;
    }
}

// Implementación de la función para mostrar una matriz de enteros
void Mostrar_Matriz(vector<vector<int> > &L){
    int n = L.size();

    cout << "   ";
    for(int i=0; i<n; i++)
        cout << i << "  ";
    cout << endl;

    for(int i=0; i<n; i++){
        cout << i << " ";
        for(int j=0; j<n; j++){
            if(L[i][j] == MAX)
                cout << " / ";
            else{
                if(L[i][j]<0)
                    cout << "-" << -L[i][j] << " ";
                else
                    cout << " " << L[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Implementación de la función para mostrar una matriz de booleanos
void Mostrar_Matriz(vector<vector<bool> > &L){
    int n = L.size();

    cout << "  ";
    for(int i=0; i<n; i++)
        cout << i << " ";
    cout << endl;

    for(int i=0; i<n; i++){
        cout << i << " ";
        for(int j=0; j<n; j++)
            cout << L[i][j] << " ";
        cout << endl;
    }
}

// Implementación del algoritmo para extender caminos mínimos
vector<vector<int> > Extender_Caminos_Minimos(vector<vector<int> > &L, vector<vector<int> > &d){
    int n = L.size();
    vector<vector<int> > L_res(n, vector<int>(n, 0));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(i!=j)
                L_res[i][j] = MAX;
            for(int k=0; k<n; k++){
                if(d[k][j] != 0 && L[i][k] != MAX){
                    if(L_res[i][j] == MAX)
                        L_res[i][j] = L[i][k] + d[k][j];
                    else
                        L_res[i][j] = min(L_res[i][j], L[i][k] + d[k][j]);
                }
            }
        }
    
    return L_res;
}

// Implementación del algoritmo de cálculo de caminos mínimo lento
vector<vector<int> > Caminos_Minimos_Todas_Parejas_Lento(vector<vector<int> > &d){
    int n = d.size();

    // Creamos la matriz L como una matriz con todo infinito, y luego añadimos elementos de d y la diagonal a 0
    vector<vector<int> > L(n, vector<int>(n, MAX));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(i == j)
                L[i][j] = 0;
            if(d[i][j] != 0)
                L[i][j] = d[i][j];
        }

    for(int i=1; i<n-1; i++)
        L = Extender_Caminos_Minimos(L, d);
    
    return L;
}

// Implementación del algoritmo de cálculo de caminos mínimo rápido
vector<vector<int> > Caminos_Minimos_Todas_Parejas_Rapido(vector<vector<int> > &d){
    int n = d.size();

    // Creamos la matriz L como una matriz con todo infinito, y luego añadimos elementos de d y la diagonal a 0
    vector<vector<int> > L(n, vector<int>(n, MAX));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(i == j)
                L[i][j] = 0;
            if(d[i][j] != 0)
                L[i][j] = d[i][j];
        }

    int m = 1;
    while(m < n - 1){
        L = Extender_Caminos_Minimos(L, L);
        m = m*2;
    }
    
    return L;
}

// Implementación del algoritmo de Floyd-Warshall
pair<vector<vector<int> >, vector<vector<int> > > Floyd_Warshall(Grafo G){
    int n = G.matriz.size();

    // Construimos las matrices D y Pi, para Pi usaremos -1 como infinito, pues no puede haber números negativos en dicha matriz
    vector<vector<int> > D(n, vector<int>(n, MAX));
    vector<vector<int> > Pi(n, vector<int>(n, -1));

    for(int i=0; i<n; i++){
        D[i][i] = 0;
        for(int j=0; j<G.lista[i].size(); j++){
            D[i][G.lista[i][j]] = G.matriz[i][G.lista[i][j]];
            Pi[i][G.lista[i][j]] = i;
        }
    }
    
    for(int k=0; k<n; k++){
        vector<vector<int> > D_aux(n, vector<int>(n, 0));
        vector<vector<int> > Pi_aux(n, vector<int>(n, 0));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++){
                if(D[i][j] <= D[i][k] + D[k][j]){
                    D_aux[i][j] = D[i][j];
                    Pi_aux[i][j] = Pi[i][j];
                }
                else {
                    D_aux[i][j] = D[i][k] + D[k][j];
                    Pi_aux[i][j] = Pi[k][j];
                }
            }
        D = D_aux;
        Pi = Pi_aux;
    }

    return pair<vector<vector<int> >, vector<vector<int> > > (D, Pi);
}

// Implementación del algoritmo de la clausura transitiva
vector<vector<bool> > Clausura_Transitiva(Grafo G){
    int n = G.matriz.size();

    vector<vector<bool> > T(n, vector<bool>(n, false));

    for(int i=0; i<n; i++){
        T[i][i] = true;
        for(int j=0; j<G.lista[i].size(); j++)
            T[i][G.lista[i][j]] = true;
    }
    
    for(int k=0; k<n; k++){
        vector<vector<bool> > T_aux(n, vector<bool>(n, false));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                T_aux[i][j] = T[i][j] || (T[i][k] && T[k][j]);
        T = T_aux;
    }

    return T;
}