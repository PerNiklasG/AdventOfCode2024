#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

void parseInput(const std::string& line, std::vector<int>& expanded_fs, 
                std::vector<std::vector<int>>& freespace, 
                std::vector<int>& filestarts, std::vector<int>& sizes, int& file_count) {
    int current_id = 0;
    bool isfile = true;

    for (char ch : line) {
        if (isfile) {
            filestarts.push_back(expanded_fs.size());
            sizes.push_back(ch - '0');
            file_count += ch - '0';
            for (int i = 0; i < ch - '0'; i++) {
                expanded_fs.push_back(current_id);
            }
            current_id++;
        } else {
            if (ch - '0' > 0) {
                freespace.push_back({(int)expanded_fs.size(), ch - '0'});
            }
            for (int i = 0; i < ch - '0'; i++) {
                expanded_fs.push_back(-1);
            }
        }
        isfile = !isfile;
    }
}

bool rearrangeFiles(std::vector<int>& expanded_fs, const std::vector<int>& filestarts, 
                    const std::vector<int>& sizes, std::vector<std::vector<int>>& freespace, 
                    std::set<int>& locs_to_skip) {
    bool any_works = false;

    for (int i = filestarts.size() - 1; i >= 0; i--) {
        if (locs_to_skip.find(i) != locs_to_skip.end())
            continue;

        bool this_works = false;

        for (int j = 0; j < freespace.size(); j++) {
            if (freespace[j][0] > filestarts[i])
                break;

            if (freespace[j][1] >= sizes[i]) {
                this_works = true;

                for (int copy_idx = 0; copy_idx < sizes[i]; copy_idx++) {
                    expanded_fs[freespace[j][0] + copy_idx] = expanded_fs[filestarts[i] + copy_idx];
                    expanded_fs[filestarts[i] + copy_idx] = -1;
                }

                freespace[j][0] += sizes[i];
                freespace[j][1] -= sizes[i];
                locs_to_skip.insert(i);
                break;
            }
        }

        any_works |= this_works;
    }

    return any_works;
}

long long calculateP2(const std::vector<int>& expanded_fs) {
    long long p2 = 0;

    for (size_t i = 0; i < expanded_fs.size(); i++) {
        if (expanded_fs[i] != -1) {
            p2 += expanded_fs[i] * i;
        }
    }

    return p2;
}

int main() {
    std::ifstream in("input.txt");
    if (!in) {
        std::cerr << "Error: Could not open input file.\n";
        return 1;
    }

    std::string line;
    getline(in, line);

    std::vector<int> expanded_fs;
    std::vector<std::vector<int>> freespace;
    std::vector<int> filestarts;
    std::vector<int> sizes;
    int file_count = 0;

    parseInput(line, expanded_fs, freespace, filestarts, sizes, file_count);

    std::set<int> locs_to_skip;
    while (rearrangeFiles(expanded_fs, filestarts, sizes, freespace, locs_to_skip)) {}

    long long p2 = calculateP2(expanded_fs);
    std::cout << "p2: " << p2 << '\n';

    return 0;
}
