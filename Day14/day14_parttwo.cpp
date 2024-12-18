#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

struct Robot {
    int x, y;
    int vx, vy;
};

bool isChristmasTreePattern(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[col][row] > 1) { // Robot exists in this cell
                return false;
            }
        }
    }
    return true;
}

void parseInput(const std::string& fileName, std::vector<Robot>& robots) {
    std::ifstream inputFile(fileName);
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
    }

    std::vector<std::vector<int>> grid;
    std::string line;

    while(std::getline(inputFile, line)) {
        if (line.empty()) continue;

        Robot robot;
        char discard;
        std::stringstream ss(line);
        ss >> discard >> discard >> robot.x >> discard >> robot.y;
        ss >> discard >> discard >> robot.vx >> discard >> robot.vy;

        robots.push_back(robot);
    }

    inputFile.close();

}

void simulateRobots(std::vector<Robot>& robots, std::vector<std::vector<int>>& grid, long long iterations) {
    int rows = grid.size();
    int cols = grid[0].size();

    for(long long i = 1; i <= iterations; i++) {
        for(auto& row: grid) {
            std::fill(row.begin(), row.end(), 0);
        }

        for(const auto& robot : robots) {
            int newX = (robot.x + robot.vx * i) % cols;
            int newY = (robot.y + robot.vy * i) % rows;

            if(newX < 0) newX += cols;
            if(newY < 0) newY += rows;

            grid[newY][newX]++;
        }
        if(isChristmasTreePattern(grid)) {
           std::cout << "Christmas tree found after: " << i << " seconds!" << std::endl;
           return;
        }
    }
}

void printGrid(std::vector<std::vector<int>>& grid, const std::vector<Robot>& robots) {
    for(auto& robot : robots) {
        grid[robot.y][robot.x]++;
    }
    for(const auto& row: grid) {
        for(int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    const std::string fileName = "input.txt";
    int rows = 103;
    int cols = 101;
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    std::vector<Robot> robots;
    parseInput(fileName, robots);
    //printGrid(grid, robots);
    simulateRobots(robots,grid,1000000000);

    return 0;
}