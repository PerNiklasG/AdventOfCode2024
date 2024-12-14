#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

long long countDigits(long long number) {
    long long count = 0;
    if(number == 0) return 1;
    while(number != 0){
        number /= 10;
        count++;
    }
    return count;
}

std::pair<long long, long long> splitNumber(long long num) {
    long long numDigits = countDigits(num);
    long long halfDigits = numDigits/2;
    long long divisor = static_cast<long long>(std::pow(10, halfDigits));

    long long secondHalf = num % divisor;
    long long firstHalf = num / divisor;

    return {firstHalf, secondHalf};
}

void rules(std::vector<long long>& numbers) {
    std::vector<long long> result;
    for(size_t i = 0; i < numbers.size(); i++) {
        if (numbers[i] == 0) {
            result.push_back(1);
        } else if(countDigits(numbers[i]) % 2 == 0) {
            std::pair<long long,long long> split = splitNumber(numbers[i]);
            result.push_back(split.first);
            result.push_back(split.second);
        } else {
            result.push_back(numbers[i]*2024);
        }
    }

    numbers = result;
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "error: could not open file." << std::endl;
        return 1;
    }

    std::vector<long long> numbers;
    std::string line;

    while(std::getline(inputFile, line)) {
        std::istringstream ss(line);
        long long number;
        while(ss >> number) {
            numbers.push_back(number);
        }

    }


    std::cout << "Stored numbers: ";
    for(const auto& num : numbers) {
        std::cout << num << " "; 
    }
    std::cout << std::endl;

    int count = 0;
    for(size_t i = 0; i < 75; i++) {
        rules(numbers);
        std::cout << "We mathing... " << count << std::endl;
        count++;
    }

    std::cout << "Answer: " << numbers.size() << std::endl;

    return 0;

}