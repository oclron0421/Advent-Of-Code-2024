#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>
#include <sstream>
#include <map> 
#include <utility>
#include <algorithm>
#include <set> 

#define ROWS 50
#define COLS 50

int main() {

    std::map < char, std::vector<std::pair<int, int>>> antenna;
    std::vector<std::vector<char>> grid;
    int antinodeCount = 0;

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
            if (c != '.') {
                antenna[c].push_back({ grid.size(), row.size() - 1 });
            }
        }
        grid.push_back(row);
    }

    //print all the antennas and their positions    
    for (const auto& entry : antenna) {
        std::cout << "Antenna: " << entry.first << " at positions: ";
        for (const auto& pos : entry.second) {
            std::cout << "(" << pos.first << ", " << pos.second << ") ";
        }
        std::cout << std::endl;
    }

    //form pairs of antennas in the grid    
    std::map<char, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> pairs;


    for (const auto& entry : antenna) {
        char antennaType = entry.first;
        const auto& positions = entry.second;

        for (size_t i = 0; i < positions.size(); ++i) {
            for (size_t j = i + 1; j < positions.size(); ++j) {
                pairs[antennaType].push_back({ positions[i], positions[j] });
            }
        }
    }

    //print all the pairs of antennas   

    for (const auto& entry : pairs) {
        std::cout << "Pairs for antenna: " << entry.first << std::endl;
        for (const auto& pair : entry.second) {
            std::cout << "Pair: (" << pair.first.first << ", " << pair.first.second << ") and ("
                << pair.second.first << ", " << pair.second.second << ")" << std::endl;
        }
    }



    // calculate the vectors between each antenna 
    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, std::pair<int, int>> vectors;
    for (const auto& entry : pairs) {
        for (const auto& pair : entry.second) {
            int dx = pair.second.first - pair.first.first;
            int dy = pair.second.second - pair.first.second;
            vectors.insert({ {pair.first, pair.second}, {dx, dy} });
        }
    }

    //print the vectors
    std::cout << "Vectors between pairs of antennas:" << std::endl;
    for (const auto& entry : vectors) {
        std::cout << "Pair: (" << entry.first.first.first << ", " << entry.first.first.second << ") and ("
            << entry.first.second.first << ", " << entry.first.second.second << ") -> Vector: ("
            << entry.second.first << ", " << entry.second.second << ")" << std::endl;
    }
    std::vector<std::pair<int, int>> antiNodes;
    // find the antinodes in the grid 
    for (const auto& entry : vectors) {
        auto pair = entry.first;
        auto vector = entry.second;
        int newx1 = pair.first.first - vector.first;
        int newy1 = pair.first.second - vector.second;
        int newx2 = pair.second.first + vector.first;
        int newy2 = pair.second.second + vector.second;
        if (newx1 >= 0 && newx1 < ROWS && newy1 >= 0 && newy1 < COLS) {
            antiNodes.push_back({ newx1, newy1 });
            std::cout << "Antinode found at: (" << newx1 << ", " << newy1 << ")" << std::endl;
            if (grid[newx1][newy1] == '.') {
                grid[newx1][newy1] = '#'; // Mark antinode with 'A'
            }
        }
        if (newx2 >= 0 && newx2 < ROWS && newy2 >= 0 && newy2 < COLS) {
            antiNodes.push_back({ newx2, newy2 });
            std::cout << "Antinode found at: (" << newx2 << ", " << newy2 << ")" << std::endl;
            if (grid[newx2][newy2] == '.') {
                grid[newx2][newy2] = '#'; // Mark antinode with 'A'
            }
        }

    }

    //eliminate duplicates in antinodes
    std::sort(antiNodes.begin(), antiNodes.end());
    antiNodes.erase(std::unique(antiNodes.begin(), antiNodes.end()), antiNodes.end());
    antinodeCount = antiNodes.size();

    //print the new grid with antinodes
    std::cout << "Grid with antinodes:" << std::endl;
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }

    std::cout << "Total number of antinodes: " << antinodeCount << std::endl;

    // part 2 -- extend the antinodes all the way to the end of the grid 
    for (const auto& entry : vectors) {
        auto pair = entry.first;
        auto vector = entry.second;
        int newx1 = pair.first.first - vector.first;
        int newy1 = pair.first.second - vector.second;
        int newx2 = pair.second.first + vector.first;
        int newy2 = pair.second.second + vector.second;
        antiNodes.push_back({ pair.first.first + vector.first, pair.first.second + vector.second });
        antiNodes.push_back({ pair.second.first - vector.first, pair.second.second - vector.second });
        do {
            if (newx1 >= 0 && newx1 < ROWS && newy1 >= 0 && newy1 < COLS) {
                antiNodes.push_back({ newx1, newy1 });
                if (grid[newx1][newy1] == '.') {
                    grid[newx1][newy1] = '#'; // Mark antinode with 'A'
                }
                newx1 -= vector.first;
                newy1 -= vector.second;
            }
        } while (newx1 >= 0 && newx1 < ROWS && newy1 >= 0 && newy1 < COLS);

        do {
            if (newx2 >= 0 && newx2 < ROWS && newy2 >= 0 && newy2 < COLS) {
                antiNodes.push_back({ newx2, newy2 });
                if (grid[newx2][newy2] == '.') {
                    grid[newx2][newy2] = '#'; // Mark antinode with 'A'
                }
                newx2 += vector.first;
                newy2 += vector.second;
            }
        } while (newx2 >= 0 && newx2 < ROWS && newy2 >= 0 && newy2 < COLS);
    }

    //eliminate duplicates in antinodes
    std::sort(antiNodes.begin(), antiNodes.end());
    antiNodes.erase(std::unique(antiNodes.begin(), antiNodes.end()), antiNodes.end());
    antinodeCount = antiNodes.size();
    //print the new grid with extended antinodes
    std::cout << "Extended grid with antinodes:" << std::endl;
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }

    std::cout << "Total number of extended antinodes: " << antinodeCount << std::endl;
    return 0;
}