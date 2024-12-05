#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>

bool pairExists(std::vector<std::pair<int,int>>& pairs, int a, int b) {
    return std::find(pairs.begin(), pairs.end(), std::make_pair(a,b)) != pairs.end();
}

int main() {
    std::ifstream inputFile("test_input.txt");
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::vector<std::pair<int,int>> pairs;
    std::vector<std::vector<int>> rows;
    std::string line;
    bool isSecondSection = false;

    while(std::getline(inputFile, line)){
        if(line.empty()) {
            isSecondSection = true;
            continue;
        }

        if(!isSecondSection) {
            std::stringstream ss(line);
            std::string left, right;
            if(std::getline(ss, left, '|') && std::getline(ss,right)) {
                int first = std::stoi(left);
                int second = std::stoi(right);
                pairs.emplace_back(first, second);
            }
        } else {
            std::stringstream ss(line);
            std::string number;
            std::vector<int> row;
            while (std::getline(ss,number,',')) {
                row.push_back(std::stoi(number));
            }
            rows.push_back(row);
        }
    }
    inputFile.close();

    std::cout << "Sorted Pairs from Section 1:\n";
    for (const auto& p : pairs) {
        std::cout << p.first << " | " << p.second << '\n';
    }

    std::cout << "\nVectors from Section 2:\n";
    for (const auto& vec : rows) {
        for (int num : vec) {
            std::cout << num << " ";
        }
        std::cout << '\n';
    }

    int sum = 0;
    for (const auto& row : rows) {
        bool isValid = true;
        for (size_t i = 0; i< row.size() && isValid; i++) {
            for(size_t j = i+1; j < row.size(); ++j) {
                int a = row[i];
                int b = row[j];
                if(!pairExists(pairs, a, b)) {
                    isValid=false;
                    break;
                }
            }
        }

        if(isValid) {
            int middleIndex = row.size() / 2;
            sum += row[middleIndex];
        }

        std::cout << "Row: ";
        for(int num : row) {
            std::cout << num << " ";
        }
        std::cout << (isValid ? "is VALID" : "is INVALID") << std::endl;
    }

    std::cout << "Sum is: " << sum << std::endl;

    return 0;
}