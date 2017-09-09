/* Windows-specific code for DLL interoperability in KB language
 * Subsystem: EXT.Subsystems.Interop
 * Tags:
 * Used In:
 *   - Loading DLLs and accessing DLL functions from KB code
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */
#include "common_config.h"

#ifndef Platform_Windows
#error You are trying to compile a windows-specific source in a non-Windows environment
#else // ONLY windows-specific code in this file

#include <windows.h>
#include "g2ss/Interop/dllLink.h"
#include <map>
#include <string>
#include <vector>



class LibraryManager {
public: //types
	typedef std::map<std::wstring, int> NameIdMap;
	typedef std::pair<HMODULE, std::wstring> LibDescr;

private: // variables

	// holds the name to library id mapping
	NameIdMap _name2libId;

	// Singleton instance
	static LibraryManager *_instance;

	/// holds a list of loaded libraries
	std::vector<LibDescr> _loaded;

protected: // functions
	// load a library by name.
	int Load(const std::wstring& path);

public: // functions
	
	// Singleton 
	static LibraryManager* Instance();

	// constructor
	LibraryManager();

	// get id of a loaded library for a given name
	int GetIdForName(const std::wstring& name);
};

LibraryManager* LibraryManager::_instance = 0;

// the singleton method
LibraryManager* LibraryManager::Instance() {
	if( _instance == 0 ) {
		//TODO: synchronize
		_instance = new LibraryManager();
	}
	return _instance;
}

// constructor.
LibraryManager::LibraryManager() {
	// adds a fake entry to the loaded library list
	_loaded.push_back( LibDescr((HMODULE)0, L"Fake entry") );
}


int LibraryManager::Load(const std::wstring& path) {
	
	/// load a library
	HMODULE hModule = LoadLibraryW( path.c_str() );
	
	if( !hModule ) {
	// return false if the library loading was not successful
		return 0;
	}
	
	//TODO: synchronize
	int ans = (int)_loaded.size();

	// add the library description in the loaded library description list
	_loaded.push_back( LibDescr(hModule, path) );

	// the index of last added library in  the list
	return ans;
}


int LibraryManager::GetIdForName(const std::wstring& name) {
	
	// search for the library and return the index.
	NameIdMap::iterator it = _name2libId.find(name);
	if( it != _name2libId.end() ) {
		return it->second;
	}

	// if library was not found earlier
	// load it
	int ans = Load(name);

	// add this library to the loaded library list
	if( ans != 0 ) {
		_name2libId.insert( NameIdMap::value_type(name, ans) );
	} else {
		//REPERR: library not loaded
	}
	return ans;
}

//// Experimental-only function. KB coder should be relieved from managing the DLL
// handles, and rather just specify the library path for an imported function
// like in .NET
int XANALYS_API g2ext_load_dynamic_library(wchar_t* path) {
	int ans = LibraryManager::Instance()->GetIdForName( path );
	return ans;
}

#endif /* Platform_Windows */
