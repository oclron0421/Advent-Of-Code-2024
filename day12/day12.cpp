#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <queue> 
#include <vector> 
#include <algorithm> 
#include <deque>

#define ROWS 140
#define COLS 140

int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

struct Plant {
    char value;
    bool visited;
};

int calculatePerimeter(std::vector<std::pair<int, int>>& filledCells, std::vector<std::vector<Plant>>& grid, Plant plant) {
    int perimeter = 0;
    char cellVal = plant.value; // get the value of the first cell
    for (const auto& cell : filledCells) {
        int x = cell.first;
        int y = cell.second;

        for (int k = 0; k < 4; k++) {
            int dx = x + dR[k];
            int dy = y + dC[k];

            //if hit a wall or out of bounds, perimeter++ 
            if (dx < 0 || dx >= ROWS || dy < 0 || dy >= COLS ||
                (dx >= 0 && dx < ROWS && dy >= 0 && dy < COLS &&
                    grid[dx][dy].value != cellVal)) {
                perimeter++;
            }
        }
    }
    return perimeter;
}

int getSidesFromUpOrDown(std::deque<std::pair<int, int>> boundaryCells) {
    int sides = 0;
    std::deque<std::pair<int, int>>::iterator itr = boundaryCells.begin();
    while (boundaryCells.size() > 0) {
        itr = boundaryCells.begin(); // reset the iterator to the beginning
        int refRow = itr->first;

        std::queue<std::pair<int, int>> q;
        for (auto& cell : boundaryCells) {
            if (cell.first == refRow) {
                q.push(cell);
                boundaryCells.pop_front(); // remove the cell from the deque
            }
        }
        //process the queue here 
        while (!q.empty()) {
            std::pair<int, int> current = q.front();
            q.pop();
            int a = current.second;
            current = q.front();
            int b = current.second;
            if (b == a + 1 || b == a - 1) {
                continue;
            }
            else {
                sides++;
            }
        }

    }
    return sides;
}

int getSidesFromLeftOrRight(std::deque<std::pair<int, int>> boundaryCells) {
    int sides = 0;
    std::deque<std::pair<int, int>>::iterator itr = boundaryCells.begin();
    while (boundaryCells.size() > 0) {
        itr = boundaryCells.begin();
        int refCol = itr->second;
        std::queue<std::pair<int, int>> q;
        for (auto& cell : boundaryCells) {
            if (cell.second == refCol) {
                q.push(cell);
                boundaryCells.pop_front(); // remove the cell from the deque
            }
        }
        //process the queue here
        while (!q.empty()) {
            std::pair<int, int> current = q.front();
            q.pop();
            int a = current.first;
            current = q.front();
            int b = current.first;
            if (b == a + 1 || b == a - 1) {
                continue;
            }
            else {
                sides++;
            }
        }
    }
    return sides;
}

int calculateSides(std::vector<std::pair<int, int>>& filledCells, std::vector<std::vector<Plant>>& grid) {

    std::deque<std::pair<int, int>> upBoundaries;
    std::deque<std::pair<int, int>> downBoundaries;
    std::deque<std::pair<int, int>> rightBoundaries;
    std::deque<std::pair<int, int>> leftBoundaries;
    int sides = 0;
    Plant plant = grid[filledCells[0].first][filledCells[0].second]; // get the plant from the first filled cell
    for (auto cell : filledCells) {
        int x = cell.first;
        int y = cell.second;

        // move up 
        if (x - 1 < 0 || grid[x - 1][y].value != plant.value) {
            upBoundaries.push_back({ x, y });
        }
        // move down 
        if (x + 1 >= ROWS || grid[x + 1][y].value != plant.value) {
            downBoundaries.push_back({ x, y });
        }
        // move right
        if (y + 1 >= COLS || grid[x][y + 1].value != plant.value) {
            rightBoundaries.push_back({ x, y });
        }
        // move left
        if (y - 1 < 0 || grid[x][y - 1].value != plant.value) {
            leftBoundaries.push_back({ x, y });
        }
    }

    std::sort(upBoundaries.begin(), upBoundaries.end());
    std::sort(downBoundaries.begin(), downBoundaries.end());
    std::sort(rightBoundaries.begin(), rightBoundaries.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
        });
    std::sort(leftBoundaries.begin(), leftBoundaries.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
        });


    std::cout << "Boundaries:" << std::endl;
    std::cout << "Up Boundaries: ";
    for (auto boundary : upBoundaries) {
        std::cout << "(" << boundary.first << ", " << boundary.second << ") ";
    }
    std::cout << std::endl;
    std::cout << "Down Boundaries: ";
    for (auto boundary : downBoundaries) {
        std::cout << "(" << boundary.first << ", " << boundary.second << ") ";
    }
    std::cout << std::endl;
    std::cout << "Right Boundaries: ";
    for (auto boundary : rightBoundaries) {
        std::cout << "(" << boundary.first << ", " << boundary.second << ") ";
    }
    std::cout << std::endl;
    std::cout << "Left Boundaries: ";
    for (auto boundary : leftBoundaries) {
        std::cout << "(" << boundary.first << ", " << boundary.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "Sides for up: " << getSidesFromUpOrDown(upBoundaries) << std::endl;
    std::cout << "Sides for down: " << getSidesFromUpOrDown(downBoundaries) << std::endl;
    std::cout << "Sides for right: " << getSidesFromLeftOrRight(rightBoundaries) << std::endl;
    std::cout << "Sides for left: " << getSidesFromLeftOrRight(leftBoundaries) << std::endl;

    sides += getSidesFromUpOrDown(upBoundaries);
    sides += getSidesFromUpOrDown(downBoundaries);
    sides += getSidesFromLeftOrRight(rightBoundaries);
    sides += getSidesFromLeftOrRight(leftBoundaries);

    std::cout << "Total sides: " << sides << std::endl;
    return sides;

}

std::vector<std::pair<int, int>> floodFill(
    std::vector<std::vector<Plant>>& grid, int startRow, int startCol) {
    std::vector<std::pair<int, int>> filledCells;
    if (grid[startRow][startCol].visited) {
        return filledCells;
    }

    std::queue<std::pair<int, int>> q;
    char originalCell = grid[startRow][startCol].value;
    q.push({ startRow, startCol });

    //mark the original cell as visited 
    grid[startRow][startCol].visited = true;
    filledCells.push_back({ startRow, startCol });

    //bfs (queue version)
    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        int x = current.first; int y = current.second;
        q.pop();


        for (int k = 0; k < 4;k++) {
            int dx = x + dR[k];
            int dy = y + dC[k];


            if (dx >= 0 && dx < ROWS &&
                dy >= 0 && dy < COLS &&
                grid[dx][dy].value == originalCell &&
                !grid[dx][dy].visited) { // check if the cell is within bounds and has the same value
                //mark the cell as visited 
                grid[dx][dy].visited = true;
                q.push({ dx, dy });
                filledCells.push_back({ dx, dy });
            }
        }
    }
    return filledCells;
}


int main() {
    std::ifstream file("input.txt");
    std::vector<std::vector<Plant>> grid;

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<Plant> row;
        for (char c : line) {
            Plant plant;
            plant.value = c;
            plant.visited = false; // initially not visited
            row.push_back(plant);
        }
        grid.push_back(row);
    }

    file.close();
    int cost = 0;
    int sidesCost = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!grid[i][j].visited) {
                Plant currentPlant = grid[i][j]; //for debugging
                std::vector<std::pair<int, int>> filledCells = floodFill(grid, i, j);
                int perimeter = calculatePerimeter(filledCells, grid, grid[i][j]);
                int area = filledCells.size();
                cost += perimeter * area; // cost is perimeter * area
                int sides = calculateSides(filledCells, grid);
                sidesCost += sides * area; // sides cost is sides * area
                // std::cout << "Sides cost: " << sidesCost << std::endl;
            }
        }
    }

    std::cout << "Total cost: " << cost << std::endl;
    std::cout << "Total sides cost: " << sidesCost << std::endl;
    return 0;
}