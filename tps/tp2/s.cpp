#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int maxElement(std::vector<int>);
//Funcion para encontrar la sequencia creciente mas larga (calculando el ancho en vez de la cantidad de elementos),
//podria haberlo optimizado mas haciendo uso del indice del ultimo edeficio que estoy teniendo en cuenta en la sequencia actual, en
//vez de la altura del mismo.
int longestIncreasingSubsequence(const std::vector<int>& buildingsHeights, const std::vector<int>& buildingsWidths, unsigned long currIndex, int lastBuildingHeight, std::vector<std::vector<int>>& matrix){
     if (currIndex == buildingsHeights.size()){
        return 0;
     }
     if (matrix[currIndex][lastBuildingHeight] != -1) {
        return matrix[currIndex][lastBuildingHeight];
     }
     int dontInclude = longestIncreasingSubsequence(buildingsHeights, buildingsWidths, currIndex + 1, lastBuildingHeight, matrix);
     int include = 0;
     if (buildingsHeights[currIndex] > lastBuildingHeight){
        include = buildingsWidths[currIndex] + longestIncreasingSubsequence(buildingsHeights, buildingsWidths, currIndex + 1, buildingsHeights[currIndex], matrix);
     }
     matrix[currIndex][lastBuildingHeight] = std::max(dontInclude, include);
     return matrix[currIndex][lastBuildingHeight];
}

//Podria haber hecho uso de una solo funcion, y usar un parametro mas
//para determinar si incrementar o decrementar el indice actual (currIndex)
int longestDecreasingSubsequence(const std::vector<int>& buildingsHeights, const std::vector<int>& buildingsWidths, int currIndex, int lastBuildingHeight, std::vector<std::vector<int>>& matrix) {
    if (currIndex == -1){
        return 0;
     }
     if (matrix[currIndex][lastBuildingHeight] != -1) {
        return matrix[currIndex][lastBuildingHeight];
     }
     int dontInclude = longestDecreasingSubsequence(buildingsHeights, buildingsWidths, currIndex - 1, lastBuildingHeight, matrix);
     int include = 0;
     if (buildingsHeights[currIndex] > lastBuildingHeight){
        include = buildingsWidths[currIndex] + longestDecreasingSubsequence(buildingsHeights, buildingsWidths, currIndex - 1, buildingsHeights[currIndex], matrix);
     }
     matrix[currIndex][lastBuildingHeight] = std::max(dontInclude, include);
     return matrix[currIndex][lastBuildingHeight];
}
// 
std::string solution(int buildingsAmount, std::vector<int> buildingsHeights, std::vector<int> buildingsWidths) {
    int maxElemen = maxElement(buildingsHeights);
    std::vector<std::vector<int>> matrixIncreasing(buildingsAmount + 1, std::vector<int>(maxElemen + 1, -1));
    std::vector<std::vector<int>> matrixDecreasing(buildingsAmount + 1, std::vector<int>(maxElemen + 1, -1));
    int lengthIncreasing = longestIncreasingSubsequence(buildingsHeights, buildingsWidths, 0, 0, matrixIncreasing);
    int lengthDecreasing = longestDecreasingSubsequence(buildingsHeights, buildingsWidths, buildingsAmount - 1, 0, matrixDecreasing);
    std::string increasingMsg = "Increasing (" + std::to_string(lengthIncreasing) + ").";
    std::string decreasingMsg = "Decreasing (" + std::to_string(lengthDecreasing) + ").";
    if (lengthDecreasing > lengthIncreasing) {
        return decreasingMsg + " " + increasingMsg;
    } else {
        return increasingMsg + " " + decreasingMsg;
    }
}

int maxElement(std::vector<int> v) {
    int curr_max = v[0];
    for (long unsigned i = 1; i < v.size(); i++) {
        if (v[i] > curr_max)
            curr_max = v[i];
    }
    return curr_max;
}

void printVector(std::vector<int> v) {
    for (int i: v) {
        std::cout << i;
    }
    std::cout << "\n";
}

void getInput() {
    int numCases{};
    std::cin >> numCases;
    std::vector<std::string> results{};
    for (int actualCase = 0; actualCase < numCases; actualCase++) {
        int buildingQuantity{};
        std::cin >> buildingQuantity;
        std::vector<int> buildingWidths(buildingQuantity);
        std::vector<int> buildingHeights(buildingQuantity);
        for (int& height : buildingHeights) std::cin >> height;
        for (int& width : buildingWidths) std::cin >> width;
        std::ostringstream result;
        result << "Case " << actualCase + 1 << ". " << solution(buildingQuantity, buildingHeights, buildingWidths);
        results.push_back(result.str());

    }
    for (const auto& res : results) {
        std::cout << res << '\n';
    }

}

int main() {
    getInput();
    return 0;
}
