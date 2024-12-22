#include <iostream> 
#include <vector> 
#include <iterator>
#include <fstream>
#include <string>
#include <sstream> 

void printGrid(std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkNW(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i - 3 < 0 || j - 3 < 0) return false;
    if (grid[i][j] == 'X' && grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkN(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i - 3 < 0) return false;
    if (grid[i][j] == 'X' && grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkNE(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i - 3 < 0 || j + 3 >= grid[i].size()) return false;
    if (grid[i][j] == 'X' && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkE(std::vector<std::vector<char>>& grid, int i, int j) {
    if (j + 3 >= grid[i].size()) return false;
    if (grid[i][j] == 'X' && grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkSE(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i + 3 >= grid.size() || j + 3 >= grid[i].size()) return false;
    if (grid[i][j] == 'X' && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkS(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i + 3 >= grid.size()) return false;
    if (grid[i][j] == 'X' && grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkSW(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i + 3 >= grid.size() || j - 3 < 0) return false;
    if (grid[i][j] == 'X' && grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkW(std::vector<std::vector<char>>& grid, int i, int j) {
    if (j - 3 < 0) return false;
    if (grid[i][j] == 'X' && grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S') {
        return true;
    }
    else {
        return false;
    }
}

bool checkNWtoSE(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i - 1 < 0 || j - 1 < 0 || i + 1 >= grid.size() || j + 1 >= grid[i].size()) return false;
    std::string str;
    str.push_back(grid[i][j]);
    str.push_back(grid[i - 1][j - 1]);
    str.push_back(grid[i + 1][j + 1]);
    if (str == "AMS" || str == "ASM") {
        return true;
    }
    else {
        return false;
    }
}

bool checkNEtoSW(std::vector<std::vector<char>>& grid, int i, int j) {
    if (i - 1 < 0 || j + 1 >= grid[i].size() || i + 1 >= grid.size() || j - 1 < 0) return false;
    std::string str;
    str.push_back(grid[i][j]);
    str.push_back(grid[i - 1][j + 1]);
    str.push_back(grid[i + 1][j - 1]);
    if (str == "AMS" || str == "ASM") {
        return true;
    }
    else {
        return false;
    }
}

int main() {

    std::vector<std::vector<char>> grid;

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
        }
        grid.push_back(row);
    }

    printGrid(grid);
    int count = 0;

    for (int i = 0; i < grid.size();i++) {
        for (int j = 0;j < grid[i].size();j++) {
            if (grid[i][j] == 'X') {
                //check if the current 'X' + 4 is out of bounds or not 
                if (checkNW(grid, i, j)) {
                    count++;
                }
                if (checkN(grid, i, j)) {
                    count++;
                }
                if (checkNE(grid, i, j)) {
                    count++;
                }
                if (checkE(grid, i, j)) {
                    count++;
                }
                if (checkSE(grid, i, j)) {
                    count++;
                }
                if (checkS(grid, i, j)) {
                    count++;
                }
                if (checkSW(grid, i, j)) {
                    count++;
                }
                if (checkW(grid, i, j)) {
                    count++;
                }
            }
            else {
                continue;
            }
        }
    }


    std::cout << "The number of 'XMAS' patterns in the grid is: " << count << std::endl;


    //part 2 

    //find all the 'A' in the grid and then check the respective coordinates 
    int XMAScount = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'A') {
                if (checkNWtoSE(grid, i, j) && checkNEtoSW(grid, i, j)) {
                    XMAScount++;
                }
            }
            else {
                continue;
            }
        }
    }

    std::cout << "The number of 'XMAS' patterns in the grid is: " << XMAScount << std::endl;

    return 0;

}