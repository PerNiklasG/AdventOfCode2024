#include <iostream>
#include <fstream>
#include <unordered_map>

int main () {
    std::ifstream inputFile("input.txt");
    if(!inputFile){
        std::cerr << "ERROR: Could not open file." << std::endl;
        return 1;
    }

    std::unordered_map<int, int> rightFrequencyMap;
    int leftValue, rightvalue;

    while (inputFile >> leftValue >> rightvalue) {
        rightFrequencyMap[rightvalue]++;
    }

    inputFile.clear();
    inputFile.seekg(0);

    long long totalSimiliarity = 0;
    std::cout << "Occurences of numbers from the left list in the right list:" << std::endl;
    while(inputFile >> leftValue >> rightvalue) {
        int occurencesInRight = rightFrequencyMap[leftValue];
        long long similarity = leftValue * occurencesInRight;
        totalSimiliarity += similarity;
        std::cout << "Number " << leftValue << " occurs " << occurencesInRight << " times in the right list. Similarity score: " << similarity << std::endl;
    }

    std::cout << "Total similarity score: " << totalSimiliarity << std::endl;
    inputFile.close();

    return 0;
}