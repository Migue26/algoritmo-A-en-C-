#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;


struct City {
    int x, y;

    // Constructor
    City(int x, int y) : x(x), y(y) {}
};

// Lista de ciudades
vector<City> cities = {
    {0, 0},
    {1, 4},
    {5, 3},
    {2, 1}
};

// Funcion para calcular la distancia euclidiana entre dos ciudades
double distance(const City& city1, const City& city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

struct State {
    int city;
    vector<int> path;
    int cost;

    bool operator>(const State& other) const {
        if (cost + heuristic() == other.cost + other.heuristic()) {
            // Desempatar por la posición de la ciudad
            return city > other.city;
        }
        return cost + heuristic() > other.cost + other.heuristic();
    }

    int heuristic() const {
        // Heurística simple: distancia mínima desde la ciudad actual hasta la ciudad de inicio
        if (path.size() < 2) {
            return 0;
        }
        return distance(cities[city], cities[path[0]]);
    }
};






vector<int> solveTSP(int startCity) {
    int numCities = cities.size();

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({startCity, {startCity}, 0});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.path.size() == numCities) {
            return current.path;
        }

        for (int nextCity = 0; nextCity < numCities; ++nextCity) {
            if (find(current.path.begin(), current.path.end(), nextCity) == current.path.end()) {
                State nextState = {nextCity, current.path, current.cost + distance(cities[current.city], cities[nextCity])};
                nextState.path.push_back(nextCity);

                pq.push(nextState);
            }
        }
    }

    return {};
}

int main() {
    int startCity = 0;

    vector<int> solution = solveTSP(startCity);

    if (!solution.empty()) {
        cout << "Camino optimo: ";
        for (int city : solution) {
            cout << city << " ";
        }

        // Calcular y mostrar el costo total del camino
        double totalCost = 0;
        for (size_t i = 0; i < solution.size() - 1; ++i) {
            totalCost += distance(cities[solution[i]], cities[solution[i + 1]]);
        }
        totalCost += distance(cities[solution.back()], cities[solution.front()]);  // Añadir la distancia de regreso a la ciudad de inicio

        cout << "\nCosto total: " << totalCost << endl;
    } else {
        cout << "No se encontró solución." << endl;
    }

    return 0;
}
