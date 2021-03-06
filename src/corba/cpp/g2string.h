#ifndef G2STRING_H
#define G2STRING_H
#include <stdio.h>

// String object for a container
class G2String {
public:
	char *str;

	const G2String& operator=(const G2String&); 
	const G2String& operator=(const char *);
	operator char*() {return str;};
	void toupper(void);
	G2String(const char *);
	G2String() {str = NULL;};
	G2String(const G2String&); // copy constructor
	virtual ~G2String() {if (str) delete str;};
};

//Octet sequence class
class G2OctSeq {
public:
	void *buf;
	int buf_len;

	const G2OctSeq& operator=(const G2OctSeq&);
	void set_buf(void *, int);
	virtual ~G2OctSeq();
	G2OctSeq();
};

#endif

