#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "../employee.h"

int main(int argc, char** args)
{

    std::wifstream fin(args[2]);
    std::wofstream fout(args[1]);

    fout << "Report on file " << args[2] << '\n';

    const int cntWorkers = atoi(args[3]);
    double hourCost;

    std::cout << "Enter the cost for 1 hour work" << std::endl;
    std::cin >> hourCost;

    std::vector<Employee> employees(cntWorkers);

    for (int i = 0; i < cntWorkers; i++) {
        fin.read((char*)&employees[i], sizeof(Employee));
    }

    std::sort(employees.begin(), employees.end());

    for (int i = 0; i < cntWorkers; i++) {
        fout << employees[i] << " " << employees[i].hours * hourCost << '\n';
    }

    fin.close();
    fout.close();

    system("pause");
}
