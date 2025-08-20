#include <iostream> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <vector> 
#include <set>

std::vector<std::vector<int>> grid;
std::vector<std::vector<bool>> visited;
std::vector<std::pair<int, int>> path;

int rows, cols;
int pathCount = 0;

int dR[4] = { -1, 1, 0, 0 };
int dC[4] = { 0, 0, -1, 1 };

// up - (-1,0)
// down - (1,0)
// left - (0,-1)
// right - (0,1) 

void dfs(int r, int c, int val, std::set<std::pair<int, int>>& reachable9, std::vector<std::vector<bool>>& visited) {
    visited[r][c] = true;

    if (val == 9) {
        reachable9.insert({ r,c }); // record this 9
        return;
    }

    for (int k = 0; k < 4; k++) {
        int nr = r + dR[k];
        int nc = c + dC[k];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (!visited[nr][nc] && grid[nr][nc] == val + 1) {
                dfs(nr, nc, val + 1, reachable9, visited);
            }
        }
    }
}

int dfs_count(int r, int c, int val, std::vector<std::vector<bool>>& visited) {
    if (val == 9) return 1; // base case: reached a 9, one valid path

    visited[r][c] = true;
    int count = 0;

    for (int k = 0; k < 4; k++) {
        int nr = r + dR[k];
        int nc = c + dC[k];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (!visited[nr][nc] && grid[nr][nc] == val + 1) {
                count += dfs_count(nr, nc, val + 1, visited);
            }
        }
    }

    visited[r][c] = false; // backtrack
    return count;
}


int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (auto c : line) {
            if (std::isdigit(c)) {
                row.push_back(c - '0');
            }
        }
        grid.push_back(row);
    }

    //print the vector 
    std::cout << "Grid:" << std::endl;
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    rows = grid.size();
    cols = grid[0].size();
    int count;
    int totalPaths = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) {
                std::set<std::pair<int, int>> reachable9;
                std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

                dfs(r, c, 0, reachable9, visited);

                std::cout << "0 at (" << r << "," << c << ") can reach "
                    << reachable9.size() << " different 9s\n";

                count += reachable9.size();


                //part 2 
                std::vector<std::vector<bool>> visited_for_count(rows, std::vector<bool>(cols, false));
                totalPaths += dfs_count(r, c, 0, visited_for_count);
                std::cout << "Total paths from (" << r << "," << c << ") to 9s: " << totalPaths << std::endl;
            }
        }
    }


    std::cout << "Total reachable 9s from all 0s: " << count << std::endl;
    std::cout << "Total paths found: " << totalPaths << std::endl;

    return 0;
}