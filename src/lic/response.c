/*
  This file when compiled:
     gcc -o response response.c
  makes an executable used as follows

  Example use:
  > response BHYDE 123
  7J64wptoZrY
  >

The "BHYDE" is a password and 123 is a challenge taken from 
the authorization server.  The output "7J64wptoZrY" is the
response to pass back to the server.

See the section "challenge response" in the sources of the
licensing server for additional information.

*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *c1(i,n,r)
    char *i,*r; int n;
{   int s = 74;
    char *nc = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789#@";
    char *p;
    sprintf(r, "%d%s%d", n, i, n);
    for(p = r; *p!='\0'; p++){
      s ^= (int)(toupper(*p));
      *p = nc[ s & 63 ];}
    return r;}

char *c2(p,n,b)
     char *p, *b; int n;
{ char b1[500];
  return c1(c1(p,0,b1),n,b);}

int main(argc, argv)
  int argc; char *argv[];
{ char r[500];
  printf("%s\n", c2( argv[1], atoi(argv[2]), r));
  return 0;
}
