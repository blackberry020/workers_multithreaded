#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>
#include "../employee.h"

void runProcess(wchar_t* command) {

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	bool status = CreateProcessW(NULL, command, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);

	if (!status) {
		std::wcout << "did not create";
		exit(-1);
	}

	WaitForSingleObject(piCom.hProcess, INFINITE);

	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	return;
}

void printFileContent(std::wstring fileName) {

	std::wstring curRow;
	std::wifstream fin(fileName);

	while (getline(fin, curRow)) {
		std::wcout << curRow << std::endl;
	}
	fin.close();

	return;
}

void printBinFileContent(std::wstring fileName) {

	std::ifstream fin(fileName, std::ios::binary);
	Employee empl;

	while (!fin.read((char*)&empl, sizeof(Employee)).eof()) {
		std::wcout << empl << std::endl;
	}

	fin.close();

	return;
}

TEST(employeeSort, sortIsNeeded) {
	std::vector<Employee> employees = { {1, "Betta", 34}, {2, "Alpha", 23} };
	std::sort(employees.begin(), employees.end());
	std::vector<Employee> expected = { {2, "Alpha", 23}, {1, "Betta", 34} };

	ASSERT_EQ(employees.size(), expected.size());
	for (size_t i = 0; i < employees.size(); ++i) {
		EXPECT_EQ(employees[i], expected[i]);
	}
};

TEST(employeeSort, alreadySorted) {
	std::vector<Employee> employees = { {2, "Alpha", 23}, {1, "Betta", 34} };
	std::sort(employees.begin(), employees.end());
	std::vector<Employee> expected = { {2, "Alpha", 23}, {1, "Betta", 34} };

	ASSERT_EQ(employees.size(), expected.size());
	for (size_t i = 0; i < employees.size(); ++i) {
		EXPECT_EQ(employees[i], expected[i]);
	}
};

int main(int argc, char** args)
{
	testing::InitGoogleTest(&argc, args);

	std::wcout << "Enter the name of the creator file" << std::endl;
	std::wstring creatorFileName;
	std::wcin >> creatorFileName;

	std::wstring cntEmployees;
	std::wcout << "Enter the amount of employees" << std::endl;
	std::wcin >> cntEmployees;

	std::wstring commandLine = L"Creator.exe ";
	commandLine += creatorFileName + L" " + cntEmployees;

	wchar_t* finalCommand = _wcsdup(commandLine.c_str());

	runProcess(finalCommand);

	printBinFileContent(creatorFileName);

	std::wcout << "Enter the name of the reporter file" << std::endl;
	std::wstring reporterFileName;
	std::wcin >> reporterFileName;

	std::wstring reporterCommandLine = L"Reporter.exe ";
	reporterCommandLine += reporterFileName + L" " + creatorFileName + L" " + cntEmployees;

	wchar_t* finalCommand2 = _wcsdup(reporterCommandLine.c_str());

	runProcess(finalCommand2);

	printFileContent(reporterFileName);

	system("pause");
	//return 0;
	return RUN_ALL_TESTS();
}