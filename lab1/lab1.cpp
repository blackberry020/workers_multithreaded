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

	std::wcout << result << std::endl;

	return result;
}

int main()
{
	std::wcout << "Enter the name of the creator file" << std::endl;
	wchar_t creatorFileName[20];
	std::wcin >> creatorFileName;

	wchar_t* commandLine;

	wchar_t cntEmployees[10] = L"";
	std::wcout << "Enter the amount of employees" << std::endl;
	std::wcin >> cntEmployees;

	commandLine = charUnion(4, L"Creator.exe ", creatorFileName, L" ", cntEmployees);

	//std::wcout << commandLine << std::endl;

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

	while (fin >> curRow) {
		std::wcout << curRow;
	}
	fin.close();

	_cputs("The new process is created.\n");
	_cputs("Press any key to finish.\n");
	_getch();
	return 0;
}