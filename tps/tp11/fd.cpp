#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include <sstream>
#include <cmath>
#include <numeric>
#include <limits>

// Mejore un poco el tema del uso de estructuras para el grafo con "using"
// Y una constante INF definida de manera que sea un numero lo suficientemente grande
//  Pero que a la vez no cause overflow facilmente (idea robada de apuntes viejos de la teorica)
const long unsigned INF = std::numeric_limits<long unsigned>::max() / 2 - 1;
using matrix = std::vector<std::vector<long unsigned>>;
using weighted_edge = std::tuple<int, int, long unsigned>;
using adjList = std::vector<std::list<std::tuple<int, long unsigned>>>;

// Obtiene el nodo del que sale el arco
int from(weighted_edge e)
{
    return std::get<0>(e);
}

// nodo al que llega
int to(weighted_edge e)
{
    return std::get<1>(e);
}

long unsigned weight(weighted_edge e)
{
    return std::get<2>(e);
}

class Graph
{
    std::vector<int> m_nodes{};
    // Lista de tuplas representando los ejes y su peso
    std::list<weighted_edge> m_edges;
    adjList m_g{};

    // Funcion para armar la lista de adyacencia
    adjList
    graphConstructor(
        const std::vector<int> &nodes,
        const std::list<weighted_edge> &edges)
    {
        adjList g(
            nodes.size(), std::list<std::tuple<int, long unsigned>>());
        for (weighted_edge edge : edges)
        {
            int fstNode{std::get<0>(edge)};
            int sndNode{std::get<1>(edge)};
            long unsigned edgeWeight{std::get<2>(edge)};
            g[fstNode - 1].push_back(
                std::make_tuple(sndNode, edgeWeight));
            g[sndNode - 1].push_back(
                std::make_tuple(fstNode, edgeWeight));
        }
        return g;
    }

public:
    // Funcion para sobreescribir el comparador de la
    // priority_queue Seguro hay algo mejor

    // Constructor del grafo
    Graph(const std::vector<int> &nodes,
          const std::list<weighted_edge> &edges)
        : m_nodes{nodes}, m_edges{edges},
          m_g{graphConstructor(nodes, edges)} {}

    std::list<weighted_edge> getEdges()
    {
        return m_edges;
    }
    // La idea del metodo es usar Floyd-Warshall, abusando el invariante
    // que determina que calcula las distancias minimas de caminos cuyos vertices intermedios
    // pertenecen a un cierto conjunto K, solo que en vez de usar un orden "natura;"
    // como vimos en clase, los nodos que se van agregando al conjunto corresponden
    // al reverso del orden en el que se quieren destruir las torres.
    // Luego sumamos a un acumulador las distancias de las torres que no estan destruidas en cada
    // iteracion, condicion que cuesta O(1) de chequear gracias a un vector de bools
    long unsigned power(std::vector<int> &orderOfDestruction)
    {
        long unsigned n = m_nodes.size();
        std::reverse(orderOfDestruction.begin(), orderOfDestruction.end());
        std::vector<bool> destroyedTowers(n, true);
        destroyedTowers[orderOfDestruction[0]] = false;
        matrix D = matrix(n, std::vector<long unsigned>(n, INF));
        long unsigned power = 0;
        for (weighted_edge e : m_edges)
        {
            D[from(e) - 1][to(e) - 1] = weight(e);
        }
        for (int k : orderOfDestruction)
        {
            destroyedTowers[k] = false;
            for (long unsigned i = 0; i < n; i++)
            {
                for (long unsigned j = 0; j < n; j++)
                {
                    if (D[i][k] == INF || D[k][j] == INF)
                        continue;
                    if (D[i][j] > D[i][k] + D[k][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                    if (!destroyedTowers[i] and !destroyedTowers[j])
                    {
                        power += D[i][j];
                    }
                }
            }
        }
        return power;
    }
};

long unsigned calculatePower(int n, std::vector<int> &orderOfDestruction, std::vector<std::vector<int>> &energyNeeded)
{
    std::vector<int> nodes(n);
    std::list<weighted_edge> edges{};
    for (long unsigned i = 0; i < orderOfDestruction.size(); i++)
    {
        nodes[i] = static_cast<int>(i) + 1;
    }
    for (long unsigned i = 0; i < orderOfDestruction.size(); i++)
    {
        for (long unsigned j = 0; j < orderOfDestruction.size(); j++)
        {
            edges.push_back(weighted_edge(i + 1, j + 1, energyNeeded[i][j]));
        }
    }
    Graph G = Graph(nodes, edges);

    return G.power(orderOfDestruction);
}

void getInput()
{
    int numCases{};
    std::cin >> numCases;
    std::vector<long unsigned> results{};
    for (int actualCase = 0; actualCase < numCases; actualCase++)
    {
        int numberOfTowers{};
        std::cin >> numberOfTowers;
        std::cin >> std::ws;
        std::vector<std::vector<int>> energyNeeded(numberOfTowers, std::vector<int>());
        for (int i = 0; i < numberOfTowers; i++)
        {
            std::string s;
            std::getline(std::cin, s);
            std::istringstream iss(s);
            int energy;
            while (iss >> energy)
            {
                energyNeeded[i].push_back(energy);
            }
        }
        std::vector<int> orderOfDestruction(0);
        std::string s;
        std::getline(std::cin, s);
        std::istringstream iss(s);
        int tower;
        while (iss >> tower)
        {
            orderOfDestruction.push_back(tower);
        }
        long unsigned res{calculatePower(numberOfTowers, orderOfDestruction, energyNeeded)};
        results.push_back(res);
    }
    for (const auto &res : results)
    {
        std::cout << res << '\n';
    }
}

int main()

{
    getInput();
    return 0;
}
