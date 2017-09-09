
#include <stdio.h>

main()
{
  int ch;

  while (1) {
    if ('K' == (ch = getchar()) &&
	'B' == (ch = getchar()) &&
	'-' == (ch = getchar()) &&
	'F' == (ch = getchar()) &&
	'L' == (ch = getchar()) &&
	'A' == (ch = getchar()) &&
	'G' == (ch = getchar()) &&
	'S' == (ch = getchar())) {
      int kb_flags = 0;
      while ('+' != (ch = getchar()) && EOF != ch) {
	if ('\n' != ch && '\r' != ch)
	  kb_flags = kb_flags * 32 +
	    (('0' <= ch && ch <= '9') ?
	     (ch - (int)'0') : (10 + ch - (int)'a'));
      }
      printf("%d\n",kb_flags);
      return 0;
    } else if (EOF == ch)
      return 1;
  }
}
