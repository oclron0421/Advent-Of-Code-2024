#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <utility>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

int main() {

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    std::vector<std::vector<int>> validUpdates;
    std::vector<std::vector<int>> invalidUpdates;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return 1;
    }

    bool isSecondPart = false; // Tracks whether we're in the second part of the input
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            isSecondPart = true; // Empty line indicates the start of the second part
            continue;
        }

        if (!isSecondPart) {
            // Process the first part (pairs of integers)
            size_t delimiterPos = line.find('|');
            if (delimiterPos != std::string::npos) {
                int first = std::stoi(line.substr(0, delimiterPos));
                int second = std::stoi(line.substr(delimiterPos + 1));
                rules.emplace_back(first, second);
            }
        }
        else {
            // Process the second part (vectors of integers)
            std::vector<int> vec;
            std::istringstream lineStream(line);
            std::string number;
            while (std::getline(lineStream, number, ',')) {
                vec.push_back(std::stoi(number));
            }
            updates.push_back(vec);
        }
    }

    inputFile.close();
    // Print the rules
    // for (auto& rule : rules) {
    //     std::cout << rule.first << " | " << rule.second << std::endl;
    // }

    // Print the updates
    // for (auto& update : updates) {
    //     for (auto& num : update) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Implement the logic here
    for (auto& update : updates) {
        bool isValid = true;
        for (int num : update) {
            //get all the rules that involve num 
            std::vector<std::pair<int, int>> relevantRules;
            for (auto& rule : rules) {
                if (rule.first == num || rule.second == num) {
                    relevantRules.push_back(rule);
                }
            }
            for (auto& rule : relevantRules) {
                if (rule.first == num) {
                    auto itr1 = find(update.begin(), update.end(), num) - update.begin();
                    auto itr2 = find(update.begin(), update.end(), rule.second) - update.begin();
                    if (itr2 >= update.size()) {
                        continue;
                    }
                    else if (itr1 > itr2) {
                        //invalid update 
                        isValid = false;
                    }
                }
                else if (rule.second == num) {
                    auto itr1 = find(update.begin(), update.end(), num) - update.begin();
                    auto itr2 = find(update.begin(), update.end(), rule.first) - update.begin();
                    if (itr2 >= update.size()) {
                        continue;
                    }
                    else if (itr1 < itr2) {
                        //invalid update 
                        isValid = false;
                    }
                }
            }
        }
        if (isValid) {
            validUpdates.push_back(update);
        }
        else if (!isValid) {
            invalidUpdates.push_back(update);
        }
    }
    //print the valid updates
    // std::cout << "Valid Updates: " << std::endl;
    // for (auto& update : validUpdates) {
    //     for (auto& num : update) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int sumOfAllMiddleElements = 0;
    //find the middle element for all the valid updates 
    for (auto& update : validUpdates) {
        if (!update.empty()) { // Ensure the vector is not empty
            int middle = update[update.size() / 2];
            sumOfAllMiddleElements += middle;
            std::cout << "Middle element: " << middle << std::endl;
        }
        else {
            std::cout << "Empty vector encountered in validUpdates.\n";
        }
    }
    std::cout << "Sum of all middle elements: " << sumOfAllMiddleElements << std::endl;

    //part 2 
    //correct all the invalid updates
    for (auto& update : invalidUpdates) {
        for (int i = 0; i < update.size(); i++) {
            for (int j = i + 1; j < update.size(); j++) {
                //get all the rules that involve num 
                std::vector<std::pair<int, int>> relevantRules;
                for (auto& rule : rules) {
                    if (rule.first == update[i] || rule.second == update[i]) {
                        relevantRules.push_back(rule);
                    }
                }
                for (auto& rule : relevantRules) {
                    if (rule.first == update[i]) {
                        auto itr1 = find(update.begin(), update.end(), update[i]) - update.begin();
                        auto itr2 = find(update.begin(), update.end(), rule.second) - update.begin();
                        if (itr2 >= update.size()) {
                            continue;
                        }
                        else if (itr1 > itr2) {
                            //swap the elements 
                            std::swap(update[i], update[j]);
                        }
                    }
                    else if (rule.second == update[i]) {
                        auto itr1 = find(update.begin(), update.end(), update[i]) - update.begin();
                        auto itr2 = find(update.begin(), update.end(), rule.first) - update.begin();
                        if (itr2 >= update.size()) {
                            continue;
                        }
                        else if (itr1 < itr2) {
                            //swap the elements 
                            std::swap(update[i], update[j]);
                        }
                    }
                }
            }
        }
    }

    //sum up all the middle elements of the invalid updates
    int sumOfAllMiddleElementsInvalid = 0;
    for (auto& update : invalidUpdates) {
        if (!update.empty()) { // Ensure the vector is not empty
            int middle = update[update.size() / 2];
            sumOfAllMiddleElementsInvalid += middle;
        }
        else {
            std::cout << "Empty vector encountered in invalidUpdates.\n";
        }
    }

    std::cout << "Sum of all middle elements of invalid updates: " << sumOfAllMiddleElementsInvalid << std::endl;


    return 0;
}