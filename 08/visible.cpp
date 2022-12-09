#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    vector<vector<int>> trees;
    size_t visible = 0;
    size_t rows = 0;

    while(std::getline(input_data, line)) {
        vector<int> current;
        for(size_t idx = 0; idx < line.size(); idx++) {
            current.push_back(line[idx] - '0');
        }

        trees.push_back(current);
        rows++;
    }

    for(size_t idx = 1; idx < trees.size() - 1; idx++) {
        for(size_t i = 1; i < trees[idx].size() - 1; i++) {
            int current_tree = trees[idx][i];

            // from left
            bool blocked = false;
            for(size_t j = 0; j < i; j++) {
                if(current_tree <= trees[idx][j]) {
                    blocked = true;
                    break;
                };
            }

            if(!blocked)  goto seen;

            // from right
            blocked = false;
            for(size_t j = trees[idx].size() - 1; j > i; j--) {
                if(current_tree <= trees[idx][j]) {
                    blocked = true;
                    break;
                }
            }

            if(!blocked) goto seen;

            //// from top
            blocked = false;
            for(size_t r = 0; r < idx; r++) {
                if(current_tree <= trees[r][i]) {
                    blocked = true;
                    break;
                }
            }

            if(!blocked) goto seen;

            // from botom
            blocked = false;
            for(size_t r = rows - 1; r > idx; r--) {
                if(current_tree <= trees[r][i]) {
                    blocked = true;
                    break;
                }
            }

            if(!blocked) goto seen;
            goto next;

            seen:
            visible++;
            next: ;
        }
    }

    //vector<vector<size_t>> scores;
    size_t max = 0;
    for(size_t idx = 1; idx < trees.size() - 1; idx++) {
        for(size_t i = 1; i < trees[idx].size() - 1; i++) {
            int current_tree = trees[idx][i];

            // left
            size_t l_score = 0;
            for(int l = i - 1; l >= 0; l--) {
                l_score++;
                if(current_tree <= trees[idx][l]) break;
            }

            // right
            size_t r_score = 0;
            for(size_t r = i + 1; r < trees[idx].size(); r++) {
                r_score++;
                if(current_tree <= trees[idx][r]) break;
            }

            // up
            size_t u_score = 0;
            for(int u = idx - 1; u >= 0; u--) {
                u_score++;
                if(current_tree <= trees[u][i]) break;
            }

            // down
            size_t d_score = 0;
            for(size_t d = idx + 1; d < rows; d++) {
                d_score++;
                if(current_tree <= trees[d][i]) break;
            }

            size_t current_score = l_score * r_score * u_score * d_score;
            if(max < current_score) max = current_score;
        }
    }

    size_t perim = (trees.size() * 2 + rows * 2) - 4;

    std::cout << "Anwser for part 1 is " << visible + perim << '\n';
    std::cout << "Anwser for part 1 is " << max << '\n';

    return 0;
}
