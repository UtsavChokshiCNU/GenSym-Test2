#include	"stdafx.h"
#include	<RTI.hh>
#include	"G2Hla.h"

#include	"HLAClass.h"
#include	"HLAClassContainer.h"
#include	"G2FederateAmbassador.h"
#include	"TestConstants.h"
#include	<cppunit/extensions/HelperMacros.h>

// Clobal variables definition
RTI::FederateHandle		federateId;

RTI::RTIambassador		srtiAmbP;
RTI::RTIambassador		*rtiAmbP = &srtiAmbP;

G2FederateAmbassador	*fedAmbP = NULL;

HLAClassContainer		hlaClassCache;
char					error_msg[2048];

long G2_Context;
long log_indentation;
BOOL G2_joined_Federation = FALSE;

//
// gsi functions definitions
//
void log_with_timestamp(long mode, char *fmt, ...)
{

}

char *__cdecl gsi_str_of(void* pData)
{
	return (char*)pData;
}

void gsirtl_copy_item_or_value(
  gsi_item arg,
  gsi_item duplicate)
{
}

void gsirtl_free_i_or_v_contents(gsi_item arg)
{
}

GSI_API_EXTERN void	   gsi_set_type
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_int gsi_type ))
{
}

GSI_API_EXTERN gsi_item	*gsi_make_items
        GSI_API_PROTO(( gsi_int  count ))
{
	return 0;
}


GSI_API_EXTERN void  gsi_rpc_return_values
        GSI_API_PROTO(( gsi_item *arguments,
			gsi_int count,
			gsi_call_identifier_type call_identifier,
			gsi_int context ))
{
	isErrorResult = strcmp(errorResult, NO_ERROR_SYM) != 0;
}

GSI_API_EXTERN void	   gsi_set_flt
        GSI_API_PROTO(( gsi_struct I_RI_ATT, double float_value ))
{
}

GSI_API_EXTERN void	   gsi_set_str
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_char *text_value ))
{
}

GSI_API_EXTERN void	   gsi_set_sym
        GSI_API_PROTO(( gsi_struct I_RI_ATT, gsi_symbol symbol_value ))
{
	errorResult = symbol_value;
}

GSI_API_EXTERN gsi_int	   gsi_log_of
        GSI_API_PROTO(( gsi_struct I_RI_ATT ))
{
	return 0;
}

GSI_API_EXTERN void      gsi_reclaim_item
        GSI_API_PROTO(( gsi_item item ))
{
}

		
