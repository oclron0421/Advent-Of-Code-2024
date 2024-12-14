#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array> 
#include <vector>
#include <unordered_map>
#include <utility>

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

bool computeSafeReports(std::vector<int>& gridVector) {
    int errorIndex = -1;
    bool isSafe = true;
    std::unordered_map<std::string, bool> arrayState;
    arrayState["isAscending"] = false;
    arrayState["isDescending"] = false;
    arrayState["isEqual"] = false;
    //check if the vector is ascending or descending 
    if (gridVector[0] < gridVector[gridVector.size() - 1]) {
        arrayState["isAscending"] = true;
    }
    else if (gridVector[0] > gridVector[gridVector.size() - 1]) {
        arrayState["isDescending"] = true;
    }
    else if (gridVector[0] == gridVector[gridVector.size() - 1]) {
        arrayState["isEqual"] = true;
        isSafe = false;
    }

    //if array is ascending
    if (arrayState["isAscending"] && !arrayState["isDescending"] && !arrayState["isEqual"]) {
        for (int j = 0; j < gridVector.size() - 1; j++) {
            if (gridVector[j + 1] - gridVector[j] <= 3 &&
                gridVector[j + 1] - gridVector[j] >= 0 &&
                gridVector[j + 1] != gridVector[j]) {
                continue;
            }
            else {
                isSafe = false;
                errorIndex = j + 1;
                break;
            }
        }
    }
    //if array is descending
    else if (!arrayState["isAscending"] && arrayState["isDescending"] && !arrayState["isEqual"]) {
        for (int j = 0; j < gridVector.size() - 1; j++) {
            if (gridVector[j] - gridVector[j + 1] <= 3 &&
                gridVector[j] - gridVector[j + 1] >= 0 &&
                gridVector[j] != gridVector[j + 1]) {
                continue;
            }
            else {
                isSafe = false;
                errorIndex = j;
                break;
            }
        }
    }
    //if array is equal
    else if (!arrayState["isAscending"] && !arrayState["isDescending"] && arrayState["isEqual"]) {
        isSafe = false;

    }

    return isSafe;
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
    int col = 0;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> rowVector;
        int num;
        while (iss >> num) {
            rowVector.push_back(num);
        }
        gridVector.push_back(rowVector);
    }
    int safeReports = 0;
    for (int i = 0; i < gridVector.size(); i++) {
        if (gridVector[i].size() < 2) {
            std::cout << "Row " << i << " is too short to evaluate." << std::endl;
            resetArrayState(arrayState);
            continue;
        }
        auto result = computeSafeReports(gridVector[i]);
        if (result) {
            std::cout << "The report " << i + 1 << " is safe" << std::endl;
            safeReports++;
        }
        else if (!result) {
            //brute force here we fucking go, erase every element and check if the report is safe
            for (int j = 0; j < gridVector[i].size(); j++) {
                std::vector<int> tempVector = gridVector[i];
                tempVector.erase(tempVector.begin() + j);
                auto result = computeSafeReports(tempVector);
                if (result) {
                    std::cout << "The report " << i + 1 << " is safe" << std::endl;
                    safeReports++;
                    break;
                }
            }
        }
    }
    //print array 
    std::cout << "The number of safe reports is: " << safeReports << std::endl;
    inputFile.close();
}