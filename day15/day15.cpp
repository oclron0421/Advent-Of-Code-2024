#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
#include <queue>
#include <utility>
#include <map> 
#include <stack>

struct Pos {
    int r, c;
};

std::map<char, Pos> dirMap = {
    {'^',{-1,0}}, {'v',{1,0}},
    {'<',{0,-1}}, {'>',{0,1}}
};

int main() {

    std::ifstream file("input.txt");
    std::vector<std::vector<char>> grid;
    std::queue<char> directions;
    std::string line;
    Pos lanternFish = { 0, 0 };
    bool readingGrid = true;

    while (std::getline(file, line)) {
        if (line.empty()) {
            readingGrid = false;
            continue;
        }
        if (readingGrid) {
            std::vector<char> row;
            for (char c : line) {
                if (c == '@') {
                    lanternFish.r = grid.size();
                    lanternFish.c = row.size();
                    row.push_back('.');
                }
                else {
                    row.push_back(c);
                }
            }
            grid.push_back(row);
        }
        else {
            for (char c : line) {
                directions.push(c);
            }
        }
    }
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[r].size(); c++) {
            if (r == lanternFish.r && c == lanternFish.c) {
                std::cout << '@';
            }
            else {
                std::cout << grid[r][c];
            }
        }
        std::cout << std::endl;
    }

    while (!directions.empty()) {
        char dir = directions.front();
        directions.pop();
        int nr = lanternFish.r + dirMap[dir].r;
        int nc = lanternFish.c + dirMap[dir].c;
        int tempR = nr; int tempC = nc;
        //check the new position 
        std::stack<Pos> tempStones;
        switch (grid[nr][nc]) {
        case '#':
            //hit a wall, do nothing
            break;
        case 'O':
            do {
                tempStones.push({ nr, nc });
                tempR += dirMap[dir].r;
                tempC += dirMap[dir].c;
            } while (!grid[tempR][tempC] == '.' || !grid[tempR][tempR] == '#');
            //temp coordinates are now at the end of the stone stack

            if (grid[nr][nc] == '#') {
                //hit a wall, do nothing
                break;
            }
            else {
                //move the stones
                while (!tempStones.empty()) {
                    Pos stone = tempStones.top();
                    tempStones.pop();
                    grid[stone.r - dirMap[dir].r][stone.c - dirMap[dir].c] = 'O';
                    tempR -= dirMap[dir].r;
                    tempC -= dirMap[dir].c;
                    grid[stone.r][stone.c] = '.';
                }
                lanternFish.r = nr;
                lanternFish.c = nc;
            }
            break;
        case '.':
            lanternFish.r = nr;
            lanternFish.c = nc;
            break;
        }
        //print the grid
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[r].size(); c++) {
                if (r == lanternFish.r && c == lanternFish.c) {
                    std::cout << '@';
                }
                else {
                    std::cout << grid[r][c];
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}