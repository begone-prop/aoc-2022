#include <iostream>
#include <cstring>
#include <fstream>

size_t findMarkerOffset(const std::string& message, size_t window_size) {
    size_t offset = 0;

    int signals[26];
    const size_t signals_size = sizeof(signals) / sizeof(signals[0]);

    for(size_t idx = 0; idx < message.size() - window_size; idx++) {
        for(size_t i = 0; i < window_size; i++) {
            signals[message[idx + i] - 'a']++;
        }

        bool term = true;
        for(size_t j = 0; j < signals_size; j++) {
            if(signals[j] >= 2) {
                term = false;
                break;
            }
        }

        if(term) {
            offset = idx + window_size;
            break;
        }

        std::memset(signals, 0, sizeof(int) * signals_size);
    }

    return offset;
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    std::getline(input_data, line);

    size_t distance = findMarkerOffset(line, 4);
    size_t distance2 = findMarkerOffset(line, 14);

    std::cout << "Anwser for part 1 is " << distance << '\n';
    std::cout << "Anwser for part 2 is " << distance2 << '\n';

    return 0;
}
