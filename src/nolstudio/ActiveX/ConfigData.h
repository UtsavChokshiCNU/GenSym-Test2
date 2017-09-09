// ConfigData.h: interface for the CConfigData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGDATA_H__22344E19_8FD6_49D2_8AC4_E3FE8919EFF5__INCLUDED_)
#define AFX_CONFIGDATA_H__22344E19_8FD6_49D2_8AC4_E3FE8919EFF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<string>
#include<iostream>
#include <fstream>
#include<vector>

using namespace std;
class CConfigData  
{
	//all private variables
private:

	//stores pathname of ini file to read/write
	string m_strPath;

	//all keys are of this time
	struct key
	{
		//list of values in key
		vector<string>values;

		//corresponding list of value names
		vector<string> names;
	};

	//list of keys in ini
	vector<key> keys;

	//corresponding list of keynames
	vector<string> names;

	//all private functions
	private:
		//overloaded to take CString
		istream & getline( istream & is, string & str );

		//returns index of specified value, in the specified key, or -1 if not found
		int FindValue(int keynum, string valuename);

		//returns index of specified key, or -1 if not found
		int FindKey(string keyname);

		//public variables
	public:

		//will contain error info if one occurs
		//ended up not using much, just in ReadFile and GetValue
		string error;


		//public functions
	public:
		//default constructor
		CConfigData();

		//constructor, can specify pathname here instead of using SetPath later
		CConfigData(string inipath);

		//default destructor
		virtual ~CConfigData();

		//sets path of ini file to read and write from
		void SetPath(string newpath);

		//reads ini file specified using CIniFile::SetPath()
		//returns true if successful, false otherwise
		bool ReadFile();

		//writes data stored in class to ini file
		void WriteFile();

		//deletes all stored ini data
		void Reset();

		//returns number of keys currently in the ini
		int GetNumKeys();

		//returns number of values stored for specified key
		int GetNumValues(string keyname);

		//gets value of [keyname] valuename =
		//overloaded to return CString, int, and double,
		//returns "", or 0 if key/value not found.  Sets error member to show problem
		bool GetValue(string strKeyName, string strValueName, string &strValue);
		bool GetValue(string strKeyName, string strValueName, int &iValue);
		bool GetValue(string strKeyName, string strValueName, double &dValue);
		//sets value of [keyname] valuename =.
		//specify the optional paramter as false (0) if you do not want it to create
		//the key if it doesn't exist. Returns true if data entered, false otherwise
		//overloaded to accept CString, int, and double
		bool SetValue(string strKeyname, string strValueName, string strValue, bool bCreate = 1);
		bool SetValue(string strKeyname, string strValueName, int iValue, bool bCreate = 1);
		bool SetValue(string strKeyname, string strValueName, double dValue, bool bCreate = 1);

		//deletes specified value
		//returns true if value existed and deleted, false otherwise
		bool DeleteValue(string strKeyName, string strValueName);

		//deletes specified key and all values contained within
		//returns true if key existed and deleted, false otherwise
		bool DeleteKey(string strKeyname);

};

#endif // !defined(AFX_CONFIGDATA_H__22344E19_8FD6_49D2_8AC4_E3FE8919EFF5__INCLUDED_)
