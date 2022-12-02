#include <iostream>
#include <fstream>

/*      B
      R P S
    R 0 W L
 A  P L 0 W
    S W L 0
*/

/*      O
      D W L
    R R P S
 A  P P S R
    S S R P
*/

enum State {
    INVALID = -1,
    DRAW = 0,
    WIN = 1,
    LOSE = 2,
};

enum Move {
    INVLAID = -1,
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2
};

static const State rps_fsm[][3] = {
    {DRAW,  WIN,   LOSE},
    {LOSE,   DRAW,   WIN},
    {WIN,   LOSE,     DRAW}
};

static const Move stm_fsm[][3] = {
    {ROCK,      PAPER,   SCISSORS},
    {PAPER,     SCISSORS,   ROCK},
    {SCISSORS,  ROCK,       PAPER}
};

Move decodeMove(char c) {
    if(c == 'A' || c == 'X') return ROCK;
    if(c == 'B' || c == 'Y') return PAPER;
    if(c == 'C' || c == 'Z') return SCISSORS;
    return INVLAID;
}

State decodeOutcome(char c) {
    if(c == 'X') return LOSE; // 2
    if(c == 'Y') return DRAW; // 0
    if(c == 'Z') return WIN; // 1
    return INVALID;
}

static const int scores[] = {3, 6, 0};

int main(void) {
    static const char* input_file = "./big_input";
    std::ifstream input_data(input_file);
    std::string line;

    size_t sum = 0;
    size_t sum2 = 0;

    while(std::getline(input_data, line)) {
        Move a = decodeMove(line[0]);
        Move b = decodeMove(line[2]);

        State result = rps_fsm[a][b];
        int score = scores[result];
        sum += score + b + 1;

        State outcome = decodeOutcome(line[2]);
        Move m = stm_fsm[a][outcome];
        sum2 += scores[outcome] + m + 1;
    }

    std::cout << "Anwser for part 1 is " << sum << '\n';
    std::cout << "Anwser for part 2 is " << sum2 << '\n';

    return 0;
}
