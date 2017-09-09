#include "stdafx.h"
#include "TestGetTWCmdLine.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestGetTWCmdLine);

/*
 *  MAX_CMD_LINE_LENGTH refers to the max command line windows supports
 */

#define MAX_CMD_LINE_LENGTH 8192

char *szCmdLineNow = NULL;

void SetCommandLine(char *szCmdLine)
{
	szCmdLineNow = szCmdLine;
}

void ClearCommandLine()
{
	if(!szCmdLineNow)
		delete []szCmdLineNow;
	szCmdLineNow = NULL;
}

WCHAR* WINAPI MyGetCommandLineW()
{
	WCHAR* buf = NULL;
	int bufLen;
	bufLen = MultiByteToWideChar(CP_ACP, 0, szCmdLineNow, strlen(szCmdLineNow), buf, 0);
	buf = new WCHAR[bufLen + 2];
	bufLen = MultiByteToWideChar(CP_ACP, 0, szCmdLineNow, strlen(szCmdLineNow), buf, bufLen);
	buf[bufLen] = '\0';
	return buf;
}

CHAR* WINAPI MyGetCommandLineA()
{
	CHAR* buf = new CHAR[strlen(szCmdLineNow) + 1];
	strcpy(buf, szCmdLineNow);
	return buf;
}

void RedirectWinapi(int *addr, int *myaddr)
{
	PIMAGE_DOS_HEADER  pDosHeader;
	PIMAGE_NT_HEADERS  pNTHeaders;
	PIMAGE_OPTIONAL_HEADER   pOptHeader;
	PIMAGE_IMPORT_DESCRIPTOR  pImportDescriptor;
	PIMAGE_THUNK_DATA         pThunkData;
	HMODULE hMod;

    hMod = GetModuleHandle(NULL);

    pDosHeader = (PIMAGE_DOS_HEADER)hMod;
    pNTHeaders = (PIMAGE_NT_HEADERS)((BYTE *)hMod + pDosHeader->e_lfanew);
    pOptHeader = (PIMAGE_OPTIONAL_HEADER)&(pNTHeaders->OptionalHeader);

    pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE *)hMod + pOptHeader->DataDirectory[1].VirtualAddress);

    while(pImportDescriptor->FirstThunk)
    {
            char * dllname = (char *)((BYTE *)hMod + pImportDescriptor->Name);

            pThunkData = (PIMAGE_THUNK_DATA)((BYTE *)hMod + pImportDescriptor->OriginalFirstThunk);

            int no = 1;
            while(pThunkData->u1.Function)
            {
                    char * funname = (char *)((BYTE *)hMod + (DWORD)pThunkData->u1.AddressOfData + 2);
                    PDWORD lpAddr = (DWORD *)((BYTE *)hMod + (DWORD)pImportDescriptor->FirstThunk) +(no-1);
                    if((*lpAddr) == (int)addr)
                    {
                            DWORD dwOLD;
                            MEMORY_BASIC_INFORMATION  mbi;
                            VirtualQuery(lpAddr,&mbi,sizeof(mbi));
                            VirtualProtect(lpAddr,sizeof(DWORD),PAGE_READWRITE,&dwOLD);
                            WriteProcessMemory(GetCurrentProcess(),
                                            lpAddr, &myaddr, sizeof(DWORD), NULL);
                            VirtualProtect(lpAddr,sizeof(DWORD),dwOLD,0);
                    }
                    no++;
                    pThunkData++;
            }
            pImportDescriptor++;
    }
	return;
}


void TestGetTWCmdLine::setUp()
{
	// construct the first command line for test
	
	szTestCmdLine_1 = new char[MAX_CMD_LINE_LENGTH];
	szTestRightRet_1 = new char[MAX_CMD_LINE_LENGTH];   // The correct return of the function
	strcpy(szTestCmdLine_1, "c:\\g2\\dst\\twng\\opt\\twng.exe localhost 1111 -log C:\\G2\\tw2mclog.text"
		" -fullscreen -closebox disable -background gensym -name aa-bb-cccc-x-long-name-!-re"
		"ally-long-1234567-long-tw-name-tw-long-11111111111111111111111111-2222222222AB");
	strcpy(szTestRightRet_1, "localhost 1111 -log C:\\G2\\tw2mclog.text"
		" -fullscreen -closebox disable -background gensym -name aa-bb-cccc-x-long-name-!-re"
		"ally-long-1234567-long-tw-name-tw-long-11111111111111111111111111-2222222222AB");
	
	// construct the second command line for test
	szTestCmdLine_2 = new char[MAX_CMD_LINE_LENGTH];
	szTestRightRet_2 = new char[MAX_CMD_LINE_LENGTH];   // The correct return of the function
	strcpy(szTestCmdLine_2, "c:\\g2\\dst\\twng\\opt\\twng.exe localhost 1111 -log C:\\G2\\tw2mclog.text"
        	" -fullscreen -closebox disable -background gensym -name aa-bb-cccc-x-long-name-!-re"
		"ally-long-1234567-long-tw-name-tw-long-11111111111111111111111111-2222222222AB"
		"TestTestABCDEFGHIJKLMNOPQRSTUVWXYZtestTEST1111111122222222333333334344444444545");
	strcpy(szTestRightRet_2, "localhost 1111 -log C:\\G2\\tw2mclog.text"
        	" -fullscreen -closebox disable -background gensym -name aa-bb-cccc-x-long-name-!-re"
		"ally-long-1234567-long-tw-name-tw-long-11111111111111111111111111-2222222222AB"
		"TestTestABCDEFGHIJKLMNOPQRSTUVWXYZtestTEST1111111122222222333333334344444444545");

	// Redirect the winapi function to my function
	RedirectWinapi((int *) GetCommandLineA, (int *) MyGetCommandLineA);
	RedirectWinapi((int *) GetCommandLineW, (int *) MyGetCommandLineW);
}

void TestGetTWCmdLine::tearDown()
{
	if(!szTestCmdLine_1)
		delete []szTestCmdLine_1;
	szTestCmdLine_1 = NULL;
	if(!szTestRightRet_1)
		delete []szTestRightRet_1;
	szTestRightRet_1 = NULL;
	if(!szTestCmdLine_2)
		delete []szTestCmdLine_2;
	szTestCmdLine_2 = NULL;
	if(!szTestRightRet_2)
		delete []szTestRightRet_2;
	szTestRightRet_2 = NULL;
	
	ClearCommandLine();
}

/*
 * Verifies the string of command line is the same as the one we send into twng program.
 */
void TestGetTWCmdLine::test()
{
	SetCommandLine(szTestCmdLine_1);
	int ret1 = strcmp(szTestRightRet_1, get_tw_cmdline());
	
	SetCommandLine(szTestCmdLine_2);
	int ret2 = strcmp(szTestRightRet_2, get_tw_cmdline());
	
	CPPUNIT_ASSERT((ret1 == 0));
	CPPUNIT_ASSERT((ret2 == 0));
}

