#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

static const size_t space_avail = 70000000;

struct Entry {
    std::string name;
    bool is_dir;
    size_t size;
    struct Entry* parent;
    std::vector<Entry*> child;

    Entry() : size(0), parent(NULL) {};
    Entry(std::string n) : name(n), size(0), parent(NULL) {};
};

size_t findDirsInThresh(const Entry* root, std::vector<size_t>& sizes) {
    size_t total = 0;

    for(size_t idx = 0; idx < root->child.size(); idx++) {
        total += findDirsInThresh(root->child[idx], sizes);
    }

    if(root->is_dir && total <= 100'000) {
        sizes.push_back(total);
    }

    total += root->size;
    return total;
}

void freeTree(Entry* root) {
    for(size_t idx = 0; idx < root->child.size(); idx++) {
        freeTree(root->child[idx]);
    }

    for(size_t idx = 0; idx < root->child.size(); idx++) {
        delete root->child[idx];
    }
}

size_t findDirsToDelete(const Entry* root, std::vector<size_t>& sizes) {
    size_t total = 0;

    for(size_t idx = 0; idx < root->child.size(); idx++) {
        total += findDirsToDelete(root->child[idx], sizes);
    }

    if(root->is_dir && total >= 8'381'165) {
        sizes.push_back(total);
    }

    total += root->size;
    return total;
}

int main(void) {
    static const char* input_file = "./input";
    std::ifstream input_data(input_file);
    std::string line;

    Entry* root = new Entry("/");
    root->parent = root;
    root->is_dir = true;

    Entry* cwd = root;

    std::getline(input_data, line);
    while(std::getline(input_data, line)) {
        if(line.find("$ cd", 0) == 0) {
            std::stringstream ss(line);
            std::string dol, cd, dir_name;
            ss >> dol >> cd >> dir_name;

            if(dir_name == "..") {
                cwd = cwd->parent;
                continue;
            }

            bool found = false;
            for(size_t idx = 0; idx < cwd->child.size(); idx++) {
                if(cwd->child[idx]->name == dir_name) {
                    cwd = cwd->child[idx];
                    found = true;
                    break;
                }
            }

            if(!found) {
                Entry* new_entry = new Entry(dir_name);
                new_entry->is_dir = true;
                new_entry->parent = cwd;
                cwd->child.push_back(new_entry);
            }
        }

        else if(line.find("$ ls", 0) == 0) {
            continue;
        }

        else {
            std::stringstream ss(line);
            std::string tok, name;
            ss >> tok >> name;

            bool found = false;
            for(size_t idx = 0; idx < cwd->child.size(); idx++) {
                if(cwd->child[idx]->name == name) {
                    found = true;
                    break;
                }
            }

            if(!found) {
                Entry* new_entry = new Entry(name);
                new_entry->is_dir = tok == "dir" ? true : false;
                new_entry->size = tok == "dir" ? 0 : std::stol(tok);
                new_entry->parent = cwd;
                cwd->child.push_back(new_entry);
            }
        }
    }

    std::vector<size_t> dirs;

    size_t sum = 0;
    findDirsInThresh(root, dirs);
    for(size_t idx = 0; idx < dirs.size(); idx++) {
        sum += dirs[idx];
    }

    dirs.clear();

    findDirsToDelete(root, dirs);
    size_t min = space_avail;;

    for(size_t idx = 0; idx < dirs.size(); idx++) {
        if(min > dirs[idx]) min = dirs[idx];
    }

    std::cout << "Anwser for part 1 is " << sum << '\n';
    std::cout << "Anwser for part 2 is " << min << '\n';

    freeTree(root);
    delete root;

    return 0;
}
