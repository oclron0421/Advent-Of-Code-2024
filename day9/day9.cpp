#include <iostream> 
#include <vector> 
#include <sstream> 
#include <fstream> 
#include <array>
#include <string> 
#include <iterator>
#include <algorithm>

#define MAX_SIZE 19

struct DiskSpace {
    char fileBlock;
    long value;
};

long long checkSum(std::vector<DiskSpace> x, int actualSize) {
    long long sum = 0;
    for (int i = 0; i < actualSize; i++) {
        int digit = x[i].value; // Convert char to int
        sum = sum + (digit * i);
        //std::cout << "x[" << i << "] = " << digit * i << ", sum = " << sum << std::endl;
    }

    return sum;
}

long long checkSum(std::vector<DiskSpace> x) {
    long long sum = 0;
    for (int i = 0; i < x.size(); i++) {
        int digit = x[i].value; // Convert char to int
        sum = sum + (digit * i);
        //std::cout << "x[" << i << "] = " << digit * i << ", sum = " << sum << std::endl;
    }

    return sum;
}

int getRange(std::vector<DiskSpace>::iterator it, std::vector<DiskSpace>& fileSystem) {
    int range = 0;
    auto val = it->value;
    while (it != fileSystem.begin() && it->value == val) {
        range++;
        it--;
    }
    return range;
}

bool isAllBlanks(std::vector<DiskSpace>vec) {
    DiskSpace first = vec.front();
    for (const auto& block : vec) {
        if (block.fileBlock != '.' || block.value != 0) {
            return false; // Found a non-blank space
        }
    }
    return true; // All spaces are blank   
}

int main() {
    std::ifstream file("input.txt");
    std::array<int, MAX_SIZE> diskMap;
    std::vector<DiskSpace> fileSystem;
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        int index = 0;

        for (char c : line) {
            if (index < MAX_SIZE) {
                diskMap[index] = std::stoi(std::string(1, c));
                index++;
            }
        }

    }

    //print out the diskMap
    // for (int i = 0; i < MAX_SIZE; ++i) {
    //     std::cout << diskMap[i] << " ";
    // }

    bool computingBlankSpace = false;
    int count = 0;
    long long actualSize = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i % 2 == 1) {
            computingBlankSpace = true;
        }
        else if (i % 2 == 0 && computingBlankSpace) {
            computingBlankSpace = false;
        }

        if (computingBlankSpace) {
            for (int j = 0; j < diskMap[i];j++) {
                fileSystem.push_back({ '.', 0 }); // Push a blank space
            }
        }
        else if (!computingBlankSpace) {
            for (int j = 0; j < diskMap[i]; j++) {
                fileSystem.push_back({ static_cast<char>('#'), static_cast<long>(count) }); // Push a file block
            }
            actualSize += diskMap[i];
            //std::cout << "File size: " << actualSize << std::endl << "Current file size: " << diskMap[i] << std::endl;
            count++;
        }

    }

    for (long long i = fileSystem.size() - 1; i >= 0; i--) {
        if (fileSystem[i].fileBlock != '.') {
            auto first_blank = std::find_if(
                fileSystem.begin(),
                fileSystem.end(),
                [](const DiskSpace& d) { return d.fileBlock == '.' && d.value == 0; }
            );
            if (first_blank != fileSystem.end()) {
                // Move the file block to the first blank space
                *first_blank = fileSystem[i];
                fileSystem[i] = { '.', 0 }; // Set the current position to blank
            }
            auto if_no_blanks = std::find_if(
                fileSystem.begin(),
                fileSystem.begin() + actualSize,
                [](const DiskSpace& d) { return d.fileBlock == '.'; }
            );

            if (if_no_blanks == fileSystem.begin() + actualSize) {
                break; // No more blank spaces available
            }

        }
    }

    //print out the fileSystem after moving files
    // std::cout << "File system after moving files:" << std::endl;
    // for (const auto& block : fileSystem) {
    //     if (block.fileBlock == '.')
    //         std::cout << block.fileBlock;
    //     else
    //         std::cout << block.value;
    // }
    //std::cout << "File size: " << actualSize << std::endl;
    //print out the fileSystem after moving files

    //std::cout << "Total sum of fileSystem: " << checkSum(fileSystem, actualSize) << std::endl;



    // part 2 
    fileSystem.clear();

    computingBlankSpace = false;
    count = 0;
    actualSize = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i % 2 == 1) {
            computingBlankSpace = true;
        }
        else if (i % 2 == 0 && computingBlankSpace) {
            computingBlankSpace = false;
        }

        if (computingBlankSpace) {
            for (int j = 0; j < diskMap[i];j++) {
                fileSystem.push_back({ '.', 0 }); // Push a blank space
            }
        }
        else if (!computingBlankSpace) {
            for (int j = 0; j < diskMap[i]; j++) {
                fileSystem.push_back({ static_cast<char>('#'), static_cast<long>(count) }); // Push a file block
            }
            actualSize += diskMap[i];
            //std::cout << "File size: " << actualSize << std::endl << "Current file size: " << diskMap[i] << std::endl;
            count++;
        }

    }

    // std::cout << "File system before moving files:" << std::endl;
    // for (const auto& block : fileSystem) {
    //     if (block.fileBlock == '.')
    //         std::cout << block.fileBlock;
    //     else
    //         std::cout << block.value;
    // }


    std::vector<DiskSpace>::iterator backItr = fileSystem.end() - 1;
    while (backItr != fileSystem.begin()) {
        int range = 0;
        bool swapped = false;
        if (backItr->fileBlock != '.') {
            range = getRange(backItr, fileSystem);

            //iterate from the start of the vector to find the appropriate blank space
            std::vector<DiskSpace>::iterator startItr = fileSystem.begin();
            while (startItr != backItr - range) {
                if (startItr->fileBlock == '.' && startItr->value == 0) {       //blank is found
                    std::vector<DiskSpace> tempVec;
                    for (long i = 0; i < range;i++) {
                        tempVec.push_back(*(startItr + i)); // Store the blank space
                    }
                    if (isAllBlanks(tempVec)) {
                        //commence the swap here 
                        for (int i = 0; i < range; i++) {
                            auto itrBlanks = startItr + i;
                            auto itrFile = backItr - i;
                            std::iter_swap(itrBlanks, itrFile); // Swap the blank space with the file block
                        }
                        //reposition the backItr 
                        backItr -= range;
                        swapped = true;
                        break;
                    }
                }
                startItr++;
            }

            if (!swapped) {
                backItr -= range;
            }
        }
        else {
            backItr--;
        }
        std::cout << std::endl;
        for (const auto& block : fileSystem) {
            if (block.fileBlock == '.')
                std::cout << block.fileBlock;
            else
                std::cout << block.value;

        }
    }

    //print out the fileSystem after moving files
    std::cout << std::endl;
    std::cout << "File system after moving files:" << std::endl;
    for (const auto& block : fileSystem) {
        if (block.fileBlock == '.')
            std::cout << block.fileBlock;
        else
            std::cout << block.value;
    }

    std::cout << std::endl;
    std::cout << "Total sum of fileSystem: " << checkSum(fileSystem) << std::endl;

    return 0;
}