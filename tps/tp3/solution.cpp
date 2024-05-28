#include <iostream>
#include <vector>


int jj(const std::vector<std::vector<int>>& trees, int f, int t, int h) {
    //matriz donde se guardan la maxima cantidad de bellotas que es posible 
    //conseguir hasta un arbol y altura determinada.
    std::vector<std::vector<int>> solution(h, std::vector<int>(t));
    //vector para guardar la maxima cantidad de bellotas que es posible 
    //conseguir hasta cierta altura
    std::vector<int> maxAcornsAtEachHeight(h);
    for (int tree = 0; tree < t; tree++) {
        solution[0][tree] = trees[tree][0];
        maxAcornsAtEachHeight[0] = std::max(maxAcornsAtEachHeight[0], solution[0][tree]);
    }
    for (int height = 1; height < h; height++) {
        for (int tree = 0; tree < t; tree++) {
            if (height < f) {
                solution[height][tree] = trees[tree][height] + solution[height - 1][tree];
            }
            else {
                //Esta es la razon por la que quiero guardar la maxima cantidad maxima de bellotas en una altura
                //determinada, sino, deberia chequear para cada arbol, cuantas bellotas tienen en la altura height - f
                //y tomar el maximo entre ellos.
                solution[height][tree] = trees[tree][height] + std::max(solution[height - 1][tree], maxAcornsAtEachHeight[height - f]);
            }
             maxAcornsAtEachHeight[height] = std::max(maxAcornsAtEachHeight[height], solution[height][tree]);
        }

    }
    return maxAcornsAtEachHeight[h - 1];

} 

void processInput() {
    int numCases{};
    std::cin >> numCases;
    std::vector<int> results(numCases);
    for (int actualCase = 0; actualCase < numCases; actualCase++) {
        int numberOfTrees{};
        std::cin >> numberOfTrees;
        int treesHeight{};
        std::cin >> treesHeight;
        int heightLoss{};
        std::cin >> heightLoss;
        //Arreglo de dimensiones t x h, en el que la celda en las posiciones t',h' 
        //contiene la cantidad de bellotas en el t'-esimo arbol en la h'-esima altura
        // para tener una estructura conveniente para recorrer
        std::vector<std::vector<int>> trees(numberOfTrees, std::vector<int>(treesHeight));
        for (std::vector<int>& tree: trees) {
            int acornsInTree{};
            std::cin >> acornsInTree;
            int acornHeight{};
            for (int i = 0; i < acornsInTree; i++) {
                std::cin >> acornHeight;
                tree[acornHeight - 1]++;
            }
            
        }
        results[actualCase] = jj(trees, heightLoss, numberOfTrees, treesHeight);
    }
    int zero{};
    std::cin >> zero;
    for (int result : results) {
        std::cout << result << '\n';
    }   
}

int main() {
    processInput();
    return 0;
}
