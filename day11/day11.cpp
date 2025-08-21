#include <iostream> 
#include <fstream> 
#include <vector> 
#include <sstream> 
#include <string>
#include <stack> 
#include <unordered_set>
#include <unordered_map>
int main() {

    std::ifstream file("input.txt");
    std::unordered_map<unsigned long long, unsigned long long> stones;

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    long long value;
    while (iss >> value) {
        stones[(unsigned long long)value] = 1;
    }

    //print the map
    // std::cout << "Stones: ";
    // for (const auto& stone : stones) {
    //     std::cout << stone.first << " ";
    // }
    // std::cout << std::endl;

    for (int i = 0; i < 25;i++) {
        std::unordered_map<unsigned long long, unsigned long long > temp;
        for (auto pair : stones) {
            unsigned long long stone = pair.first;
            unsigned long long count = pair.second;

            if (stone == 0) {
                temp[1] += count; //
            }
            else if (std::to_string(stone).length() % 2 == 0) {
                std::string stoneStr = std::to_string(stone);

                int n = stoneStr.length();
                unsigned long long firstHalf = std::stoull(stoneStr.substr(0, n / 2));
                unsigned long long secondHalf = std::stoull(stoneStr.substr(n / 2, n / 2));

                temp[firstHalf] += count;
                temp[secondHalf] += count;

            }
            else {
                temp[stone * 2024] += count;
            }
        }
        stones = temp;
    }


    unsigned long long total = 0;
    for (auto pair : stones) {
        total += pair.second;
    }
    std::cout << "The total number of stones is: " << total << std::endl;

    return 0;
}