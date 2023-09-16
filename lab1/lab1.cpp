#include <windows.h>
#include <conio.h>

#include <iostream>
#include <fstream>

int main()
{
	wchar_t creatorFileName[20];

	std::wcout << "Enter the name of the creator file" << std::endl;
	std::wcin >> creatorFileName;

	wchar_t lpszCommandLine[35] = L"Creator.exe ";
	wcscat_s(lpszCommandLine, creatorFileName);

	wchar_t cntEmployees[10] = L"";

	std::wcout << "Enter the amount of employees" << std::endl;
	std::wcin >> cntEmployees;

	wcscat_s(lpszCommandLine, L" ");
	wcscat_s(lpszCommandLine, cntEmployees);

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	bool status = CreateProcessW(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);

	if (!status) {
		_cputs("did not create");
		return 0;
	}

	WaitForSingleObject(&piCom, INFINITE);

	// закрываем дескрипторы этого процесса
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