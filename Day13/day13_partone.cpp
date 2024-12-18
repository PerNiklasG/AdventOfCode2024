#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <fstream>
#include <sstream>
#include <string>

struct State {
    int x, y, cost, countA, countB;
};

int calculateMinimumCost(int ax, int ay, int costA, int bx, int by, int costB, int targetX, int targetY) {
    std::queue<State> q;
    std::set<std::tuple<int, int, int, int>> visited;
    q.push({0,0,0,0,0});
    visited.insert({0,0,0,0});

    int minCost = INT_MAX;

    while(!q.empty()) {
        State current = q.front();
        q.pop();

        if(current.x == targetX && current.y == targetY) {
            minCost = std::min(minCost, current.cost);
            continue;
        }

        if(current.countA < 100) {
            int newX = current.x + ax;
            int newY = current.y + ay;
            if(newX <= targetX && newY <= targetY && !visited.count({newX, newY, current.countA + 1, current.countB})) {
                visited.insert({newX, newY, current.countA + 1, current.countB});
                q.push({newX, newY, current.cost + costA, current.countA + 1, current.countB});
            }
        }

        if(current.countB < 100) {
            int newX = current.x + bx;
            int newY = current.y + by;
            if (newX <= targetX && newY <= targetY && !visited.count({newX, newY, current.countA, current.countB + 1})) {
                visited.insert({newX, newY, current.countA, current.countB + 1});
                q.push({newX, newY, current.cost + costB, current.countA, current.countB + 1});
            }
        }

    }

    return (minCost == INT_MAX) ? -1 : minCost;
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::string line;
    int ax, ay, bx, by, targetX, targetY;
    int caseNumber = 1;
    int ans = 0;
    while (std::getline(inputFile, line)) {
        if(line.empty()) continue;

        if(line.find("Button A") != std::string::npos) {
            std::sscanf(line.c_str(), "Button A: X+%d, Y+%d", &ax, &ay);
        }

        if(line.find("Button B") != std::string::npos) {
            std::sscanf(line.c_str(), "Button B: X+%d, Y+%d", &bx, &by);
        }

        if(line.find("Prize: ") != std::string::npos) {
            std::sscanf(line.c_str(), "Prize: X=%d, Y=%d", &targetX, &targetY);
            int minCost = calculateMinimumCost(ax, ay, 3, bx, by, 1, targetX, targetY);

            std::cout << "Case " << caseNumber++ << ": ";

            if(minCost == -1) {
                std::cout << "Target not reachable" << std::endl;
            } else {
                std::cout << "Minimum cost to reach target: " << minCost << std::endl;
                ans += minCost;
            }
        }
    }

    inputFile.close();

    std::cout << "Ans: " << ans << std::endl;

    return 0;
}