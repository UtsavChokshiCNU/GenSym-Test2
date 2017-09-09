#if defined (WIN32)

#define COBJMACROS
#include <activeds.h>

#define BUFSIZE 1024
#define MAXUSERMODES 1024

const LPWSTR TRUE_STRING = L"TRUE";
const LPWSTR FALSE_STRING = L"TRUE";

LPWSTR szPathName = NULL; // L"LDAP://DC=softservecom,DC=com";
LPWSTR szG2check = L"is-g2-application-user";
LPWSTR szLogin = L"sAMAccountName";
LPWSTR szMode = L"g2-user-mode";
LPWSTR szModes = L"g2-user-modes";
LPWSTR szExpireTime = L"g2-user-expire";
LPWSTR szDomain = NULL;
LPWSTR szAttributes = NULL;
LPWSTR szHardModesValue = NULL;

long isG2User=0;
char userLogin[BUFSIZE];
char userPassword[BUFSIZE];
char userMode[BUFSIZE];
char userModes[BUFSIZE];
char userModesUpperCase[BUFSIZE];

const LPWSTR SEPARATORLIST_W = L" ,;";
const char* SEPARATORLIST = ",;";

const char SPACE = ' ';

long numUserModes=0;
char* userModesList[MAXUSERMODES];

UINT g2use_ldap = 0;

long get_column(IDirectorySearch* pDirectorySearch, HANDLE hSearch, LPWSTR pszAttr, LPWSTR pszResult)
{
	LPWSTR szValue = pszResult;
	ULONG cCharacters=0;

	HRESULT hr;
	ADS_SEARCH_COLUMN col;
	hr = IDirectorySearch_GetColumn(pDirectorySearch, hSearch, pszAttr, &col );
	if ( SUCCEEDED(hr) )
	{
		  switch (col.dwADsType)
		  {
			 case ADSTYPE_UTC_TIME:
				 {
					SYSTEMTIME t,st;
					GetSystemTime(&st);
					t = col.pADsValues->UTCTime;

					if( t.wYear==0 ||
						t.wYear > st.wYear ||
						t.wMonth > st.wMonth ||
						t.wDay > st.wDay ||
						t.wHour > st.wHour ||
						t.wMinute > st.wMinute ||
						t.wSecond > st.wSecond ||
						t.wMilliseconds > st.wMilliseconds)
						lstrcpyW(szValue,TRUE_STRING);
					else
						lstrcpyW(szValue,FALSE_STRING);
				 }
			 break;

			 case ADSTYPE_DN_STRING:
				lstrcpyW(szValue,col.pADsValues->DNString);
			 break;
			 
			 case ADSTYPE_CASE_EXACT_STRING:
				lstrcpyW(szValue,col.pADsValues->CaseExactString);
			 break;
			 
			 case ADSTYPE_CASE_IGNORE_STRING:
				lstrcpyW(szValue,col.pADsValues->CaseIgnoreString);
			 break;
			 
			 case ADSTYPE_PRINTABLE_STRING:
				lstrcpyW(szValue,col.pADsValues->PrintableString);
			 break;
			 
			 case ADSTYPE_NUMERIC_STRING:
				lstrcpyW(szValue,col.pADsValues->NumericString);
			 break;

			 case ADSTYPE_PROV_SPECIFIC:
				cCharacters =  lstrlen(col.pADsValues->ProviderSpecific.lpValue)+1;
				MultiByteToWideChar(CP_ACP, 0, col.pADsValues->ProviderSpecific.lpValue, cCharacters, szValue, cCharacters);
			 break;
				
			 case ADSTYPE_BOOLEAN:
				if(col.pADsValues->Boolean)
					lstrcpyW(szValue,TRUE_STRING);
				else
					lstrcpyW(szValue,FALSE_STRING);
			 break;

			 default:
				return 0; //Unexpected ADsType
			 break;
		  }
		  IDirectorySearch_FreeColumn(pDirectorySearch, &col );

		  return 1;
	}
	return 0;
}

LPWSTR get_env_var(LPTSTR szName)
{
	LPTSTR env=NULL;
	LPWSTR szEnv=NULL;
	ULONG cCharacters=0;
	DWORD dwRet;

	if(szName)
	{
		env = (LPTSTR) malloc(BUFSIZE*sizeof(TCHAR));
		dwRet = GetEnvironmentVariable(szName, env, BUFSIZE);
		if(dwRet != 0)
		{
			cCharacters =  strlen(env)+1;
			szEnv = (LPWSTR) HeapAlloc(GetProcessHeap(), 0, cCharacters * sizeof(wchar_t)); 
			MultiByteToWideChar(CP_ACP, 0, env, cCharacters, szEnv, cCharacters);
		}
	}

	return szEnv;
}

#define NUM_ATTRS 5

void init_options_from_env()
{
	if(!szPathName)
	{
		szPathName = get_env_var("G2_LDAP");
	}

	if(!szDomain)
	{
		szDomain = get_env_var("G2_LDAP_DOMAIN");
	}

	if(!szAttributes)
	{
		LPWSTR pch;
		int numAttributes = NUM_ATTRS;
		LPWSTR* szAttr[NUM_ATTRS];
		long index=0;

		szAttributes = get_env_var("G2_LDAP_USER_ATTRIBUTES");

		szAttr[0]=&szG2check;
		szAttr[1]=&szMode;
		szAttr[2]=&szModes;
		szAttr[3]=&szExpireTime;
		szAttr[4]=&szLogin;
#if defined(_MSC_VER) && _MSC_VER >= 1900
		pch = wcstok (szAttributes,SEPARATORLIST_W, 0);
#else
		pch = wcstok (szAttributes, SEPARATORLIST_W);
#endif
		while (pch != NULL && index<NUM_ATTRS)
		{
			*szAttr[index] = pch;
			index++;
#if defined(_MSC_VER) && _MSC_VER >= 1900
			pch = wcstok (NULL, SEPARATORLIST_W, 0);
#else
			pch = wcstok (NULL, SEPARATORLIST_W);
#endif
		}
	}

	if(!szHardModesValue)
	{
		szHardModesValue = get_env_var("G2_LDAP_MODES");
	}
}

void strtoupper(char* str)
{
	int i;
	if(str)
		for(i = 0; str[i]; i++)
		{
			str[i] = toupper(str[i]);
		}
}

void check_user_and_load_info(char *defaultLogin, char *login, char *password)
{
	ULONG cCharacters=0;

	WCHAR szUserLoginShort[BUFSIZE];

	isG2User=0;
	userLogin[0]=0;
	userPassword[0]=0;
	userMode[0]=0;
	userModes[0]=0;

	userModesUpperCase[0]=0;
	numUserModes=0;

	if(defaultLogin || login && password)
	{
		HRESULT hr;
		IADsContainer *pCont=NULL;
		IDirectorySearch* pDirectorySearch=NULL;

		WCHAR szUsername[BUFSIZE];
		WCHAR szPassword[BUFSIZE];

		DWORD  dwReserved=ADS_SECURE_AUTHENTICATION;

		char* res;
		char userLoginShort[BUFSIZE];
		char buffer[BUFSIZE];

		//
		//  Get Active Directory access option from environment
		//
		init_options_from_env();

		if(!login) login = defaultLogin;
		
		//
		// Copy supplied login and password, check for correctness and fix if needed
		//
		strcpy(userLogin,login);
		strtoupper(userLogin);
		if(password) strcpy(userPassword,password);

		res = strstr(userLogin,"~");
		if(res)
		{
			long length = strlen(res);
			strncpy(buffer,res+1,length);
			strncpy(res,buffer,length);
		}

		res = strstr(userLogin,"/");
		if(res)
		{
			*res='\\';
		}

		res = strstr(userLogin,"\\");
		if(!res)
		{
			res = userLogin;
		}
		else
		{
			res++;
		}

		strcpy(userLoginShort,res);
		strtoupper(userLoginShort);
		if(strcmp(userLoginShort,defaultLogin)==0) password=NULL;

		cCharacters =  strlen(userLoginShort)+1;
		MultiByteToWideChar(CP_ACP, 0, userLoginShort, cCharacters, szUserLoginShort, cCharacters);

		// 
		// Prepare to call AD LDAP check
		//
		{
			LPWSTR szADsUsername=NULL;
			LPWSTR szADsPassword=NULL;

			//
			// If password provided
			//
			if(password)
			{
				//
				//  Use default domain if no one specified in login
				//
				if(strstr(userLogin,"\\") || !szDomain)
					strcpy(buffer, userLogin);
				else
					wsprintf(buffer,"%S\\%S",szDomain,szUserLoginShort);

				cCharacters =  strlen(buffer)+1;
				if(cCharacters>BUFSIZE) cCharacters = BUFSIZE;
				MultiByteToWideChar(CP_ACP, 0, buffer, cCharacters, szUsername, cCharacters);

				cCharacters =  strlen(password)+1;
				if(cCharacters>BUFSIZE) cCharacters = BUFSIZE;
				MultiByteToWideChar(CP_ACP, 0, userPassword, cCharacters, szPassword, cCharacters);
				
				szADsUsername = szUsername;
				szADsPassword = szPassword;
				dwReserved=0;
			}

			// Initialize COM before calling any ADSI functions or interfaces.
			CoInitialize(NULL);

			hr = ADsOpenObject(szPathName,szADsUsername,szADsPassword,dwReserved,&IID_IADsContainer,(void**) &pCont);
		}

		if ( SUCCEEDED(hr) )
		{
			//
			// Search the directory for required attributes
			//

			hr = IADsContainer_QueryInterface(pCont, &IID_IDirectorySearch ,(void**)&pDirectorySearch);

			if ( SUCCEEDED(hr) )
			{
				WCHAR szSearchString[BUFSIZE];
				PWCHAR pszAttr[NUM_ATTRS];

				DWORD dwCount=0;

				HANDLE hSearch=NULL;

				szSearchString[0]=0;
				
				pszAttr[dwCount] = szG2check;dwCount++;
				pszAttr[dwCount] = szMode;dwCount++;
				pszAttr[dwCount] = szModes;dwCount++;
				pszAttr[dwCount] = szExpireTime;dwCount++;
				pszAttr[dwCount] = NULL;

				wsprintf(buffer,"(%S=%S)",szLogin,szUserLoginShort);
				cCharacters = strlen(buffer)+1;
				MultiByteToWideChar(CP_ACP, 0, buffer, cCharacters, szSearchString, cCharacters);

				hr = IDirectorySearch_ExecuteSearch(pDirectorySearch,szSearchString,pszAttr,dwCount,&hSearch);

				if(SUCCEEDED(hr))
				{
					while(SUCCEEDED(hr = IDirectorySearch_GetNextRow(pDirectorySearch,hSearch)))
					{
						if(S_OK == hr)
						{
							WCHAR szValue[BUFSIZE];
							char* pch;
							int i;

							//
							//  Get g2 user attribute
							//
							if(get_column(pDirectorySearch, hSearch, pszAttr[0], szValue))
							{
								isG2User = (wcscmp(szValue,TRUE_STRING)==0);
							}

							//
							//  Get default user mode attribute
							//
							if(get_column(pDirectorySearch, hSearch, pszAttr[1], szValue))
							{
								cCharacters = wcslen(szValue)+1;
								WideCharToMultiByte( CP_ACP, 0, szValue, -1, userMode, cCharacters, NULL, NULL );
							}

							//
							//  Get user modes attribute
							//
							if(get_column(pDirectorySearch, hSearch, pszAttr[2], szValue))
							{
								cCharacters = wcslen(szValue)+1;
								WideCharToMultiByte( CP_ACP, 0, szValue, -1, userModes, cCharacters, NULL, NULL );

								if(szHardModesValue)
								{
									cCharacters = wcslen(szHardModesValue)+1;
									WideCharToMultiByte( CP_ACP, 0, szHardModesValue, -1, userModes, cCharacters, NULL, NULL );
								}

								for( i = 0; userModes[i]; i++)
								{
									if(userModes[i]==',') userModes[i]=';';

									//
									// Replace all bad chars
									//
									if(!isalpha(userModes[i]) && userModes[i]!=SPACE 
										&& userModes[i]!=',' && userModes[i]!=';')
										userModes[i]='-';
								}

								//
								//  Split user modes string into separate modes array
								//
								strcpy(userModesUpperCase, userModes);
								strtoupper(userModesUpperCase);
								pch = strtok (userModesUpperCase,SEPARATORLIST);
								while (pch != NULL)
								{
									char* endof;

									// 
									// Trim spaces from beginning and end of each mode
									//
									while(*pch==SPACE) pch++;
									endof = strrchr (pch, SPACE);
									while(endof && endof!=pch && *endof==SPACE) 
									{
										*endof=0;
										endof--;
									}

									if(numUserModes<MAXUSERMODES)
									{
										userModesList[numUserModes]=pch;
										numUserModes++;
									}
									pch = strtok (NULL, SEPARATORLIST);
								}
							}

							//
							//  Get user expire attribute
							//
							if(get_column(pDirectorySearch, hSearch, pszAttr[3], szValue))
							{
								if (wcscmp(szValue,FALSE_STRING)==0)
									isG2User=FALSE;
							}
						}
						else if(S_ADS_NOMORE_ROWS == hr)
						{
							// Call ADsGetLastError to see if the search is waiting for a response.
							DWORD dwError = ERROR_SUCCESS;
							WCHAR szError[BUFSIZE];
							WCHAR szProvider[BUFSIZE];

							ADsGetLastError(&dwError, szError, BUFSIZE, szProvider, BUFSIZE);
							if(ERROR_MORE_DATA != dwError)
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
					
					hr = IDirectorySearch_CloseSearchHandle(pDirectorySearch,hSearch);
				}
			}
		}
		CoUninitialize();
	}
}

#endif

long g2_check_authentification_ldap(char *login, char *mode)
{
#if defined (WIN32)
	if(isG2User)
	{
		isG2User = 0;
		if(login && strcmp(login, userLogin)==0 && mode)
		{
			int i;
			char modeToTest[BUFSIZE];

			strcpy(modeToTest, mode);
			strtoupper(modeToTest);

			for(i=0; i<numUserModes; i++)
			{
				if(strcmp(userModesList[i],modeToTest)==0) return 0;
			}
		}
		return 2;
	}
	return 1;
#else
	return 0;
#endif
}

long g2_check_user_ldap(char *defaultLogin, char *login, char *password)
{
#if defined (WIN32)
	check_user_and_load_info(defaultLogin, login, password);

	if(isG2User)
	{
		return 0;
	}
	return 1;
#else
	return 0;
#endif
}

long g2_check_ldap_mode()
{
#if defined (WIN32)
	return g2use_ldap;
#else
	return 0;
#endif	
}
