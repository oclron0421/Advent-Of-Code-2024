#include <iostream> 
#include <fstream> 
#include <string> 
#include <stack>
#include <vector> 
#include <queue>
#include <sstream> 

void popStack(std::stack<long long>& s, std::stack<std::vector<long long>>& ops) {
    if (!s.empty() && !ops.empty()) {
        s.pop();
        ops.pop();
    }
    else {
        std::cerr << "Error: Stack is empty." << std::endl;
    }
}

std::queue<std::string> operatorGenerator(int n) {
    std::queue<std::string> operators;
    for (int i = 0; i < (1 << n); i++) { // generate 2^n patterns
        std::string pattern;
        for (int b = n - 1; b >= 0; b--) { // loop over bits
            if (i & (1 << b))
                pattern += "*";
            else
                pattern += "+";
        }
        operators.push(pattern);
    }
    return operators;
}


int main() {

    std::stack<long long> answer;
    std::stack<std::vector<long long>> operands;
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(input, line)) {
        // Process each line of the input file
        std::stringstream ss(line);
        std::string leftPart;
        std::getline(ss, leftPart, ':');

        long long leftNum = std::stoll(leftPart);
        answer.push(leftNum);

        std::vector<long long> nums;
        long long num;
        while (ss >> num) {
            nums.push_back(num);
        }

        operands.push(nums);
    }

    if (answer.size() != operands.size()) {
        std::cerr << "Error: Mismatched sizes of answers and operators." << std::endl;
        return 1;
    }

    long long totalCalibrationResult = 0;

    while (!answer.empty() && !operands.empty()) {
        long long currentAnswer = answer.top();
        std::vector<long long> currentOperands = operands.top();

        int operatorsNeeded = currentOperands.size() - 1;
        std::queue<std::string> operatorQueue = operatorGenerator(operatorsNeeded);

        while (!operatorQueue.empty()) {
            std::string currentOperators = operatorQueue.front();
            std::string originalOperators = currentOperators; // keep copy for printing
            int i = 0;
            long long tempAnswer = currentOperands[0];

            while (!currentOperators.empty()) {
                char currentOp = currentOperators.front();
                currentOperators.erase(currentOperators.begin());
                if (currentOp == '*') {
                    tempAnswer *= currentOperands[i + 1];
                }
                else if (currentOp == '+') {
                    tempAnswer += currentOperands[i + 1];
                }
                i++;
            }

            if (tempAnswer == currentAnswer) {
                std::cout << "Found a match: " << currentAnswer
                    << " with operators: " << originalOperators << std::endl;
                totalCalibrationResult += currentAnswer;
                operatorQueue.pop(); // pop the current operator pattern
                break; // exit the operator loop, we found a match
            }

            operatorQueue.pop(); // pop once, always at the end
        }
        popStack(answer, operands);
    }

    std::cout << "Total Calibration Result: " << totalCalibrationResult << std::endl;
    return 0;

}
