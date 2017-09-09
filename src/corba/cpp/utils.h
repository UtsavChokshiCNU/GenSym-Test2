#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#define F_LAST_ACCESSED     1
#define F_LAST_MODIFIED     2
#define F_CREATION_TIME     3
#define F_SIZE              4



// file IO
short  file_exists (char *file);
char  *file_exists_in_path (char *file, char **filePath, int nPath);
long   file_attribs (char *file, int attrib);

// String Manipulation
int     substr(char *msg, char* lk4) ;
void	msg_to_cout(char *msg, char *l1i, char *oli, unsigned int ll) ;


#endif

