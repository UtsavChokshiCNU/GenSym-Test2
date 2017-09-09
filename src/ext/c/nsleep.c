/*
 * Module NSLEEP
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 */

/*
 * NOTE: THIS FILE SHOULD STAND ALONE
 *
 * Do not introduce any interdependencies between this file and any
 * other bits of Gensym source code.  It is intended that this file
 * could be used by other systems (such as the bridge products) for
 * authorization.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#define NSLEEP_SUCCESS 0L
#define NSLEEP_FAILURE -1L


/***************
 * Shared code *
 ***************/

/*
 * jh, 4/13/95.  See Ben Hyde, licensing czar, for details about the following
 * feature.
 */

#define MAYBE_ESTABLISH_CACHE(buffer)     \
  do {                                    \
    if (CACHE_IS_ESTABLISHED) {           \
      strcpy(buffer, ESTABLISHED_CACHE);  \
      return NSLEEP_SUCCESS;                     \
    } else {                              \
      MAYBE_ESTABLISH_CACHE_1(buffer);    \
      if (CACHE_IS_ESTABLISHED)           \
        return NSLEEP_SUCCESS;                   \
    }                                     \
  } while (0)

/* devious names */
#define MAYBE_ESTABLISH_CACHE_1 check_sleep_interval_roundoff
#define CACHE_IS_ESTABLISHED    sleep_interval_roundoff_deviation
#define ESTABLISHED_CACHE       encoded_permissible_roundoffs
#define CACHE_SIZE              256

long CACHE_IS_ESTABLISHED = 0;
char ESTABLISHED_CACHE[CACHE_SIZE];

void MAYBE_ESTABLISH_CACHE_1(buffer)
char   *buffer;
{
 char    comparison_string1[3], comparison_string2[4];
 char    comparison_string3[5], comparison_string4[6];

 strcpy(comparison_string1, "it");
 strcpy(comparison_string2, "It");
 strcpy(comparison_string3, "iT");
 strcpy(comparison_string4, "IT");

 /*
  * If buffer begins with "Site:", insensitive to case, no trailing space
  * necessary, computed opaquely ...
  */
 if (strlen(buffer) > 5 &&
     (buffer[0] == 'S' || buffer[0] == 's') &&
     buffer[4] == ':' &&
     (buffer[3] == 'e' || buffer[3] == 'E') &&
     (!strncmp(comparison_string1, buffer + 1, 2) ||
      !strncmp(comparison_string2, buffer + 1, 2) ||
      !strncmp(comparison_string3, buffer + 1, 2) ||
      !strncmp(comparison_string4, buffer + 1, 2)))
  {
   strncpy(ESTABLISHED_CACHE, buffer, CACHE_SIZE);
   ESTABLISHED_CACHE[CACHE_SIZE - 1] = '\0';
   CACHE_IS_ESTABLISHED = 1;
  }
}



/*
 * jh,2/27/92.  Added g2ext_get_extra_device_table for non-VMS platforms since
 * it makes the logic a lot easier for all platforms.
 */
#ifndef vms
long
g2ext_get_extra_device_table(outbuffer)
char     *outbuffer;
{
 return (0L);
}
#endif




/* New: (MHD 7/3/00)

   g2ext_nsleep_next ("nsleep_next") is a C foreign function known to Lisp as
   c-nsleep-next.  It is to be called after a call to g2ext_nsleep (known to
   Lisp as c-nsleep), which returns the first machine ID, to obtain the second
   and subsequent available machine IDs, if any can be found.  This is not
   meaningfully implemented for all platforms at this time; on non-WIN32
   platforms, this finds nothing.  This is implemented for WIN32 in the release
   pending (7/3/00) primarily to support Rainbow Superpro dongle chains.  This
   has the same side effect and returns the same results as nsleep.  In
   addition, it allows all ethernet adaptors to join the dongles; previously,
   the presence of a dongle would prevent the caller from seeing an ethernet
   adaptor, and only the first ethernet adaptor of several (order undefined)
   would be seen.

   The code immediately below implements the stubbed out version of
   g2ext_nsleep_next.  The Win32 version comes below just above the Win32
   implementation of g2ext_nsleep.  */

#if !defined(WIN32)
long g2ext_nsleep_next(buffer)
     char *buffer;
{
  return(NSLEEP_FAILURE);
}
#endif



/**************
 * IBM RS6000 *
 **************/

#ifdef _IBMR2
#include <sys/utsname.h>

long g2ext_nsleep(buffer)
  char *buffer;
{
  struct utsname utsn;
  int i;

  MAYBE_ESTABLISH_CACHE(buffer);

  i = uname(&utsn);
  sprintf(buffer, utsn.machine);
  return(NSLEEP_SUCCESS);
}
#endif


/*******
 * SGI *
 *******/

#ifdef sgi

/* 7/8/94, mes: SGI tech support states that sysid returns the same string
 *   as that returned by the command   sysinfo -s
 */
long g2ext_nsleep(buffer)
  char *buffer;
{
  MAYBE_ESTABLISH_CACHE(buffer);

  sysid(buffer);
  return(NSLEEP_SUCCESS);
}
#endif



/***********
 * SUN OS 4*
 ***********/

#if defined(sun) && !defined(__SVR4)
#  include <stdio.h>
#  include <syscall.h>

long g2ext_nsleep(str)
char *str;
{
  MAYBE_ESTABLISH_CACHE(str);

  (void)sprintf( str, "%x", syscall(SYS_gethostid));
  return(NSLEEP_SUCCESS);
}
#endif


/*****************
 * SPARC SOLARIS *
 *****************/

#ifdef sun
#  include <sys/types.h>
#  include <sys/systeminfo.h>
long g2ext_nsleep(str)
char *str;
{
    unsigned long i;

    MAYBE_ESTABLISH_CACHE(str);

    sysinfo(SI_HW_SERIAL,str,16);
    i = atoi(str);
    if ( i > 0xffff )
        sprintf(str, "%x", (unsigned int)i);
    return(NSLEEP_SUCCESS);
}
#endif



/******
 * HP *
 ******/

#ifdef __hpux
#include <sys/utsname.h>

long g2ext_nsleep(str)
char *str;
{
  struct utsname uname_structure;

  MAYBE_ESTABLISH_CACHE(str);

  str[0] = 0;
  uname(&uname_structure);
  if ((uname_structure.idnumber[0]==0)
      || ((uname_structure.idnumber[0]=='0' &&
	   uname_structure.idnumber[1]==0)))
    {
      strcpy(str, "ERROR");
    }
  else
    {
      strcpy(str, uname_structure.idnumber);
    }
  return(NSLEEP_SUCCESS);
}
#endif




/*************************
 * Tru64 Unix (alphaosf) *
 *************************/

#if defined(__osf__) || defined(linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define IFREQCNT 64     /* need enough room for total number of possible
                         * interfaces, including aliases for LAT and DECnet
                         */

/* GENSYMCID-1370: G2 won't start on specific MAC address
 * Now Linux and Tru64 Unix share the same function for finding the first
 * valid/real network interface name (for computing the machine-id).
 */

long g2pvt_find_network_interface(s, name)
    int s;
    char *name;
{
    struct ifreq *ifr;
    struct ifreq ifreqs[IFREQCNT];
    struct ifreq tmp_ifr;
    struct ifconf ifc;
    char *maybe = NULL;     /* a device that might be it */

    /* Need to find a reasonable name for the device. */
    ifc.ifc_req = ifreqs;
    ifc.ifc_len = sizeof(ifreqs);
    if (ioctl(s, SIOCGIFCONF, &ifc) < 0) {
            /* perror("ioctl: SIOCGIFCONF"); */
            return(NSLEEP_FAILURE);
    }
    for(ifr = ifreqs; ifr < &ifreqs[IFREQCNT]; ifr++) {
        if(strlen(ifr->ifr_name) == 0) {
            if (maybe == NULL) {
                 /* perror("No network devices configured\n"); */
                    return(NSLEEP_FAILURE);
            } else
                    break;  /* check out maybe */
        } else {
            (void) strcpy(tmp_ifr.ifr_name, ifr->ifr_name);
            if (ioctl(s, SIOCGIFFLAGS, &tmp_ifr) < 0) {
                 /* perror("ioctl: SIOCGIFFLAGS"); */
                    return(NSLEEP_FAILURE);
            }
            if ((tmp_ifr.ifr_flags & (IFF_POINTOPOINT))
                 == (IFF_POINTOPOINT)) {
                continue; /* skip point to point */
            }
            if ((tmp_ifr.ifr_flags
                & (IFF_MULTICAST|IFF_BROADCAST))
                  != (IFF_MULTICAST|IFF_BROADCAST)) {
                continue;       /* skip CI, etc. */
            }
            if ((tmp_ifr.ifr_flags & (IFF_UP|IFF_RUNNING))
                 != (IFF_UP|IFF_RUNNING)) {
                /* Save this name, it might be the
                 * right one but just isn't up now.
                 */
                if (maybe == NULL)
                        maybe = ifr->ifr_name;
                continue;   /* not up and running */
            }
            (void)strcpy(name, tmp_ifr.ifr_name);
            maybe = NULL; /* found real one, clear maybe */
            break;
        }
    }

    if (maybe != NULL) {
        (void) strcpy(name, maybe);
    }

    return(NSLEEP_SUCCESS);
}

#endif

#if defined(__osf__)

long g2ext_nsleep(buf)
char *buf;
{
    int s;
    struct ifdevea ifdv;

    MAYBE_ESTABLISH_CACHE(buf);

    bzero(&ifdv, sizeof(struct ifdevea));
    if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
     /* perror("socket"); */
        return( -1);
    }

    if (g2pvt_find_network_interface(s, &ifdv.ifr_name) == NSLEEP_FAILURE) {
      close(s);
      return(NSLEEP_FAILURE);
    }

    if (ioctl(s, SIOCRPHYSADDR, &ifdv) < 0) {
         /* perror("ioctl: SIOCRPHYSADDR"); */
            close(s);
            return(NSLEEP_FAILURE);
    }

    close(s);

    sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x",
            (unsigned char) ifdv.default_pa[0],
            (unsigned char) ifdv.default_pa[1],
            (unsigned char) ifdv.default_pa[2],
            (unsigned char) ifdv.default_pa[3],
            (unsigned char) ifdv.default_pa[4],
            (unsigned char) ifdv.default_pa[5]);

    return(NSLEEP_SUCCESS);
}

#endif


/*********
 * LINUX *
 *********/

#ifdef linux

#include <unistd.h>

long
g2ext_nsleep(char *str)
{
  int fd;
  struct ifreq ifr;

  MAYBE_ESTABLISH_CACHE(str);

  bzero(&ifr, sizeof (struct ifreq));
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    return(NSLEEP_FAILURE);

  if (g2pvt_find_network_interface(fd, &ifr.ifr_name) == NSLEEP_FAILURE) {
    close(fd);
    return(NSLEEP_FAILURE);
  }

  /* Note: SIOCGIFHWADDR is part of LSB 3.1 but 3.0 */
  if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) {
    close(fd);
    return(NSLEEP_FAILURE);
  }

  /* GENSYMCID-578: G2 authorization 'sees' strange non-existent machine id under Linux.
     According to the struct definition of "sockaddr", ifr.ifr_hwaddr.sa_data[?] is of
     type "char", so when MAC address is bigger than 0x80 (128), as a signed char, a
     minus number will be passed to sprintf(), and elements like 0xf8 will be output as
     "fffffff8".  The solution is do force type convention to "unsigned char".
     -- Chun Tian (binghe), Glority, 2011/11/16
   */
  sprintf(str, "%x%x%x%x%x%x%x%x%x%x%x%x",
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[0] & 0xF0) >> 4,
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[1] & 0xF0) >> 4,
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[2] & 0xF0) >> 4,
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[3] & 0xF0) >> 4,
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[4] & 0xF0) >> 4,
	  ((unsigned char) ifr.ifr_hwaddr.sa_data[5] & 0xF0) >> 4,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[0] & 0xF,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[1] & 0xF,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[2] & 0xF,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[3] & 0xF,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[4] & 0xF,
	  (unsigned char) ifr.ifr_hwaddr.sa_data[5] & 0xF);

  close(fd);
  return(NSLEEP_SUCCESS);
}

#endif


/************
 * Mac OS X *
 ************/
#ifdef __APPLE__
long g2ext_nsleep(id)
char *id;
{
  MAYBE_ESTABLISH_CACHE(id);

  sprintf(id,"");
  return(NSLEEP_SUCCESS);
}

#endif


/*********
 * WIN32 *
 *********/

#ifdef WIN32

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define CHAIN_BUF_LEN 16
#define CHAIN_ELT_LEN 13

typedef struct
{
  int c_fill;
  int c_pos;
  char c_buf[CHAIN_BUF_LEN][CHAIN_ELT_LEN];
} chain_t;

static int enum_phys_addr (chain_t *);
static int enum_super_pro (chain_t *);

static chain_t *chain_init(chain_t *);
#ifdef NOT_YET
static chain_t *chain_copy(chain_t *, chain_t *);
#endif
static int chain_full(chain_t *);
static int chain_add(char *, chain_t *);
static int chain_sprintf_add(chain_t *, char *, ...);
static int chain_next(chain_t *, char *);


long g2ext_nsleep(char *);
long g2ext_nsleep_next(char *);

static chain_t global_chain;


/*
 * Subroutines for "chain" abstract data type.
 */

static chain_t *
chain_init(chain_t *chain)
{
  memset(chain, 0, sizeof(chain_t));

  return chain;
}

#ifdef NOT_YET
/*
 * If we ever run nsleep more than once, this can be used to compare chains.
 */
static chain_t *
chain_copy(chain_t *dst_chain, chain_t *src_chain)
{
  memcpy(dst_chain, src_chain, sizeof(chain_t));
}
#endif

static int
chain_full(chain_t *chain)
{
  return chain->c_fill == CHAIN_BUF_LEN ? 1 : 0;
}

static int
chain_add(char *string, chain_t *chain)
{
  if (chain->c_fill == CHAIN_BUF_LEN)
    return -1;

  strncpy(chain->c_buf[chain->c_fill],
	  string,
	  sizeof(char) * CHAIN_ELT_LEN);

  chain->c_fill++;

  return 0;
}

static int
chain_sprintf_add(chain_t *chain, char *format, ...)
{
  va_list ap;
  int n;

  if (chain->c_fill == CHAIN_BUF_LEN)
    return -1;

  va_start(ap, format);
  n = vsprintf(chain->c_buf[chain->c_fill], format, ap);
  va_end(ap);

  chain->c_fill++;

  return n;
}

static int
chain_next(chain_t *chain, char *string)
{
  if (chain->c_pos == chain->c_fill)
    return -1;

  strncpy(string,
	  chain->c_buf[chain->c_pos++],
	  sizeof(char) * CHAIN_ELT_LEN);

  return 0;
}

/*
 * Enumerators for Win32 machine id's.
 *
 * GENSYMCID-1701: Machine-id output changes after every restart
 */

/*
 * Enumerate physical addresses using Microsoft IP Helper API
 */
 
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

static int
enum_phys_addr(chain_t *chain)
{
    PIP_ADAPTER_INFO pAdapterInfo;
    IP_ADAPTER_INFO AdapterInfo[32];       // Allocate information for up to 32 NICs
    DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer
    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);                  
    int nErr;

    if (dwStatus != ERROR_SUCCESS) {
	return -1;
    }

    pAdapterInfo = AdapterInfo;
    while(pAdapterInfo)
    {
	if(pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)
	{
	    nErr = chain_sprintf_add(chain, "%.2x%.2x%.2x%.2x%.2x%.2x"
			, pAdapterInfo->Address[0]
			, pAdapterInfo->Address[1]
			, pAdapterInfo->Address[2]
			, pAdapterInfo->Address[3]
			, pAdapterInfo->Address[4]
			, pAdapterInfo->Address[5]
			);
	    if (nErr < 0) {
		return -1;
	    }
	}
	pAdapterInfo = pAdapterInfo->Next;
    }

    return 0;
}


/*
 * Canonical, exported, NSLEEP functionality.
 */

long
g2ext_nsleep(char *string)
{
  MAYBE_ESTABLISH_CACHE(string);

  chain_init(&global_chain);

  if (enum_phys_addr(&global_chain) != 0)
  {
    *string = '\0';
    return -1;
  }

  if (chain_next(&global_chain, string) != 0)
  {
    *string = '\0';
    return -1;
  }

  return 0;
}

long
g2ext_nsleep_next(char *string)
{
  return chain_next(&global_chain, string);
}


#endif /* WIN32 */
