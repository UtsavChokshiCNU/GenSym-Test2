/************************************************************************************/
/* GSI_FCNS_CPP																		*/
/*																					*/
/* This file contains all of the GSI callback routines that do not have 
/* significant logic						*/
/************************************************************************************/
#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
	
#define TCPIP_PORT_NUMBER  30009



gsi_int gsi_get_tcp_port()
{
    return( TCPIP_PORT_NUMBER );
}

void gsi_receive_registration( gsi_registration item_registration )
{
}
				      
void gsi_get_data( gsi_registered_item registered_items[], gsi_int count )    
{
    printf ("gsi_get_data in context %d\n",gsi_current_context());
}

void gsi_set_data( gsi_registered_item registered_items[], gsi_int count )
{
    printf ("gsi_set_data in context %d\n",gsi_current_context());
}

void gsi_g2_poll()
{
	return;
}

void gsi_receive_deregistrations( gsi_registered_item registered_items[], gsi_int count )
{
	printf("Got dereg: of %d items\n", count);
	for (int i = 0; i < count; i++) {
		printf("Handle = %d\n", gsi_handle_of(registered_items[i]));
	}
}

void gsi_receive_message( char *message, gsi_int length )
{
    printf ("gsi_receive_message in context %d\n",gsi_current_context());
    printf ("G2 says:%s\n",message);
}





