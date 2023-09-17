#include <iostream>
#include <fstream>
#include <algorithm>

#include "../employee.h"

int getLastSpaceIndex(char* row) {
    for (int i = strlen(row) - 1; i >= 0; i--) {
        if (row[i] == ' ') return i;
    }

    return -1;
}

double getLastNumber(char* row) {
    char number[10] = {0};
    int numPos = getLastSpaceIndex(row);
    strncpy_s(number, row + numPos, strlen(row) - numPos + 1);
    return atof(number); //?
};

int main(int argc, char** args)
{
    std::cout << "Args amount: " << argc << std::endl << "Args: ";

    for (int i = 0; i < argc; i++)
        std::cout << args[i] << " ";

    std::cout << std::endl;

    std::ifstream fin(args[2]);
    std::ofstream fout(args[1]);

    fout << "Report on file " << args[2] << '\n';

    const int cntWorkers = atoi(args[3]);
    double hourCost;

    std::cout << "Enter the cost for 1 hour work" << std::endl;
    std::cin >> hourCost;

    Employee employees[105];

    for (int i = 0; i < cntWorkers; i++) {
        fin >> employees[i];
    }

    std::sort(employees, employees + cntWorkers);

    for (int i = 0; i < cntWorkers; i++) {
        fout << employees[i] << " " << employees[i].hours * hourCost << '\n';
    }

    fin.close();
    fout.close();

    system("pause");
}
