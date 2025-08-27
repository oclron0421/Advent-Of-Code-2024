#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
#include <utility>
#include <algorithm>
#include <cmath> 
#define ROWS 103 
#define COLS 101
#define TIME 1916

struct Robot {
    std::pair<int, int> position;
    std::pair<int, int> velocity;
};

struct Point {
    std::vector<Robot> robots;
};

long long getSafetyFactor(const std::vector<std::vector<Point>>& grid) {
    long long safetyFactor = 1;
    int size = 0;
    //find the median for row and cols
    int medianRow = ROWS / 2;
    int medianCol = COLS / 2;

    //first quadrant 
    for (int i = 0; i <= medianRow - 1; i++) {
        for (int j = medianCol + 1; j < COLS; j++) {
            size += grid[i][j].robots.size();
        }
    }

    if (size == 0) {
        size = 1;
        safetyFactor *= size;
    }
    else {
        safetyFactor *= size;
    }
    //second quadrant  
    size = 0;
    for (int i = 0; i <= medianRow - 1; i++) {
        for (int j = 0; j <= medianCol - 1; j++) {
            size += grid[i][j].robots.size();
        }
    }
    if (size == 0) {
        size = 1;
        safetyFactor *= size;
    }
    else {
        safetyFactor *= size;
    }
    //third quadrant
    size = 0;
    for (int i = medianRow + 1; i < ROWS; i++) {
        for (int j = 0; j <= medianCol - 1; j++) {
            size += grid[i][j].robots.size();
        }
    }
    if (size == 0) {
        size = 1;
        safetyFactor *= size;
    }
    else {
        safetyFactor *= size;
    }
    size = 0;
    //fourth quadrant
    for (int i = medianRow + 1; i < ROWS; i++) {
        for (int j = medianCol + 1; j < COLS; j++) {
            size += grid[i][j].robots.size();
        }
    }
    if (size == 0) {
        size = 1;
        safetyFactor *= size;
    }
    else {
        safetyFactor *= size;
    }
    return safetyFactor;
}

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
        iss >> r.velocity.first;
        iss >> ignore;
        iss >> r.velocity.second;
        robots.push_back(r);
    }


    for (auto& r : robots) {
        //remove robot from current position 
        auto currentPoint = r.position;
        auto rVelocity = r.velocity;
        int newX = (currentPoint.first + (TIME * rVelocity.first)) % COLS;
        if (newX < 0) {
            newX = std::abs(newX) % COLS;
            newX = COLS - newX;
        }
        else {
            newX = newX % COLS;
        }

        int newY = (currentPoint.second + (TIME * rVelocity.second)) % ROWS;
        if (newY < 0) {
            newY = std::abs(newY) % ROWS;
            newY = ROWS - newY;
        }
        else {
            newY = newY % ROWS;
        }
        r.position = { newX, newY };
    }

    std::cout << "After moving robots:" << std::endl;
    for (auto& r : robots) {
        grid[r.position.second][r.position.first].robots.push_back(r);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j].robots.size() == 0) {
                std::cout << ".";
                continue;
            }
            std::cout << grid[i][j].robots.size();
        }
        std::cout << std::endl;
    }

    // std::cout << "The safety factor is: " << getSafetyFactor(grid) << std::endl;

    //reset the grid and robot position
    int bestTime = -1;
    long long bestArea = LLONG_MAX;
    for (int t = 0; t < 10000; t++) {
        std::vector<std::pair<int, int>> positions;
        for (auto& r : robots) {
            int x = (r.position.first + r.velocity.first * t) % COLS;
            int y = (r.position.second + r.velocity.second * t) % ROWS;
            if (x < 0) x += COLS;
            if (y < 0) y += ROWS;
            positions.push_back({ x,y });
        }

        int minX = COLS, maxX = 0, minY = ROWS, maxY = 0;
        for (auto [x, y] : positions) {
            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
        }
        long long area = 1LL * (maxX - minX + 1) * (maxY - minY + 1);
        if (area < bestArea) {
            bestArea = area;
            bestTime = t;
        }
    }
    std::cout << "Tree likely appears at time " << bestTime << "\n";

    return 0;
}