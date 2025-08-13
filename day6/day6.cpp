#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#define COLS 10
#define ROWS 10

struct Point {
    int x;
    int y;
    char value;
    int timesVisited = 0;
};

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct guardPos {
    int x;
    int y;
    bool exited = false; // Flag to indicate if the guard has exited the map
    char value = '^'; // Default value for the guard    
    void visited(Point& p) {
        //p.value = 'X'; // enable this line when solving for part 1 
        p.timesVisited++;
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
            //std::cout << "Guard has exited the map at (" << guard.x << ", " << guard.y << ")\n";
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
    std::queue<Point> guardPath;
    int guardX, guardY;
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
                guardX = i;
                guardY = map.size();
                guardPath.push(p); // Add the guard's starting position to the path queue
                std::cout << "Guard starts at (" << guard.x << ", " << guard.y << ") facing " << guard.value << "\n";
            }
        }
        map.push_back(row);
    }

    // code for the guard path in the map
    while (!guard.exited) {
        switch (guard.value) {
        case '^':
            goUp(map);
            guardPath.push(map[guard.y][guard.x]);
            break;
        case 'v':
            goDown(map);
            guardPath.push(map[guard.y][guard.x]);
            break;
        case '<':
            goLeft(map);
            guardPath.push(map[guard.y][guard.x]);
            break;
        case '>':
            goRight(map);
            guardPath.push(map[guard.y][guard.x]);
            break;
        }
    }

    //cycle through the map and look for 'X'
    int count = 0;
    for (const auto& row : map) {
        for (const auto& point : row) {
            if (point.value == 'X') {
                count++;
            }
        }
    }

    std::cout << "Guard has visited " << count << " points.\n";

    //print the whole map
    // for (const auto& row : map) {
    //     for (const auto& point : row) {
    //         std::cout << point.value;
    //     }
    //     std::cout << std::endl;
    // }

//find the point that has been visited the most in the map 
    // int maxVisits = 0;
    // Point mostVisitedPoint;
    // for (const auto& row : map) {
    //     for (const auto& point : row) {
    //         if (point.timesVisited > maxVisits) {
    //             maxVisits = point.timesVisited;
    //             mostVisitedPoint = point;
    //         }
    //     }
    // }
    // std::cout << "Most visited point is at (" << mostVisitedPoint.x << ", " << mostVisitedPoint.y
    //     << ") with " << mostVisitedPoint.timesVisited << " visits.\n";

    //part 2 
    int obsCount = 0;
    bool isLoop = false;
    std::vector<Point> obsPoint;
    Point previousPoint;
    //reset guard position
    guard.x = guardX;
    guard.y = guardY;
    guard.value = '^';
    guard.exited = false;
    guardPath.pop(); // Remove the initial guard position from the queue


    while (!guardPath.empty()) {
        Point current = guardPath.front();
        if ((current.x == guardX && current.y == guardY) || (previousPoint.x == current.x && previousPoint.y == current.y)) {
            guardPath.pop(); // Skip the initial position
            continue;
        }
        guard.x = guardX;
        guard.y = guardY;
        map[current.y][current.x].value = '#'; // Put an obstacle infront of the guard and test
        //print the whole map
        // for (const auto& row : map) {
        //     for (const auto& point : row) {
        //         std::cout << point.value;
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << "Obstacle at (" << current.x << ", " << current.y << ")\n";

        while (!guard.exited && !isLoop) {
            switch (guard.value) {
            case '^':
                goUp(map);
                if (map[guard.y][guard.x].timesVisited > 4) {
                    isLoop = true; // Loop detected
                    obsCount++;
                    std::cout << "obstacle that caused a loop is at (" << current.x << ", " << current.y << ")\n";
                    map[current.y][current.x].value = '.'; // Reset the point to empty
                    obsPoint.push_back(current); // Store the obstacle point
                    break;
                }
                break;
            case 'v':
                goDown(map);
                if (map[guard.y][guard.x].timesVisited > 4) {
                    isLoop = true; // Loop detected
                    obsCount++;
                    std::cout << "obstacle that caused a loop is at (" << current.x << ", " << current.y << ")\n";
                    map[current.y][current.x].value = '.';
                    obsPoint.push_back(current); // Store the obstacle point
                    break;
                }
                break;
            case '<':
                goLeft(map);
                if (map[guard.y][guard.x].timesVisited > 4) {
                    isLoop = true; // Loop detected
                    obsCount++;
                    std::cout << "obstacle that caused a loop is at (" << current.x << ", " << current.y << ")\n";
                    map[current.y][current.x].value = '.';
                    obsPoint.push_back(current); // Store the obstacle point
                    break;
                }
                break;
            case '>':
                goRight(map);
                if (map[guard.y][guard.x].timesVisited > 4) {
                    isLoop = true; // Loop detected
                    obsCount++;
                    std::cout << "obstacle that caused a loop is at (" << current.x << ", " << current.y << ")\n";
                    map[current.y][current.x].value = '.';
                    obsPoint.push_back(current); // Store the obstacle point
                    break;
                }
                break;
            }
        }
        guard.x = guardX;
        guard.y = guardY;
        guard.value = '^'; // Reset the guard's direction
        map[current.y][current.x].value = '.'; // Restore the point to the guard's value
        guard.exited = false; // Reset the guard's exited status for the next iteration
        isLoop = false; // Reset the loop detection flag
        //reset all the times each point is visited 
        for (auto& row : map) {
            for (auto& point : row) {
                point.timesVisited = 0; // Reset the times visited count
            }
        }
        previousPoint = current; // Store the current point as the previous point
        guardPath.pop();
    }

    std::unordered_set<std::pair<int, int>, PairHash> seen;
    obsPoint.erase(
        std::remove_if(obsPoint.begin(), obsPoint.end(), [&](const Point& p) {
            auto coord = std::make_pair(p.x, p.y);
            if (seen.find(coord) != seen.end()) {
                return true; // already exists → remove
            }
            seen.insert(coord);
            return false;
            }),
        obsPoint.end()
    );

    std::cout << "Total possible obstacles to put in the map: " << obsPoint.size() << "\n";
    return 0;
}
