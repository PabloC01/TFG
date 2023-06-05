// Pablo Cantón Ruiz - TFG

#include <climits>
#include <vector>

#include "BF.h"

using namespace std;

// Implementación del algoritmo de Bellman-Ford
bool BF(Grafo G, int ini, vector<vector<int> > &padre){
    // Vector para almacenar la distancia actual de cada nodo
    vector<int> distancia (G.n_nodos, INT_MAX - 1000000); // restamos una cantidad al límite para evitar overflow

    distancia[ini] = 0;

    for(int i=0; i<G.n_nodos-1; i++)
        for(int j=0; j<G.n_nodos; j++)
            for(int k=0; k<G.lista[j].size(); k++){
                if (G.lista[j][k] != ini){
                    if(distancia[G.lista[j][k]] > distancia[j]+G.matriz[j][G.lista[j][k]]){

                        distancia[G.lista[j][k]] = distancia[j]+G.matriz[j][G.lista[j][k]];

                        padre[G.lista[j][k]].clear();
                        padre[G.lista[j][k]].push_back(j);
                    }
                }
            }
    
    for(int i=0; i<G.n_nodos; i++)
        for(int j=0; j<G.lista[i].size(); j++)
            if(distancia[G.lista[i][j]] > distancia[i]+G.matriz[i][G.lista[i][j]])
                return false;
    
    return true;
}