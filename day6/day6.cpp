#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define COLS 130
#define ROWS 130

struct Point {
    int x;
    int y;
    char value;
};

struct guardPos {
    int x;
    int y;
    bool exited = false; // Flag to indicate if the guard has exited the map
    char value = '^'; // Default value for the guard    
    void visited(Point& p) {
        p.value = 'X';
    }
}guard;

void goUp(std::vector<std::vector<Point>>& map) {
    if (guard.y > 0 && map[guard.y - 1][guard.x].value != '#') {
        guard.y--;
        guard.visited(map[guard.y][guard.x]);

        if (guard.y <= 0) {
            guard.exited = true; // Guard has exited the map
        }
    }
    else if (guard.y > 0 && map[guard.y - 1][guard.x].value == '#') {
        //turn right 90 degrees
        guard.value = '>';
    }
}

void goDown(std::vector<std::vector<Point>>& map) {
    if (guard.y < ROWS - 1 && map[guard.y + 1][guard.x].value != '#') {
        guard.y++;
        guard.visited(map[guard.y][guard.x]);
        if (guard.y >= ROWS - 1) {
            guard.exited = true; // Guard has exited the map
            std::cout << "Guard has exited the map at (" << guard.x << ", " << guard.y << ")\n";
        }
    }
    else if (guard.y < ROWS - 1 && map[guard.y + 1][guard.x].value == '#') {
        //turn right 90 degrees
        guard.value = '<';
    }
}

void goLeft(std::vector<std::vector<Point>>& map) {
    if (guard.x > 0 && map[guard.y][guard.x - 1].value != '#') {
        guard.x--;
        guard.visited(map[guard.y][guard.x]);
        if (guard.x <= 0) {
            guard.exited = true; // Guard has exited the map
        }
    }
    else if (guard.x > 0 && map[guard.y][guard.x - 1].value == '#') {
        //turn right 90 degrees
        guard.value = '^';
    }
}

void goRight(std::vector<std::vector<Point>>& map) {
    if (guard.x < COLS - 1 && map[guard.y][guard.x + 1].value != '#') {
        guard.x++;
        guard.visited(map[guard.y][guard.x]);
        if (guard.x >= COLS - 1) {
            guard.exited = true; // Guard has exited the map
        }
    }
    else if (guard.x < COLS - 1 && map[guard.y][guard.x + 1].value == '#') {
        //turn right 90 degrees
        guard.value = 'v';
    }
}

int main() {

    std::vector<std::vector<Point>> map;
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(input, line)) {
        std::vector<Point> row;
        for (int i = 0; i < line.size(); ++i) {
            Point p;
            p.x = i;
            p.y = map.size();
            p.value = line[i];
            row.push_back(p);
            if (line[i] == '^') {
                guard.x = i;
                guard.y = map.size();
            }
        }
        map.push_back(row);
    }

    // code for the guard path in the map
    while (!guard.exited) {
        switch (guard.value) {
        case '^':
            goUp(map);
            break;
        case 'v':
            goDown(map);
            break;
        case '<':
            goLeft(map);
            break;
        case '>':
            goRight(map);
            break;
        }
        std::cout << "Guard is at (" << guard.x << ", " << guard.y << ") facing " << guard.value << "\n";
    }

    //cycle through the map and look for 'X'
    int count = 0;
    for (const auto& row : map) {
        for (const auto& point : row) {
            if (point.value == 'X') {
                std::cout << "Guard has visited point (" << point.x << ", " << point.y << ")\n";
                count++;
            }
        }
    }

    std::cout << "Guard has visited " << count << " points.\n";

    // //print the map
    // for (const auto& row : map) {
    //     for (const auto& point : row) {
    //         std::cout << point.value;
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}
