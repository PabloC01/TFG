// Pablo Cantón Ruiz - TFG

#include <iostream>
#include <chrono>
#include <vector>
#include <random>

#include "Grafos.h"
#include "BFS.h"
#include "DJK.h"
#include "BF.h"
#include "Warshall.h"

using namespace std;

int main(int argc, char** argv){
    if(argc != 4){
        cerr << "Fallo de parámetros, [-BFS | -DJK | -BF | -MatS | -MatF | -FW | -CT] [número de nodos] [densidad]" << endl;
        exit(1);
    }

    int n_nodos = atoi(argv[2]);
    float densidad = atof(argv[3]);

    Grafo grafo;
    int n_inicial, n_final;
    int n_iter = 10;

    n_inicial = rand() % n_nodos;
    n_final = rand() % n_nodos;

    while(n_inicial == n_final)
        n_final = rand() % n_nodos;

    if(string(argv[1]) == "-BFS"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            vector<vector<int> > padres(grafo.n_nodos, vector<int>());
            auto momentoInicio = clock();
            bool camino = BFS(grafo, n_inicial, n_final, padres);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-DJK"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            vector<vector<int> > padres(grafo.n_nodos, vector<int>());
            auto momentoInicio = clock();
            bool camino = DJK(grafo, n_inicial, n_final, padres);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-BF"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            vector<vector<int> > padres(grafo.n_nodos, vector<int>());
            auto momentoInicio = clock();
            bool no_ciclo_neg = BF(grafo, n_inicial, padres);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-MatS"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            auto momentoInicio = clock();
            vector<vector<int> > res = Caminos_Minimos_Todas_Parejas_Lento(grafo.matriz);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-MatF"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            auto momentoInicio = clock();
            vector<vector<int> > res = Caminos_Minimos_Todas_Parejas_Rapido(grafo.matriz);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-FW"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            auto momentoInicio = clock();
            auto res = Floyd_Warshall(grafo);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else if(string(argv[1]) == "-CT"){
        float avg = 0;
        for(int i=0; i<n_iter; i++){
            grafo = grafo_aleatorio(n_nodos, densidad, i, false, false);
            auto momentoInicio = clock();
            auto sol = Clausura_Transitiva(grafo);
            auto momentoFin = clock();

            avg += 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        }
        cout << avg/n_iter << endl;
    }
    else{
        cerr << "Fallo de parámetros, [-BFS | -DJK | -BF | -MatS | -MatF | -FW | -CT] [número de nodos] [densidad]" << endl;
        exit(1);
    }

    return 0;
}