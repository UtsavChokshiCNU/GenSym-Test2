/* $Revision: 10383 $ $Date: 2009-09-11 18:08:19 -0700 (Fri, 11 Sep 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * Implementations of open, close, read, write, lseek using functionality in <stdio.h>
 */

#include <stdio.h>
#define O_CREAT 0x0100
#define O_RDONLY 0
#define O_RDWR 2
#define O_WRONLY 1
#define S_IRUSR 0x0100
#define S_IWUSR 0x0080

int open(const char* path, int oflag, int mode)
{
	int fd = -1;
	const char* m = "rb";
	FILE* file;
	if ((mode & O_RDONLY) == 0) {
		m = "r+b";
	}
	file = fopen(path, m);
	if (file == NULL && (mode & O_CREAT) != 0) {
		file = fopen(path, "w+b");
	}
	if (file != NULL) {
		fd = (int)file;
	}
	return fd;
}

int close(int fildes)
{
	return fclose((FILE*)fildes);
}

int read(int fildes, void* buf, unsigned nbyte)
{
	int n = (int)fread(buf, 1, nbyte, (FILE*)fildes);
	if (n == 0 && nbyte != 0) {
		n = -1;
	}
	return n;
}

int write(int fildes, const void* buf, unsigned nbyte)
{
	int n;
	if (fildes == 2) {
		fildes = (int)stderr;
	}
	n = (int)fwrite(buf, 1, nbyte, (FILE*)fildes);
	if (n == 0 && nbyte != 0) {
		n = -1;
	}
	return n;
}

off_t lseek(int fildes, off_t offset, int whence)
{
	off_t off = -1;
	if (fseek((FILE*)fildes, offset, whence) == 0) {
		off = ftell((FILE*)fildes);
	}
	return off;
}
