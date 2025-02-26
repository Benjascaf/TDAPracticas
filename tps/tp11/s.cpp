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

const int INF = std::numeric_limits<int>::max() / 2 - 1;
using matrix = std::vector<std::vector<int>>;
using weighted_edge = std::tuple<int, int, int>;

int from(weighted_edge e)
{
    return std::get<0>(e);
}

int to(weighted_edge e)
{
    return std::get<1>(e);
}

int weight(weighted_edge e)
{
    return std::get<2>(e);
}

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

    std::list<std::tuple<int, int, int>> getEdges()
    {
        return m_edges;
    }

    matrix floyd_warshall()
    {
        long unsigned n = m_nodes.size();
        matrix D = matrix(n, std::vector<int>(n, INF));
        for (weighted_edge e : m_edges)
        {
            D[from(e) - 1][to(e) - 1] = weight(e);
        }
        for (long unsigned k = 0; k < n; k++)
        {
            for (long unsigned i = 0; i < n; i++)
            {
                for (long unsigned j = 0; j < n; j++)
                {
                    if (D[i][j] > D[i][k] + D[k][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
        return D;
    }
};

int calculatePower(int n, std::vector<int> orderOfDestruction, std::vector<std::vector<int>> energyNeeded)
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
    matrix D = G.floyd_warshall();
    std::vector<bool> destroyedTowers(n, false);
    int powerNeeded{};
    for (int tower : orderOfDestruction)
    {
        for (long unsigned i = 0; i < nodes.size(); i++)
        {
            if (destroyedTowers[i])
            {
                continue;
            }
            for (long unsigned j = 0; j < nodes.size(); j++)
            {
                if (destroyedTowers[j])
                    continue;
                powerNeeded += D[i][j];
            }
        }
        destroyedTowers[tower] = true;
    }

    return powerNeeded;
}

void getInput()
{
    int numCases{};
    std::cin >> numCases;
    std::vector<int> results{};
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
        int res{calculatePower(numberOfTowers, orderOfDestruction, energyNeeded)};
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
    std::vector<int> nodes{1, 2, 3};
    std::list<weighted_edge> edges{weighted_edge(1, 2, 35), weighted_edge(1, 3, 58), weighted_edge(1, 1, 0),
                                   weighted_edge(2, 2, 0), weighted_edge(2, 1, 12), weighted_edge(2, 3, 5),
                                   weighted_edge(3, 2, 2), weighted_edge(3, 1, 1), weighted_edge(3, 3, 0)};
    Graph g = Graph(nodes, edges);
    matrix D = g.floyd_warshall();
    return 0;
}
