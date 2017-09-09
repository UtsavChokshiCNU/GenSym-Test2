/***********************************************************************
 * $Revision: 10903 $ $Date: 2010-02-25 14:18:16 -0800 (Thu, 25 Feb 2010) $
 *
 * CONFIDENTIAL
 *    This source file contains copyrighted, proprietary information of
 *    Bullseye Testing Technology.
 *
 * Do not compile this file directly. It should be included into a platform-specific source file.
 */

#if _MSC_VER
	#pragma check_stack(off)
#endif

#if __MWERKS__
	#define _MSL_USE_DEFAULT_LIBS 0
#endif

/*lint -e1924 */

/* Do not include stdarg.h unless needed due to Sony Ericsson toolchain */
#if !defined(va_arg)
	#include <stdarg.h>
#endif

#include "version.h"

/*========== Constants ===============================================*/

const char cov_version[] = VERSION_number;

/* The product name and version */
static const char Title[] = VERSION_title;
/*lint -esym(528,Title)*/

/* The copyright string */
static const char Copyright[] = VERSION_copyright;
/*lint -esym(528,Copyright)*/

/* For the Unix command "what" */
static const char whatString[] = "@(#)" VERSION_title;
/*lint -esym(528,whatString) */

/* Information about a run-time error */
typedef struct {
	/* Error severity level, lower numbers are less severe
	 *   1: informational; continue business as usual
	 *   2: continue processing current coverage file
	 *   3: go to next coverage file
	 *   4: do not access instrumentation data or coverage file
	 */
	unsigned short level;
	/* User documentation error code */
	short number;
	/* Error message, like printf format */
	const char* message;
} Error;

/* Error descriptions */
static const Error error_none          = { 0,  0, NULL };
static const Error error_memoryCorrupt = { 4,  1,  "1: Memory corrupted %d" };
#if COVRT_PASSIVE
static const Error error_passiveWrite  = { 1, 19, NULL }; /* cov_write called from passive mode */
#else
static const Error error_wrongFile     = { 2,  2,  "2: Wrong coverage file. Use same coverage file for building and running. Path is %s (%x). Object %s (%x)" };
static const Error error_fcntl         = { 4,  3,  "3: File lock error on %s, errno=%d" };
static const Error error_objectMissing = { 2,  4,  "4: Object missing, possibly overwritten during build. Enable covc option --retain and rebuild. Path is %s (%x). Object %s (%x)" };
static const Error error_io            = { 4,  5,  "5: File i/o error on %s at %x, errno=%d" };
static const Error error_fileCorrupt   = { 3,  6,  "6: Corrupt file %s at %x" };
static const Error error_fileMismatch  = { 2,  7,  "7: Object mismatch. Check coverage data file is same one created when building. Or, try covc option --retain. Path is %s. Recompile object %s (%x)" };
static const Error error_atexit        = { 2,  8,  "8: atexit failed, errno=%d" };
static const Error error_threadCreate  = { 1, 13, NULL /* pthread_create failed */ };
static const Error error_openDefault   = { 3, 15, "15: Cannot open %s.  COVFILE is not set, errno=%d" };
static const Error error_open          = { 3, 16, "16: Cannot open %s.  COVFILE is probably set to an incorrect path, errno=%d" };
static const Error error_fileEmpty     = { 3, 17, "17: Coverage file %s is empty" };
static const Error error_fileInvalid   = { 3, 18, "18: Not a BullseyeCoverage file or wrong version: %s" };
static const Error error_noProbes      = { 1, 20, NULL /* No probes have been encountered */ };
static const Error error_noSave        = { 1, 21, NULL /* COVNOSAVE is set */ };
static const Error error_busy          = { 1, 22, NULL /* cov_write is busy */ };
#endif /* !COVRT_PASSIVE */

/* The current error status */
static const Error* error = &error_none;

/*----------------------------- Constant -------------------------------
 | Name:    File_id
 | Purpose: The coverage data file identification string.
 */
static const char File_id[] = "C-Cover 7.11.0\n";

/* The region of the file head that we keep locked */
enum { fileHeaderSize = sizeof(File_id) - 1 + 9 + 9 + 9 };

/*----------------------------- Constant -------------------------------
 | Name:    Path_default
 | Purpose: The default coverage data file name.
 */
#if !defined(Libcov_covfile)
	#define Libcov_covfile "test.cov"
#endif

/*----------------------------- Constant -------------------------------
 | Name:    Offset_...
 | Purpose: Offset of values in header.
 */
#define Offset_dir      (sizeof(File_id)-1)

/*========== Types ===================================================*/

/*========== Variables ===============================================*/

/* Set this to 0 to prevent cov_probe from making system calls
 *   Set to 0 for as short a time as possible
 *   This is a temporary setting for system initialization,
 *     for example measuring the standard C library
 */
#if __cplusplus
	extern "C" {
#endif
int cov_syscall = 1;
#if __cplusplus
	}
#endif

#if !COVRT_PASSIVE
/*------------------------- Private Variable ---------------------------
 | Name:    Dir_next
 | Purpose: The offset of the next file directory entry.
 */
static unsigned Dir_next;

/*------------------------- Private Variable ---------------------------
 | Name:    File
 | Purpose: Low level file i/o information.
 |          Member <limit> prevents reading beyond what we need which
 |          allows us to not bother with file locking at this level.
 */
static struct {
	unsigned offset;    /* seek position of this buffer */
	unsigned limit;     /* maximum number of bytes to read beyond <offset> */
	int fd;             /* file descriptor */
	unsigned buf_i;     /* position of next read in <buf> */
	unsigned buf_n;     /* number of bytes read into buffer */
	char     buf[512 + 1];
} File;

/* Whether we are the child process of fork(), and so should avoid certain library functions.
 * According to http://www.opengroup.org/onlinepubs/009695399/functions/fork.html,
 * "the child process may only execute async-signal-safe operations"
 */
static int isForkChild;
static cov_atomic_t probe_init_once = cov_atomic_initializer;
static cov_atomic_t saveCwd_once = cov_atomic_initializer;
#endif /* !COVRT_PASSIVE */

#if COV_ARRAY
	/* One CovObject structure per entry */
	/*   HP-UX kernel object count 2650, Apr 2004 */
	#if _AIX || __FreeBSD__
		/* Redefine cov_array so FreeBSD puller does not find it */
		#define cov_array cov_array1
		static CovObject* volatile cov_array[4096];
		CovKernel cov_kernel = { CovKernel_version, sizeof(CovObject*), cov_array, 4096 };
	#else
		CovObject* volatile cov_array[4096];
	#endif
#else
/* Points to chain of CovObject structures */
#if __cplusplus
	extern "C" {
#endif
CovObject* volatile cov_list = NULL;
#if __cplusplus
	}
#endif

#endif
static cov_atomic_t cov_list_lock = cov_atomic_initializer;

#if !COVRT_PASSIVE
/* The coverage file path currently being used */
static char path_current[PATH_MAX];
/* The coverage data file path set by cov_file, else NULL */
static const char* covFile_user;
static char covFile_buf[PATH_MAX];

/*------------------------- Private Variable ---------------------------
 | Name:    Path_is_set
 | Purpose: True if coverage data file path is set (not allowed to change).
 */
static int Path_is_set = 0;

/* The number of calls to cov_term expected. */
static unsigned Term_count = 0;

/* Lock to synchronize cov_write */
static cov_atomic_t covWriteLock = cov_atomic_initializer;

/*========== Private Functions =======================================*/

/* Copy nul-terminated string s2 to s1+i.
 * Return new length of s1.
 * Do not store more than 'size' bytes at s1
 */
static unsigned stringCopy(char* s1, unsigned i, unsigned size, const char* s2)
{
	unsigned j = 0;
	for (; i < size - 1; i++) {
		const char c = s2[j++];
		if (c == '\0') {
			break;
		}
		s1[i] = c;
	}
	s1[i] = '\0';
	return i;
}

static unsigned strtou(
	const char* s,
	char** endptr)
{
	unsigned value = 0;
	/* assert(base == 16); */
	while (*s == ' ') {
		s++;
	}
	for (;; s++) {
		unsigned digit;
		if (*s >= '0' && *s <= '9') {
			digit = (unsigned char)(*s - '0');
		} else if (*s >= 'a' && *s <= 'f') {
			digit = (unsigned char)(*s - 'a') + 10;
		} else {
			break;
		}
		value = (value << 4) + digit;
	}
	if (endptr != NULL) {
		*endptr = (char*)s;
	}
	return value;
}

/* Get the index'th coverage file path
 */
static int cov_path(unsigned index)
{
	int success = 0;
	/* Set pathList to comma separated list of paths */
	const char* pathList = covFile_user;
	if (pathList == NULL) {
		pathList = getenv("COVFILELIST");
	}
	if (pathList == NULL && index == 0) {
		pathList = getenv("COVFILE");
	}
	if (pathList == NULL) {
		pathList = covFile_buf;
	}
	Path_is_set = 1;

	if (pathList[0] != '\0') {
		/* Begin index of substring */
		unsigned begin = 0;
		/* Number of ',' seen */
		unsigned count = 0;
		/* Index to path */
		unsigned i;

		/* Find begin, at index'th comma */
		for (i = 0; count < index && pathList[i] != '\0'; i++) {
			if (pathList[i] == ',') {
				begin = i + 1;
				count++;
			}
		}
		if (count == index) {
			/* Copy until nul or ',' */
			for (i = 0;
				pathList[begin + i] != '\0' &&
				pathList[begin + i] != ',' &&
				i < sizeof(path_current) - 1;
				i++)
			{
				path_current[i] = pathList[begin + i];
				success = 1;
			}
			path_current[i] = '\0';
		}
	}
	return success;
}

/* Convert a signed number to a decimal string */
static void formatDecimal(int nSigned, char* buf)
{
	unsigned n;
	char bufReverse[sizeof("-2147483647")];
	unsigned i = 0;
	unsigned j = 0;
	if (nSigned < 0) {
		buf[0] = '-';
		i = 1;
		nSigned = -nSigned;
	}
	n = (unsigned)nSigned;
	do {
		/* Compute divide and modulus without using modulus operator (which
		 * references a helper function on some architectures)
		 */
		const unsigned nDiv10 = n / 10;
		const unsigned nMod10 = n - nDiv10 * 10;
		bufReverse[j] = (char)('0' + nMod10);
		j++;
		n = nDiv10;
	} while (n != 0);
	do {
		j--;
		buf[i] = bufReverse[j];
		i++;
	} while (j != 0);
	buf[i] = '\0';
}

/* Convert an unsigned number to a hex string length exactly 8 */
static void formatHex(unsigned n, char* buf)
{
	int i;
	for (i = 7; i >= 0; i--) {
		const char digit = (char)(n & 0xf);
		char c = '0';
		if (digit > 9) {
			c = 'a' - 10;
		}
		buf[i] = c + digit;
		n >>= 4;
	}
	buf[8] = '\0';
}
#endif

/* Record an error in 'error' and write the error message.
 * Do nothing if an error of the same or higher severity level was already reported.
 * There is no error message for level 1 errors.
 */
static void error_report(const Error* e, ...)
{
	/* Previous error level, kept separate from 'error' since that variable gets reset */
	static unsigned short level;
	if (error->level < e->level) {
		error = e;
	}
	/* If previous error less severe than new error */
	if (level < e->level) {
		level = e->level;
#if !COVRT_PASSIVE
		if (level > 1) {
			/* Format the message */
			static char buf[128 + PATH_MAX];
			unsigned bi;
			const char* coverr;
			const char* format = error->message;
			unsigned fi;
			va_list va;
			bi = stringCopy(buf,  0, sizeof(buf), Title);
			bi = stringCopy(buf, bi, sizeof(buf), " error ");
			va_start(va, e);
			for (fi = 0; format[fi] != '\0'; fi++) {
				if (format[fi] == '%') {
					char bufNumber[sizeof("-2147483647")];
					const char* p = bufNumber;
					fi++;
					switch (format[fi]) {
					case 's':
						p = va_arg(va, const char*);
						break;
					case 'd':
						formatDecimal(va_arg(va, int), bufNumber);
						break;
					case 'x':
						formatHex(va_arg(va, unsigned), bufNumber);
						break;
					default:
						/* Not reachable */
						bufNumber[0] = '\0';
						break;
					}
					bi = stringCopy(buf, bi, sizeof(buf), p);
				} else {
					buf[bi++] = format[fi];
				}
			}
			va_end(va);
			/* Write the error message */
			coverr = getenv("COVERR");
			if (coverr == NULL) {
				/* Write to standard error */
				buf[bi++] = '\n';
				buf[bi] = '\0';
				write(2, buf, bi);
			} else {
				/* Append message to file */
				const int fd = open(coverr, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
				if (fd == -1) {
					static const char s[] = "Cannot open error log. Check COVERR\n";
					write(2, s, sizeof(s) - 1);
				} else {
					#if _WIN32
						buf[bi++] = '\r';
					#endif
					buf[bi++] = '\n';
					lseek(fd, 0L, SEEK_END);
					write(fd, buf, bi);
					close(fd);
				}
			}
		}
#endif
	}
}

#if !COVRT_PASSIVE
/*------------------------- Private Function ---------------------------
 | Name:    file_read
 | Args:      char *    buf     - buffer to read into
 |            unsigned  length  - number of bytes to read
 | Return:    int               - same as read()
 | Purpose: Read from the coverage data file.
 |          Store a nul at the end of the buffer.
 */
static void file_read(
	char* buf,
	unsigned length)
{
	unsigned total = 0;
	if (error->level < 3) {
		int n;
		do {
			n = (int)read(File.fd, buf + total, length - total);
			if (n < 0) {
				if (errno != EINTR) {
					const int errno_ = errno;
					error_report(&error_io, path_current, (unsigned)lseek(File.fd, 0, SEEK_CUR), errno_);
					break;
				}
			} else {
				total += (unsigned)n;
			}
		} while (total < length && n != 0);
	}
	buf[total] = '\0';
}

/* Seek in the coverage data file.  */
static void file_seek(unsigned offset)
{
	if (error->level < 3 &&
		lseek(File.fd, (off_t)offset, SEEK_SET) == (off_t)-1)
	{
		error_report(&error_io, path_current, offset, errno);
	}
}

/* Read a 8 digit hexadecimal number at the current file position.
 */
static unsigned file_read_hex(unsigned offset)
{
	unsigned n;
	char buf[sizeof("12345678")];
	char* end = NULL;
	file_seek(offset);
	file_read(buf, sizeof(buf)-1);
	n = strtou(buf, &end);
	if (end != buf + sizeof(buf)-1) {
		error_report(&error_fileCorrupt, path_current, offset);
		n = 0;
	}
	return n;
}

static void fileLock(short type, unsigned offset, unsigned length)
{
	if (error->level < 3) {
		int status;
		struct flock fl;
		fl.l_whence = SEEK_SET;
		fl.l_start = (off_t)offset;
		fl.l_len = (off_t)length;
		fl.l_type = type;
		do {
			status = fcntl(File.fd, F_SETLKW, &fl);
		} while (status != 0 && errno == EINTR);
		if (status != 0 && errno != ENOSYS) {
			error_report(&error_fcntl, path_current, errno);
		}
	}
}

/*------------------------- Private Function ---------------------------
 | Name:    buf_fill
 | Args:      none
 | Return:    none
 | Purpose: Read a new buffer of data.  Requires that <File.offset> be
 |          set to the file position to access.
 */
static void buf_fill(void)
{
	File.buf_n = (unsigned)sizeof(File.buf) - 1;
	if (File.buf_n > File.limit) {
		File.buf_n = File.limit;
	}
	file_seek(File.offset);
	file_read(File.buf, File.buf_n);
	File.buf_i = 0;
	File.buf[File.buf_n] = '\0';
	File.limit -= File.buf_n;
}

/*------------------------- Private Function ---------------------------
 | Name:    buf_flush
 | Args:      none
 | Return:    none
 | Purpose: Write the current buffer of data.
 |          Only write as much of the buffer as we changed.
 |          Advance <File.offset> to the position following the buffer.
 */
static void buf_flush(void)
{
	unsigned total = 0;
	file_seek(File.offset);
	/* if buffer has been changed */
	if (error->level < 3 && File.buf_n != 0) {
		int n;
		do {
			n = (int)write(File.fd, File.buf + total, File.buf_n - total);
			if (n < 0) {
				if (errno != EINTR) {
					const int errno_ = errno;
					error_report(&error_io, path_current, (unsigned)lseek(File.fd, 0, SEEK_CUR), errno_);
					break;
				}
			} else {
				total += (unsigned)n;
			}
		} while (total < File.buf_n && n != 0);
	}
	File.offset += total;
}

/*------------------------- Private Function ---------------------------
 | Name:    buf_getc
 | Args:      none
 | Return:    int   c   - a char or -1
 | Purpose: Read the next character from the current buffer <File.buf>.
 |          Return -1 if there is an error condition.
 */
static int buf_getc(void)
{
	int c;  /* return value */
	/* if not EOF */
	if (File.buf_n != 0) {
		/* check to see if we need to go to the next buffer */
		if (File.buf_i >= File.buf_n) {
			buf_flush();
			buf_fill();
		}
	}
	/* if not EOF */
	if (File.buf_n != 0) {
		/* get next char */
		c = File.buf[File.buf_i];
		File.buf_i++;
	} else {
		c = -1;
	}
	return c;
}

/*------------------------- Private Function ---------------------------
 | Name:    buf_putc
 | Args:      char  c   - a char
 | Return:    none
 | Purpose: Write a char, buffered.  Only one call to this function is
 |          allowed between calls to buf_getc.
 */
static void buf_putc(int c)
{
	File.buf[File.buf_i - 1] = (char)c;
}

/*------------------------- Private Function ---------------------------
 | Name:    cov_open
 | Args:      none
 | Return:    none
 | Purpose: Open the coverage data file.  Set <Cov> to the file path.
 */
static int cov_open(unsigned* fileId)
{
	File.fd = open(path_current, O_RDWR, 0);
	if (File.fd == -1) {
		const Error* e = &error_open;
		if (getenv("COVFILE") == NULL) {
			e = &error_openDefault;
		}
		error_report(e, path_current, errno);
	} else {
		unsigned i;
		unsigned directory;
		fileLock(F_RDLCK, 0, fileHeaderSize);
		File.offset = 0;
		File.limit = fileHeaderSize;
		buf_fill();
		/* check file identification line */
		for (i = 0; i < sizeof(File_id) - 1; i++) {
			if (buf_getc() != File_id[i]) {
				error_report(&error_fileInvalid, path_current);
				break;
			}
		}
		*fileId = file_read_hex(sizeof(File_id) - 1 + 9 + 9);
		/* Read directory offset */
		directory = file_read_hex(Offset_dir);
		if (directory == 0) {
			/* no directory - empty coverage file */
			error_report(&error_fileEmpty, path_current);
		}
		/* Wait for run-time versions prior to 7.13.26 */
		fileLock(F_RDLCK, directory, 1);
		fileLock(F_UNLCK, directory, 1);
		/* Get offset of first directory entry */
		Dir_next = directory + (unsigned)sizeof("Dir 12345678");
	}
	return error->level < 3;
}

/*------------------------- Private Function ---------------------------
 | Name:    cov_close
 | Args:      none
 | Return:    none
 | Purpose: Close the coverage data file.
 */
static void cov_close(void)
{
	/* Unlock directory */
	fileLock(F_UNLCK, 0, fileHeaderSize);
	if (close(File.fd) != 0) {
		error_report(&error_io, path_current, 0, errno);
	}
}

/*------------------------- Private Function ---------------------------
 | Name:    cov_obj_next
 | Args:      ulong *   id_p        - where to put object id
 |            ulong *   offset_p    - where to put object offset
 | Return:    bool      success     - false after last entry
 | Purpose: Read the coverage file directory to get the next object entry.
 */
static int cov_obj_next(
	unsigned* id_p,
	unsigned* offset_p)
{
	char ent[sizeof("o12 12345678 12345678")];
	unsigned len;
	char* end = NULL;
	*offset_p = 0;

	file_seek(Dir_next);
	/* read length then read entry so we do not read too much - locking */
	file_read(ent, 4);  /* o12, s123, or End\n */
	len = strtou(ent + 1, &end);
	Dir_next += len;

	if (ent[0] == 'o') {
		/* read object entry */
		file_seek(Dir_next - len);
		file_read(ent, len);
		*id_p = strtou(end, &end);
		*offset_p = strtou(end, NULL);
	} else {
		/* found Section_end or error */
		if (ent[0] != 'E') {
			error_report(&error_fileCorrupt, path_current, Dir_next);
		}
		*id_p = 0;
		*offset_p = 0;
	}
	return ent[0] == 'o';
}

/*------------------------- Private Function ---------------------------
 | Name:    object_write_event
 | Args:      unsigned  data        - CovObject.data[i]
 |            char      char_new    - char for event
 | Return:    none
 | Purpose: Update and check an event character in the file.
 |          This function reads and then may write one char in its place.
 */
static void object_write_event(
	unsigned data,
	int char_new)
{
	int c;
	c = buf_getc();
	/* if the <event> is set in <data> */
	if (data != 0) {
		/* if this is the first time this event occurred */
		if (c == ' ') {
			buf_putc(char_new);
		}
	}
}

/*------------------------- Private Function ---------------------------
 | Name:    object_write
 | Args:      CovObject *  p       - ptr to memory object
 |            ulong     offset  - where to write
 | Return:    none
 | Purpose: Update an object structure in the file at <offset>.
 */
static void object_write(
	CovObject* p,
	unsigned offset)
{
	int c;      /* input buffer */
	int kind;   /* type of probe in file */
	unsigned i; /* index to p->data[] */
	unsigned event_count = 0;

	/* Lock file for writing */
	fileLock(F_WRLCK, offset, 1);
	/* get size */
	File.limit = file_read_hex(offset + (unsigned)sizeof("Obj"));
	File.offset = offset;
	buf_fill();
	/* skip object header */
	do {
		c = buf_getc();
	} while (c != -1 && c != '\n');

	/* for each probe */
	for (i = 0; i < p->data_n; i++) {
		const unsigned data = p->data[i];
		event_count += data;

		/* go to next probe */
		kind = buf_getc();
		while (kind == 's' || kind == 'k') {
			if (kind == 's') {
				/* Skip source view index */
				do {
					c = buf_getc();
				} while (c != -1 && c != '\n');
			}
			kind = buf_getc();
		}
		/* update events */
		switch (kind) {
		case 'n':
			object_write_event(data, 'X');
			break;
		case 'c':
			i++;
			event_count += p->data[i];
			object_write_event(p->data[i],  't');
			object_write_event(data, 'f');
			break;
		case 'd':
			i++;
			event_count += p->data[i];
			object_write_event(p->data[i],  'T');
			object_write_event(data, 'F');
			break;
		case 'h':
		case 'l':
		case 'y':
			object_write_event(data, 'X');
			break;
		case 'E':
		case -1:
			/* more probes in memory than in file */
			error_report(&error_fileMismatch, path_current, p->basename, p->id);
			i = p->data_n;
			break;
		default:
			error_report(&error_fileCorrupt, path_current, offset);
			i = p->data_n;
			break;
		}
	}
	p->events_written = event_count;
	c = buf_getc();
	/* A source 's' might occur (if it contains only constant 'k' entries) */
	if (c != 'E' && c != 'k' && c != 's') {
		/* fewer probes in memory than in file */
		error_report(&error_fileMismatch, path_current, p->basename, p->id);
	}
	buf_flush();
	/* Release write lock */
	fileLock(F_UNLCK, offset, 1);
}

static void saveCwd(void)
{
	if (cov_atomic_tryLock(&saveCwd_once) && covFile_user == NULL) {
		static const char path[] = Libcov_covfile;
		unsigned i = 0;
		#if _WIN32
			const int isAbsolute = path[0] == '/' || path[0] == '\\' || path[1] == ':';
		#else
			const int isAbsolute = path[0] == '/';
		#endif
		if (!isAbsolute) {
			if (getcwd(covFile_buf, sizeof(covFile_buf)) == NULL) {
				covFile_buf[0] = '\0';
			} else {
				/* Append a slash if not already present */
				while (covFile_buf[i] != '\0') {
					i++;
				}
				if (i != 0) {
					const char c = covFile_buf[i - 1];
					if (c != '/' && c != '\\') {
						covFile_buf[i++] = '/';
					}
				}
			}
		}
		stringCopy(covFile_buf, i, sizeof(covFile_buf), path);
	}
}

static unsigned events_count(const CovObject* object)
{
	unsigned i = object->data_n;
	unsigned count = 0;
	const unsigned char* data = object->data;
	do {
		i--;
		count += data[i];
	} while (i != 0);
	return count;
}
#endif /* !COVRT_PASSIVE */

#if __cplusplus
extern "C" {
#endif

#if __hpux

static void cov_memcpy(void* s1, const void* s2, size_t n)
{
	char* p1 = s1;
	const char* p2 = s2;
	unsigned i;
	for (i = 0; i < n; i++) {
		p1[i] = p2[i];
	}
}

/* Copy all coverage data into a buffer
 * Return number of bytes copied upon success
 * Return -1 if the buffer is not big enough
 * Return -2 if data structures corrupt
 */
int cov_dump(char* buf, unsigned size)
{
	int status = 0;
	cov_dumpHeader header;
	char* header_p = buf;
	CovObject* object;
	unsigned j;
	buf += sizeof(cov_dumpHeader);
	size -= sizeof(cov_dumpHeader);
#if COV_ARRAY
	for (j = 1; j < sizeof(cov_array) / sizeof(cov_array[0]); j++) {
		CovObject* object = cov_array[j];
		if (object != NULL) {
#else
	for (object = cov_list; object != NULL; object = object->next) {
#endif
			unsigned i;
			unsigned size_object = (unsigned)(
				offsetof(CovObject, next) +
				offsetof(CovObject, basename) - offsetof(CovObject, id) +
				object->data_n);
			if (object->signature != CovObject_signature) {
				status = -2;
				break;
			}
			if (size < size_object) {
				status = -1;
				break;
			}
			size -= size_object;
			cov_memcpy(buf, object, offsetof(CovObject, next));
			buf += offsetof(CovObject, next);
			cov_memcpy(buf, &object->id,
				offsetof(CovObject, basename) - offsetof(CovObject, id));
			buf += offsetof(CovObject, basename) - offsetof(CovObject, id);
			for (i = 0; (buf[i] = object->basename[i]) != '\0' && --size != 0; i++) {
			}
			if (size == 0) {
				status = -1;
				break;
			}
			buf += i + 1;
			cov_memcpy(buf, object->data, object->data_n);
			buf += object->data_n;
#if COV_ARRAY
		}
#endif
	}
	header.magic = libcovMagic;
	header.size = (unsigned)(buf - header_p - sizeof(cov_dumpHeader));
	cov_memcpy(header_p, &header, sizeof(cov_dumpHeader));
	return status < 0 ? status : (int)(buf - header_p);
}

#endif

#if COVRT_PASSIVE
void Libcov_cdecl cov_countDown(void)
{
}

void Libcov_cdecl cov_countUp(void)
{
}

/* The FreeBSD 7.1 kernel calls execve */
void Libcov_cdecl cov_term(void)
{
}

#else /* COVRT_PASSIVE */
/* Get the total number of coverage events */
Export unsigned Libcov_cdecl cov_eventCount(void)
{
	unsigned count = 0;
	if (error->level < 4) {
		CovObject* p;
		/* Spin on the cov_list lock.
		 * Since we do not modify cov_list here, this is only necessary in case an assignment to
		 * cov_list appears to execute out of order.
		 */
		while (!cov_atomic_tryLock(&cov_list_lock))
			;
		for (p = cov_list; p != NULL; p = p->next) {
			count += events_count(p);
		}
	}
		cov_atomic_unlock(&cov_list_lock);
	return count;
}

/*------------------------- Public Function ----------------------------
 | Name:    cov_file
 | Args:      path      - string
 | Return:    success   - true if successful, false if already set by probe
 | Purpose: Set the path (name) of the coverage data file.
 |          You must call this function before any BullseyeCoverage probe occurs.
 |          This setting overrides environment variable COVFILE.
 */
Export int Libcov_cdecl cov_file(const char* path)
{
	int success = !Path_is_set;
	if (success) {
		covFile_user = covFile_buf;
		stringCopy(covFile_buf, 0, sizeof(covFile_buf), path);
	}
	return success;
}

void Libcov_cdecl cov_countDown(void)
{
	Term_count--;
	if (Term_count == 0) {
		cov_term();
	} else {
		#if !_WIN32
			/* A static destructor might occur due to unloading a shared library
			 * so write and unlink.
			 */
			cov_write();
			cov_unlink();
		#endif
	}
}

void Libcov_cdecl cov_countUp(void)
{
	Term_count++;
}

/*------------------------- Public Function ----------------------------
 | Name:    cov_term
 | Args:      none
 | Return:    none
 | Purpose: Terminate the BullseyeCoverage run-time.  This function is called
 |          by atexit and then maybe by static destructors.  Termination
 |          is not permanent.  Calls into the BullseyeCoverage run-time may continue.
 */
void Libcov_cdecl cov_term(void)
{
	autoSave_join();
	cov_write();
	/* Unlink chain, to allow restarting, as is possible on VxWorks */
	cov_unlink();
	cov_atomic_unlock(&probe_init_once);
	cov_atomic_unlock(&saveCwd_once);
}
#endif /* !COVRT_PASSIVE */

/* CovObject initialization */
#if COV_ARRAY
	static void cov_probe_init(CovObject* p, int probe)
	{
		union {
			CovObject* p;
			unsigned long i;
		} u;
		unsigned i = sizeof(cov_array) / sizeof(cov_array[0]);
		u.i = i;
		cov_array[0] = u.p;
		if (p->signature == CovObject_signature &&
			(unsigned)probe < p->data_n)
		{
			/* Search for empty slot, or one already pointing to this object
			 *   (due to module unload/reload at same address) */
			do {
				i--;
			} while (i != 0 && cov_array[i] != NULL && cov_array[i] != p);
			if (i != 0) {
				if (cov_atomic_tryLock(&cov_list_lock)) {
					if ((cov_array[i] == NULL || cov_array[i] == p) && !p->is_linked) {
						p->is_linked = 1;
						cov_array[i] = p;
					}
					cov_atomic_unlock(&cov_list_lock);
				}
			}
			p->data[probe] = 1;
		}
	}
#else

#if Libcov_posix && !Libcov_noAutoSave
static void atfork()
{
	/* Reset all locks that we wait on.
	 * Our process was copied but any thread holding a lock was not copied.
	 * Since the fork occurred outside our run-time, no lock should be held now.
	 */
	cov_atomic_unlock(&covWriteLock);
	cov_atomic_unlock(&cov_list_lock);
	isForkChild = 1;
}
#endif

#if !defined(isReady)
	/* Defined as a function to avoid warning that condition is constant */
	static int isReady(void) { return 1; }
#endif
static void cov_probe_init(CovObject* p, int probe)
{
	if (p->signature != CovObject_signature ||
		(unsigned)probe >= p->data_n)
	{
		error_report(&error_memoryCorrupt, __LINE__);
	} else {
		if (cov_atomic_tryLock(&cov_list_lock)) {
			if (!p->is_linked) {
				p->is_linked = 1;
				p->next = cov_list;
				cov_list = p;
			}
			cov_atomic_unlock(&cov_list_lock);
			p->data[probe] = 1;
		}
		#if !COVRT_PASSIVE
			if (cov_atomic_tryLock(&probe_init_once)) {
				if (!isForkChild && cov_syscall && isReady()) {
					/* Term_count is non-zero if the program has any static
					 * ctors, in which case atexit is not needed. Also, in
					 * that case it is not safe to call atexit because
					 * library may not be initialized yet.
					 */
					if (Term_count == 0) {
						/* Register termination with atexit */
						if (atexit(cov_term) != 0 && errno != ENOSYS) {
							error_report(&error_atexit, errno);
						}
					}
					#if Libcov_posix && !Libcov_noAutoSave
						pthread_atfork(NULL, NULL, atfork);
					#endif
					if (autoSave_create() != 0) {
						error_report(&error_threadCreate);
					}
					saveCwd();
				} else {
					cov_atomic_unlock(&probe_init_once);
				}
			}
		#endif
	}
}
#endif

/* Record a probe event */
void Libcov_cdecl Libcov_probe(void* p_void, int probe)
{
	CovObject* p;

	#if _MSC_VER && _M_IX86
		/* Preserve __fastcall parameter registers,
		 * in case they are referenced from inline assembly */
		int reg_cx, reg_dx;
		__asm {
			mov reg_cx,ecx
			mov reg_dx,edx
		}
	#endif

	p = (CovObject*)p_void;
	/* If this run-time data structure is already in our chain */
	if (p->is_linked == 1) {
		p->data[probe] = 1;
	} else if (p->is_linked == 0) {
		cov_probe_init(p, probe);
	} else {
		/* This error may be due to the BSS section not clear on startup */
		error_report(&error_memoryCorrupt, __LINE__);
	}

	#if _MSC_VER && _M_IX86
		__asm {
			mov ecx,reg_cx
			mov edx,reg_dx
		}
	#endif
}	/*lint !e529 */

static void cov_reset_1(CovObject* p)
{
	unsigned i;
	for (i = 0; i < p->data_n; i++) {
		p->data[i] = 0;
	}
	p->events_written = 0;
}

/*------------------------- Public Function ----------------------------
 | Name:    cov_reset
 | Args:      none
 | Return:    none
 | Purpose: Reset measurements to zero coverage.  Callable by user.
 */
Export int Libcov_cdecl cov_reset(void)
{
	const int status = cov_check();
	if (status < 0) {
		/* Spin on the cov_list lock.  We cannot skip the operation if
		 * cov_list is busy, like we can elsewhere.
		 */
		while (!cov_atomic_tryLock(&cov_list_lock))
			;
		{
#if COV_ARRAY
		unsigned i;
		for (i = sizeof(cov_array) / sizeof(cov_array[0]) - 1; i != 0; i--) {
			CovObject* p = cov_array[i];
			if (p != NULL) {
				cov_reset_1(p);
				/* Do not bother resetting cov_array[i], there is no point */
			}
		}
#else
		CovObject* p = cov_list;
		cov_list = NULL;
		while (p != NULL) {
			CovObject* next = p->next;
			cov_reset_1(p);
			p->is_linked = 0;
			p->next = NULL;
			p = next;
		}
#endif
		}
		cov_atomic_unlock(&cov_list_lock);
	}
	return status;
}

static int cov_check_1(const CovObject* p)
{
	int success = 1;
	if (p->signature != CovObject_signature ||
		p->version != Libcov_version ||
		p->data_n == 0 ||
		p->is_linked > 1)
	{
		error_report(&error_memoryCorrupt, __LINE__);
		success = 0;
	} else {
		unsigned i;
		for (i = 0; i < p->data_n; i++) {
			if (p->data[i] > 1) {
				error_report(&error_memoryCorrupt, __LINE__);
				success = 0;
				break;
			}
		}
	}
	return success;
}

Export int Libcov_cdecl cov_check(void)
{
	/* Do not lock cov_list_lock because this function does not modify cov_list */
	int status;
	unsigned count = 0;
	{
#if COV_ARRAY
	unsigned i;
	for (i = sizeof(cov_array) / sizeof(cov_array[0]) - 1; i != 0; i--) {
		const CovObject* p = cov_array[i];
		if (p != NULL) {
			if (!cov_check_1(p)) {
				break;
			}
			count++;
		}
	}
#else
	const CovObject* p;
	for (p = cov_list; p != NULL; p = p->next) {
		if (!cov_check_1(p)) {
			break;
		}
		count++;
	}
#endif
	}
	status = error->number;
	if (status == 0) {
		status = -(int)count;
	}
	return status;
}

/* Disconnect chain, to avoid pointers into unloaded
 * shared library or module
 */
void Libcov_cdecl cov_unlink(void)
{
#if !COV_ARRAY
	CovObject* p;
	while (!cov_atomic_tryLock(&cov_list_lock))
		;
	p = cov_list;
	cov_list = NULL;
	while (p != NULL) {
		CovObject* next = p->next;
		p->is_linked = 0;
		p->next = NULL;
		p = next;
	}
	cov_atomic_unlock(&cov_list_lock);
#endif
}

/*------------------------- Public Function ----------------------------
 | Name:    cov_write
 | Args:      none
 | Return:    int     status  - error code or 0
 | Purpose: Write coverage data.
 |          Documented user callable.
 */
Export int Libcov_cdecl cov_write(void)
{
#if COVRT_PASSIVE
	return error_passiveWrite.number;
#else
	int status;
	CovObject* cov_list_copy = NULL;
	static enum { notSet, setFalse, setTrue } enable;
	int isBusy = 0;
	cov_check();
	if (error->level < 4) {
		/* Skip to first object with new coverage.  Possibly there is no new coverage at all */
		for (cov_list_copy = cov_list;
			cov_list_copy != NULL;
			cov_list_copy = cov_list_copy->next)
		{
			if (events_count(cov_list_copy) > cov_list_copy->events_written) {
				break;
			}
			/* assert(cov_list_copy->is_found); */
		}
	}
	switch (enable) {
	case notSet:
		enable = getenv("COVNOSAVE") == NULL ? setTrue : setFalse;
		break;
	case setFalse:
	case setTrue:
		break;
	default:
		error_report(&error_memoryCorrupt, __LINE__);
		break;
	}
	if (cov_list_copy != NULL && enable == setTrue) {
		/* Do not lock cov_list_lock because this function does not modify cov_list */
		/* If no other thread is already doing this */
		int isLock;
		#if Libcov_dynamic
			staticImage.covWriteLock = &covWriteLock;
		#endif
		for (;;) {
			struct timespec rqt;
			isLock = cov_atomic_tryLock(&covWriteLock);
			if (isLock) {
				break;
			}
			/* Sleep for 0.01s */
			rqt.tv_sec = 0;
			rqt.tv_nsec = 10000000;
			if (nanosleep(&rqt, NULL) != 0) {
				break;
			}
		}
		isBusy = !isLock;
		if (isLock) {
			unsigned fileId = 0;
			unsigned index;
			unsigned objectCount = 0;
			unsigned objectsFound = 0;
			CovObject* p;
			saveCwd();
			for (p = cov_list_copy; p != NULL; p = p->next) {
				objectCount++;
			}
			for (index = 0; error->level < 4 && objectsFound < objectCount && cov_path(index); index++) {
				const Error* errorSave = error;
				error = &error_none;
				if (cov_open(&fileId)) {
					unsigned obj_id = 0;
					unsigned obj_offset = 0;
					/* for each object in directory */
					while (objectsFound < objectCount && cov_obj_next(&obj_id, &obj_offset)) {
						/* search chain for the object */
						for (p = cov_list_copy; p != NULL; p = p->next) {
							if (p->id == obj_id) {
								p->is_found = 1;
								objectsFound++;
								if (events_count(p) > p->events_written) {
									object_write(p, obj_offset);
								}
								/* Do not stop the loop. It is possible to have more than one copy of the same object file in memory */
							}
						}
					}
					cov_close();
				}
				if (error->level <= errorSave->level) {
					error = errorSave;
				}
			}
			/* check that all objects were found */
			if (objectsFound < objectCount) {
				for (p = cov_list_copy; p != NULL; p = p->next) {
					if (!p->is_found) {
						const Error* e = &error_wrongFile;
						if (fileId - p->id < 100000) {
							e = &error_objectMissing;
						}
						error_report(e, path_current, fileId, p->basename, p->id);
					}
				}
			}
			cov_atomic_unlock(&covWriteLock);
		}
	}
	status = error->number;
	if (status == 0) {
		if (enable == setFalse) {
			status = error_noSave.number;
		} else if (cov_list == NULL) {
			status = error_noProbes.number;
		} else if (isBusy) {
			status = error_busy.number;
		}
	}
	return status;
#endif
}

#if __cplusplus
}
#endif
