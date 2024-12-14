#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>

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

void mapLoop(std::unordered_map<long long, long long>& numbers) {

}

void rules(std::unordered_map<long long, long long>& numbers) {
    std::unordered_map<long long, long long> result;
    for(auto& [num, count] : numbers) {
        if(num == 0) {
            result[1] += numbers[num];
        } else if(countDigits(num) % 2 == 0) {
            std::pair<long long, long long> split = splitNumber(num);
            result[split.first] += numbers[num];
            result[split.second] += numbers[num];
        } else {
            result[num*2024] += numbers[num];
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

    std::unordered_map<long long, long long> numbers;
    std::string line;

    while(std::getline(inputFile, line)) {
        std::istringstream ss(line);
        long long number;
        while(ss >> number) {
            numbers[number]++;
        }

    }


    std::cout << "Stored numbers: ";
    for(const auto& [num, count] : numbers) {
        std::cout << num << " : " << count << std::endl; 
    }
    std::cout << std::endl;

    int count = 1;
    for(size_t i = 1; i <= 75; i++) {
        rules(numbers);
        std::cout << "We mathing... " << count << std::endl;
        count++;
    }

    long long ans = 0;
    for(const auto& [num, counter] : numbers) {
        ans += counter; 
    }
    std::cout << "Answer: " << ans << std::endl;

    return 0;

}