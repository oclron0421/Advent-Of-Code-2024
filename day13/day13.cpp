#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <sstream> 
#include <array>
#include <cmath>

struct Machine {
    int buttons[2][2];
    int prize[2]; // Prize
};

int getDet(int matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool isWholeNumber(double num) {
    // Method 1: Using floor()
    if (std::floor(num) == num && num >= 0) {
        return true;
    }
    // Method 2: Using fmod() (consider floating-point precision)
    // if (fmod(num, 1.0) == 0.0 && num >= 0) {
    //     return true;
    // }
    return false;
}

std::array<double, 2> multiply2Matrices(int a[2][2], int b[2]) {
    std::array<double, 2> result;
    result[0] = a[0][0] * b[0] + a[0][1] * b[1];
    result[1] = a[1][0] * b[0] + a[1][1] * b[1];

    return result;
}

std::array<long double, 2> multiply2Matrices(int a[2][2], long double b[2]) {
    std::array<long double, 2> result;
    result[0] = a[0][0] * b[0] + a[0][1] * b[1];
    result[1] = a[1][0] * b[0] + a[1][1] * b[1];

    return result;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    long long token = 0;
    std::vector<Machine> machines;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // skip blank lines

        Machine m;

        // --- Button A ---
        // Format: "Button A: X+94, Y+34"
        std::stringstream ssA(line);
        std::string tmp;
        ssA >> tmp >> tmp; // skip "Button A:"
        ssA.ignore(2);     // skip "X+"
        ssA >> m.buttons[0][0];
        ssA.ignore(3);     // skip ", Y+"
        ssA >> m.buttons[1][0];

        // --- Button B ---
        std::getline(file, line);
        std::stringstream ssB(line);
        ssB >> tmp >> tmp; // skip "Button B:"
        ssB.ignore(2);     // skip "X+"
        ssB >> m.buttons[0][1];
        ssB.ignore(3);     // skip ", Y+"
        ssB >> m.buttons[1][1];

        // --- Prize ---
        std::getline(file, line);
        std::stringstream ssP(line);
        ssP >> tmp; // skip "Prize:"
        ssP.ignore(3); // skip "X="
        ssP >> m.prize[0];
        ssP.ignore(4); // skip ", Y="
        ssP >> m.prize[1];

        machines.push_back(m);
    }

    file.close();
    //Test print 
    for (const auto& m : machines) {
        std::cout << "A(" << m.buttons[0][0] << "," << m.buttons[0][1] << ") "
            << "B(" << m.buttons[1][0] << "," << m.buttons[1][1] << ") "
            << "P(" << m.prize[0] << "," << m.prize[1] << ")\n";
    }


    /*    for (auto m : machines) {
            int det = getDet(m.buttons);
            if (det == 0) {
                std::cout << "No unique solution for machine with buttons: ["
                    << m.buttons[0][0] << "," << m.buttons[0][1] << ";"
                    << m.buttons[1][0] << "," << m.buttons[1][1] << "]\n";
                continue;
            }

            // Inverse of 2x2 matrix
            int inv[2][2] = {
                { m.buttons[1][1], -m.buttons[0][1] },
                { -m.buttons[1][0], m.buttons[0][0] }
            };



            std::array<double, 2> result = multiply2Matrices(inv, m.prize);
            result[0] /= det;
            result[1] /= det;
            if (result[0] > 100 || result[1] > 100 || !isWholeNumber(result[0]) || !isWholeNumber(result[1])) {
                continue;
            }
            token += result[0] * 3 + result[1];
            std::cout << "Press Button A " << result[0] << " times and Button B " << result[1] << " times.\n";
        }

        std::cout << "Total token: " << token << "\n";

    */
    //part 2 
    token = 0;
    for (auto m : machines) {
        int det = getDet(m.buttons);
        if (det == 0) {
            std::cout << "No unique solution for machine with buttons: ["
                << m.buttons[0][0] << "," << m.buttons[0][1] << ";"
                << m.buttons[1][0] << "," << m.buttons[1][1] << "]\n";
            continue;
        }

        // Inverse of 2x2 matrix
        int inv[2][2] = {
            { m.buttons[1][1], -m.buttons[0][1] },
            { -m.buttons[1][0], m.buttons[0][0] }
        };

        long double tempX = 10000000000000 + m.prize[0];
        long double tempY = 10000000000000 + m.prize[1];

        long double newPrize[2] = { tempX, tempY };

        std::array<long double, 2> result = multiply2Matrices(inv, newPrize);
        result[0] /= det;
        result[1] /= det;
        if (!isWholeNumber(result[0]) || !isWholeNumber(result[1])) {
            continue;
        }
        token += result[0] * 3 + result[1];
        std::cout << "Press Button A " << result[0] << " times and Button B " << result[1] << " times.\n";
    }
    std::cout << "Total token: " << token << "\n";
    return 0;
}