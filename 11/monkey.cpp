#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

enum Operation { ADD = 0, MUL, SQR, DBL};

struct Monkey {
    std::queue<long> items;
    Operation op;
    long op_arg;
    long test_arg;
    long test_dest[2];
    size_t inpections;
};

typedef long (*tactic_proto)(long, int);

inline long divideByTree(long item, int prod) {
    (void) prod;
    return item / 3;
}

inline long supmod(long item, int prod) {
    return item % prod;
}

tactic_proto tactic[] = { divideByTree, supmod };

size_t simulateMonkeys(std::vector<Monkey> monkeys, size_t max_rounds) {
    int tac_idx = max_rounds > 20;

    long prod = 1;
    for(size_t i = 0; i < monkeys.size(); i++) {
        prod *= monkeys[i].test_arg;
    }

    for(size_t round = 0; round < max_rounds; round++) {
        for(size_t idx = 0; idx < monkeys.size(); idx++) {
            while(!monkeys[idx].items.empty()) {
                long item = monkeys[idx].items.front();
                monkeys[idx].items.pop();
                monkeys[idx].inpections++;

                switch(monkeys[idx].op) {
                    case ADD: item += monkeys[idx].op_arg; break;
                    case MUL: item *= monkeys[idx].op_arg; break;
                    case SQR: item *= item; break;
                    case DBL: item += item; break;
                }

                item = tactic[tac_idx](item, prod);

                long cond = item % monkeys[idx].test_arg == 0;
                int dest = monkeys[idx].test_dest[cond];

                monkeys[dest].items.push(item);
            }
        }
    }

    std::vector<long> inspections;
    for(size_t idx = 0; idx < monkeys.size(); idx++) {
        inspections.push_back(monkeys[idx].inpections);
    }

    std::sort(inspections.begin(), inspections.end(), std::greater<long>());
    return inspections[0] * inspections[1];
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    std::vector<Monkey> monkeys;
    Monkey current;

    while(std::getline(input_data, line)) {
        if(line.find("Starting") == 2) {
            std::stringstream ss(line.substr(18, line.size()));
            std::string arg;

            while(ss >> arg) {
                current.items.push(std::stol(arg));
            }
        }

        else if(line.find("Operation") == 2) {
            char cop = line[23];
            std::string arg = line.substr(25, line.size());

            if(arg == "old") {
                switch(cop) {
                    case '+': current.op = DBL; break;
                    case '*': current.op = SQR; break;
                }
            } else {
                switch(cop) {
                    case '+': current.op = ADD; break;
                    case '*': current.op = MUL; break;
                }

                current.op_arg = std::stol(arg);
            }
        }

        else if(line.find("Test") == 2) {
            current.test_arg = std::stol(line.substr(21, line.size()));
        }

        else if(line.find("If true") == 4) {
            current.test_dest[1] = std::stol(line.substr(29, line.size()));
        }

        else if(line.find("If false") == 4) {
            current.test_dest[0] = std::stol(line.substr(29, line.size()));
            current.inpections = 0;
            monkeys.push_back(current);
            while(!current.items.empty()) current.items.pop();
        }
    }

    size_t part1 = simulateMonkeys(monkeys, 20);
    size_t part2 = simulateMonkeys(monkeys, 10000);

    std::cout << "Anwser for part 1 is " << part1 << '\n';
    std::cout << "Anwser for part 2 is " << part2 << '\n';

    return 0;
}
