#pragma once
#include <windows.h>

class CommandLineRunner
{
public:
	bool run(LPWSTR cmd)
	{
		STARTUPINFO cif;
		PROCESS_INFORMATION processInfo;
		ZeroMemory(&cif, sizeof(STARTUPINFO));
		return CreateProcess(NULL, cmd,	NULL, NULL, FALSE, CREATE_NO_WINDOW,
			NULL, NULL, &cif, &processInfo) != FALSE;

	}
};
