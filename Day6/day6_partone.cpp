#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Guard {
    std::pair<int,int> position;
    char direction;
};

Guard findGuard (const std::vector<std::string>& grid) {
    Guard guard = {{-1, -1}, '\0'};
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            char c = grid[i][j];
            if(c== '^' || c == 'v' || c == '<' || c == '>') {
                guard = {{i, j}, c};
                std::cout << "Guard found!" << std::endl;
                return guard;
            }
        }
    }
    std::cerr << "Could not find guard!" << std::endl;
    return guard;
}

char rotateDirection(char currentDirection) {
    switch(currentDirection) {
        case '^': return '>';  // Up -> Right
        case '>': return 'v';  // Right -> Down
        case 'v': return '<';  // Down -> Left
        case '<': return '^';  // Left -> Up
        default: return currentDirection;
    }
}

void setDirectionDelta(char direction, int& dRow, int& dCol) {
    switch (direction) {
        case '^': dRow = -1; dCol = 0; break; // Up
        case 'v': dRow = 1; dCol = 0; break;  // Down
        case '<': dRow = 0; dCol = -1; break; // Left
        case '>': dRow = 0; dCol = 1; break;  // Right
        default: dRow = 0; dCol = 0; break;  
    }
}

void path(std::vector<std::string>& grid, Guard& guard) {
    grid[guard.position.first][guard.position.second] = 'x';

    int dRow = 0, dCol = 0;
    setDirectionDelta(guard.direction, dRow, dCol);
    int ans = 1;
    while (true) {
        guard.position.first += dRow;
        guard.position.second += dCol;

        if(guard.position.first < 0 || guard.position.first >= grid.size() || guard.position.second < 0 || guard.position.second >= grid[0].size()) {
            std::cout << "Guard has exited the map!" << std::endl;
            break;
        }

        if(grid[guard.position.first][guard.position.second] == '#') {
            guard.position.first -= dRow;
            guard.position.second -= dCol;
            guard.direction = rotateDirection(guard.direction);
            setDirectionDelta(guard.direction, dRow, dCol);
            continue;
        }
        if(grid[guard.position.first][guard.position.second] != 'x') {
            ans++;
            grid[guard.position.first][guard.position.second] = 'x';
        }
    }
    std::cout << "Number of squares visited: " << ans << std::endl;
}

int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    Guard guard;

    while(getline(inputFile, line)){
        grid.push_back(line);
    }

    inputFile.close();

    for(const auto& it : grid) {
        std::cout << it << std::endl;
    }
    guard = findGuard(grid);

    if(guard.position.first != -1 && guard.position.second != -1) {
        path(grid, guard);

        std::cout << "Updated grid: " << std::endl;
        for(const auto& row: grid) {
            std::cout << row << std::endl;
        }
    }

    return 0;
}