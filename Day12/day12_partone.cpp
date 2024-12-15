#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void floodFill(int x, int y, char field, const std::vector<std::vector<char>>& grid,
               std::vector<std::vector<bool>>& visited, int& perimeter, int& size) {
    
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::pair<int, int>> stack;
    stack.push_back({x,y});
    visited[x][y] = true;

    while(!stack.empty()) {
        auto [cx, cy] = stack.back();
        stack.pop_back();
        size++;

        int localNeighbours = 0;

        for(int d = 0; d < 4; d++) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if(nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == field) {
                localNeighbours++;
                if(!visited[nx][ny]) {
                    visited[nx][ny] = true;
                    stack.push_back({nx, ny});
                }
            }
        }

        perimeter += 4 - localNeighbours;
    }
}

int main() {
    std::ifstream inputFile("input.txt");
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
    std::vector<std::tuple<char, int, int>> results;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(!visited[i][j]) {
                char field = grid[i][j];
                int perimeter = 0;
                int size = 0;
                floodFill(i, j, field, grid, visited, perimeter, size);
                results.emplace_back(field, size, perimeter);
            }
        }
    }

    long long ans = 0;
    for(const auto& [field, size, perimeter] : results) {
        std::cout << "Field '" << field << "' - Size: " << size << ", Perimeter: " << perimeter
                << ", Product: " << size * perimeter << "\n";
        ans += size*perimeter;
    }

    std::cout << "Answer: " << ans << std::endl;

    return 0;
}