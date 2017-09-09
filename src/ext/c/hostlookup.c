/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      hostlookup.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   yduJ
 +
 + Description: This module contains a standalone program to do hostname lookup,
 +              printing IP address to standard output.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#if !defined(WIN32)
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <netinet/ip.h>
#  include <arpa/inet.h>
#  include <unistd.h>
#  include <netdb.h>
#endif

#if defined(WIN32)
#   include <winsock.h>
#   include <io.h>
#   include "msincls.h"
#endif

#define BUFLEN 256
#define SUCCESS 0
#define FAILURE -1

int main(argc, argv)
int argc;
char *argv[];
{
/* GENSYMCID-453: Fix all LSB compatibility issues of the Gensym Linux bundle */
#if !defined(linux)
  struct hostent *hostdata;
#else
  struct addrinfo hints, *result;
  struct sockaddr_in *result_in;
  int error;
#endif
  struct sockaddr_in *addr;
  unsigned char *data;
  FILE *output;

#if defined(_WINSOCKAPI_)
    WSADATA WSAStartupData;
    if (WSAStartup(MAKEWORD(1,1), &WSAStartupData) != 0) {
      printf("WINSOCK Startup Error.\n");
      return(FAILURE);
    }
#endif

  if (argc < 2) {
    printf("Usage: hostlookup hostname [filename]\n");
    return FAILURE;
  }

#if !defined(linux)
  hostdata = gethostbyname(argv[1]);
#if defined(_WINSOCKAPI_)
  if (!hostdata) {
    printf("Failed to resolve hostname\n");
    return FAILURE;
  }
#else
  if (!hostdata) {
    switch (h_errno) {
    case HOST_NOT_FOUND:
      /* most common case */
      printf("Host not found\n");
      break;
    case TRY_AGAIN:
      printf("Host not found (non-authoritative)\n");
      break;
    case NO_RECOVERY:
      printf("Non-recoverable error\n");
      break;
    case NO_DATA:
      printf("Valid name but no address information\n");
      break;
    }
    return FAILURE;
  }
#endif /* defined(_WINSOCKAPI_) */

#else /* defined(linux) */

  /* LSB requires using getaddrinfo() instead of gethostbyname */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_INET;
  error = getaddrinfo(argv[1], "domain", &hints, &result);
  
  if (error != 0) {
    printf("%s\n", gai_strerror(error));
    return FAILURE;
  }

  if (result->ai_family != AF_INET) {
    return FAILURE;
  }

  result_in = (struct sockaddr_in*) result->ai_addr;
#endif

  addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

  if (addr == NULL) {
    printf("Out of memory\n");
    return FAILURE;
  }

#if !defined(linux)
  memcpy(&(addr->sin_addr),hostdata->h_addr,hostdata->h_length);
  addr->sin_family = hostdata->h_addrtype;
#else
  memcpy(&(addr->sin_addr),&(result_in->sin_addr),result->ai_addrlen);
  addr->sin_family = result->ai_family;
  freeaddrinfo(result);
#endif

  data = (unsigned char *)&(addr->sin_addr);

  printf("%u.%u.%u.%u\n", data[0], data[1], data[2], data[3]);

  /* For GENSYMCID-1093. also output results to a file */
  if (argc > 2) {
    output = fopen(argv[2], "w");
    if (output) {
      fprintf(output, "%u.%u.%u.%u\n", data[0], data[1], data[2], data[3]);
      fclose(output);
    }
  }

  free(addr);

  return SUCCESS;
}
