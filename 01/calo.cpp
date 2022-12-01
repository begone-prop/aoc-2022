#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

int main(void) {
    static const char* input_file = "./input";

    std::ifstream input_data(input_file);
    std::string line;

    long sum = 0;

    std::vector<long> sums;

    while(std::getline(input_data, line)) {
        if(line != "") {
            sum += std::stol(line);
            if(input_data.peek() != EOF) continue;
        }

        sums.push_back(sum);
        sum = 0;
    }

    std::sort(sums.begin(), sums.end());

    std::cout << "Anwser for part 1 is " << sums[sums.size() - 1] << '\n';
    std::cout << "Anwser for part 1 is " <<
        sums[sums.size() - 1] + sums[sums.size() - 2] + sums[sums.size() - 3] << '\n';

    return 0;
}
