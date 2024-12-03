#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "ERROR: Could not open file!" << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::regex mulPattern(R"(mul\((\d+),(\d+)\))");
    std::regex doPattern(R"(do\(\))");
    std::regex dontPattern(R"(don't\(\))");  
    std::regex combinedPattern("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");

    bool isActive = true;
    auto words_begin = std::sregex_iterator(content.begin(), content.end(), combinedPattern);
    auto words_end = std::sregex_iterator();

    long long totalSum = 0;

    std::cout << "Found matches: " << std::endl;
    for(auto it = words_begin; it != words_end; ++it) {
        std::smatch match = *it;
        std::string matchStr = match.str();

        if(std::regex_match(matchStr, doPattern)) {
            isActive = true;
            std::cout << "Enabled multiplication." << std::endl;
        } else if (std::regex_match(matchStr, dontPattern)) {
            isActive = false;
            std::cout << "Disabled multiplication." << std::endl;
        }

        if(isActive && std::regex_match(matchStr, mulPattern)) {
            std::cout << "First number (match[1]): " << match[1].str() << '\n';
            std::cout << "Second number (match[2]): " << match[2].str() << '\n';
            std::cout << "Full match: " << match.str() << std::endl;

            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str()); 
            int product = num1 * num2;   
            totalSum += product;
        }
    }

    std::cout << "Total Sum: " << totalSum << std::endl;
    return 0;
}