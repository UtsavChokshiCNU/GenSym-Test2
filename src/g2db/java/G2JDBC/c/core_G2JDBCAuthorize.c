#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "core_G2JDBCAuthorize.h"
#include "gsi_brg.h"

#define TRUE 1
#define FALSE 0

JNIEXPORT jboolean JNICALL Java_core_G2JDBCAuthorize_authorize
  (JNIEnv *jev, jclass vc)
{
    if (stage1("G2-JDBC", "V11") != TRUE)
	return FALSE;
    if (stage2() != TRUE)
	return FALSE;
    
    return TRUE;
}
