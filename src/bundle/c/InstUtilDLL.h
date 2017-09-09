
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the GENSYM_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// GENSYM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GENSYM_EXPORTS
#define GENSYM_API __declspec(dllexport)
#else
#define GENSYM_API __declspec(dllimport)
#endif

//89+

#include "codes.h"

// This class is exported from the Gensym.dll
class GENSYM_API CGensym {
public:
	CGensym(void);
	// TODO: add your methods here.
};



/* This file contains the definitions needed for processing license keys.
 */

extern "C" __declspec(dllexport)  int initialize_license_key (char*);
extern "C" __declspec(dllexport)  int Test_key (char*);

extern "C" __declspec(dllexport)  int get_installer_version();
extern "C" __declspec(dllexport)  int get_familyid();
extern "C" __declspec(dllexport)  int get_bundleid();
extern "C" __declspec(dllexport)  int get_systemid();

extern "C" __declspec(dllexport)  int get_first_component_index();
extern "C" __declspec(dllexport)  int get_next_component_index();

extern "C" __declspec(dllexport) void test_key_interface(char* key);
extern "C" __declspec(dllexport) void test_key_interface2();


#include "key-common.h"


