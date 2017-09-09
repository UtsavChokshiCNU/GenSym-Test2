#include "g2string.h"
#include <string.h>
#include <ctype.h>


// String routines

const G2String& G2String::operator=(const G2String& RHS) // Assignment

{
	if (str) delete str;  // free up old memory
	str = new char[strlen(RHS.str)+1];
	strcpy(str, RHS.str);
	return *this;
}
const G2String& G2String::operator=(const char *RHS) 

{
	if (str) delete str;
	str = new char[strlen(RHS)+1];
	strcpy(str, RHS);
	return *this;
}

void G2String::toupper(void) {

	char *ptr;

	for (ptr = str; *ptr; ptr++) {
		if (islower(*ptr)) *ptr = *ptr - 'a' + 'A';
	}
}

G2String::G2String(const char *ptr)

{
	str = new char[strlen(ptr)+1];
	strcpy(str,ptr);
}

G2String::G2String(const G2String& RHS)

{
	str = new char[strlen(RHS.str)+1];
	strcpy(str, RHS.str);
}
	

		  
//
// These are routines that work binary sequences
//

const G2OctSeq& G2OctSeq::operator=(const G2OctSeq& RHS) // Assignment

{
	if (buf) delete (char *)buf;  // free up old memory
	buf_len = RHS.buf_len;
	buf = new char[buf_len];
	memcpy(buf,RHS.buf,buf_len);
	return *this;
}

G2OctSeq::~G2OctSeq() {
	if (buf) delete (char *)buf;
}

void G2OctSeq::set_buf(void *ptr, int len) {
	if (buf) delete (char *)buf;
	buf = new unsigned char[len];
	memcpy(buf, ptr, len);
	buf_len = len;
}

G2OctSeq::G2OctSeq() {
	buf_len = 0;
	buf = NULL;
}



