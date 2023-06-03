// Pablo Cantón Ruiz - TFG

#include <climits>
#include <queue>
#include <vector>
#include <set>

#include "BFS.h"

using namespace std;

// Implementación del algoritmo de búsqueda en anchura BFS
bool BFS(Grafo G, int ini, int fin, vector<vector<int> > &padre){
    // Vectores para almacenar distancia actual y estado de exploración de los nodos
    vector<bool> explorado (G.n_nodos, false);
    vector<int> distancia (G.n_nodos, INT_MAX);

    distancia[ini] = 0;
    queue<int> Q;
    Q.push(ini);
    while(!Q.empty()){
        // Sacamos el primer elemento de la cola y los eliminamos
        int u = Q.front();
        Q.pop();

        if(!explorado[u]){
            if(u == fin)
                return true;
            
            for(int i=0; i<G.lista[u].size(); i++){
                if(!explorado[G.lista[u][i]])
                    if(distancia[G.lista[u][i]] >= distancia[u]+1){
                        distancia[G.lista[u][i]] = distancia[u]+1;
                        padre[G.lista[u][i]].push_back(u);
                        Q.push(G.lista[u][i]);
                    }
                explorado[u] = true;
            }
        }
    }

    return false;
}

// Implementación del algoritmo de cálculo de componentes conexas con BFS
int BFS_conexas(Grafo G){
    int conexas = 0;
    vector<bool> explorado (G.n_nodos, false);
    set<int> N;
    for(int i=0; i<G.n_nodos; i++)
        N.insert(i);

    while(!N.empty()){
        conexas++;
        auto it = N.begin();
        int u = *it;
        N.erase(it);
        explorado[u] = true;
        queue<int> Q;
        Q.push(u);
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();

            for(int i=0; i<G.lista[u].size(); i++){
                if(!explorado[G.lista[u][i]]){
                    Q.push(G.lista[u][i]);
                    explorado[G.lista[u][i]] = true;
                    N.erase(G.lista[u][i]);
                }
            }
        }
    }

    return conexas;
}