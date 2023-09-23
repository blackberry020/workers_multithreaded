#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>

#include "../employee.h"

#include <gtest/gtest.h>

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

void printTextFileContent(std::wstring fileName) {

	std::wstring curRow;
	std::wifstream fin(fileName);

	if (!fin.is_open()) {
		std::wcout << L"could not open the file " << fileName << std::endl;
		return;
	}

	while (getline(fin, curRow)) {
		std::wcout << curRow << std::endl;
	}
	fin.close();

	return;
}

void printEmployeesFileContent(std::wstring fileName) {

	std::wifstream fin(fileName);

	if (!fin.is_open()) {
		std::wcout << L"could not open the file " << fileName << std::endl;
		return;
	}

	Employee curEmployee;

	while (!fin.read( (wchar_t*)&curEmployee, sizeof(Employee)).eof()) {
		std::wcout << curEmployee << std::endl;
	}
	fin.close();

	return;
}

TEST() {

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

	wchar_t* finalCreatorCommand = _wcsdup(commandLine.c_str());

	runProcess(finalCreatorCommand);

	printEmployeesFileContent(creatorFileName);

	std::wcout << "Enter the name of the reporter file" << std::endl;
	std::wstring reporterFileName;
	std::wcin >> reporterFileName;

	std::wstring reporterCommandLine = L"Reporter.exe ";
	reporterCommandLine += reporterFileName + L" " + creatorFileName + L" " + cntEmployees;

	wchar_t* finalReporterCommand = _wcsdup(reporterCommandLine.c_str());

	runProcess(finalReporterCommand);

	printTextFileContent(reporterFileName);

	system("pause");
	return RUN_ALL_TESTS();
}