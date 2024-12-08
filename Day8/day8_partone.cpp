#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

bool isValid(const std::pair<int, int>& pos, int rows, int cols) {
    return pos.first >= 0 && pos.first < rows && pos.second >= 0 && pos.second < cols;
}

void calculateDistance(const std::vector<std::string>& grid, std::set<std::pair<int,int>>& uniquePositions) {
    std::unordered_map<char, std::vector<std::pair<int, int>>> letterPositions;

    for(int row = 0; row < grid.size(); ++row) {
        for(int col = 0; col < grid[row].size(); ++col) {
            char cell = grid[row][col];
            if(std::isalnum(cell)) {
                letterPositions[cell].emplace_back(row, col);
            }
        }
    }

    int rows = grid.size();
    int cols = grid[0].size();

    for(const auto& [letter, positions] : letterPositions) {
        for(size_t i = 0; i < positions.size(); ++i) {
            for(size_t j = i + 1; j < positions.size(); ++j) {
                auto p1 = positions[i];
                auto p2 = positions[j];
                if(p1.second > p2.second || p1.second == p2.second && p1.first > p2.first) {
                    std::swap(p1,p2);
                }


                int dx = p2.second - p1.second;
                int dy = p2.first - p1.first;

                uniquePositions.insert(p1);
                uniquePositions.insert(p2);
                
                int step = 1;
                while (true) {
                    std::pair<int, int> pos1 = {p1.first - dy * step, p1.second - dx  * step};
                    std::pair<int, int> pos2 = {p2.first + dy * step, p2.second + dx * step};

                    if(!isValid(pos1, rows, cols) && !isValid(pos2, rows, cols)) {
                        break;
                    }
                    if(isValid(pos1,rows,cols)) {
                        uniquePositions.insert(pos1);
                    }
                    if(isValid(pos2, rows,cols)){
                        uniquePositions.insert(pos2);
                    }

                    std::cout << "Incrementing step: " << step << " position: " << pos1.first << "," << pos1.second << " " << pos2.first << "," << pos2.second << std::endl;
                    step++;
                }




            }
        }
    }

}

int main () {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;

    while(std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    inputFile.close();

    std::set<std::pair<int,int>> uniquePositions;

    calculateDistance(grid, uniquePositions);

    std::cout << "Unique valid positions: " << std::endl;
    for(const auto& pos : uniquePositions) {
        std::cout << "(" << pos.first << "," << pos.second << ")" << std::endl;
    }

    std::cout << "Sum: " << uniquePositions.size() << std::endl;

    return 0;
}