#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool isXPattern(const std::vector<std::vector<char>>&grid, int row, int col) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    if(row - 1 < 0 ||row + 1 >= numRows || col -1 < 0 || col +1 >= numCols) {
        return false;
    }

    return (
        // Pattern 1: S.S, .A., M.M
        (grid[row - 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'S' &&
         grid[row][col] == 'A' &&
         grid[row + 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'M') ||

        // Pattern 2: S.M, .A., S.M
        (grid[row - 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'M' &&
         grid[row][col] == 'A' &&
         grid[row + 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M') ||

        // Pattern 3: M.M, .A., S.S
        (grid[row - 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'M' &&
         grid[row][col] == 'A' &&
         grid[row + 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'S') ||

        // Pattern 4: M.S, .A., M.S
        (grid[row - 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'S' &&
         grid[row][col] == 'A' &&
         grid[row + 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S')
    );
}

int findXPattern(const std::vector<std::vector<char>>& grid) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();

    for(int row=1 ; row < numRows - 1; ++row) {
        for(int col = 1; col < numCols - 1; ++col) {
            if(isXPattern(grid, row, col)) {
                ++count;
            }
        }
    }
    
    return count;
}

int main () {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> grid;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    inputFile.close();

    int occurences = findXPattern(grid);

    std::cout << "Total num of occurences: " << occurences << std::endl;

    return 0;
}