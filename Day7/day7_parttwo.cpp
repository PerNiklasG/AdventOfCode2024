#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

bool findCombinations(const std::vector<long long>& values, long long target, std::vector<char>& operators, int index);
long long calibrationEquation(const std::vector<long long>& values, std::vector<char>& operators);

bool findCombinations(const std::vector<long long>& values, long long target, std::vector<char>& operators, int index) {
    if(index == values.size() -1) {
        long long result = calibrationEquation(values, operators);

        if (result == target) {
            std::cout << values[0];
            for(size_t i = 0; i < operators.size(); ++i) {
                std::cout << " " << operators[i] << " " << values[i + 1];
            }
            std::cout << " = " << result << std::endl;
            return true;
        }
        return false;;
    }

    bool found = false;
    operators[index] = '+';
    found |= findCombinations(values, target, operators, index+1);

    operators[index] = '*';
    found |= findCombinations(values, target, operators, index + 1);

    operators[index] = '|';
    found |= findCombinations(values, target, operators, index +1);

    return found;
}

long long calibrationEquation(const std::vector<long long>& values, std::vector<char>& operators) {
    long long result = values[0];

    for(size_t i = 0; i < operators.size(); ++i) {
        if(operators[i] == '+') {
            result += values[i+1];
        } else if (operators[i] == '*') {
            result *= values[i+1];
        } else if (operators[i] == '|') {
            std::string concatenated = std::to_string(result)+std::to_string(values[i+1]);
            result = std::stoll(concatenated);
        }
    }
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::map<long long, std::vector<long long>> calibrations;
    std::string line;

    while(std::getline(inputFile, line)) {
        std::istringstream lineStream(line);

        long long key;
        char colon;
        lineStream >> key >> colon;

        if(colon != ':') {
            std::cout << key << std::endl;
            std::cerr << "Error: Invalid input values." << std::endl;
            return 1; 
        }

        std::vector<long long> values;
        long long value;
        while(lineStream >> value) {
            values.emplace_back(value);
        }

        calibrations[key] = values;
    }

    inputFile.close();

    long long count = 0;
    for(const auto& [key, values] : calibrations) {
        std::vector<char> operators(values.size()-1, '*');
        if(findCombinations(values, key, operators, 0)) {
            count += key;
        }
    }

    std::cout << "Number of possible calibrations: " << count << std::endl;

    return 0;
}