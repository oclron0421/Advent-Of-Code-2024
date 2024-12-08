#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#include <unordered_map>
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

void resetArrayState(std::unordered_map<std::string, bool>& arrayState) {
    arrayState["isAscending"] = false;
    arrayState["isDescending"] = false;
    arrayState["isEqual"] = false;
}

int main() {

    std::unordered_map<std::string, bool> arrayState;
    arrayState["isAscending"] = false;
    arrayState["isDescending"] = false;
    arrayState["isEqual"] = false;
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
        //check if the array is ascending or descending 
        if (grid[i][0] < grid[i][SIZE_ROW - 1]) {
            arrayState["isAscending"] = true;
        }
        else if (grid[i][0] > grid[i][SIZE_ROW - 1]) {
            arrayState["isDescending"] = true;
        }
        else if (grid[i][0] == grid[i][SIZE_ROW - 1]) {
            arrayState["isEqual"] = true;
        }

        //if array is ascending
        if (arrayState["isAscending"] && !arrayState["isDescending"] && !arrayState["isEqual"]) {
            bool isSafe = true;
            for (int j = 0; j < SIZE_ROW - 1; j++) {
                if (grid[i][j + 1] - grid[i][j] <= 3 && grid[i][j + 1] - grid[i][j] >= 0 && grid[i][j + 1] != grid[i][j]) {
                    continue;
                }
                else {
                    isSafe = false;
                    break;
                }
            }
            if (isSafe) {
                safeReports++;
            }
        }
        //if array is descending
        else if (!arrayState["isAscending"] && arrayState["isDescending"] && !arrayState["isEqual"]) {
            bool isSafe = true;
            for (int j = 0; j < SIZE_ROW - 1; j++) {
                if (grid[i][j] - grid[i][j + 1] <= 3 && grid[i][j] - grid[i][j + 1] >= 0 && grid[i][j] != grid[i][j + 1]) {
                    continue;
                }
                else {
                    isSafe = false;
                    break;
                }
            }
            if (isSafe) {
                safeReports++;
            }
        }
        //if array is equal
        else if (!arrayState["isAscending"] && !arrayState["isDescending"] && arrayState["isEqual"]) {
            bool isSafe = true;
            for (int j = 0; j < SIZE_ROW - 1; j++) {
                if (grid[i][j] == grid[i][j + 1]) {
                    continue;
                }
                else {
                    isSafe = false;
                    break;
                }
            }
            if (isSafe) {
                safeReports++;
            }
        }
        resetArrayState(arrayState);
    }
    std::cout << "The number of safe reports is: " << safeReports << std::endl;
    inputFile.close();
}