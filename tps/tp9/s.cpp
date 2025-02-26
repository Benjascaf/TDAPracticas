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
    // Funcion para sobreescribir el comparador de la
    // priority_queue Seguro hay algo mejor
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

    // Corre el algoritmo de Prim sobre un nodo del grafo
    // usando priority_queue
    Graph prim(long unsigned startingNode)
    {
        // Vector de booleanos para determinar
        // que nodos ya estan presentes en el arbol
        std::vector<bool> treeNodes(m_g.size(), false);
        long unsigned currNode{startingNode};
        treeNodes[currNode - 1] = true;
        std::list<std::tuple<int, int, int>> treeEdges{};
        std::priority_queue<
            std::tuple<int, int, int>,
            std::vector<std::tuple<int, int, int>>, Compare>
            candidates;
        for (long unsigned i = 0; i < m_g.size() - 1; i++)
        {
            for (std::tuple<int, int> edge :
                 m_g[currNode - 1])
            {
                int neighbour{std::get<0>(edge)};
                int weight{std::get<1>(edge)};
                if (not treeNodes[neighbour - 1])
                {
                    candidates.push(
                        std::make_tuple(currNode, neighbour, weight));
                }
            }
            // Esto... tambien deberia ser un do while
            std::tuple<int, int, int> newEdge =
                candidates.top();
            while (treeNodes[std::get<1>(newEdge) - 1] &&
                   not candidates.empty())
            {
                candidates.pop();
                newEdge = candidates.top();
            }
            candidates.pop();
            treeEdges.push_front(newEdge);
            treeNodes[std::get<1>(newEdge) - 1] = true;
            currNode = std::get<1>(newEdge);
        }
        return Graph(m_nodes, treeEdges);
    }
};

// Funcion para calcular el costo entre dos claves
// Asumiendo que las mismas tienen como mucho cuatro digitos

int digitsDiff(int n, int m)
{
    int total{};
    for (int i = 0; i < 4; i++)
    {
        int lastDigitN{n % 10};
        int lastDigitM{m % 10};
        // El costo de moverme hacia atras
        int costRollingBack{10 + std::min(lastDigitM, lastDigitN) - std::max(lastDigitM, lastDigitN)};
        // La diferencia digito a digito representa el costo de llegar desde ese digito
        // Al otro moviendome hacia adelante
        int costRollingForward{std::abs(n % 10 - m % 10)};
        // El costo total termina siendo la suma del costo minimo para cada uno de los digitos
        total += std::min(costRollingBack, costRollingForward);
        n /= 10;
        m /= 10;
    }
    return total;
}

// El grafo que representa el problema tiene n nodos, donde n es la cantidad de claves
// Del candado, y es completo. Primero obtenemos el grafo dandole pesos a las aristas entre
//  cada uno de los nodos correspondiente a la minima cantidad de roles que nos tomaria llegar desde uno
//  al otro, una vez logrado esto, identificamos la clave que esta mas cerca del 0 (la que menos roles necesita para llegar)
// y corremos Prim desde ahi, obteniendo el AGM minimo. Ahora simplemente sumamos el costo de todas las aristas
// del AGM, sin olvidarnos de sumar tambien el costo que calculamos previamente para llegar desde 0.
int minimum_moves(std::vector<int> keys)
{
    std::vector<int> nodes(keys.size());
    for (int i = 1; i <= int(nodes.size()); i++)
    {
        nodes[i - 1] = static_cast<int>(i);
    }
    std::list<std::tuple<int, int, int>> edges = std::list<std::tuple<int, int, int>>();
    for (long unsigned i = 0; i < keys.size(); i++)
    {
        for (long unsigned j = i; j < keys.size(); j++)
        {
            if (j != i)
            {
                // Calculamos el costo de cada una de las aristas
                int cost{digitsDiff(keys[i], keys[j])};
                edges.push_front(std::tuple<int, int, int>{i + 1, j + 1, cost});
            }
        }
    }
    Graph g = Graph(nodes, edges);
    int minCostFrom0{10000};
    long unsigned minCostKey{};
    for (long unsigned i = 0; i < keys.size(); i++)
    {
        int cost{digitsDiff(0, keys[i])};
        if (cost < minCostFrom0)
        {
            minCostFrom0 = cost;
            minCostKey = i + 1;
        }
    }
    Graph res = g.prim(minCostKey);
    int totalRolls{};
    for (std::tuple<int, int, int> edge : res.getEdges())
    {
        totalRolls += std::get<2>(edge);
    }
    return totalRolls + minCostFrom0;
}

void getInput()
{
    int numCases{};
    std::cin >> numCases;
    std::vector<int> results{};
    for (int actualCase = 0; actualCase < numCases; actualCase++)
    {
        int numberOfKeys{};
        std::cin >> numberOfKeys;
        std::vector<int> keys(numberOfKeys);
        for (int &key : keys)
            std::cin >> key;
        int res{minimum_moves(keys)};
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
