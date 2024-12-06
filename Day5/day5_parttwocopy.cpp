#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>

bool findInSet(const std::unordered_map<int, std::set<int>> pairsMap, int key, int number) {
    auto it = pairsMap.find(key);
    if (it == pairsMap.end()) {
        return false;
    }

    const std::set<int>&numberSet = it-> second;

    auto setIt = numberSet.find(number);
    if(setIt != numberSet.end()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::set<std::pair<int, int>> pairsSet;
    std::vector<std::vector<int>> validRows, invalidRows;
    std::string line;

    while(std::getline(inputFile, line) && !line.empty()){
        std::stringstream ss(line);
        std::string left, right;
        if(std::getline(ss, left, '|') && std::getline(ss,right)) {
            int first = std::stoi(left);
            int second = std::stoi(right);
            pairsSet.insert({first, second});
        }
    }

    std::cout << "PairsMap contents:\n";
    for (const auto& pair : pairsSet) {
        std::cout << "(" << pair.first << "," << pair.second << ")" << std::endl;
    }
    std::cout << "\n";

    int sum = 0;
    while (std::getline(inputFile, line)) {
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string number;
        std::vector<int> row;
        
        while (std::getline(ss,number,',')) {
            row.push_back(std::stoi(number));
        }

        bool ok = true;
        for (int i = 0; i < row.size(); i++) {
            for(int j = i + 1; j < row.size(); j++) {
                if(pairsSet.find({row[j], row[i]}) != pairsSet.end()) {
                    ok = false;
                    break;
                }
            }
        }

        if(!ok) {
            while(!ok) {
                ok = true;
                for(int i = 0; i < row.size(); i++) {
                    for(int j = i + 1; j < row.size(); j++) {
                        if(pairsSet.find({row[j], row[i]}) != pairsSet.end()) {
                            ok = false;
                            std::swap(row[i], row[j]);
                        }
                    }
                }
            }
            sum += row[row.size() / 2];
        }   
    }
    inputFile.close();


    std::cout << "Sum: " << sum << std::endl;

    return 0;
}