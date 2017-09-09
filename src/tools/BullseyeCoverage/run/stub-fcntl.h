/* $Revision: 9747 $ $Date: 2009-02-06 18:09:16 -0800 (Fri, 06 Feb 2009) $
 * Copyright (c) Bullseye Testing Technology
 */

#define flock Libcov_flock
struct flock {
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
};
#undef F_SETLKW
#undef F_RDLCK
#undef F_UNLCK
#undef F_WRLCK
#define F_SETLKW 0
#define F_RDLCK 0
#define F_UNLCK 1
#define F_WRLCK 2

#define fcntl Libcov_fcntl
static int fcntl(int fildes, int cmd, ...)
{
	fildes = fildes;
	cmd = cmd;
	errno = ENOSYS;
	return -1;
}
