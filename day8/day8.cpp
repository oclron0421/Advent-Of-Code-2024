#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>
#include <sstream>
#include <map> 
#include <utility>

#define ROWS 12
#define COLS 12

int main() {

    std::map < char, std::vector<std::pair<int, int>>> antenna;

    std::vector<std::vector<char>> grid;
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
    std::map<char, std::vector<std::pair<int, int>>> vectors;
    for (const auto& entry : pairs) {
        char antennaType = entry.first;
        for (const auto& pair : entry.second) {
            int dx = pair.second.first - pair.first.first;
            int dy = pair.second.second - pair.first.second;
            vectors[antennaType].push_back({ dx, dy });
        }
    }

    //print all the vectors between antennas
    for (const auto& entry : vectors) {
        std::cout << "Vectors for antenna: " << entry.first << std::endl;
        for (const auto& vec : entry.second) {
            std::cout << "Vector: (" << vec.first << ", " << vec.second << ")" << std::endl;
        }
    }

    int antinodeCount = 0;
    //insert an antinode extending from each antenna according to the vector calculated on the grid by replacing the char with '#', DO NOT replace antennas 
    for (const auto& entry : vectors) {
        char antennaType = entry.first;
        for (const auto& vec : entry.second) {
            int dx = vec.first;
            int dy = vec.second;

            for (const auto& pos : antenna[antennaType]) {
                int x = pos.first;
                int y = pos.second;

                // Calculate the new positions
                // Extend the antinode in both directions along the vector
                int newX = x + dx;
                int newY = y + dy;
                int newX2 = x - (2 * dx);
                int newY2 = y - (2 * dy);


                // Check bounds and replace if within grid limits
                if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS &&
                    newX2 >= 0 && newX2 < ROWS && newY2 >= 0 && newY2 < COLS &&
                    grid[newX][newY] == '.' &&
                    grid[newX2][newY2] == '.') {
                    grid[newX][newY] = '#';
                    grid[newX2][newY2] = '#'; // Extend in the opposite direction
                    antinodeCount += 2; // Count both new positions as antinodes

                }
            }
        }
    }


    //cycle through the grid and count the amount of antinodes 

        //print the new grid with antinodes
    std::cout << "Grid with antinodes:" << std::endl;
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }

    std::cout << "Total number of antinodes: " << antinodeCount << std::endl;





    return 0;
}