#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 
#include <utility>

struct Guard {
    std::pair<int, int> pos;
    char direction;
}guardPos;

int main() {
    std::vector<std::vector<char>> grid;
    int init_x, init_y;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream issline(line);
        std::vector<char> row;
        for (char c; issline >> c;) {
            row.push_back(c);
            if (c == '^') {
                init_x = grid.size();
                init_y = row.size() - 1;
                guardPos.pos = std::make_pair(grid.size(), row.size() - 1);
                guardPos.direction = '^';
            }
        }
        grid.push_back(row);
    }

    std::cout << "Guard position: " << guardPos.pos.first << " " << guardPos.pos.second << std::endl;

    int count = 0;
    do
    {
        if (guardPos.direction == '^') {
            if (guardPos.pos.first - 1 < 0) {
                guardPos.direction = '>';
                continue;
            }
            else if (grid[guardPos.pos.first - 1][guardPos.pos.second] == '#') {
                guardPos.direction = '>';
                guardPos.pos.second++;
            }
            else {
                guardPos.pos.first--;
            }
        }
        else if (guardPos.direction == '>') {
            if (guardPos.pos.second + 1 > grid[0].size() - 1) {
                guardPos.direction = 'v';
                continue;
            }
            else if (grid[guardPos.pos.first][guardPos.pos.second + 1] == '#') {
                guardPos.direction = 'v';
                guardPos.pos.first++;
            }
            else {
                guardPos.pos.second++;
            }
        }
        else if (guardPos.direction == 'v') {
            if (guardPos.pos.first + 1 > grid.size() - 1) {
                guardPos.direction = '<';
                continue;
            }
            else if (grid[guardPos.pos.first + 1][guardPos.pos.second] == '#') {
                guardPos.direction = '<';
                guardPos.pos.second--;
            }
            else {
                guardPos.pos.first++;
            }
        }
        else if (guardPos.direction == '<') {
            if (guardPos.pos.second - 1 < 0) {
                guardPos.direction = '^';
                continue;
            }
            else if (grid[guardPos.pos.first][guardPos.pos.second - 1] == '#') {
                guardPos.direction = '^';
                guardPos.pos.first--;
            }
            else {
                guardPos.pos.second--;
            }
        }
        count++;
        std::cout << guardPos.pos.first << " " << guardPos.pos.second << std::endl;
    } while (guardPos.pos.first != init_x || guardPos.pos.second != init_y);

    std::cout << "Steps taken by the guard in her path: " << count << std::endl;
    return 0;
}