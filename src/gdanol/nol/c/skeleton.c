/***************************************************************
 * File name: Skeleton.c
 * Copyright (C) 1986-2017 Gensym Corporation.,
 * 125 CambridgePark Drive, Cambridge, MA  02140
 ***************************************************************/
 
#include <stdio.h>
#include "gsi_main.h"

gsi_int gsi_get_tcp_port() 
{
  /* register port number for UNIX systems */ 
  return 0; 
}


gsi_int gsi_initialize_context(char *init_str, gsi_int str_len) 
{ 
  printf("Initializing context\n", init_str );
  return GSI_ACCEPT;
} 

 
void gsi_get_data(gsi_registered_item *items, gsi_int count) 
{ 
} 


void gsi_set_data(gsi_registered_item *itsms, gsi_int count) 
{ 
} 

void gsi_pause_context() 
{ 
  printf("\nInside gsi_pause_context" );
} 
 
 
void gsi_resume_context() 
{ 
  printf( "\nInside gsi_resume_context" );
} 

  
void gsi_shutdown_context() 
{ 
  printf( "\nInside gsi_shutdown_context" );
} 


void gsi_g2_poll() 
{ 
} 

void gsi_receive_message(char* message, gsi_int length)
{
}


void gsi_receive_registration( gsi_registration item_registration)
{
}


void gsi_receive_deregistrations(gsi_registered_item *registered_items, gsi_int count)
{
}
