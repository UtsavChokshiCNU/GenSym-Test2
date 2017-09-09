// ConfigData.cpp: implementation of the CConfigData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConfigData.h"

CConfigData::CConfigData()
{

}

//constructor, can specify pathname here instead of using SetPath later
CConfigData::CConfigData(string inipath)
{
	m_strPath = inipath;
}

//default destructor
CConfigData::~CConfigData()
{

}

/////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////

//sets path of ini file to read and write from
void CConfigData::SetPath(string newpath)
{
	m_strPath = newpath;
}

//reads ini file specified using CConfigData::SetPath()
//returns true if successful, false otherwise
bool CConfigData::ReadFile()
{
	ifstream inifile;
	string readinfo;

	inifile.open(m_strPath.c_str(), ifstream::out/*|fstream::in*/|ifstream::app);
	int curkey = -1, curval = -1;
	if (inifile.fail())
	{
		error = "Unable to open ini file.";
		return false;
	}
	string keyname, valuename, value;
	string temp;
	while (getline(inifile,readinfo))
	{
		if (readinfo != "")
		{
			if (readinfo[0] == '[' && readinfo[readinfo.size()-1] == ']') //if a section heading
			{
				keyname = readinfo;
				string::iterator iterKeyName;
				iterKeyName = keyname.begin();

				keyname.erase(iterKeyName);

				//iterKeyName = keyname.end();
				keyname.erase(iterKeyName + keyname.size() -1 );

			}
			else //if a value
			{
				string::size_type pos = -1;
				pos = readinfo.find("=", 0);
				if (pos <0)
				{
					return false;
				}

				char bufValueName[8000];
				char bufValue[8000];
				memset(bufValueName,0, 8000);
				memset(bufValue, 0, 8000);

				readinfo.copy(bufValueName, pos, 0);
				valuename = bufValueName;

				readinfo.copy(bufValue, readinfo.size() - valuename.size() - 1, pos + 1);
				value = bufValue;

				SetValue(keyname,valuename,value);
			}
		}
	}
	inifile.close();
	return true;
}

//writes data stored in class to ini file
void CConfigData::WriteFile()
{
	ofstream inifile;
	inifile.open(m_strPath.data());
	for (int keynum = 0; keynum <= names.size() - 1; keynum++)
	{
		if (keys[keynum].names.size() != 0)
		{
			inifile << '[' << names[keynum] << ']' << endl;
			for (int valuenum = 0; valuenum <= keys[keynum].names.size() - 1; valuenum++)
			{
				inifile << keys[keynum].names[valuenum] << "=" << keys[keynum].values[valuenum];
				if (valuenum != keys[keynum].names.size() - 1)
					inifile << endl;
				else
					if (keynum < names.size())
						inifile << endl;
			}
			if (keynum < names.size())
				inifile << endl;
		}
	}
	inifile.close();
}

//deletes all stored ini data
void CConfigData::Reset()
{
	keys.resize(0);
	names.resize(0);
}

//returns number of keys currently in the ini
int CConfigData::GetNumKeys()
{
	return keys.size();
}

//returns number of values stored for specified key, or -1 if key found
int CConfigData::GetNumValues(string keyname)
{
	int keynum = FindKey(keyname);
	if (keynum == -1)
		return -1;
	else
		return keys[keynum].names.size();
}


bool CConfigData::GetValue(string strKeyName, string strValueName, string &strValue)
{
	int keynum = FindKey(strKeyName), valuenum = FindValue(keynum,strValueName);

	if (keynum == -1)
	{
		error = "Unable to locate specified key.";
		strValue = "";
		return false;
	}

	if (valuenum == -1)
	{
		error = "Unable to locate specified value.";
		strValue = "";
		return false;
	}

	strValue = keys[keynum].values[valuenum];
	return true;
}



//gets value of [keyname] valuename =
//overloaded to return string, int, and double
bool CConfigData::GetValue(string strKeyName, string strValueName, int &iValue)
{
	string strValue;
	if (GetValue(strKeyName,strValueName, strValue))
	{
		iValue = atoi(strValue.c_str());
		return true;
	}

	iValue = 0;
	return false;
}

//gets value of [keyname] valuename =
//overloaded to return string, int, and double
bool CConfigData::GetValue(string strKeyName, string strValueName, double &dValue)
{
	string strValue;
	if (GetValue(strKeyName,strValueName, strValue))
	{
		dValue = atof(strValue.c_str());
		return true;
	}

	dValue = 0.00;
	return false;
}


//sets value of [keyname] valuename =.
//specify the optional paramter as false (0) if you do not want it to create
//the key if it doesn't exist. Returns true if data entered, false otherwise
//overloaded to accept string, int, and double
bool CConfigData::SetValue(string strKeyname, string strValueName, string strValue, bool bCreate)
{
	int keynum = FindKey(strKeyname), valuenum = 0;
	//find key
	if (keynum == -1) //if key doesn't exist
	{
		if (!bCreate) //and user does not want to create it,
			return false; //stop entering this key
		names.resize(names.size()+1);
		keys.resize(keys.size()+1);
		keynum = names.size()-1;
		names[keynum] = strKeyname;
	}

	//find value
	valuenum = FindValue(keynum,strValueName);
	if (valuenum == -1)
	{
		if (!bCreate)
			return false;
		keys[keynum].names.resize(keys[keynum].names.size()+1);
		keys[keynum].values.resize(keys[keynum].names.size()+1);
		valuenum = keys[keynum].names.size()-1;
		keys[keynum].names[valuenum] = strValueName;
	}
	keys[keynum].values[valuenum] = strValue;
	return true;
}

//sets value of [keyname] valuename =.
//specify the optional paramter as false (0) if you do not want it to create
//the key if it doesn't exist. Returns true if data entered, false otherwise
//overloaded to accept string, int, and double
bool CConfigData::SetValue(string strKeyname, string strValueName, int iValue, bool bCreate)
{
	char buf[24];
	memset(buf, 0, 24);
	sprintf(buf, "%d", iValue);
	string temp = buf;
	return SetValue(strKeyname, strValueName, temp, bCreate);
}

//sets value of [keyname] valuename =.
//specify the optional paramter as false (0) if you do not want it to create
//the key if it doesn't exist. Returns true if data entered, false otherwise
//overloaded to accept string, int, and double
bool CConfigData::SetValue(string strKeyname, string strValueName, double dValue, bool bCreate)
{
	char buf[64];
	memset(buf, 0, 64);
	sprintf(buf, "%e", dValue);
	string temp = buf;
	return SetValue(strKeyname, strValueName, temp, bCreate);
}

//deletes specified value
//returns true if value existed and deleted, false otherwise
bool CConfigData::DeleteValue(string strKeyName, string strValueName)
{
	int keynum = FindKey(strKeyName);
	int valuenum = FindValue(keynum,strValueName);
	if (keynum == -1 || valuenum == -1)
		return false;

	vector<string>::iterator iterNames;
	vector<string>::iterator iterValues;

	iterValues = keys[keynum].values.begin();
	iterNames = keys[keynum].names.begin();

	keys[keynum].names.erase(iterNames + valuenum);
	keys[keynum].values.erase(iterValues + valuenum);
	return true;
}

//deletes specified key and all values contained within
//returns true if key existed and deleted, false otherwise
bool CConfigData::DeleteKey(string strKeyname)
{
	int keynum = FindKey(strKeyname);
	if (keynum == -1)
		return false;
	vector<string>::iterator iterNames;
	vector<key>::iterator iterKeys;
	iterKeys = keys.begin();
	iterNames = names.begin();
	keys.erase(iterKeys + keynum);
	names.erase(iterNames + keynum);
	return true;
}

/////////////////////////////////////////////////////////////////////
// Private Functions
/////////////////////////////////////////////////////////////////////

//returns index of specified key, or -1 if not found
int CConfigData::FindKey(string strKeyName)
{
	int keynum = 0;
	while ( keynum < keys.size() && names[keynum] != strKeyName)
		keynum++;
	if (keynum == keys.size())
		return -1;
	return keynum;
}

//returns index of specified value, in the specified key, or -1 if not found
int CConfigData::FindValue(int keynum, string valuename)
{
	if (keynum == -1)
		return -1;
	int valuenum = 0;
	while (valuenum < keys[keynum].names.size() && keys[keynum].names[valuenum] != valuename)
		valuenum++;
	if (valuenum == keys[keynum].names.size())
		return -1;
	return valuenum;
}

//overloaded from original getline to take string
istream & CConfigData:: getline(istream & is, string & str)
{
    char buf[2048];
    is.getline(buf,2048);
    str = buf;
    return is;
}
