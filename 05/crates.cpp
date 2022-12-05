#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define MAX_VECTOR 256

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    std::vector<char> crates[MAX_VECTOR];
    std::vector<char> crates2[MAX_VECTOR];
    size_t max_idx = 0;

    while(std::getline(input_data, line)) {
        if(line.find(" 1", 0) == 0) break;

        for(size_t idx = 0; idx < line.size(); idx++) {
            if(line[idx] == ' ' || line[idx] == '[' || line[idx] == ']')
                continue;

            size_t crate_idx = idx / 4;
            if(crate_idx > max_idx) max_idx = crate_idx;
            crates[crate_idx].push_back(line[idx]);
        }
    }

    for(size_t idx = 0; idx <= max_idx; idx++) {
        std::reverse(crates[idx].begin(), crates[idx].end());
    }

    for(size_t idx = 0; idx <= max_idx; idx++) {
        crates2[idx] = crates[idx];
    }

    std::getline(input_data, line);
    while(std::getline(input_data, line)) {
        size_t count, src, dest;
        std::string nop;

        std::stringstream ss(line);
        ss >> nop >> count >> nop >> src >> nop >> dest;
        src--;
        dest--;

        for(size_t _ = 0; _ < count; _++) {
            char value = crates[src].back();
            crates[src].pop_back();
            crates[dest].push_back(value);
        }

        for(size_t idx = 0; idx < count; idx++) {
            size_t i = crates2[src].size() - count + idx;
            crates2[dest].push_back(crates2[src][i]);
        }

        for(size_t idx = 0; idx < count; idx++) {
            crates2[src].pop_back();
        }
    }

    //for(size_t idx = 0; idx <= max_idx; idx++) {
        //std::cout << idx + 1 << " ";
        //for(size_t i = 0; i < crates[idx].size(); i++) {
            //std::cout << crates[idx][i] << ' ';
        //}
        //std::cout << std::endl;
    //}

    std::cout << "Anwser for part 1 is ";
    for(size_t idx = 0; idx <= max_idx; idx++) {
        std::cout << crates[idx].back();
    }
    std::cout << std::endl;

    std::cout << "Anwser for part 2 is ";
    for(size_t idx = 0; idx <= max_idx; idx++) {
        std::cout << crates2[idx].back();
    }
    std::cout << std::endl;

    return 0;
}
