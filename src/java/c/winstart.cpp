// winstart.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"

void PrintHelp (void)
{
	printf("Gensym Executable command line application launcher v1.0\n");
	printf("========================================================\n");
	printf("\n");
	printf("Copyright (C) 1986-2017 Gensym Corporation.\n");
	printf("\n");
	printf("Command line: winstart [-hide] \"Start Up Command\"\n");
	printf("\n");
}

int main(int argc, char* argv[])
{
	// See if user has requested help with the command line parameter
	char tempstr[1024];
	if ( argc <2)
	{
		PrintHelp();
		return -1;
	}
	strcpy(tempstr, argv[1]);
	strupr(tempstr);
	if (strstr(tempstr,"-?") == tempstr || strstr(tempstr, "/?"))
	{
		PrintHelp();
		return -1;
	}

	STARTUPINFO supinfo;
	PROCESS_INFORMATION procinfo;

	memset(&supinfo, 0, sizeof(supinfo));
	supinfo.cb = sizeof(supinfo);
	memset(&procinfo, 0, sizeof(procinfo));

	// Check for hide flag
	char cmdstr[1024];
	cmdstr[0] = 0;
	strcpy(tempstr,argv[1]);
	strupr(tempstr);
	if (strstr(tempstr, "-HIDE") == tempstr)
	{
		supinfo.wShowWindow = SW_HIDE;
		supinfo.dwFlags = STARTF_USESHOWWINDOW;
	}

	for (int i = 1; i < argc; i++)
	{
		strcpy(tempstr, argv[i] );
		strupr(tempstr);
		if (strstr(tempstr, "-HIDE") == tempstr && i == 1) ;
		else
		{
			strcat(cmdstr, argv[i]);
			strcat(cmdstr, " ");
		}
	}

	BOOL bl = CreateProcess(NULL, cmdstr, NULL, NULL, false, 
							CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, 
							NULL, NULL, &supinfo, &procinfo);
	printf("\nApplication launched with process ID: %d \n\n", procinfo.hProcess);

	return true;
}
