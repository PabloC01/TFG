// Pablo Cantón Ruiz - TFG

#include <climits>
#include <queue>
#include <vector>

#include "DJK.h"

using namespace std;

// Comparador para la priority_queue
class comparador{
    vector<int>* distancia;
    public:
        comparador(vector <int>* dist){
            distancia = dist;
        }
        bool operator() (const int& lhs, const int& rhs) const {
            return (*distancia)[lhs]>(*distancia)[rhs];
        }
};

// Implementación del algoritmo de Dijkstra
bool DJK(Grafo G, int ini, int fin, vector<vector<int> > &padre){
    vector<bool> explorado (G.n_nodos, false);
    vector<int> distancia (G.n_nodos, INT_MAX);

    distancia[ini] = 0;
    priority_queue<int, vector<int>, comparador> Q(&distancia);
    Q.push(ini);
    while(!Q.empty()){
        int u = Q.top();
        Q.pop();

        if(!explorado[u]){
            if(u == fin)
                return true;
            
            for(int i=0; i<G.lista[u].size(); i++){
                if(!explorado[G.lista[u][i]])
                    if(distancia[G.lista[u][i]] > distancia[u]+G.matriz[u][G.lista[u][i]]){
                        distancia[G.lista[u][i]] = distancia[u]+G.matriz[u][G.lista[u][i]];
                        padre[G.lista[u][i]].clear();
                        padre[G.lista[u][i]].push_back(u);
                        Q.push(G.lista[u][i]);
                    }
                    else if(distancia[G.lista[u][i]] == distancia[u]+G.matriz[u][G.lista[u][i]]){
                        padre[G.lista[u][i]].push_back(u);
                        Q.push(G.lista[u][i]);
                    }
                        
                explorado[u] = true;
            }
        }
    }

    return false;
}