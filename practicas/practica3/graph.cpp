#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

class Graph {
    std::vector<int> m_nodes{};
    // Lista de tuplas representando los ejes y su peso
    std::list<std::tuple<int, int, int>>         m_edges;
    std::vector<std::list<std::tuple<int, int>>> m_g{};

    // class DisjointSetp {
    //     DisjointSetp *m_padre;
    //     int           node{};
    //     int           rank{};

    //   public:
    //     DisjointSetp(int node)
    //         : node{node}, rank{0}, m_padre{this} {}
    //     int getNode
    // };

    class DisjointSet {
        // Rango de cada una de los conjuntos
        std::vector<int> m_ranks{};
        // Padre de cada nodo
        std::vector<int> m_parents{};

        // En vez de tener un make_set para cada vertice
        // Inicializo la estructura en su totalidad,
        // estoy sacrificando flexibilidad por ahora
        // La implementacion tambien se limita a nodos
        // identificados con enteros
        std::vector<int>
          makeSets(const std::vector<int> &nodes) {
          std::vector<int> parents =
            std::vector<int>(nodes.size(), 0);
          for (int node : nodes) {
            parents[node - 1] = node;
          }
          return parents;
        }

        // Funcion auxiliar para determinar como unir dos
        //  conjuntos.
        void link(int nodeA, int nodeB) {
          if (m_ranks[nodeA - 1] < m_ranks[nodeB - 1]) {
            m_parents[nodeA - 1] = nodeB;
          } else {
            m_ranks[nodeB - 1] = nodeA;
            if (m_ranks[nodeA - 1] == m_ranks[nodeB - 1]) {
              m_ranks[nodeA - 1]++;
            }
          }
        }

      public:
        DisjointSet(const std::vector<int> &nodes)
            : m_ranks{std::vector<int>(nodes.size(), 0)},
              m_parents{makeSets(nodes)} {}

        // findSet con path compression para intentar
        // optimizar
        int findSet(int node) {
          if (m_parents[node - 1] != node) {
            m_parents[node - 1] =
              findSet(m_parents[node - 1]);
          }
          return m_parents[node - 1];
        }

        void unionSet(int nodeA, int nodeB) {
          link(findSet(nodeA), findSet(nodeB));
        }
    };

    // Funcion para armar la lista de adyacencia
    std::vector<std::list<std::tuple<int, int>>>
      graphConstructor(
        const std::vector<int>                     &nodes,
        const std::list<std::tuple<int, int, int>> &edges) {
      std::vector<std::list<std::tuple<int, int>>> g(
        nodes.size(), std::list<std::tuple<int, int>>());
      for (std::tuple<int, int, int> edge : edges) {
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
    struct Compare {
        bool operator()(std::tuple<int, int, int> &a,
                        std::tuple<int, int, int> &b) {
          return std::get<2>(a) > std::get<2>(b);
        }
    };

    // Constructor del grafo
    Graph(const std::vector<int>                     &nodes,
          const std::list<std::tuple<int, int, int>> &edges)
        : m_nodes{nodes}, m_edges{edges},
          m_g{graphConstructor(nodes, edges)} {}

    void printGraph() {
      for (long unsigned i = 0; i < m_g.size(); i++) {
        std::cout << "Vecinos de " << i + 1 << ":\n";
        for (std::tuple<int, int> vecino : m_g[i]) {
          std::cout << std::get<0>(vecino) << " ";
        }
        std::cout << '\n';
      }
    }

    // Corre el algoritmo de Prim sobre un nodo del grafo
    // usando priority_queue
    Graph prim(int startingNode) {
      // Vector de booleanos para determinar
      // que nodos ya estan presentes en el arbol
      std::vector<bool> treeNodes(m_g.size(), false);
      int               currNode{startingNode};
      treeNodes[currNode - 1] = true;
      std::list<std::tuple<int, int, int>> treeEdges{};
      std::priority_queue<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>, Compare>
        candidates;
      for (long unsigned i = 0; i < m_g.size() - 1; i++) {
        for (std::tuple<int, int> edge :
             m_g[currNode - 1]) {
          int neighbour{std::get<0>(edge)};
          int weight{std::get<1>(edge)};
          if (not treeNodes[neighbour - 1]) {
            candidates.push(
              std::make_tuple(currNode, neighbour, weight));
          }
        }
        // Esto... tambien deberia ser un do while
        std::tuple<int, int, int> newEdge =
          candidates.top();
        while (treeNodes[std::get<1>(newEdge) - 1] &&
               not candidates.empty()) {
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

    Graph kruskal() {
      std::list<std::tuple<int, int, int>> treeEdges{};
      m_edges.sort([](std::tuple<int, int, int> &a,
                      std::tuple<int, int, int> &b) {
        return std::get<2>(a) < std::get<2>(b);
      });
      DisjointSet components = DisjointSet(m_nodes);
      // iterador de las aristas
      auto p{m_edges.begin()};
      for (long unsigned i = 0; i < m_nodes.size() - 1;
           i++) {
        // Esto...deberia ser un do while
        std::tuple<int, int, int> currEdge = *p;
        while (components.findSet(std::get<0>(currEdge)) ==
               components.findSet(std::get<1>(currEdge))) {
          ++p;
          currEdge = *p;
        }
        ++p;
        treeEdges.push_front(currEdge);
      }

      return Graph(m_nodes, treeEdges);
    }
};

int main() {
  Graph g = Graph(
    std::vector<int>{1, 2, 3, 4, 5, 6, 7},
    std::list<std::tuple<int, int, int>>{
      std::make_tuple(1, 2, 1), std::make_tuple(1, 3, 4),
      std::make_tuple(2, 4, 3), std::make_tuple(4, 5, 3),
      std::make_tuple(2, 3, 7), std::make_tuple(2, 6, 5),
      std::make_tuple(3, 6, 1), std::make_tuple(6, 7, 1)});
  Graph gp = g.prim(4);
  gp.printGraph();
  return 0;
}
