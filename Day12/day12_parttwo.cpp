#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y, const std::vector<std::vector<char>>& grid, 
             std::vector<std::vector<bool>>& visited, char target) {
    return x >= 0 && x < grid.size() &&
           y >= 0 && y < grid[0].size() &&
           !visited[x][y] &&
           grid[x][y] == target;
}

void floodFill(const std::vector<std::vector<char>>& grid, int x, int y, 
               std::vector<std::vector<bool>>& visited, int& size, int& sides) {
    
    int rows = grid.size();
    int cols = grid[0].size();
    char target = grid[x][y];
    visited[x][y] = true;
    size++;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (isValid(nx, ny, grid, visited, target)) {
            floodFill(grid, nx, ny, visited, size, sides);
        } else if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != target) {
            sides++;
        }
    }
}

int main() {
    std::ifstream inputFile("test_input.txt");
    if(!inputFile)  {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> grid;
    std::string line;
    while(std::getline(inputFile,line)) {
        grid.emplace_back(line.begin(), line.end());
    }

    inputFile.close();

    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::pair<int, int>> results;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(!visited[i][j]) {
                int sides = 0;
                int size = 0;
                floodFill(grid, i, j, visited, size, sides);
                results.emplace_back(size, sides);
            }
        }
    }

    long long ans = 0;
    for(const auto& [size, sides] : results) {
        std::cout << "Size: " << size << ", Sides: " << sides
                << ", Product: " << size * sides << "\n";
        ans += size*sides;
    }

    std::cout << "Answer: " << ans << std::endl;

    return 0;
}