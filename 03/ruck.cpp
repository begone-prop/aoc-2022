#include <iostream>
#include <fstream>
#include <set>

static int counts[52];
static int counts2[52];

inline size_t char_to_idx(char c) {
    if(c > 'a') return c - 'a';
    else return c - 'A' + 26;
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    size_t sum = 0;
    size_t sum2 = 0;

    size_t line_no = 0;

    while(std::getline(input_data, line)) {
        size_t comp_size = line.size() / 2;

        for(size_t idx = 0; idx < comp_size; idx++) {
            int count_idx = char_to_idx(line[idx]);
            counts[count_idx]++;
        }

        for(size_t idx = comp_size; idx < line.size(); idx++) {
            int cdx = char_to_idx(line[idx]);
            if(counts[cdx] > 0) {
                sum += cdx + 1;
                break;
            }
        }

        for(int i = 0; i < 52; i++) {
            counts[i] = 0;
        }

        if(line_no && line_no % 3 == 2) {
            std::cout << "Group end\n";
            for(size_t idx = 0; idx < line.size(); idx++) {
                int cdx = char_to_idx(line[idx]);
                if(counts2[cdx] == 2) {
                    sum2 += cdx + 1;
                    std::cout << line[idx] << '\n';
                    break;
                }
            }

            for(int i = 0; i < 52; i++) {
                counts2[i] = 0;
            }
        } else {
            std::cout << "Counting...\n";
            std::set<char> uniq;

            for(size_t idx = 0; idx < line.size(); idx++) {
                uniq.insert(line[idx]);
            }

            std::set<char>::iterator it;
            for(it = uniq.begin(); it != uniq.end(); it++) {
                int cdx = char_to_idx(*it);
                counts2[cdx]++;
            }
        }

        line_no++;
    }

    std::cout << "Anwser for part 1 is " << sum << '\n';
    std::cout << "Anwser for part 2 is " << sum2 << '\n';

    return 0;
}
