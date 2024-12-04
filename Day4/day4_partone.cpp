#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const std::string WORD = "XMAS";
const int DIRECTIONS[8][2] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0},
    {1,1},
    {1,-1},
    {-1,1},
    {-1,-1}
};

bool searchFromPosition(const std::vector<std::vector<char>>&grid, int row, int col, int dirX, int dirY) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    for(int i = 0; i < WORD.size(); ++i) {
        int newRow = row +i * dirX;
        int newCol = col +i * dirY;

        if(newRow < 0 || newRow >= numRows || newCol < 0 || newCol > numCols) {
            return false;
        }

        if(grid[newRow][newCol] != WORD[i]) {
            return false;
        }
    }
    return true;
}

int findOccurences(const std::vector<std::vector<char>>& grid) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();

    for(int row=0; row < numRows; ++row) {
        for(int col = 0; col < numCols; ++col) {
            for(const auto& dir: DIRECTIONS) {
                if(searchFromPosition(grid, row, col, dir[0], dir[1])) {
                    count++;
                }
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

    int occurences = findOccurences(grid);

    std::cout << "Total num of occurences: " << occurences << std::endl;

    return 0;
}