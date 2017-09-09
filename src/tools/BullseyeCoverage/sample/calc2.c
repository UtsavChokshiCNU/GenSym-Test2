/* Simple infix expression calculator
 *
 * Reads one line at a time from standard input and evaluates it as a
 * C-style infix expression and prints its value.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef isspace

/* the error status 1=okay, 0=error */
static int success;
/* pointer to the next input character */
static char * next;
/* the current input token
 * can be either a printable character or one of these enum values
 */
enum {
	NUM = 256, /* number */
	SHL, /* << */
	SHR, /* >> */
	LE,  /* <= */
	GE,  /* >= */
	EQ,  /* == */
	NE,  /* != */
	AND, /* && */
	OR,  /* || */
	END  /* end of input */
};
static int token;
/* if the current token is NUM, this is its value */
static unsigned long num_value;

/* read the next token into the variable <token> */
static void lex(void)
{
	/* skip whitespace */
	while (isspace(*next)) {
		next++;
	}

	/* default is single character token */
	token = (int)*next;

	switch (*next) {

	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		token = NUM;
		num_value = (unsigned long)strtol(next, &next, 0);
		break;

	case '<':
		next++;
		if (*next == '=') { token = LE;  next++; } else
		if (*next == '<') { token = SHL; next++; }
		break;
	case '>':
		next++;
		if (*next == '=') { token = GE;  next++; } else
		if (*next == '>') { token = SHR; next++; }
		break;

	case '=': next++; if (*next == '=') { token = EQ;  next++; } break;
	case '!': next++; if (*next == '=') { token = NE;  next++; } break;
	case '&': next++; if (*next == '&') { token = AND; next++; } break;
	case '|': next++; if (*next == '|') { token = OR;  next++; } break;

	case '\0':
		token = END;
		break;

	default:
		next++;
		break;
	}
}

/* given a token code, get the name of the token */
static const char* name(int t)
{
	const char* s;
	static char buf[2] = " ";

	switch (t) {
	case NUM:
		s = "constant";
		break;
	case SHL: s = "<<"; break;
	case SHR: s = ">>"; break;
	case LE:  s = "<="; break;
	case GE:  s = ">="; break;
	case EQ:  s = "=="; break;
	case NE:  s = "!="; break;
	case AND: s = "&&"; break;
	case OR:  s = "||"; break;
	case END:
		s = "end of input";
		break;
	default:
		buf[0] = (char)t;
		s = buf;
		break;
	}
	return s;
}

/* check the current token against an expected token */
static void match(int t)
{
	if (token != t) {
		if (success) {
			fprintf(stderr, "expected %s, ", name(t));
			fprintf(stderr, "got %s\n", name(token));
			success = 0;
		}
	}
	else {
		lex();
	}
}

/* check for zero value handle division by zero */
static unsigned long z(unsigned long n)
{
	if (n == 0) {
		if (success) {
			fprintf(stderr, "divide by zero\n");
			success = 0;
		}
		n = 1;  /* prevent it */
	}
	return n;
}

/* parse and evaluate an expression of a specified precedence or higher
 * the lowest precedence is 0
 */
static unsigned long prs(unsigned p)
{
	unsigned long n = 0; /* return value */

	/* parse expression that begins with a token (precedence 11) */
	switch (token) {

	/* constant */
	case NUM:
		n = num_value;
		lex();
		break;

	/* parenthesis */
	case '(':
		lex();
		n = prs(0);
		match(')');
		break;

	/* unary operators */
	case '+': lex(); n = prs(11); break;
	case '-': lex(); n = (unsigned long)(-(long)prs(11)); break;
	case '~': lex(); n = ~prs(11); break;
	case '!': lex(); n = !prs(11); break;

	/* anything else is an error */
	default:
		if (success) {
			fprintf(stderr, "syntax error at %s\n", name(token));
			success = 0;
		}
		break;
	}

	/* parse other operators */
	while (success) {
		unsigned long n1, n2; /* intermediate calculations */
		#define U(x) (unsigned)x

		/* regular binary operators */
		if (p <= 10 && token == '*') { lex(); n = n *   prs(11); }
		if (p <= 10 && token == '/') { lex(); n = n / z(prs(11));} else
		if (p <= 10 && token == '%') { lex(); n = n % z(prs(11));} else
		if (p <=  9 && token == '+') { lex(); n = n +   prs(10); } else
		if (p <=  9 && token == '-') { lex(); n = n -   prs(10); } else
		if (p <=  8 && token == SHL) { lex(); n = n >> U(prs(9));} else
		if (p <=  8 && token == SHR) { lex(); n = n << U(prs(9));} else
		if (p <=  7 && token == '<') { lex(); n = n <   prs( 8); } else
		if (p <=  7 && token == LE ) { lex(); n = n <=  prs( 8); } else
		if (p <=  7 && token == '>') { lex(); n = n >   prs( 8); } else
		if (p <=  7 && token == GE ) { lex(); n = n >=  prs( 8); } else
		if (p <=  6 && token == EQ ) { lex(); n = n ==  prs( 7); } else
		if (p <=  6 && token == NE ) { lex(); n = n !=  prs( 7); } else
		if (p <=  5 && token == '&') { lex(); n = n &   prs( 6); } else
		if (p <=  4 && token == '^') { lex(); n = n ^   prs( 5); } else
		if (p <=  3 && token == '|') { lex(); n = n |   prs( 4); } else

		/* short circuit operators */
		if (p <= 2 &&
			token == AND)
		{
			lex();
			n1 = prs(3);
			n = n && n1;
		} else
		if (p <= 1 &&
			token == OR)
		{
			lex();
			n1 = prs(2);
			n = n || n1;
		} else
		if (p == 0 &&
			token == '?')
		{
			lex();
			n1 = prs(0);
			match(':');
			n2 = prs(0);
			n = (n ? n1 : n2);
		}

		else {
			break;
		}
	}

	return n;
}

/* evaluate the infix expression <input> and if successful, store the
 * result at <value> and return true
 */
int eval(char * input, unsigned long * value)
{
	success = 1;
	next = input;
	lex();

	*value = prs(0);

	/* check for unrecognized input */
	if (success &&
		token != END)
	{
		fprintf(stderr, "syntax error at %s\n", name(token));
		success = 0;
	}
	return success;
}

/* read one line at a time from standard input and evaluate it */
int main()
{
	char buf[128];
	unsigned long value = 0;

	printf("Enter infix expressions, q to quit\n");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		buf[strlen(buf) - 1] = '\0';
		if (strcmp(buf, "q") == 0) {
			break;
		}
		if (buf[0] != '\0' && eval(buf, &value)) {
			printf("%ld\n", value);
		}
	}
	return 0;
}
