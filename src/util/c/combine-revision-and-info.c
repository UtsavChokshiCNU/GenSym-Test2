
#include <stdio.h>
#include <string.h>

main()
{
  char line[100],ch;

  while (1) {
    if (NULL == gets(line)) return;
    if (0==strncmp("revision ",line,9))
      {int i;
       for (i=9; (ch = line[i]) != '\0' && ch != ' '; i++);
       if (ch == ' ') line[i] = '\0';
       fputs(line+9,stdout);
       fputc(' ',stdout);
       if (NULL == gets(line)) return;
       puts(line);
       fflush(stdout);
     }
  }
}
