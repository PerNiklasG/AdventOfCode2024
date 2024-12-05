#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>

void printRow(const std::vector<int>& row) {
    std::cout << "Checking row: ";
    for (int num : row) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void printPairsMap(const std::unordered_map<int, std::vector<int>>& pairsMap) {
    std::cout << "pairsMap contents:" << std::endl;
    for (const auto& pair : pairsMap) {
        std::cout << pair.first << ": ";
        for (int num : pair.second) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

bool isValidRow(const std::unordered_map<int, std::vector<int>>& pairsMap, const std::vector<int>& row) {
    for(size_t i = 0; i < row.size()-1; ++i) {
        int current = row[i];
        auto it = pairsMap.find(current);
        if(it==pairsMap.end()) {
            return false;
        }

        const auto& validRightNumbers = it->second;
        for(size_t j = i + 1; j < row.size(); ++j) {
            int next = row[j];
            if(std::find(validRightNumbers.begin(), validRightNumbers.end(), next) == validRightNumbers.end()) {
                return false;
            } else {
            }
        }
    
    }
    return true;
}

bool backtrack(std::unordered_map<int, std::vector<int>>& pairsMap, std::vector<int>& row, std::vector<int>& result, std::vector<bool>& used, int depth) {
    if(depth == row.size()) {
        return isValidRow(pairsMap, result);
    }

    for(size_t i = 0; i < row.size(); ++i) {
        if(used[i]) continue;

        result[depth] = row[i];
        used[i] = true;

        if (backtrack(pairsMap, row, result, used, depth + 1)) {
            return true;
        }

        used[i] = false;
    }

    return false;
}

std::vector<int> reorderRow(std::unordered_map<int, std::vector<int>>& pairsMap, std::vector<int>& row) {
    std::vector<int> result(row.size(), 0);
    std::vector<bool> used(row.size(), false);

    if(backtrack(pairsMap, row, result, used, 0)) {
        return result;
    }

    return {};
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::unordered_map<int, std::vector<int>> pairsMap;
    std::vector<std::vector<int>> validRows, invalidRows;
    std::string line;

    while(std::getline(inputFile, line) && !line.empty()){
        std::stringstream ss(line);
        std::string left, right;
        if(std::getline(ss, left, '|') && std::getline(ss,right)) {
            int first = std::stoi(left);
            int second = std::stoi(right);
            pairsMap[first].push_back(second);
        }
    }

    std::cout << "PairsMap contents:\n";
    for (const auto& pair : pairsMap) {
        std::cout << pair.first << ": ";
        for (int num : pair.second) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    while (std::getline(inputFile, line)) {
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string number;
        std::vector<int> row;
        
        while (std::getline(ss,number,',')) {
            row.push_back(std::stoi(number));
        }

        if (isValidRow(pairsMap, row)) {
            validRows.push_back(row);
        }
        else {
            invalidRows.push_back(row);
        }
    }
    inputFile.close();

    std::cout << "Valid rows:\n";
    for (const auto& row : validRows) {
        for(int num: row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> reorderedRows;
    std::cout << "Invalid rows:\n";
    for (std::vector<int> row : invalidRows) {
        for(int num: row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int counter = 0;
    for (std::vector<int> row : invalidRows) {
        std::cout << "Trying to reorder row: " << ++counter << " out of " << invalidRows.size() << std::endl;
        std::vector<int> reorderedRow = reorderRow(pairsMap, row);
        if (!reorderedRow.empty()) {
            reorderedRows.push_back(reorderedRow);
        }
    }

    int sum = 0;
    std::cout << "Reordered valid rows: " << std::endl;
    for (auto& row: reorderedRows) {
        int middleIndex = row.size() / 2;
        sum += row[middleIndex];
        for(int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}