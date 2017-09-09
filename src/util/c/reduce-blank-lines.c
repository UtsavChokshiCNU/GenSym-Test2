
#include <stdio.h>
#include <string.h>

#define SIZE 200

main(argc, argv)
    int argc;
    char **argv;
{
  char line[SIZE];

  while (1) {
  again:
    if (NULL == fgets(line, SIZE, stdin)) return 0;
    fputs(line, stdout);
    if (line[0] != '\n') goto again;
  skip:
    if (NULL == fgets(line, SIZE, stdin)) return 0;
    if (line[0] == '\n') goto skip;
    fputs(line, stdout);
  }
}
