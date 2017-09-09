
#include <stdio.h>
#include <string.h>

#define SIZE 200
#define TRUE 1
#define FALSE 0

main(argc, argv)
    int argc;
    char **argv;
{
  char *prefix = "";
  char line[SIZE];
  int len, eofp = FALSE;

  if (argc>=1) prefix = argv[1];

  while (1) {
  newline:
    if (NULL == fgets(line, SIZE, stdin)) return 0;
    len = strlen(line);
    if (line[len-1] == '\n')
      line[len-1] = '\0';
    else if (len == SIZE-1) {
      fputs(line, stdout);
      goto newline;
    }
    else eofp = TRUE;
    fputs(line, stdout);
    fputs(prefix, stdout);
    fputc('\n', stdout);
    if (eofp) return 0;
  }
}
