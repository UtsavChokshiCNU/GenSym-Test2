// socks2http.h : main header file for the s2h library
#ifndef __S2HLIB__
#define __S2HLIB__

typedef void (STATUSCB)(const char *name, const char* value, const char* msg);

 __declspec( dllexport )   const char* __stdcall getAllConfigOptions();
 __declspec( dllexport )   const char* __stdcall getConfigOption(const char* option);
 __declspec( dllexport )   void        __stdcall setConfigOption(const char* name, const char* value);
 __declspec( dllexport )   const char* __stdcall getSystemOption(const char* option);
 __declspec( dllexport )   void        __stdcall setSystemOption(const char* name, const char* value);
 __declspec( dllexport )   void        __stdcall setOptionType  (const char* name, const char* type);
 __declspec( dllexport )   int         __stdcall startS2H();
 __declspec( dllexport )   int         __stdcall stopS2H ();
 __declspec( dllexport )   int         __stdcall startPM (unsigned short port, const char* protocol);
 __declspec( dllexport )   int         __stdcall stopPM  (unsigned short port, const char* protocol);
 __declspec( dllexport )   int         __stdcall isRunning();
 __declspec( dllexport )   int         __stdcall loadConfigFromIniFile(const char * filename);
 __declspec( dllexport )   int         __stdcall saveConfigToIniFile(const char * filename);
 __declspec( dllexport )   void        __stdcall registerStatusCB(STATUSCB* pcb);
 __declspec( dllexport )   const char* __stdcall getStatusString();
 __declspec( dllexport )   int         __stdcall locateGateway();
 __declspec( dllexport )   const char* __stdcall getGatewayMessage();
 __declspec( dllexport )   const char* __stdcall getCurrentClientVersion();
 __declspec( dllexport )   void        __stdcall setProxyAuthentication(const char* user, const char* password, const char* domain);

 

#endif 

