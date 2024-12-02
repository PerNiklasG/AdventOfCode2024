#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

bool isValidRow(const std::vector<int>& row) {
    if (row.size() < 2) {
        return true;
    }

    auto isMonotonic = [](const std::vector<int>& vec) {
        bool increasing = vec[1] > vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            int diff = std::abs(vec[i] - vec[i - 1]);
            if (diff < 1 || diff > 3) return false;
            if ((increasing && vec[i] <= vec[i - 1]) || 
                (!increasing && vec[i] >= vec[i - 1])) return false; 
        }
        return true;
    };

    if (isMonotonic(row)) return true;

    for (size_t i = 0; i < row.size(); ++i) {
        std::vector<int> modifiedRow = row;
        modifiedRow.erase(modifiedRow.begin() + i);
        if (isMonotonic(modifiedRow)) return true;
    }

    return false;
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "ERROR: Could not open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> matrix;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int number;

        while(iss >> number) {
            row.push_back(number);
        }

        matrix.push_back(row);
    }

    inputFile.close();
    int numberOfValidRows = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if(isValidRow(matrix[i])) {
            std::cout << "Row " << i + 1 << " is valid." << std::endl;
            numberOfValidRows++;
        } else {
            std::cout << "Row " << i + 1 << " is invalid." << std::endl;
        }
    }

    std::cout << "Number of valid rows: " << numberOfValidRows << std::endl;

    return 0;
}