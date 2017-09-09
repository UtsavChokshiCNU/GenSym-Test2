#include <iostream_ver.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utils.h"

/* Compiler debug mode flag */
extern "C"
{
#include "yacc_supp.h"
}

/*=============================================================
  file_exists
    - checks for the existence of a file by attempting to get
      its size. 
    - 1=file exists, 0=not found
 =============================================================*/

short file_exists (char *file)
{
  if (file_attribs(file,F_SIZE) < 0)
    return(0);
  else
    return(1);
}



/*=============================================================
  file_exists_in_path
    - if 'file' exists in any directory designated by 'filepath'
      then allocate a buffer and return ptr to 'filepath[n]+file'
      NOTE: user must release buffer when finished
    - if it can't be found then return NULL
 =============================================================*/

char *file_exists_in_path (char *file, char **filePath, int nPath)
{
#ifdef WIN32
#define PATH_DELIM  '\\'
#else
#define PATH_DELIM  '/'
#endif

  char   *tmpBuf=NULL;

  int flen = strlen(file);

  for (int n=0; n<nPath; n++) {
    int splen = strlen(filePath[n]);
    tmpBuf = (char *)calloc(flen+splen+2,sizeof(char));
    if ((filePath[n])[splen-1] != PATH_DELIM)
      sprintf(tmpBuf,"%s%c%s",filePath[n],PATH_DELIM,file);
    else
      sprintf(tmpBuf,"%s%s",filePath[n],file);

    if (file_exists(tmpBuf)) {
      file = tmpBuf;   
      break;
    }

    free(tmpBuf);
    tmpBuf = (char *)NULL;

  }

  // note: memory is not released if file is found in path

  return(tmpBuf);

}



/*=============================================================
  file_attribs
    - return the requested file info. Available info is indicated
      by one of the "all-caps" tags below
    - if info cannot be obtained, return -1

    tag       function
    --------  --------------------------------------------------
    ST_ATIME  Time of last access of file.
    ST_CTIME  Time of creation of file.
    st_dev    Drive number of the disk containing the file (same as st_rdev).
    st_gid    Numeric identifier of group that owns file (UNIX-specific)
    st_ino    Number of the information node (the inode) for the file (UNIX-specific).
              On UNIX file systems, the inode describes the file date and time stamps,
              permissions, and content. When files are soft-linked to one another, 
              they share the same inode. The inode, and therefore st_ino, has no 
              meaning in the FAT, HPFS, or NTFS file systems.
    st_mode   Bit mask for file-mode information. The _S_IFDIR bit is set if path
              specifies a directory; the _S_IFREG bit is set if path specifies an
              ordinary file or a device. User read/write bits are set according to 
              the file's permission mode; user execute bits are set according to the
              filename extension.
    ST_MTIME  Time of last modification of file.
    st_nlink  Always 1 on non-NTFS file systems.
    st_rdev   Drive number of the disk containing the file (same as st_dev).
    ST_SIZE   Size of the file in bytes; a 64-bit integer for _stati64 and _wstati64
    st_uid    Numeric identifier of user who owns file (UNIX-specific)
 =============================================================*/

long file_attribs (char *file, int attrib)
{
#ifdef WIN32
#define STAT _stat
struct _stat buf;   
#else
#define STAT stat
struct stat buf;   
#endif

  /* get file details */
  if (STAT( file, &buf ) < 0)
    return -1;

  if (compiler_debug_state) {
    cout << "Created:  " << ctime(&buf.st_ctime) << endl;
    cout << "Accessed: " << ctime(&buf.st_atime) << endl;
    cout << "Modified: " << ctime(&buf.st_mtime) << endl;
  }

  switch (attrib) {
    case F_LAST_ACCESSED: return buf.st_atime;
    case F_LAST_MODIFIED: return buf.st_mtime;
    case F_CREATION_TIME: return buf.st_ctime;
    case F_SIZE: return buf.st_size;
  };

  return -1;

}

// Look for lk4 in msg
// ===================
int substr(char *msg, char* lk4)
{
	int	pos = -1 ;
	int	idx = 0 ;

	size_t msgl = strlen(msg) ;
	size_t lk4l = strlen(lk4) ;

	if (lk4l <= msgl)
		while (idx + lk4l <= msgl)
		{
			if (!strncmp(msg+idx, lk4, lk4l))
			{
				pos = idx ;
				break ;
			}
			idx++ ;
		}
	return pos ;
}

// Break message into lines and send it to cout
//
// msg: message to display
// l1i: line 1 intro like "**" or "--" or "==>" or ""
// oli: other line intro, e.g., "  " or "| "
// ll:  line length
// ==================================================
void	msg_to_cout(char *msg, char *l1i, char *oli, unsigned int ll)
{
	char			*buffer = new char[ll+1] ;
	unsigned int	idx = 0, start, p ;
	size_t			msgl = strlen(msg) ;
	size_t			l1il = strlen(l1i) ;
	size_t			olil = strlen(oli) ;

	
	// Look for the easy case
	// ----------------------
	if (l1il + msgl <= ll)
	{
		cout << l1i << msg << endl ;
		goto freebuf ;
	}

	// Make sure the input is reasonable
	// ---------------------------------
	if (ll < 10)
	{
		cout << msg << endl ;
		goto freebuf ;
	}
	if (l1il >= ll)
	{
		l1i = "" ;
		l1il = 0 ;
	}
	if (olil >= ll)
	{
		oli = "" ;
		olil = 0 ;
	}

	// First line
	// ----------
	strcpy(buffer, l1i) ;
	p = idx+ll-l1il ;

	while (p >= 0 && idx == 0)
	{
		if (msg[p] == ' ')
		{
			if (p > 0)
				strncat(buffer, msg, p) ;
			idx = p+1 ;
			strcat(buffer, "") ;
			cout << buffer << endl ;
		}
		else
			p-- ;
	}
	if (!idx)
	{
		cout << l1i << msg << endl ;
		goto freebuf ;
	}

	// Remaining lines
	// ---------------
	while (idx < msgl)
	{
		while (idx < msgl && msg[idx] == ' ')
			idx++ ;
		if (idx >= msgl)
			goto freebuf ;
		strcpy(buffer, oli) ;
		start = idx ;
		p = idx+ll-olil ;
		if (p >= msgl)
		{
			strcat(buffer, msg+idx) ;
			cout << buffer << endl ;
			goto freebuf ;
		}
		while (p > start && msg[p] != ' ')
			p-- ;
		if (p == start)
		{
			cout << msg+start << endl ;
			goto freebuf ;
		}
		else
		{
			strncat(buffer, msg+start, p-start) ;
			strcat(buffer,"") ;
			cout << buffer << endl ;
			idx = p ;
		}
	}
freebuf:
	delete [] buffer ;
}	
