#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>

enum OP {
    NOOP = 0,
    ADDX
};

void printCRT(const char crt[6][40]) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 40; j++) {
            std::cout << crt[i][j];
        }
        std::cout << '\n';
    }
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    long int regx = 1;
    size_t cycle = 0;
    int cycle_count;

    long int sum = 0;
    char crt[6][40];
    memset(crt, '.', 240);

    while(std::getline(input_data, line)) {
        OP op;
        std::stringstream ss(line);
        std::string opstr;
        int arg;

        ss >> opstr >> arg;

        if(opstr == "noop") {
            cycle_count = 1;
            op = NOOP;
        }
        else {
            cycle_count = 2;
            op = ADDX;
        }

        for(int count = 1; count <= cycle_count; count++) {
            int crt_row = cycle / 40;
            int crt_col = cycle % 40;

            if(std::abs(regx - crt_col) < 2) crt[crt_row][crt_col] = '#';

            cycle++;

            if((cycle == 20 || ((cycle > 40 && ((cycle - 20) % 40) == 0)))) {
                sum += (cycle * regx);
            }

            if(op == ADDX && count == cycle_count) regx += arg;

        }
    }

    std::cout << "Anwser for part 1 is " << sum << '\n';
    std::cout << "Anwser for part 2 is\n";
    printCRT(crt);

    return 0;
}
