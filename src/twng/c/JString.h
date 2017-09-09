#pragma once

class JString
{
public:
	JString(const char* str);
	JString(const JString& jStr);

	explicit JString(long l);
	explicit JString(double d);
	explicit JString(const CString& str);
	explicit JString(LPWSTR lpstr);
	
	~JString();
	operator const char*() const;

private:
	void Convert(const CString&);
	void CopyStr(const char* str);

	char* m_pStr;
};
