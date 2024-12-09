#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void parseInput(const std::string& line, std::vector<int>& expanded_fs, 
                std::vector<std::vector<int>>& freespace, int& file_count) {
    int curr = 0;
    bool isFile = true;

    for (char c : line) {
        if (isFile) {
            file_count += c - '0';
            for (int i = 0; i < c - '0'; i++) {
                expanded_fs.push_back(curr);
            }
            curr++;
        } else {
            if (c - '0' > 0) {
                freespace.insert(freespace.begin(), {(int)expanded_fs.size(), c - '0'});
            }
            for (int i = 0; i < c - '0'; i++) {
                expanded_fs.push_back(-1);
            }
        }
        isFile = !isFile;
    }
}

void redistributeFiles(std::vector<int>& expanded_fs, std::vector<std::vector<int>>& freespace, 
                       int& last_file, int& working_files, int file_count) {
    while (working_files != file_count) {
        std::vector<int> firstfreespace = freespace.back();
        freespace.pop_back();

        int filesLeft = 0;
        for (int end = last_file; end >= firstfreespace[0] + firstfreespace[1]; end--) {
            if (expanded_fs[end] != -1) {
                expanded_fs[firstfreespace[0] + filesLeft] = expanded_fs[end];
                expanded_fs[end] = -1;
                filesLeft++;
            }
            if (filesLeft == firstfreespace[1]) {
                break;
            }
        }

        for (int i = 0; i < expanded_fs.size(); i++) {
            if (expanded_fs[i] == -1) {
                working_files = i;
                break;
            }
        }
        for (int end = last_file; end >= 0; end--) {
            if (expanded_fs[end] != -1) {
                last_file = end;
                break;
            }
        }
    }
}

long long calculateP1(const std::vector<int>& expanded_fs, int file_count) {
    long long p1 = 0;
    for (int i = 0; i < file_count; i++) {
        p1 += expanded_fs[i] * i;
    }
    return p1;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inputFile, line);

    std::vector<int> expanded_fs;
    std::vector<std::vector<int>> freespace;
    int file_count = 0;

    parseInput(line, expanded_fs, freespace, file_count);

    int last_file = expanded_fs.size() - 1;
    int working_files = line[0] - '0';

    redistributeFiles(expanded_fs, freespace, last_file, working_files, file_count);

    long long p1 = calculateP1(expanded_fs, file_count);
    std::cout << "p1: " << p1 << '\n';

    return 0;
}
