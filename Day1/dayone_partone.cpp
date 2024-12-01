#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <queue>

int main () {
    std::ifstream inputFile("input.txt");
    if(!inputFile){
        std::cerr << "ERROR: Could not open file." << std::endl;
        return 1;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> leftHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightHeap;

    int leftValue, rightvalue;

    while (inputFile >> leftValue >> rightvalue) {
        leftHeap.push(leftValue);
        rightHeap.push(rightvalue);

    }

    inputFile.close();

    long long totalDistance = 0;
    std::cout << "Paired values and their differences:\n";
    while(!leftHeap.empty() && !rightHeap.empty()) {
        totalDistance += std::abs(leftHeap.top() - rightHeap.top());
        leftHeap.pop();
        rightHeap.pop();
    }

    std::cout << "Total distance: " << totalDistance << std::endl;
    return 0;
}