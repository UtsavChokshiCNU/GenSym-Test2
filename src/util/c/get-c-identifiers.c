
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define ngetchar() (next_c_p?(next_c_p=FALSE,next_c):getchar())
#define peekchar() (next_c_p?next_c:(next_c_p=TRUE,next_c=getchar()))

main(argc, argv)
    int argc;
    char **argv;
{
  char tr[256];
  int i,c,next_c, next_c_p = FALSE;
  int n_p;
  int last_in_char_was_newline_p = TRUE;
  int last_out_char_was_newline_p = TRUE;
  
  for(i=0;i<256;i++)tr[i]='\n';
  for(i='a';i<='z';i++)tr[i]=i;
  for(i='A';i<='Z';i++)tr[i]=i;
  for(i='0';i<='9';i++)tr[i]=i;
  tr['_']='_';

  while (TRUE) {
  next:
    while(('/'==(c=ngetchar())) &&
	  ('*'==(next_c_p=TRUE,next_c=getchar()))) {
      next_c_p=FALSE;
      while('*'!=getchar() || '/'!=getchar()){}
    }
    if(c==EOF)break;
    if(last_in_char_was_newline_p && ('#'==c)) {
      while('\n'!=ngetchar()){};
      next_c = '\n'; next_c_p = TRUE;
      goto next;
    }
    last_in_char_was_newline_p = (c=='\n');
    if(c=='\''){
      if('\\'==ngetchar()){
	if('0'<=(c=getchar()) && c<='9')
	  while('0'<=(c=getchar()) && c<='9'){}
	else
	  {getchar();getchar();}
      }
      else
	getchar();
      c=' ';
    }
    if(c=='"') {
      while('"'!=(c=ngetchar())){if(c=='\\')getchar();}
      c=' ';
    }
    c=tr[c];
    if(!(n_p = (c=='\n')) || !last_out_char_was_newline_p) {
      putchar(c);
      last_out_char_was_newline_p = n_p;
    }
  }
}
