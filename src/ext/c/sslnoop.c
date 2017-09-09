/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      sslnoop.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Fred White
 +
 + Description: Stubs for SSL routines.
 + 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "ssl.h"

int g2pvt_ssl_initialize(char *certificate)
{
  return 0;
}

int g2pvt_ssl_set_callback(G2SSL_CONNECTION_CALLBACK cb)
{
  return 0;
}

int g2pvt_ssl_destroy(void)
{
  return -1;
}

G2SSL g2pvt_ssl_accept(int sock)
{
  return (G2SSL)0;
}

G2SSL g2pvt_ssl_connect(int sock)
{
  return (G2SSL)0;
}

int g2pvt_ssl_read(G2SSL ssl, char *buf, int num)
{
  return -1;
}

int g2pvt_ssl_write(G2SSL ssl, char *buf, int num)
{
  return -1;
}

int g2pvt_ssl_close(G2SSL ssl)
{
  return -1;
}

int g2pvt_ssl_available(int server_p)
{
  return 0;
}

