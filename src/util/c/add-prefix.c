
#include <stdio.h>
#include <string.h>

#define SIZE 200

main(argc, argv)
    int argc;
    char **argv;
{
  char *prefix = "";
  char line[SIZE];
  int len;

  if (argc>=1) prefix = argv[1];

  while (1) {
    if (NULL == fgets(line, SIZE, stdin)) return 0;
    fputs(prefix, stdout);
    fputs(line, stdout);
    len = strlen(line);
    while (line[len-1] != '\n' && len == SIZE-1) {
      if (NULL == fgets(line, SIZE, stdin)) return 0;
      fputs(line, stdout);
      len = strlen(line);
    }
    if (line[len-1] != '\n') break;
  }
}
