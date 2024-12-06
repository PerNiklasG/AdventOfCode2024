#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

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

void printGrid(std::vector<std::string>& grid) {
    for(const auto& it : grid) {
        std::cout << it << std::endl;
    }
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

bool loopPath(std::vector<std::string>& grid, Guard& guard) {
    std::unordered_set<std::string> visitedStates;
    int row = guard.position.first;
    int col = guard.position.second;

    int dRow = 0, dCol = 0;
    setDirectionDelta(guard.direction, dRow, dCol);
    int ans = 1;
    while (true) {
        guard.position.first += dRow;
        guard.position.second += dCol;
        if(guard.position.first < 0 || guard.position.first >= grid.size() || guard.position.second < 0 || guard.position.second >= grid[0].size()) {
            std::cout << "Guard has exited the map!" << std::endl;
            return false;
        }

        std::string state = std::to_string(row) + "," + std::to_string(col) + "," + std::string(1, guard.direction);

        if (visitedStates.count(state) > 0) {
            return true; 
        }

        visitedStates.insert(state);

        if(grid[guard.position.first][guard.position.second] == '#') {
            
            guard.position.first -= dRow;
            guard.position.second -= dCol;
            guard.direction = rotateDirection(guard.direction);
            setDirectionDelta(guard.direction, dRow, dCol);
        }

    }
    return false;
}

int countLoopCreatingPositions(std::vector<std::string>& grid, Guard& guard) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    // Try placing a '#' at every empty cell ('.') and check if it creates a loop
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#'; // Place the wall

                printGrid(grid);
                // Simulate guard's movement and check if it forms a loop
                if (loopPath(grid, guard)) {
                    ++count; // Increment if a loop is formed
                }

                grid[i][j] = '.'; // Remove the wall after checking
            }
        }
    }

    return count; // Return the count of valid positions
}



int main() {
    std::ifstream inputFile("test_input.txt");
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

    int loopCount = 0;
    if(guard.position.first != -1 && guard.position.second != -1) {
        loopCount = countLoopCreatingPositions(grid, guard);
    }

    std::cout << "Number of possible loop conditions: " << loopCount << std::endl;

    return 0;
}