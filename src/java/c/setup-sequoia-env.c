#include <windows.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string.h>

static void AppendDirsToEnvVar(HKEY hCreatedKey, const char* pKey,
                               char* paDirs[], int dirCount);

#define PATH_VARS (sizeof (pathData) / sizeof (char*))
#define CLASSPATH_VARS (sizeof (classpathData) / sizeof (char*))
#define BIN_DIR "\\Java\\bin"

int main (int argc, char** argv)
{
    char *classpathData[] = 
        {"%SEQUOIA_HOME%\\Java\\classes",
         "%SEQUOIA_HOME%\\Java\\classes\\antlr.jar",
         "%SEQUOIA_HOME%\\Java\\classes\\sequoia.jar",
         "%SWING_HOME%\\windows.jar",
         "%SWING_HOME%\\swing.jar",
         "%SWING_HOME%\\motif.jar",
         "%SWING_HOME%\\jlf.jar"};
    char *pathData[] = {"%SEQUOIA_HOME%\\Java\\bin", "%JAVA_HOME%\\bin"};
    int flen, plen;
    char path[250];
    HKEY hCreatedKey;
    LONG lngRegError = ERROR_SUCCESS ;
    LPTSTR cmdLine, pFileName;
    LPCTSTR envKey = "Environment";
    LPCTSTR sequoiaKey = "SEQUOIA_HOME";
    LPCTSTR classpathKey = "CLASSPATH";
    LPCTSTR pathKey = "PATH";
    OSVERSIONINFO osver ;

    /* Get platform */
    osver.dwOSVersionInfoSize = sizeof (osver);
    GetVersionEx(&osver);

    /* we only know how to do windows NT */    
    if (osver.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        return 0;
    }

    /* get our name */
    cmdLine = argv[0];
    
    /* Get the full path */
    GetFullPathName ((LPCTSTR)cmdLine, sizeof (path), (LPTSTR)path,
        &pFileName);
    plen = strlen(path);
    flen = strlen(pFileName);
    
    /* cut off the filename and bin dir */
    path[plen - flen - sizeof (BIN_DIR)] = 0;
    
    if (RegOpenKey(HKEY_CURRENT_USER, envKey, &hCreatedKey) ==
        ERROR_FILE_NOT_FOUND)
    {
        /* we are the first to set a variable */
        RegCreateKey(HKEY_CURRENT_USER, envKey, &hCreatedKey);
    }
    
    /* set SEQUOIA_HOME value under the ENVIRONMENT key.
       Created if doesnt exist */
    RegSetValueEx(hCreatedKey, sequoiaKey, 0, REG_SZ, path,
                  strlen(path)+1);
    
    AppendDirsToEnvVar(hCreatedKey, classpathKey, classpathData,
                       CLASSPATH_VARS);
    AppendDirsToEnvVar(hCreatedKey, pathKey, pathData, PATH_VARS);
   
    return 0 ;
}

static void AppendDirsToEnvVar(HKEY hCreatedKey, const char* pKey,
                               char* paDirs[], int dirCount) 
{
    int i;
    char varEntry[2048];
    DWORD dwType;    
    DWORD cbValue;
    char tmpVar[2048];
    char* pToken;
    int dirLen;
    int updateNeeded;

    /* zero terminate the entry in case we it does not exist */
    varEntry[0] = 0;
   
    cbValue = sizeof (&varEntry);
    RegQueryValueEx(hCreatedKey, pKey, NULL, &dwType,
       (LPBYTE) &varEntry, &cbValue);

    /* we do not want duplicates */
    strcpy(tmpVar, varEntry);
    updateNeeded = FALSE;
    for (i = 0; i < dirCount; i++)
    {
        pToken = strstr(tmpVar, paDirs[i]);
        if (pToken != NULL)
        {
            /* the token may be subdirectory of paDir[i] */
            dirLen = strlen(paDirs[i]);
            if (pToken[dirLen] == 0 || pToken[dirLen] == ';')
                continue;
        }
        
        strcat(varEntry, ";" ) ;
        strcat(varEntry, paDirs[i]);
        updateNeeded = TRUE;
    }  

    if (updateNeeded) {
        /* Set the modified variable back */
        RegSetValueEx(hCreatedKey, pKey, 0, REG_SZ, varEntry,
            strlen(varEntry)+1);
    }
}    
