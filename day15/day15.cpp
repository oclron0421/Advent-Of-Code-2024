#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
#include <queue>
#include <utility>
#include <map> 

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
                    lanternFish.c = row.size() - 1;
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


    while (!directions.empty()) {
        char dir = directions.front();
        directions.pop();
        int nr = lanternFish.r + dirMap[dir].r;
        int nc = lanternFish.c + dirMap[dir].c;
        int tempR, tempC;
        //check the new position 
        std::vector<Pos> tempStones;
        switch (grid[nr][nc]) {
        case '#':
            //hit a wall, do nothing
            break;
        case 'O':
            do {
                tempStones.push_back({ nr, nc });
                tempR = nr + dirMap[dir].r;
                tempC = nc + dirMap[dir].c;
            } while (!grid[tempR][tempC] == '.' || !grid[tempR][tempR] == '#');
            if (grid[nr][nc] == '#') {
                //hit a wall, do nothing
                break;
            }
            else {
                //move the stones
                for (Pos p : tempStones) {
                    grid[p.r][p.c] = '.';
                    int sr = p.r + dirMap[dir].r;
                    int sc = p.c + dirMap[dir].c;
                    grid[sr][sc] = 'O';
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
    }
    return 0;
}