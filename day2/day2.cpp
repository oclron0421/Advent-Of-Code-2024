#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#include <vector>
#include <unordered_map>




void printVector(std::vector < std::vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            std::cout << vec[i][j] << " ";
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
    std::vector<std::vector<int>> gridVector;
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file input.txt";
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> rowVector;
        int num;
        while (iss >> num) {
            rowVector.push_back(num);
        }
        gridVector.push_back(rowVector);
    }

    // Print the array
    printVector(gridVector);
    int safeReports = 0;

    for (int i = 0; i < gridVector.size(); i++) {
        // Check if the row is too short
        if (gridVector[i].size() < 2) {
            std::cout << "Row " << i << " is too short to evaluate." << std::endl;
            resetArrayState(arrayState);
            continue;
        }

        // Determine the row pattern
        if (gridVector[i][0] < gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isAscending"] = true;
        }
        else if (gridVector[i][0] > gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isDescending"] = true;
        }
        else if (gridVector[i][0] == gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isEqual"] = true;
        }

        // If the row is ascending
        if (arrayState["isAscending"] && !arrayState["isDescending"] && !arrayState["isEqual"]) {
            //std::cout << "Array is ascending at row: " << i << std::endl;
            bool isSafe = true;
            bool alreadyRemoved = false;
            for (int j = 0; j < gridVector[i].size() - 1; j++) {
                if (gridVector[i][j + 1] - gridVector[i][j] <= 3 &&
                    gridVector[i][j + 1] - gridVector[i][j] >= 0 &&
                    gridVector[i][j + 1] != gridVector[i][j]) {
                    continue;
                }
                else {
                    if (gridVector[i][j + 2] - gridVector[i][j] <= 3 &&
                        gridVector[i][j + 2] - gridVector[i][j] >= 0 &&
                        gridVector[i][j + 2] != gridVector[i][j] &&
                        (j + 2) < gridVector[i].size() &&
                        !alreadyRemoved) {
                        alreadyRemoved = true;
                        j += 2;
                        continue;
                    }
                    else {
                        isSafe = false;
                        break;
                    }
                }
            }
            if (isSafe) {
                safeReports++;
                std::cout << "Safe report at row: " << i + 1 << std::endl;
            }
            else {
                std::cout << "Unsafe report at row: " << i + 1 << std::endl;
            }
        }
        // If the row is descending
        else if (!arrayState["isAscending"] && arrayState["isDescending"] && !arrayState["isEqual"]) {
            //std::cout << "Array is descending at row: " << i << std::endl;
            bool isSafe = true;
            bool alreadyRemoved = false;
            for (int j = 0; j < gridVector[i].size() - 1; j++) {
                if (gridVector[i][j] - gridVector[i][j + 1] <= 3 &&
                    gridVector[i][j] - gridVector[i][j + 1] >= 0 &&
                    gridVector[i][j] != gridVector[i][j + 1]) {
                    continue;
                }
                else {
                    if (gridVector[i][j] - gridVector[i][j + 2] <= 3 &&
                        gridVector[i][j] - gridVector[i][j + 2] >= 0 &&
                        gridVector[i][j] != gridVector[i][j + 2] &&
                        (j + 2) < gridVector[i].size() &&
                        !alreadyRemoved) {
                        alreadyRemoved = true;
                        j += 2;
                        continue;
                    }
                    else {
                        isSafe = false;
                        break;
                    }
                }
            }
            if (isSafe) {
                safeReports++;
                std::cout << "Safe report at row: " << i << std::endl;
            }
            else {
                std::cout << "Unsafe report at row: " << i << std::endl;
            }
        }
        // If the row is equal
        else if (arrayState["isEqual"]) {
            std::cout << "Array is equal at row: " << i << std::endl;
            std::cout << "Unsafe report at row: " << i << " (default for equal rows)." << std::endl;

        }
        // Handle unhandled cases
        else {
            std::cout << "Row " << i << " does not match any pattern and is unsafe." << std::endl;
        }

        resetArrayState(arrayState);
    }

    std::cout << "The number of safe reports is: " << safeReports << std::endl;
    inputFile.close();
}

