#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;

// Estructura que representa un estado del juego de pancakes
struct Estado {
    vector<char> pancakes;
    int costo; // cantidad de volteos realizados
    vector<int> camino; // lista de los �ndices de los pancakes volteados

    Estado(vector<char> p, int c, vector<int> cam) {
        pancakes = p;
        costo = c;
        camino = cam;
    }
};

// Funci�n que imprime el camino de volteos de pancakes para llegar a la soluci�n
void imprimir_camino(vector<int> camino) {
    for (int i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
    cout << endl;
}

// Funci�n que verifica si el estado actual es la soluci�n (pancakes ordenados de forma ascendente)
bool es_solucion(vector<char> pancakes) {
    vector<char> pancakes_ordenados = pancakes;
    sort(pancakes_ordenados.begin(), pancakes_ordenados.end());
    return pancakes == pancakes_ordenados;
}

// Funci�n que realiza el volteo de los pancakes
void voltear_pancakes(vector<char>& pancakes, int desde, int hasta) {
    while (desde < hasta) {
        char temp = pancakes[desde];
        pancakes[desde] = pancakes[hasta];
        pancakes[hasta] = temp;
        desde++;
        hasta--;
    }
}

// Funci�n que imprime el arreglo de pancakes
void imprimir_pancakes(vector<char> pancakes) {
    for (int i = 0; i < pancakes.size(); i++) {
        cout << pancakes[i] << " ";
    }
    cout << endl;
}

// Funci�n que realiza la b�squeda en profundidad iterativa
void busqueda_en_Profundidad_Iterativa(vector<char> pancakes) {
    int profundidadMaxima = 1;

    while (true) {
        vector<int> camino;
        Estado estadoInicial = Estado(pancakes, 0, camino);

        stack<Estado> pila;
        pila.push(estadoInicial);

        while (!pila.empty()) {
            Estado estadoActual = pila.top();
            pila.pop();

            if (es_solucion(estadoActual.pancakes)) {

                cout << "Voltear pancakes: ";
                imprimir_camino(estadoActual.camino);
                cout << " " <<endl;
                cout << "Arreglo ordenado: ";
                imprimir_pancakes(estadoActual.pancakes);
                cout << " " <<endl;
                cout << "Nodos visitados: " << estadoActual.costo  << endl;
                return;
            }

            if (estadoActual.costo < profundidadMaxima) {
                for (int i = 2; i <= estadoActual.pancakes.size(); i++) {
                    vector<char> pancakesVolteados = estadoActual.pancakes;
                    voltear_pancakes(pancakesVolteados, 0, i-1);

                    vector<int> caminoNuevo = estadoActual.camino;
                    caminoNuevo.push_back(i-1);

                    Estado estadoNuevo = Estado(pancakesVolteados, estadoActual.costo+1, caminoNuevo);
                    pila.push(estadoNuevo);
                }
            }
        }

        profundidadMaxima++;
        if (profundidadMaxima > 100) {
            cout << "No se encontr� soluci�n en " << profundidadMaxima << " pasos." << endl;
            return;
        }
    }
}




// Funci�n principal
int main() {
    string entrada;
    vector<char> pancakes;

    cout << "Pancakes con busqueda en profundidad iterativa";
    cout << " "<< endl;
    cout << "Ingrese los caracteres a ordenar(letras) Ejemplo( flrpmend ) caracteres: ";
    getline(cin, entrada);
    istringstream iss(entrada);

    char c;
    while (iss >> c) {
        pancakes.push_back(c);
    }

    cout << "Arreglo de pancakes: ";
    imprimir_pancakes(pancakes);

    busqueda_en_Profundidad_Iterativa(pancakes);
    return 0;
}
