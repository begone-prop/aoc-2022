#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <set>

struct Point {
    int y;
    int x;

    bool operator<(Point a) const;
};

struct Crit {
    size_t distance;
    Point p;
};

bool Point::operator<(Point a) const {
    return this->x < a.x || (this->x == a.x && this->y < a.y);
}

bool inBounds(Point p, const std::vector<std::vector<char>>& height_map) {
    return
        0 <= p.y && (size_t) p.y < height_map.size() &&
        0 <= p.x && (size_t) p.x < height_map[0].size();
}

bool isAccessible(char c, char n, bool reversed) {
    if(reversed) {
        char tmp = c;
        c = n;
        n = tmp;
    }

    return ((c == 'S' && n == 'a') ||
            (c == 'z' && n == 'E') ||
            (n - c <= 1 && n != 'E'));
}

size_t shortestPath(const std::vector<std::vector<char>>& height_map, Point start, char target, bool reversed) {
    std::set<Point> seen;
    std::queue<Crit> Q;

    Crit c = {0, start};
    Q.push(c);
    size_t distance = 0;

    while(!Q.empty()) {
        Crit m = Q.front();
        Q.pop();

        if(seen.find(m.p) != seen.end()) continue;;
        seen.insert(m.p);
        char height = height_map[m.p.y][m.p.x];

        if(height == target) {
            distance = m.distance;
            break;
        }

        for(int y = -1; y <= 1; y++) {
            for(int x = -1; x <= 1; x++) {
                if(y == x || x + y == 0) continue;
                Point z = { m.p.y + y, m.p.x + x };
                if(inBounds(z, height_map) &&
                        isAccessible(height, height_map[z.y][z.x], reversed)) {
                    Q.push({m.distance + 1, z});
                }
            }
        }
    }

    return distance;
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    std::vector<std::vector<char>> height_map;

    Point start, end;

    int row = 0;

    while(std::getline(input_data, line)) {
        std::vector<char> current;

        for(int idx = 0; (size_t) idx < line.size(); idx++) {

            if(line[idx] == 'S') start = {row, idx};
            if(line[idx] == 'E') end = {row, idx};

            current.push_back(line[idx]);
        }

        height_map.push_back(current);
        row++;
    }

    size_t steps1 = shortestPath(height_map, start, 'E', false);
    size_t steps2 = shortestPath(height_map, end, 'a', true);

    std::cout << "Anwser for part 1 is " << steps1 << '\n';
    std::cout << "Anwser for part 2 is " << steps2 << '\n';

    return 0;
}
