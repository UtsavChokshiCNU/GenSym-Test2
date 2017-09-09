
#include <stdio.h>

main()
{
  char name[30];
  long size;
  while (EOF != scanf(" %s %lx\n",name,&size))
    printf("%12s %8d\n",name,size);

  /*
  char line[100];
  while (NULL != gets(line)) {
    int result = sscanf(line," %s %lx",name,size);
    if (result==EOF) break;
    printf("%12s %8d\n",name,size);
  }
  */
}
