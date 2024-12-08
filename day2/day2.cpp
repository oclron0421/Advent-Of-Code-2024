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


    //print array 
    printVector(gridVector);
    int safeReports = 0;

    for (int i = 0; i < gridVector.size(); i++) {
        //check if the array is ascending or descending 
        if (gridVector[i][0] < gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isAscending"] = true;
        }
        else if (gridVector[i][0] > gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isDescending"] = true;
        }
        else if (gridVector[i][0] == gridVector[i][gridVector[i].size() - 1]) {
            arrayState["isEqual"] = true;
        }

        //if array is ascending
        if (arrayState["isAscending"] && !arrayState["isDescending"] && !arrayState["isEqual"]) {
            bool isSafe = true;
            for (int j = 0; j < gridVector[i].size() - 1; j++) {
                if (gridVector[i][j + 1] - gridVector[i][j] <= 3 && gridVector[i][j + 1] - gridVector[i][j] >= 0 && gridVector[i][j + 1] != gridVector[i][j]) {
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
            for (int j = 0; j < gridVector[i].size() - 1; j++) {
                if (gridVector[i][j] - gridVector[i][j + 1] <= 3 && gridVector[i][j] - gridVector[i][j + 1] >= 0 && gridVector[i][j] != gridVector[i][j + 1]) {
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
            for (int j = 0; j < gridVector[i].size() - 1; j++) {
                if (gridVector[i][j] == gridVector[i][j + 1]) {
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