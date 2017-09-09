/* $Revision: 9758 $ $Date: 2009-02-11 11:49:41 -0800 (Wed, 11 Feb 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 */

#include "cmn-getenvBuf.h"

/* Environment variables are read from a plain text file, which has the form:
//   name1=value1
//   name2=value2
//   ...
*/
static char* getenvFile(const char* name, const char* path)
{
	/* Buffer containing return value */
	static char buf[512];
	/* Length of data read into buf */
	static unsigned n;
	static int isOnce;
	if (!isOnce) {
		/* File descriptor */
		const int fd = open(path, O_RDONLY, 0);
		/* Read whole file into buf */
		if (fd != -1) {
			const int nbyte = (int)read(fd, buf, sizeof(buf) - 1);
			if (nbyte > 0) {
				n = (unsigned)nbyte;
			}
			close(fd);
		}
	}
	return getenvBuf(name, buf, n);
}
