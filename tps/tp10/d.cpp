#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <numeric>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class Graph
{
    std::vector<int> m_nodes{};
    // Lista de tuplas representando los ejes y su peso
    std::list<std::tuple<int, int, int>> m_edges;
    std::vector<std::list<std::tuple<int, int>>> m_g{};

    // Funcion para armar la lista de adyacencia
    std::vector<std::list<std::tuple<int, int>>>
    graphConstructor(
        const std::vector<int> &nodes,
        const std::list<std::tuple<int, int, int>> &edges)
    {
        std::vector<std::list<std::tuple<int, int>>> g(
            nodes.size(), std::list<std::tuple<int, int>>());
        for (std::tuple<int, int, int> edge : edges)
        {
            int fstNode{std::get<0>(edge)};
            int sndNode{std::get<1>(edge)};
            int edgeWeight{std::get<2>(edge)};
            g[fstNode - 1].push_back(
                std::make_tuple(sndNode, edgeWeight));
            g[sndNode - 1].push_back(
                std::make_tuple(fstNode, edgeWeight));
        }
        return g;
    }

public:
    struct Compare
    {
        bool operator()(std::tuple<int, int, int> &a,
                        std::tuple<int, int, int> &b)
        {
            return std::get<2>(a) > std::get<2>(b);
        }
    };

    // Constructor del grafo
    Graph(const std::vector<int> &nodes,
          const std::list<std::tuple<int, int, int>> &edges)
        : m_nodes{nodes}, m_edges{edges},
          m_g{graphConstructor(nodes, edges)} {}

    void printGraph()
    {
        for (long unsigned i = 0; i < m_g.size(); i++)
        {
            std::cout << "Vecinos de " << i + 1 << ":\n";
            for (std::tuple<int, int> vecino : m_g[i])
            {
                std::cout << std::get<0>(vecino) << " ";
            }
            std::cout << '\n';
        }
    }

    std::list<std::tuple<int, int, int>> getEdges()
    {
        return m_edges;
    }

    // Corre el algoritmo de Dijkstra usando la implementacion
    // trivial porque soy vago y el conjunto de nodos esta acotado por una
    // constante chica, por lo que su complejidad es constante asintoticamente hablando.
    std::vector<int> dijkstra(int sourceVertex)
    {
        std::vector<int> distances(m_nodes.size(), INF);
        std::list<int> relaxedNodes{sourceVertex};
        std::vector<bool> includedNodes(m_nodes.size(), false);
        includedNodes[sourceVertex - 1] = true;
        distances[sourceVertex - 1] = 0;
        for (std::tuple<int, int> edge : m_g[sourceVertex - 1])
        {
            int adjVertex = std::get<0>(edge);
            int edgeDistance = std::get<1>(edge);
            distances[adjVertex - 1] = edgeDistance;
        }
        auto nodesLeftToProcess = m_nodes.size() - relaxedNodes.size();
        for (long unsigned i = 0; i < nodesLeftToProcess; i++)
        {
            int minDistanceNode{INF};
            for (int node : m_nodes)
            {
                if (includedNodes[node - 1])
                {
                    continue;
                }
                if (minDistanceNode == INF)
                {
                    minDistanceNode = node;
                }
                else
                {
                    if (distances[node - 1] < distances[minDistanceNode - 1])
                    {
                        minDistanceNode = node;
                    }
                }
            }
            relaxedNodes.push_back(minDistanceNode);

            includedNodes[minDistanceNode - 1] = true;
            for (std::tuple<int, int> edge : m_g[minDistanceNode - 1])
            {
                int adjVertex = std::get<0>(edge);
                if (includedNodes[adjVertex - 1])
                {
                    continue;
                }
                int edgeWeight = std::get<1>(edge);
                if (distances[minDistanceNode - 1] != INF and distances[adjVertex - 1] > distances[minDistanceNode - 1] + edgeWeight)
                {
                    distances[adjVertex - 1] = distances[minDistanceNode - 1] + edgeWeight;
                }
            }
        }
        return distances;
    };
};

// Aca la idea del modelo es que para cada representar cada piso tenemos n ascensores
// luego, siendo k la cantidad de pisos, nk nodos. Agragamos arcos entre lo nodos representando
// ascensores en cada piso con un costo de 60. Luego, los arcos del grafo unen solo los
// pisos de sus respectivos ascensores con el costo dado como input, siendo que en cada
// piso se simula la opcion de gastar 60 segundos y tomar otro ascensor, o seguir con el mismo.
std::string getTime(std::vector<std::vector<int>> &elevatorStops, int targetFloor, std::vector<int> &elevatorTimes, long unsigned n)
{
    std::vector<int> nodes(100 * n);
    std::list<std::tuple<int, int, int>> edges = std::list<std::tuple<int, int, int>>();
    for (long unsigned i = 0; i < 100 * n; i++)
    {
        nodes[i] = static_cast<int>(i) + 1;
    };
    for (long unsigned i = 0; i < 100 * n; i += n)
    {
        for (long unsigned j = 0; j < n; j++)
        {
            int time;
            if (i == 0)
            {
                time = 0;
            }
            else
            {
                time = 60;
            }
            for (long unsigned k = 0; k < n - 1; k++)
            {
                if (k == j)
                {
                    continue;
                }
                edges.push_back(std::tuple<int, int, int>(nodes[i + j], nodes[i + k], time));
            }
        }
    }
    for (long unsigned elevator = 0; elevator < n; elevator++)
    {
        int elevatorTime = elevatorTimes[elevator];
        for (long unsigned stop = 0; stop < elevatorStops[elevator].size() - 1; stop++)
        {
            int floor = elevatorStops[elevator][stop];
            int nextFloor = elevatorStops[elevator][stop + 1];
            int seconds = (nextFloor - floor) * elevatorTime;
            edges.push_back(std::tuple<int, int, int>(nodes[floor * n + elevator], nodes[nextFloor * n + elevator], seconds));
            edges.push_back(std::tuple<int, int, int>(nodes[nextFloor * n + elevator], nodes[floor * n + elevator], seconds));
        }
    };
    Graph g = Graph(nodes, edges);
    std::vector<int> distances = g.dijkstra(1);
    int min{INF};
    for (long unsigned i = 0; i < n; i++)
    {
        if (distances[targetFloor * n + i] < min)
        {
            min = distances[targetFloor * n + i];
        }
    }
    if (min == INF)
    {
        return "IMPOSSIBLE";
    }
    else
    {
        return std::to_string(min);
    }
}
void getInput()
{
    std::list<std::string> res = std::list<std::string>();
    int cantAscensores, pisoDestino;
    while (std::cin >> cantAscensores >> pisoDestino)
    {
        std::vector<int> elevatorTimes(cantAscensores);
        std::vector<std::vector<int>> elevatorStops(cantAscensores, std::vector<int>());
        for (int i = 0; i < cantAscensores; i++)
        {
            std::cin >> elevatorTimes[i];
        }
        std::cin >> std::ws;
        for (int i = 0; i < cantAscensores; i++)
        {
            std::string stops;
            std::getline(std::cin, stops);
            std::istringstream iss(stops);
            int floor;
            while (iss >> floor)
            {
                elevatorStops[i].push_back(floor);
            }
        }

        res.push_back(getTime(elevatorStops, pisoDestino, elevatorTimes, cantAscensores));
    }
    for (std::string s : res)
    {
        std ::cout << s << '\n';
    };
}
int main()
{
    getInput();

    return 0;
}
