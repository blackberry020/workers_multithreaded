#include <iostream>
#include <fstream>

#include "../employee.h"

int main(int argc, char** args)
{
    std::cout << "Args amount: " << argc << std::endl << "Args: ";

    for (int i = 0; i < argc; i++)
        std::cout << args[i] << " ";

    std::cout << std::endl;

    char* fileEmployees = args[1];
    Employee curEmployee;

    std::ofstream fout(fileEmployees);

    for (int i = 0; i < atoi(args[2]); i++) {
        std::cin >> curEmployee;
        fout << curEmployee << '\n';
    }

    fout.close();

    system("pause");
}
