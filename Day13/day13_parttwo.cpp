#include <iostream>
#include <fstream>
#include <tuple>
#include <algorithm>
#include <limits>
#include <numeric>
#include <string>

// Extended Euclidean Algorithm to solve gcd(a, b) = ax + by
std::tuple<long long, long long, long long> extendedGCD(long long a, long long b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = extendedGCD(b, a % b);
    return {g, y1, x1 - (a / b) * y1};
}

// Solve the equation: a * n_a + b * n_b = target
bool solveDiophantine(long long a, long long b, long long target, long long& n_a, long long& n_b) {
    auto [g, x, y] = extendedGCD(a, b);
    if (target % g != 0) return false; // No solution exists
    long long scale = target / g;
    n_a = x * scale;
    n_b = y * scale;
    return true;
}

// Minimize cost using the general solution form
long long minimizeCost(long long A_x, long long A_y, long long B_x, long long B_y, long long X, long long Y) {
    long long n_a_x, n_b_x, n_a_y, n_b_y;
    long long gcd_x = std::gcd(A_x, B_x);
    long long gcd_y = std::gcd(A_y, B_y);

    // Check if the equations are solvable
    if (X % gcd_x != 0 || Y % gcd_y != 0) return -1; // No solution

    // Find initial solutions
    if (!solveDiophantine(A_x, B_x, X, n_a_x, n_b_x)) return -1;
    if (!solveDiophantine(A_y, B_y, Y, n_a_y, n_b_y)) return -1;

    // General solution parameters
    long long stepX_a = B_x / gcd_x, stepX_b = -A_x / gcd_x;
    long long stepY_a = B_y / gcd_y, stepY_b = -A_y / gcd_y;

    long long minCost = std::numeric_limits<long long>::max();

    // Iterate over possible values for one variable and adjust the other
    for (long long k_x = -1000000; k_x <= 1000000; ++k_x) {
        long long new_n_a_x = n_a_x + k_x * stepX_a;
        long long new_n_b_x = n_b_x + k_x * stepX_b;

        if (new_n_a_x < 0 || new_n_b_x < 0) continue;

        for (long long k_y = -1000000; k_y <= 1000000; ++k_y) {
            long long new_n_a_y = n_a_y + k_y * stepY_a;
            long long new_n_b_y = n_b_y + k_y * stepY_b;

            if (new_n_a_y < 0 || new_n_b_y < 0) continue;

            if (new_n_a_x == new_n_a_y && new_n_b_x == new_n_b_y) {
                long long cost = 3 * new_n_a_x + new_n_b_x;
                minCost = std::min(minCost, cost);
            }
        }
    }

    return (minCost == std::numeric_limits<long long>::max()) ? -1 : minCost;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    long long tokens = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        long long ax, ay, bx, by, targetX, targetY;

        if(line.find("Button A") != std::string::npos) {
            std::sscanf(line.c_str(), "Button A: X+%d, Y+%d", &ax, &ay);
        }

        if(line.find("Button B") != std::string::npos) {
            std::sscanf(line.c_str(), "Button B: X+%d, Y+%d", &bx, &by);
        }

        if(line.find("Prize: ") != std::string::npos) {
            std::sscanf(line.c_str(), "Prize: X=%d, Y=%d", &targetX, &targetY);
        }

        targetX += 10000000000000;
        targetY += 10000000000000;

        long long numeratorX = targetX*by - targetY*bx;
        long long denomiatorX = ax*by - ay*bx;

        long long numeratorY = targetX * ay - targetY * ax;
        long long denomiatorY = ay * bx - ax*by;

        if(numeratorX % denomiatorX == 0 && numeratorY % denomiatorY == 0) {
            long long a = numeratorX / denomiatorX;
            long long b = numeratorY / denomiatorY;
            tokens += 3*a+b;
            std::cout << 3*a+b << std::endl;
        }

        
    }

    std::cout << "Answer: " << tokens << std::endl;
    return 0;
}
