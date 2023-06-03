// Pablo Cantón Ruiz - TFG

#include <iostream>
#include <chrono>
#include <vector>

#include "Grafos.h"
#include "BFS.h"
#include "DJK.h"
#include "BF.h"
#include "Warshall.h"

using namespace std;

// Función para comprobar los parámetros de entrada
void check_params(int argc, char** argv);

// Función para mostrar los caminos encontrados a partir de los padres calculados
void mostrar_caminos(vector<vector<int> > &padres, int n_final);
void mostrar_caminos_rec(vector<vector<int> > &padres, string camino, int actual);

// Función para calcular el coste de un camino
int coste(Grafo grafo, vector<vector<int> > &padres, int n_final);

int main(int argc, char** argv){
    check_params(argc, argv);

    Grafo grafo;
    int n_inicial, n_final;

    if(argc == 2){
        grafo = Grafo(argv[1]);
    }
    else{
        int n_nodos = atoi(argv[1]);

        bool dirigido;
        if(string(argv[4]) == "si")
            dirigido=true;
        else
            dirigido=false;

        bool ponderado;
        if(string(argv[5]) == "si")
            ponderado=true;
        else
            ponderado=false;

        int min = 1;
        int max = 1;

        if(ponderado){
            cout << "Introduce el valor mínimo para los pesos:\n";
            cin >> min;

            cout << "Introduce el valor máximo para los pesos:\n";
            do{
                cin >> max;
            } while(max < min);

            grafo = grafo_aleatorio(n_nodos, atof(argv[2]), atoi(argv[3]), dirigido, ponderado, min, max);
        }
        else
            grafo = grafo_aleatorio(n_nodos, atof(argv[2]), atoi(argv[3]), dirigido, ponderado);
    }
    
    // Mostramos primero el grafo si no hay demasiados nodos
    if(grafo.n_nodos < 10)
        grafo.mostrar_grafo();

    // Pedimos nodo inicial y final para BFS, Dijkstra y Bellman-Ford
    cout << "Introduce el nodo inicial para el algoritmo BFS, Dijkstra y Bellman-Ford:\n";

    do{
        cin >> n_inicial;
    } while(n_inicial < 0 || n_inicial > grafo.n_nodos);

    if(grafo.min>=0){

        // Pedimos el nodo final para BFS y Dijkstra
        cout << "Introduce el nodo final para el algoritmo BFS y de Dijkstra:\n";

        do{
            cin >> n_final;
        } while(n_final < 0 || n_final >= grafo.n_nodos);

        if(!grafo.ponderado){
            // Ejecutamos el algoritmo BFS y medimos tiempos
            cout << "\nEjecución algoritmo de búsqueda en anchura BFS:\n";

            vector<vector<int> > padres(grafo.n_nodos, vector<int>());
            auto momentoInicio = clock();
            bool camino = BFS(grafo, n_inicial, n_final, padres);
            auto momentoFin = clock();

            // Imprimimos los resultados
            if(!camino)
                cout << "No existe camino entre los nodos " << n_inicial << " y " << n_final << endl;
            else{
                cout << "Caminos encontrados:\n";
                mostrar_caminos(padres, n_final);
            }

            auto tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
            cout <<"Tiempo Ejecución: " << tiempo << endl;

            cout << "Coste: " << coste(grafo, padres, n_final) << endl << endl;

            if(!grafo.dirigido){
                // Ejecutamos el algoritmo BFS de cálculo de componentes conexas
                cout << "Ejecución algoritmo BFS para cálculo de componentes conexas:\n";

                momentoInicio = clock();
                int conexas = BFS_conexas(grafo);
                momentoFin = clock();

                tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
                cout <<"Tiempo Ejecución: " << tiempo << endl;

                cout << "Componentes conexas: " << conexas << endl << endl;
            }
            else
                cout << "No se puede ejecutar el algoritmo BFS de cálculo de componentes conexas pues el grafo es dirigido.\n\n";
        }
        else 
            cout << "No se puede ejecutar el algoritmo de búsqueda en anchura BFS pues el grafo es ponderado.\n\n";
        
        // Ejecutamos el algoritmo de Dijkstra y medimos tiempos
        cout << "\nEjecución algoritmo de Dijkstra:\n";

        vector<vector<int> > padres(grafo.n_nodos, vector<int>());
        auto momentoInicio = clock();
        bool camino = DJK(grafo, n_inicial, n_final, padres);
        auto momentoFin = clock();

        // Imprimimos los resultados
        if(!camino)
            cout << "No existe camino entre los nodos " << n_inicial << " y " << n_final << endl;
        else{
            cout << "Caminos encontrados:\n";
            mostrar_caminos(padres, n_final);
        }

        auto tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
        cout <<"Tiempo Ejecución: " << tiempo << endl;

        cout << "Coste: " << coste(grafo, padres, n_final) << endl << endl;
    }
    else
        cout << "No se pueden ejecutar ni el algoritmo BFS ni Dijkstra pues hay pesos negativos\n\n";
    

    // Ejecutamos el algoritmo de Bellman-Ford y medimos tiempos
    cout << "\nEjecución algoritmo de Bellman-Ford:\n";

    vector<vector<int> > padres(grafo.n_nodos, vector<int>());
    auto momentoInicio = clock();
    bool no_ciclo_neg = BF(grafo, n_inicial, padres);
    auto momentoFin = clock();

    // Imprimimos los resultados
    auto tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
    cout <<"Tiempo Ejecución: " << tiempo << endl;

    if(no_ciclo_neg){
        // Pedimos un nodo final para comprobar los caminos encontrados
        cout << "Introduce el nodo final para mostrar los caminos encontrados:\n";

        do{
            cin >> n_final;
        } while(n_final < 0 || n_final >= grafo.n_nodos);

        if(padres[n_final].empty())
            cout << "No existe camino entre los nodos " << n_inicial << " y " << n_final << endl;
        else{
            cout << "Caminos encontrados:\n";
            mostrar_caminos(padres, n_final);
        }

        cout << "Coste: " << coste(grafo, padres, n_final) << endl << endl;
    }
    else
        cout << "Hay un ciclo negativo en el grafo alcanzable desde un camino que conecta el nodo inicial y final\n\n";
    
    // Ejecutamos los algoritmos de la sección de Warshall y medimos tiempos
    cout << "\nEjecución de la versión lenta del algoritmo de cálculo de caminos mínimos para todas las parejas de nodos:\n";

    momentoInicio = clock();
    vector<vector<int> > res = Caminos_Minimos_Todas_Parejas_Lento(grafo.matriz);
    momentoFin = clock();

    // Imprimimos los resultados
    tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
    cout <<"Tiempo Ejecución: " << tiempo << endl;

    // Imprimimos matriz de resultados si no es demasiado grande
    if(grafo.n_nodos < 10){
        cout << "Matriz de resultados:\n";
        Mostrar_Matriz(res);
    }
    else
        cout << "No se muestra la matriz de resultados por ser demasiado grande\n";

    cout << "\nEjecución de la versión rápida del algoritmo de cálculo de caminos mínimos para todas las parejas de nodos:\n";

    momentoInicio = clock();
    res = Caminos_Minimos_Todas_Parejas_Rapido(grafo.matriz);
    momentoFin = clock();

    // Imprimimos los resultados
    tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
    cout <<"Tiempo Ejecución: " << tiempo << endl;

    // Imprimimos matriz de resultados si no es demasiado grande
    if(grafo.n_nodos < 10){
        cout << "Matriz de resultados:\n";
        Mostrar_Matriz(res);
    }
    else
        cout << "No se muestra la matriz de resultados por ser demasiado grande\n";

    // Ejecutamos el algoritmo de Floyd-Warshall y medimos tiempos
    cout << "\nEjecución del algoritmo de Floyd-Warshall:\n";

    momentoInicio = clock();
    auto war = Floyd_Warshall(grafo);
    momentoFin = clock();

    // Imprimimos los resultados
    tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
    cout <<"Tiempo Ejecución: " << tiempo << endl;

    // Imprimimos matriz de resultados si no es demasiado grande
    if(grafo.n_nodos < 10){
        cout << "Matriz de distancias:\n";
        Mostrar_Matriz(war.first);
        cout << "Matriz de predecesores:\n";
        Mostrar_Matriz(war.second);
    }
    else
        cout << "No se muestran las matrices de resultados por ser demasiado grandes\n";

    cout << "Camino encontrado entre el nodo inicial y final a partir de la matriz de predecesores:\n";

    Mostrar_Camino(war.second, n_inicial, n_final);

    // Ejecutamos el algoritmo de Clausura Transitiva y medimos tiempos
    cout << "\n\nEjecución del algoritmo de Clausura-Transitiva:\n";

    momentoInicio = clock();
    auto tran = Clausura_Transitiva(grafo);
    momentoFin = clock();

    // Imprimimos los resultados
    tiempo = 1000.0*(momentoFin - momentoInicio)/CLOCKS_PER_SEC;
    cout <<"Tiempo Ejecución: " << tiempo << endl;

    // Imprimimos matriz de resultados si no es demasiado grande
    if(grafo.n_nodos < 10){
        cout << "Matriz de clausura transitiva:\n";
        Mostrar_Matriz(tran);
    }
    else
        cout << "No se muestran las matrices de resultados por ser demasiado grandes\n";


    return 0;
}

void check_params(int argc, char** argv){
    // Los argumentos son el número de nodos, densidad del grafo, semilla, dirigido o no, ponderado o no y, opcionalmente,
    // mínimo, máximo, algoritmo concreto y tiempo o coste
    if(argc != 6 && argc != 2){
        cerr << "Fallo de parámetros, [número de nodos] [densidad (0-1)] [semilla] [dirigido (si/no)] [ponderado (si/no)] o [path]" << endl;
        exit(1);
    }

    if(argc == 6 && string(argv[4]) != "si" && string(argv[4]) != "no"){
        cerr << "Fallo de parámetros, [número de nodos] [densidad (0-1)] [semilla] [dirigido (si/no)] [ponderado (si/no)] o [path]" << endl;
        exit(1);
    }

    if(argc == 6 && string(argv[5]) != "si" && string(argv[5]) != "no"){
        cerr << "Fallo de parámetros, [número de nodos] [densidad (0-1)] [semilla] [dirigido (si/no)] [ponderado (si/no)] o [path]" << endl;
        exit(1);
    }
}

void mostrar_caminos(vector<vector<int> > &padres, int n_final){
    mostrar_caminos_rec(padres, to_string(n_final), n_final);
}

void mostrar_caminos_rec(vector<vector<int> > &padres, string camino, int actual){
    if(padres[actual].empty()){
        cout << camino << endl;
        return;
    }

    for(int i=0; i<padres[actual].size(); i++)
        mostrar_caminos_rec(padres, to_string(padres[actual][i]) + " -> " + camino, padres[actual][i]);
}

int coste(Grafo grafo, vector<vector<int> > &padres, int n_final){
    int actual = n_final;
    int padre;
    int suma = 0;

    // Calculamos el coste del primer camino encontrado, todos tienen el mismo
    while(!padres[actual].empty()){
        padre = padres[actual][0];
        suma += grafo.matriz[padre][actual];
        actual = padre;
    }

    return suma;
}