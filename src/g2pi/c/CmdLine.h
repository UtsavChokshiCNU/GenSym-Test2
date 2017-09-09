#ifndef _CMDLINE_H_
#define _CMDLINE_H_

extern int  nrArgsForGSI ;
extern char *argsForGSI[] ;

#define MAX_NR_GSI_ARGS   25
#define MAX_SZ_CFG_FILE 4096
#define MAX_CMD_LEN      128

typedef enum { cmdBin, cmdYNA, cmdFN, cmdSpec, cmdHelp } cmdType ;
typedef struct {    char    let ;
                    cmdType type ;
                    void    *gVar ; } cmdLnCmd ;

int  procCmdLine(int argc, char **argv, int top) ;
int  procInitCmd(char let, char *p, char *pn) ;
int  procSpecial(char let, char *p, void **ppVar) ;
void saveForGSI(char *p) ;

#endif
