
#include <stdio.h>
#include <string.h>

/*  <![CDATA[ */
/* ]]>        */
main(argc, argv)
    int argc;
    char **argv;
{
  int chr;

  chr = getchar();
  while (EOF != chr) {
    if ('<' == chr) {
      if (('!' == (chr = getchar())) &&
	  ('[' == (chr = getchar())) &&
	  ('C' == (chr = getchar())) &&
	  ('D' == (chr = getchar())) &&
	  ('A' == (chr = getchar())) &&
	  ('T' == (chr = getchar())) &&
	  ('A' == (chr = getchar())) &&
	  ('[' == (chr = getchar()))) {
	int c1 = getchar();
	int c2 = getchar();
	int c3 = getchar();
	while (c1 != ']' || c2 != ']' || c3 !='>') {
	  putchar(c1);
	  c1 = c2;
	  c2 = c3;
	  c3 = getchar();
	}
	puts("\n__________________________");
      }
    } else
      chr = getchar();
  }
}
