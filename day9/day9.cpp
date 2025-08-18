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
    for (int i = 0; i < MAX_SIZE; ++i) {
        std::cout << diskMap[i] << " ";
    }

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
    std::cout << std::endl;
    // std::cout << "File system after moving files:" << std::endl;
    // for (const auto& block : fileSystem) {
    //     if (block.fileBlock == '.')
    //         std::cout << block.fileBlock;
    //     else
    //         std::cout << block.value;
    // }
    //std::cout << "File size: " << actualSize << std::endl;
    //print out the fileSystem after moving files

    std::cout << "Total sum of fileSystem: " << checkSum(fileSystem, actualSize) << std::endl;



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

    for (long long i = fileSystem.size() - 1; i > 0;i--) {
        if (fileSystem[i].fileBlock != '.') {       //if the value is not a blank spot 
            int range = 0;

            long val = fileSystem[i].value; // Get the value of the file block
            while (fileSystem[i - 1].value == val && i - 1 >= 0) { // Check if the previous block has the same value
                range++;
                i--;
            }

            bool swapped = false;
            int startIndex = 0;
            while (!swapped) {
                //once i found the range, the i will find the blank spots corrosponding to the range from the start of the vector 
                auto first_blank = std::find_if(
                    fileSystem.begin() + startIndex,
                    fileSystem.end(),
                    [range](const DiskSpace& d) { return d.fileBlock == '.' && d.value == 0; }
                );
                int locFirstBlank = std::distance(fileSystem.begin(), first_blank); // Get the index of the first blank space
                //find the range of the blanks 
                startIndex = locFirstBlank + range; // Update the start index for the next searchs
                bool spotFound = true;
                for (int j = 0; j < range; j++) {
                    if (fileSystem[locFirstBlank + j].fileBlock != '.') {
                        spotFound = false;
                        break;
                    }
                }
                if (spotFound) {
                    for (int k = 0; k < range; k++) {
                        fileSystem[locFirstBlank + k] = fileSystem[i + k];
                        fileSystem[i + k] = { '.', 0 }; // Set the current position to blank    
                    }
                    swapped = true; // Mark as swapped
                }
                else if (!spotFound) {
                    continue;
                }
            }
        }
    }

    std::cout << "File system after moving files:" << std::endl;
    for (const auto& block : fileSystem) {
        if (block.fileBlock == '.')
            std::cout << block.fileBlock;
        else
            std::cout << block.value;
    }
    return 0;
}