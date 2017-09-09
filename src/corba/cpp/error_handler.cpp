#include <iostream_ver.h>
#include "gsi_main_cpp.h"
#include <gsi_main.h>
#include "error_handler.h"
#include "string.h"

int		substr(char *, char *) ;
void	msg_to_cout(char *, char *, char *, unsigned int ll) ;

void	*error_handler(gsi_int error_context, gsi_int error_code, gsi_char *error_msg)
{
	cout << "===========================================================================" << endl ;
	if (error_code == 34 && substr(error_msg, "_G2ORB-VERCHK") >= 0)
	{
		cout << "*** Warning:  It appears that you are using an old version of g2orb.kb." << endl ;
		cout << "As a result, it is not possible to verify that your kb supports the newer"<< endl ;
		cout << "features of Corbalink.  Please use the copies of g2orb.kb and g2idl.kb" << endl ;
		cout << "that were included with the distribution of this version of Corbalink." << endl ;
	}
	else
	{
		cout << "** GSI ERROR.  Code " << error_code << ", Context " << error_context << endl ;
        msg_to_cout(error_msg, "-- ", "   ",70) ;
	}
	cout << "===========================================================================" << endl ;
	return NULL ;
}



