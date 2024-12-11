#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <map>

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

void dfs(const std::vector<std::vector<int>>& grid, int x, int y, int prevHeight, std::set<std::pair<int,int>>& visited, std::map<std::pair<int, int>, std::set<std::pair<int, int>>>& pathCount) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (!isValid(x, y, rows, cols) || grid[x][y] != prevHeight + 1 || visited.count({x,y})) {
        return;
    }

    visited.insert({x,y});

    if (grid[x][y] == 9) {
        for(const auto& pos : visited) {
            if(grid[pos.first][pos.second] == 0 ) {
                pathCount[pos].insert({x,y});
            }
        }
    } else {
        dfs(grid, x + 1, y, grid[x][y], visited, pathCount);
        dfs(grid, x - 1, y, grid[x][y], visited, pathCount);
        dfs(grid, x, y + 1, grid[x][y], visited, pathCount);
        dfs(grid, x, y - 1, grid[x][y], visited, pathCount);
    }

    // Backtrack
    visited.erase({x,y});
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    // Read the grid from the input file
    std::vector<std::vector<int>> grid;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<int> row;
        for (char ch : line) {
            if (isdigit(ch)) {
                row.push_back(ch - '0');
            }
        }
        grid.push_back(row);
    }
    inputFile.close();

    int rows = grid.size();
    int cols = grid[0].size();

    std::map<std::pair<int, int>, std::set<std::pair<int, int>>> pathCounts;
    int totalPaths = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 0) {
                std::set<std::pair<int,int>> visited;
                std::cout << "found a 0 at: " << i << "," << j << std::endl;
                dfs(grid, i, j, -1, visited, pathCounts);
            }
        }
    }

    int sum = 0;
    for (const auto& [zero, nines] : pathCounts) {
        std::cout << "0 at " << zero.first << "," << zero.second << " can reach:\n";
        for (const auto& nine : nines) {
            std::cout << "    9 at " << nine.first << "," << nine.second << "\n";
            sum++;
        }
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}