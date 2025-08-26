#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
#include <utility>
#include <algorithm>
#define ROWS 7 
#define COLS 11

struct Robot {
    std::pair<int, int> position;
    std::pair<int, int> velocity;
};

struct Point {
    std::vector<Robot> robots;
};

int main() {

    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<Point>> grid(ROWS, std::vector<Point>(COLS));
    std::vector<Robot> robots;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Robot r;
        char ignore;


        iss >> ignore >> ignore;
        iss >> r.position.first;
        iss >> ignore;
        iss >> r.position.second;

        iss >> ignore;
        iss >> ignore;
        iss >> ignore;
        iss >> r.velocity.first;
        iss >> ignore;
        iss >> r.velocity.second;
        grid[r.position.second][r.position.first].robots.push_back(r);
        robots.push_back(r);
    }

    //print number of robots in each point
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << grid[i][j].robots.size() << " ";
        }
        std::cout << std::endl;
    }

    for (auto& r : robots) {
        //remove robot from current position 
        auto currentPoint = r.position;
        auto rVelocity = r.velocity;

        r.position.first = (r.position.first + (100 * r.velocity.first) + COLS) % COLS;
        r.position.second = (r.position.second + (100 * r.velocity.second) + ROWS) % ROWS;
    }

    std::cout << "After moving robots:" << std::endl;
    for (auto& r : robots) {
        grid[r.position.second][r.position.first].robots.push_back(r);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << grid[i][j].robots.size() << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}