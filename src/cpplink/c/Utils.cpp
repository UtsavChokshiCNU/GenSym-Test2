#include "Utils.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include "windows.h"
#else

#endif

namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/

#ifdef WIN32

void Utils::debugLogException(int priority, char *message)
{
  static char buf[256];
  int room_left_in_buf = 255;
  time_t now_universal_time;
  struct tm *now_local_time_structure;
  char *bufptr = buf;
  int chars_written = 0, accumulated_strlen = 0;
  
  now_universal_time = time(NULL);
  if (now_universal_time != -1) {
    now_local_time_structure = localtime(&now_universal_time);
    if (now_local_time_structure) {
      chars_written = (int) strftime(bufptr, room_left_in_buf,
        " %d/%m/%Y %I:%M:%S %p  ",
        now_local_time_structure);
    }
  }
  if (chars_written > 0) {
    room_left_in_buf -= chars_written;
    accumulated_strlen += chars_written;
    bufptr += chars_written;
  } else {
    OutputDebugString("Warning: error formatting the following message.\n");
  }
  
  // chars_written = _vsnprintf(bufptr, room_left_in_buf,
  // format_string, (va_list)(&format_string+1));
  
  strcat(bufptr, message);
  chars_written = strlen(message);
  
  if (chars_written > 0) {
    room_left_in_buf -= chars_written;
    accumulated_strlen += chars_written;
    bufptr += chars_written;
    } else {
    OutputDebugString("Warning: error formatting the following message.\n");
    }
    if (room_left_in_buf < 1) {
      // Overwrite the last character with the newline.
      accumulated_strlen--;
    }
    if (buf[accumulated_strlen-1] == '\n') {
      buf[accumulated_strlen] = 0;
    } else {
      buf[accumulated_strlen] = '\n';
      buf[++accumulated_strlen] = 0;
    }
    
    OutputDebugString(buf);
}


#else


Utils::debugLogException(int priority, char *message)
{
  // FIND ME. stubbed out for now
}

#endif


void Utils::toUpper(char *pString)
{
  int len = strlen(pString);

  for (int i=0; i<len; i++) {
      pString[i] = toupper(pString[i]);
  }
}


/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

}