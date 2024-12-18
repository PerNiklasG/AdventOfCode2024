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

void divideGrid(const std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    int midRowStart = rows / 2;
    int midColStart = cols / 2;
    int midRowEnd = (rows % 2 == 0) ? midRowStart - 1 : midRowStart;
    int midColEnd = (cols % 2 == 0) ? midColStart - 1 : midColStart;

    std::map<std::string, int> sectionSums = {
        {"Top-Left", 0},
        {"Top-Right", 0},
        {"Bottom-Left", 0},
        {"Bottom-Right", 0}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < midRowStart && j < midColStart) {
                sectionSums["Top-Left"] += grid[i][j];
            } else if (i < midRowStart && j > midColEnd) {
                sectionSums["Top-Right"] += grid[i][j];
            } else if (i > midRowEnd && j < midColStart) {
                sectionSums["Bottom-Left"] += grid[i][j];
            } else if (i > midRowEnd && j > midColEnd) {
                sectionSums["Bottom-Right"] += grid[i][j];
            }
        }
    }

    long long ans = 1;
    for (const auto& [section, sum] : sectionSums) {
        std::cout << section << " Sum: " << sum << std::endl;
        ans *= sum;
    }

    std::cout << "Answer: " << ans << std::endl;
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

void simulateRobots(std::vector<Robot>& robots, std::vector<std::vector<int>>& grid, int iterations) {
    int rows = grid.size();
    int cols = grid[0].size();

    for(int i = 1; i <= iterations; i++) {
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

/*
        std::cout << "After second: " << i << std::endl;
        for (const auto& row : grid) {
            for(int cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------" << std::endl;
*/
    }
    
    divideGrid(grid);
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
    simulateRobots(robots,grid,100);

    return 0;
}