/* Note: this file is guessed by Chun Tian (binghe), not the original file. */

#include <ctype.h>
#include <string.h>
#include <stdio.h>

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
  char *p,*b; int n;
{ char b1[500];
  return c1(c1(p,0,b1),n,b);}

char* compute_response(
  char *response_buffer,
  int challenge,
  char *password)
{
  return c2(password, challenge, response_buffer);
}
