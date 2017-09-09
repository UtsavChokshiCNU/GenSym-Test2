#ifndef __GSI_COMPILE_IDL_H__
#define __GSI_COMPILE_IDL_H__


#ifdef WIN32
#define PATH_DELIM          '\\'
#else
#define PATH_DELIM          '/'
#endif
#define IDL_MAIN_FILE       1
#define IDL_INCLUDE_FILE    2

#define FILE_ATTR           "G2ORB-FILE-PATH"
#define FILE_MTIME_ATTR     "G2ORB-TIME-OF-LAST-CHANGE"

#endif

