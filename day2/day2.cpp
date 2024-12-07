#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#define SIZE_ROW 5
#define SIZE_COLUMN 6

void printArray(const std::array<std::array<int, SIZE_ROW>, SIZE_COLUMN>& array) {
    for (int i = 0; i < SIZE_COLUMN; i++) {
        for (int j = 0; j < SIZE_ROW; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int main() {

    std::array<std::array<int, SIZE_ROW>, SIZE_COLUMN> grid;
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file input.txt";
        return 1;
    }

    std::string line;
    int col = 0;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        for (int j = 0; j < SIZE_ROW; j++) {
            iss >> grid[col][j];
        }
        col++;
    }


    //print array 
    printArray(grid);
    int safeReports = 0;

    for (int i = 0; i < SIZE_COLUMN; i++) {
        for (int j = 0; j < SIZE_ROW - 1; j++) {
            if (grid[i][j])
        }
    }

    inputFile.close();
}