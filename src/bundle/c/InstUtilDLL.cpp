// Gensym.cpp : Defines the entry point for the DLL application.
//

#include "InstUtilAfx.h"
#include "stdio.h"
#include "InstUtilDLL.h"

#include "obfuscate.h"

#include "wmexport.h"


extern "C" int make_watermark_file_g2pwaux (char *, char *, char *, char *, char *);
extern "C" int add_watermark_to_ok_file_g2pwaux (char *, char *, char *, char *, char *);

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}




int add_watermark_to_ok_file (char *ok_namestring, char *bundle, char *user, char *org, char *key)
{
  return(add_watermark_to_ok_file_g2pwaux (ok_namestring, bundle, user, org, key));
}

int make_watermark_file (char *directory_path, char *bundle, char *user, char *org, char *key)
{
  return(make_watermark_file_g2pwaux (directory_path, bundle, user, org, key));
}

//From MSDN library

//From several sources:
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/shell/programmersguide/versions.asp

#define PACKVERSION(major,minor) MAKELONG(minor,major)

// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore/html/vcconversioncheckingofredistributablefiles.asp

// This function gets the file version info structure
HRESULT GetFileVersion (char *filename, VS_FIXEDFILEINFO *pvsf) {
   DWORD dwHandle;
   DWORD cchver = GetFileVersionInfoSize(filename,&dwHandle);
   if (cchver == 0) 
      return E_FAIL;
   char* pver = new char[cchver];
   BOOL bret = GetFileVersionInfo(filename,dwHandle,cchver,pver);
   if (!bret) 
      return E_FAIL;
   UINT uLen;
   void *pbuf;
   bret = VerQueryValue(pver,"\\",&pbuf,&uLen);
   if (!bret) 
      return E_FAIL;
   memcpy(pvsf,pbuf,sizeof(VS_FIXEDFILEINFO));
   delete[] pver;
   return S_OK;
}

// Check if the DLL named is at least at the major.minor version
// requested.  The fourth argument is a special hack for SHELL32.DLL,
// which it's OK if it's not at the required version, as long as
// SHFOLDER.DLL is present.

int CheckDllVersion(LPTSTR base_dll_name, int major, int minor, LPTSTR other_acceptable_dll)
{
  DWORD requiredversion = PACKVERSION(major,minor);
  HRESULT ret;
  VS_FIXEDFILEINFO versioninfo;

  if (SUCCEEDED((ret = GetFileVersion(base_dll_name, &versioninfo)))) {
    if (versioninfo.dwFileVersionMS >= requiredversion) {
      //Basic file was OK.
      return 1;
    } else {
      if (SUCCEEDED((ret = GetFileVersion(other_acceptable_dll, &versioninfo)))) {
	// Basic file was too young, but other file was available.
	return 1;
      } else {
	//Basic file too young and no standin.
	return 0;
      }
    }
  } else {
    //Some error in getting file version.
    return -1;
  }
}


CGensym::CGensym()
{
	return;
}

