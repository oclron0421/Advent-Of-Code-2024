#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <algorithm>
#include <sstream> 

struct ascendingOperator {
    bool operator()(int a, int b) const {
        return a < b;
    }
} inAscendingOrder;

bool isEqual(int a, int b) {
    return a == b;
}

int main() {
    int difference = 0;
    std::vector<int> leftNums, rightNums;
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file input.txt";
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int numL = 0, numR = 0;
        iss >> numL >> numR;
        leftNums.push_back(numL);
        rightNums.push_back(numR);
    }
    inputFile.close();

    std::sort(leftNums.begin(), leftNums.end(), inAscendingOrder);
    std::sort(rightNums.begin(), rightNums.end(), inAscendingOrder);

    for (int i = 0; i < leftNums.size(); i++) {
        difference += abs(leftNums[i] - rightNums[i]);
    }

    std::cout << "The difference between the two lists is: " << difference << std::endl;

    //part 2 
    int similarityScore = 0;
    for (int i = 0; i < leftNums.size(); i++) {
        int dupes = 0;
        for (int j = 0; j < rightNums.size(); j++) {
            if (leftNums[i] < rightNums[j]) {
                break;
            }
            else if (isEqual(leftNums[i], rightNums[j])) {
                dupes++;
            }
            else {
                continue;
            }
        }
        similarityScore += dupes * leftNums[i];

    }
    std::cout << "The similarity score is: " << similarityScore << std::endl;
    return 0;
}