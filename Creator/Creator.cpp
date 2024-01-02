#include <iostream>
#include <fstream>

#include "../employee.h"

int main(int argc, char** args)
{

    std::cout << "Enter info for " << args[2] << " empolyees (id, name, hours)" << std::endl;

    char* fileEmployees = args[1];
    Employee curEmployee;

    std::ofstream fout(fileEmployees, std::ios::binary);

    for (int i = 0; i < atoi(args[2]); i++) {
        std::cin >> curEmployee;
        fout.write((char*)&curEmployee, sizeof(Employee));
    }

    fout.close();

    system("pause");
}
