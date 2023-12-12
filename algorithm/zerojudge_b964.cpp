// https://zerojudge.tw/ShowProblem?problemid=b964

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main() {
    std::string line;
    int studentNum;

    while (std::cin >> studentNum && std::cin.ignore()) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::vector<int> studentList, great, nope;
        int score;

        while (iss >> score) {
            studentList.push_back(score);
        }

        std::sort(studentList.begin(), studentList.end());

        for (std::vector<int>::size_type i = 0; i < studentList.size(); ++i) {
            if (studentList[i] < 60) {
                nope.push_back(studentList[i]);
            } else if (studentList[i] <= 100) {
                great.push_back(studentList[i]);
            }
        }

        for (std::vector<int>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        if (nope.empty()) {
            std::cout << "best case" << std::endl;
        } else {
            std::cout << *std::max_element(nope.begin(), nope.end()) << std::endl;
        }

        if (great.empty()) {
            std::cout << "worst case" << std::endl;
        } else {
            std::cout << *std::min_element(great.begin(), great.end()) << std::endl;
        }
    }

    return 0;
}