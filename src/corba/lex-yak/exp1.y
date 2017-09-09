/* Bison grammar file. */

%{

/*
C declarations
The C declarations may define types and variables used in the actions. You can also use preprocessor commands to define macros
used there, and use #include to include header files that do any of these things.
*/
#define YYSTYPE double
#include <math.h>


%}

/*
Bison declarations
The Bison declarations declare the names of the terminal and nonterminal symbols, and may also describe operator precedence and the
data types of semantic values of various symbols.
*/
%token NUM

%%
/*
Grammar rules
The grammar rules define how to construct each nonterminal symbol from its parts. 
*/
input:    /* empty */								/*An empty input is valid and marked this way*/
        | input line
;

line:     '\n'			  /* No action taken upon receiving a newline character */
        | exp '\n'  { printf ("\t%.10g\n", $1); }
;

exp:      NUM             { $$ = $1;         }		/* '$$' is the result of the action */
        | exp exp '+'     { $$ = $1 + $2;    }
        | exp exp '-'     { $$ = $1 - $2;    }
        | exp exp '*'     { $$ = $1 * $2;    }
        | exp exp '/'     { $$ = $1 / $2;    }
      /* Exponentiation */
        | exp exp '^'     { $$ = pow ($1, $2); }
      /* Unary minus    */
        | exp 'n'         { $$ = -$1;        }
;
%%

/*
Additional C code
The additional C code can contain any C code you want to use. Often the definition of the lexical analyzer yylex goes here, plus
subroutines called by the actions in the grammar rules. In a simple program, all the rest of the program can go here. 
*/

/* Lexical analyzer returns a double floating point 
   number on the stack and the token NUM, or the ASCII
   character read if not a number.  Skips all blanks
   and tabs, returns 0 for EOF. */

#include <stdio.h>
#include <ctype.h>

main ()
{
  yyparse ();
}


yylex ()
{
  int c;

  /* skip white space  */
  while ((c = getchar ()) == ' ' || c == '\t')  
    ;
  /* process numbers   */
  if (c == '.' || isdigit (c))                
    {
      ungetc (c, stdin);
      scanf ("%lf", &yylval);
      return NUM;
    }
  /* return end-of-file  */
  if (c == EOF)                            
    return 0;
  /* return single chars */
  return c;                                
}


yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}
