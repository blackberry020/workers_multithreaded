#include <windows.h>
#include <conio.h>
#include <stdarg.h>

#include <iostream>
#include <fstream>

wchar_t* charUnion(int cntArguments,...) {

	va_list valist;
	va_start(valist, cntArguments);

	wchar_t mainString[100] = L"";

	for (int i = 0; i < cntArguments; i++) {
		wchar_t* curString = va_arg(valist, wchar_t*);
		wcscat_s(mainString, curString);
	}

	va_end(valist);

	wchar_t* result = mainString;

	return result;
}

void createProcess() {

}

int main()
{
	std::wcout << "Enter the name of the creator file" << std::endl;
	wchar_t creatorFileName[20];
	std::wcin >> creatorFileName;

	wchar_t cntEmployees[10] = L"";
	std::wcout << "Enter the amount of employees" << std::endl;
	std::wcin >> cntEmployees;

	wchar_t commandLine[100] = L"Creator.exe ";
	wcscat_s(commandLine, creatorFileName);
	wcscat_s(commandLine, L" ");
	wcscat_s(commandLine, cntEmployees);

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	bool status = CreateProcessW(NULL, commandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);

	if (!status) {
		_cputs("did not create");
		return 0;
	}

	WaitForSingleObject(piCom.hProcess, INFINITE);

	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	char curRow[30];
	std::ifstream fin(creatorFileName);

	while (fin.getline(curRow, 100)) {
		std::wcout << curRow << std::endl;
	}
	fin.close();

	STARTUPINFO si2;
	PROCESS_INFORMATION piCom2;
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);

	std::wcout << "Enter the name of the reporter file" << std::endl;
	wchar_t reporterFileName[20];
	std::wcin >> reporterFileName;

	wchar_t reporterCommandLine[100] = L"Reporter.exe ";
	wcscat_s(reporterCommandLine, reporterFileName);
	wcscat_s(reporterCommandLine, L" ");
	wcscat_s(reporterCommandLine, creatorFileName);
	wcscat_s(reporterCommandLine, L" ");
	wcscat_s(reporterCommandLine, cntEmployees);

	status = CreateProcessW(NULL, reporterCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si2, &piCom2);

	if (!status) {
		_cputs("did not create");
		return 0;
	}

	WaitForSingleObject(piCom2.hProcess, INFINITE);

	CloseHandle(piCom2.hThread);
	CloseHandle(piCom2.hProcess);

	fin.open(reporterFileName);

	while (fin.getline(curRow, 100)) {
		std::wcout << curRow << std::endl;
	}
	fin.close();

	_cputs("Press any key to finish.\n");
	_getch();
	return 0;
}