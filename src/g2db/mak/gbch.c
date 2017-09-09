#include <stdio.h>
#include <time.h>

/* ================================================== */
/* Print to standard output "#define BUILD_CODE <bc>" */
/* where <bc> is the build code for today's date.     */
/* ================================================== */
int main()
{
    time_t      ttNow ;
    struct tm   stX ;
    char        year, month ;

    time(&ttNow) ;
    stX = *localtime(&ttNow) ;
    year = (char)((stX.tm_year - 98) % 26 + (unsigned)'A') ;
    month = (char)(stX.tm_mon + (unsigned)'A') ;
    printf("#ifndef _BUILD_CODE_H_\n");
    printf("#define _BUILD_CODE_H_\n") ;
	printf("#define BUILD_CODE \"%c%c%02d\"\n", year, month, stX.tm_mday) ;
    printf("#endif\n") ;
    return 0 ;
}
