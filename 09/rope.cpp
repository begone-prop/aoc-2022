#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

struct knot {
    int y;
    int x;
};

struct Move {
    char direction;
    int count;
};

size_t countVisited(const std::vector<Move>& moves, size_t knot_count) {
    std::vector<knot> rope(knot_count, {0, 0});
    std::vector<knot> seen;

    for(size_t idx = 0; idx < moves.size(); idx++) {
        knot move;
        switch(moves[idx].direction) {
            case 'U': move = {-1,  0}; break;
            case 'D': move = { 1,  0}; break;
            case 'L': move = { 0, -1}; break;
            case 'R': move = { 0,  1}; break;
        }

        for(int step = 0; step < moves[idx].count; step++) {
            rope[0].y += move.y;
            rope[0].x += move.x;

            for(int k = 1; k < knot_count; k++) {
                int prev = k - 1;

                knot delta = {
                    abs(rope[prev].y - rope[k].y),
                    abs(rope[prev].x - rope[k].x),
                };

                if(delta.y > 1 && delta.x == 0) {
                    int m = rope[prev].y > rope[k].y ? 1 : -1;
                    rope[k].y += m;
                }

                else if(delta.x > 1 && delta.y == 0) {
                    int m = rope[prev].x > rope[k].x ? 1 : -1;
                    rope[k].x += m;
                }
                else if(delta.y + delta.x > 2) {
                    int x = rope[prev].x > rope[k].x ? 1 : -1;
                    int y = rope[prev].y > rope[k].y ? 1 : -1;
                    rope[k].y += y;
                    rope[k].x += x;
                }
            }

            bool already_seen = false;
            for(size_t i = 0; i < seen.size(); i++) {
                if(seen[i].x == rope[knot_count - 1].x && seen[i].y == rope[knot_count - 1].y) {
                    already_seen = true;
                    break;
                }
            }

            if(seen.size() == 0 || !already_seen) {
                seen.push_back(rope[knot_count - 1]);
            }
        }
    }

    return seen.size();
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    knot head = {0, 0};
    knot tail = {0, 0};

    size_t step = 1;
    std::vector<Move> moves;

    knot rope[] = { head, tail };
    const size_t knot_size = 2;

    while(std::getline(input_data, line)) {
        std::stringstream ss(line);
        char direction;
        int step_size;

        knot move;

        ss >> direction >> step_size;
        moves.push_back({direction, step_size});
    }

    std::cout << "Anwser for part 1 is " << countVisited(moves, 2) << '\n';
    std::cout << "Anwser for part 2 is " << countVisited(moves, 10) << '\n';

    return 0;
}
