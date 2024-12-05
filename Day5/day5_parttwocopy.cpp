#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <sstream>


int main() {
    std::ifstream inputFile("input.txt");
    if(!inputFile) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::set<std::pair<int,int>> st;
    std::string line;

    while(std::getline(inputFile, line)) {
        if(line.empty() || !isdigit(line[0])) {
            break;
        }

        int pipe = static_cast<int>(line.find('|'));

        int x = std::stoi(line.substr(0, pipe));
        int y = std::stoi(line.substr(pipe + 1));
        st.insert({x,y});
    }

    int ans = 0;
    while(std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string tmp;
        std::vector<int> pages;

        while(std::getline(ss, tmp, ',')) {
            pages.push_back(std::stoi(tmp));
        }

        int n = static_cast<int>(pages.size());


        bool ok = true;

        for(int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if(st.find({pages[j], pages[i]}) != st.end()) {
                    ok = false;
                    break;
                }
            }
        }
        if(!ok) {
            while(!ok) {
                ok = true;
                for(int i = 0; i < n; i++) {
                    for(int j = i + 1; j < n; j++) {
                        if(st.find({pages[j], pages[i]}) != st.end()) {
                            ok = false;
                            std::swap(pages[i], pages[j]);
                        }
                    }
                }
            }   
            ans += pages[n / 2]; 
        }
    }  
    std::cout << "Sum: " << ans << std::endl;

    return 0;
}