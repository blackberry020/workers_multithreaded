#include <iostream>
#include <fstream>

int getLastSpaceIndex(char* row) {
    for (int i = strlen(row) - 1; i >= 0; i--) {
        if (row[i] == ' ') return i;
    }

    return -1; // TODO exception
}

double getLastNumber(char* row) {
    char number[10];
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

    int cntWorkers = atoi(args[3]);
    double curHourCost;
    double curWorkingHours;
    char curRow[100];

    std::cout << "Enter working hours for " << cntWorkers << " workers" << std::endl;

    for (int i = 0; i < cntWorkers; i++) {
        fin.getline(curRow, 100);
        curHourCost = getLastNumber(curRow);
        std::cin >> curWorkingHours;
        fout << curRow << " " << curHourCost * curWorkingHours << '\n';
    }

    fin.close();
    fout.close();

    system("pause");
}
