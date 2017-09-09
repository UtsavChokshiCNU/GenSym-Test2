
#include <stdio.h>
#include <string.h>

/* { */
/* } */
main(argc, argv)
    int argc;
    char **argv;
{
  int chr;

  chr = getchar();
  while (EOF != chr) {
    if ('{' == chr) {
      chr = getchar();
      putchar('{');
      while (chr != '}') {
	putchar(chr);
	chr = getchar();
      }
      puts("}\n");
    } else
      chr = getchar();
  }
}
