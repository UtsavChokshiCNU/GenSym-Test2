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

/*
#if defined(hp9000s300) || defined(hp9000s400) || defined(hp9000s700) || defined(hp9000s800)
#define hpux
#endif
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

#if !defined(sun) && !defined(masscomp) && !defined(_SEQUENT_)
#include <stdlib.h>
#endif

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



/* New: (MHD 7/3/00)

   g2ext_nsleep_next ("nsleep_next") is a C foreign function known to Lisp as
   c-nsleep-next.  It is to be called after a call to g2ext_nsleep (known to
   Lisp as c-nsleep), which returns the first mahcine ID, to obtain the second
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






/************
 * MASSCOMP *
 ************/

#ifdef masscomp
#include <sys/cpu.h>
#include <sinfo.h>

long g2ext_nsleep(buffer)
     char *buffer;
{
  struct si_packet Packet;	/* command packet to sinfo() */
  int Status;			/* from sinfo() */
  int Addr;			/* for SYMBOL access results */
  static char String[128];	/* results from sinfo() */
  struct sid_ST Sid;		/* Serial ID */

  MAYBE_ESTABLISH_CACHE(buffer);

  buffer[0] = '\0';
  Packet.link = SI_LINK_NULL;	/* one packet */
  Packet.binary_ident = SI_OBJ_TRANSLATE; /* we're passing in a string */
  Packet.string_ident = "sid";	/* and this is it's address */
  Packet.operation = SI_OP_RDATA;
  Packet.operands[0].address = (char *)&Sid;
  Packet.operands[0].size = sizeof(Sid);
  Packet.modifier = 0;		/* no fancy stuff */
  Status = sinfo(&Packet);	/* Status is struct si_status */
  if (Status >= 0) {
    sprintf(buffer, "%d-%d-%d-%d",
	    Sid.mfg_plant,
	    Sid.package_type,
	    Sid.system_type,
	    Sid.serial_number);
    return(NSLEEP_SUCCESS);
  }
  else {
    sprintf(buffer, "Error: no serial number");	/* "num" => "number" (MHD 4/4/95) */
    return(NSLEEP_FAILURE);
  }
}

#include <sys/signal.h>
long sigfpe_on_aviion()
{
	signal(SIGFPE,sigfpe_on_aviion);
	return(NSLEEP_SUCCESS);
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
 * VMS *
 *******/

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



#ifdef vms
#include <stdio.h>
#include <stdlib.h>

#include <descrip.h>

#include <iodef.h>
#include <ssdef.h>
#include <psldef.h>
#include <lnmdef.h>



#define NMA$C_PCLI_HWA 0x0488
/* = 1160 */

#ifndef False
#define False 0
#endif

#ifndef True
#define True 1
#endif

#ifndef Boolean
#define Boolean int
#endif

#define DUMMY 0
#define DEBUG 0


/*
 * Data Structures for IO calls
 */

/*
 * Structure of IO Status Block
 */
typedef struct
{
  unsigned short iostat;
  unsigned short transfer_sz;
  unsigned char filler1;
  unsigned char unit_status;
  unsigned char error_summary;
  unsigned char filler2;
} iostat_block_t;


/*
 * External Character Descriptor
 */
typedef union
{
  unsigned char b[512];
  unsigned short w[256];
} external_character_descriptor_t;

/*
 * Extended Character Descriptor
 */
typedef struct
{
  unsigned short length;
  unsigned char  dtype;
  unsigned char  class;
  unsigned char *address;
} extended_character_descriptor_t;


/*
 * Network Control Block Description structure
 */
typedef struct
{
  unsigned long ncb_size;
  char *ncb;
} ncb_description_t;





/*
 * The existing Ethernet cards.  This list must be maintained
 * according to hardware releases from DEC.
 */

/* jh, 5/29/91.  Added EXA0 and increased MAXDEVICES. */

#define MAXDEVICES 16
ncb_description_t network_device_name[MAXDEVICES] =
{
  { 5, "XQA0:"},
  { 5, "XEA0:"},
  { 5, "ESA0:"},
  { 5, "ETA0:"},
  { 5, "EXA0:"},
  { 5, "EZA0:"},  /* jh per rb, 6/91 */
  { 5, "ERA0:"},  /* jh on behalf of mes, for Alpha pc AXP 150, 2/25/94 */
  { 5, "EWA0:"},  /* jh, for Alpha PC bug HQ-153368, 12/19/94 */
  { 5, "EWA1:"},  /* jh, for Alpha PC bug HQ-179135, 1/25/95 */
  { 5, "ELA0:"},  /* ajs, for ATM adapters, see issue HQ-1641622, 10/28/97*/
  { 5, "     "},  /* 6 blanks, jh per dwr & blm, 6/19/91 */
  { 5, "     "},
  { 5, "     "},
  { 5, "     "},
  { 5, "     "},
  { 5, "     "}
};

/*
 * rxn pseudo-devices (see blm for details)
 */

struct dsc$descriptor_s rxn_logical_name_descriptor;
struct dsc$descriptor_s rxn_destination_descriptor;

rxn_ethernet_device_p(encoded_device_spec)
char     *encoded_device_spec;
{
 if (strlen(encoded_device_spec) == 8 &&
     encoded_device_spec[1] == '8' &&
     encoded_device_spec[3] == '8' &&
     encoded_device_spec[4] == '8' &&
     encoded_device_spec[7] == '8')
    return 1;
 else
    return(NSLEEP_SUCCESS);
}

rxn_device_active_p(encoded_device_spec)
char     *encoded_device_spec;
{
 if (encoded_device_spec[6] == '0' &&
     encoded_device_spec[0] == '2' &&
     encoded_device_spec[2] == '3' &&
     encoded_device_spec[5] == '6')
    return 1;
 else
    return(NSLEEP_SUCCESS);
}


long
g2ext_get_extra_device_table(outbuffer)
char     *outbuffer;
{
 char  inbuffer[100];
 int   result;
 short destination_length;
 char  name_table;
 char  access_mode;
 char  disable_mask = 0;
 char  logical_name_string[LNM$C_NAMLENGTH];
 char  destination_string[LNM$C_NAMLENGTH];

 strncpy(inbuffer+7, "LMT", 3);
 strncpy(inbuffer+3, "RXN", 3);

 inbuffer[0] = 'G';
 inbuffer[4] = 'G';
 inbuffer[2] = '$';
 inbuffer[6] = '3';
 inbuffer[1] = '2';
 inbuffer[10] = '\0';

 strcpy(logical_name_string, inbuffer);

 rxn_logical_name_descriptor.dsc$w_length = strlen(logical_name_string);
 rxn_logical_name_descriptor.dsc$a_pointer = &logical_name_string;
 rxn_logical_name_descriptor.dsc$b_dtype = DSC$K_DTYPE_T;
 rxn_logical_name_descriptor.dsc$b_class = DSC$K_CLASS_S;

 rxn_destination_descriptor.dsc$a_pointer = &destination_string;
 rxn_destination_descriptor.dsc$b_dtype = DSC$K_DTYPE_T;
 rxn_destination_descriptor.dsc$b_class = DSC$K_CLASS_S;
 rxn_destination_descriptor.dsc$w_length = LNM$C_NAMLENGTH;

 result = lib$sys_trnlog(
                         &rxn_logical_name_descriptor,
                         &destination_length,
                         &rxn_destination_descriptor,
                         &name_table,
                         &access_mode,
                         &disable_mask
                        );

 if (result == SS$_NORMAL)
    {
     destination_string[destination_length] = '\0';
     if (rxn_ethernet_device_p(destination_string) &&
         rxn_device_active_p(destination_string))
        {
         int i;

         outbuffer[17] = '\0';
         for (i = 2; i < 17; i+=3)
             outbuffer[i] = '-';
         strncpy(outbuffer+15, "83", 2);
         strncpy(outbuffer+12, "9E", 2);
         strncpy(outbuffer+9, "1C", 2);
         strncpy(outbuffer+6, "2B", 2);
         strncpy(outbuffer+3, "00", 2);
         strncpy(outbuffer, "08", 2);

         return (1L);
        }
    }
 return (0L);
}


#define MAXETHERIDLEN 20

int inform_action_elision_flagged = False;
#define ETHERNET_CARD_FOUND_ONCE inform_action_elision_flagged

char icp_compression_key[MAXETHERIDLEN];
#define CACHED_ETHERNET_ID icp_compression_key

long g2ext_nsleep(r_id)
  char *r_id;
{
  long int status = 0;
  int io_channel;	/* Can't declare as register */
  external_character_descriptor_t external_descriptor;
  extended_character_descriptor_t extended_descriptor;
  iostat_block_t iostat_block;
  char id[MAXETHERIDLEN];

  MAYBE_ESTABLISH_CACHE(r_id);

  /*
   * Get the Ethernet Card
   */
  { register Boolean ethernet_card_found = False;

    { register int i;
      for (i=0; ((i<MAXDEVICES) && (!(ethernet_card_found))); i++)
	{
	  status = SYS$ASSIGN (&network_device_name[i],
			       &io_channel, DUMMY, DUMMY);
	  if (status == SS$_NORMAL) ethernet_card_found = True;
	}
    }
    if (!(ethernet_card_found))
     {
      /* jh per blm, 1/20/92. */
      if (g2ext_get_extra_device_table(id) == 1)
       {
        strcpy ( r_id, id );
        return(NSLEEP_SUCCESS);
       }

      /*
       * jh, 4/1/92.  Added a branch which used a cached value for the machine
       * ID, if we get a machine ID at least once.  We think that getting a
       * channel to the ethernet card is unreliable on Vaxes running standalone,
       * since the Decnet manager occasionally locks the ethernet card in this
       * situation.  Since we don't think it is possible to "hot swap" ethernet
       * boards while a Vax is running, and since we think that it is difficult
       * to impossible to move the core image of a process to another machine or
       * to migrate a running process to another clustered machine, using a
       * cached value is acceptable here.
       */
      else
       {
        if (ETHERNET_CARD_FOUND_ONCE)
         {
          strcpy (r_id, CACHED_ETHERNET_ID);
          return (0);
         }
        else
         { /* jh, 3/25/92.  More accurate reporting in VMS. */
          printf("\nerror %d: device not found",
                 (errno == EVMSERR) ?  vaxc$errno : errno);
            exit(0);
         }
       }
     }
  }

  /*
   * Call QIOW to get the address
   */
  extended_descriptor.address = &external_descriptor;
  extended_descriptor.length = 512;
  status = SYS$QIOW(DUMMY,
		    io_channel,
		    (IO$_SENSEMODE | IO$M_CTRL),  /* = (0x0027 | 0x0200) */
		    &iostat_block,
		    DUMMY,
		    DUMMY,
		    DUMMY,
		    &extended_descriptor,
		    DUMMY,
		    DUMMY,
		    DUMMY,
		    DUMMY);
  /*  lib$signal(status,0); */

  /*
   * Assign the IO channel
   */
  sys$DASSGN (io_channel);

  /*
   * Print the Ethernet Address
   */
  { register int i;
    register Boolean continue_p = True;

    for (i = 0; ((i < iostat_block.transfer_sz) && (continue_p)); ) {
	if ((external_descriptor.w[i/2] & 0x0fff) == NMA$C_PCLI_HWA) {

		sprintf(id,"%02x-%02x-%02x-%02x-%02x-%02x",
		   external_descriptor.b[i+4],
		   external_descriptor.b[i+5],
		   external_descriptor.b[i+6],
		   external_descriptor.b[i+7],
		   external_descriptor.b[i+8],
		   external_descriptor.b[i+9]);

	    continue_p = False;
	  }

        /* jh per blm, 1/20/92. */
        if (g2ext_get_extra_device_table(id) == 1)
           continue_p = False;

	if ( (external_descriptor.w[i/2] & 0x1000) == 0 ) {
	    i = i + 6;
    }
	else {
	    i = i + external_descriptor.w[i/2 + 1] + 4;
	  }
      }
  }
  strcpy(CACHED_ETHERNET_ID, id);
  if (!ETHERNET_CARD_FOUND_ONCE)
     ETHERNET_CARD_FOUND_ONCE = True;

  strcpy ( r_id, id );
  return(NSLEEP_SUCCESS);
}
#endif




/**********
 * APOLLO *
 **********/

#ifdef apollo
#  include <stdio.h>
#  include <apollo/base.h>
#  include <apollo/proc2.h>
#  define NUMBER_OF_NODE_ID_BITS 20		/* => 0x000FFFFF */
#  define NODE_ID_MASK ( (1 << NUMBER_OF_NODE_ID_BITS) - 1 )
/*
 * NOTE:  According to the SR9.x Domain OS call manuals, for the low part
 * of a uid_$t, bits 0 thru 19 (20 bits) are for the node_id, and bits 20
 * thru 27 (8 bits) are reserved for future use (time stamping, or the like).
 * Thus, we have, strictly, 20 bits for the node_id (although it's defined
 * to be 32 bits) or 5 hex digits.  However, according to Apollo, bits
 * 20 thru 27 are 0's, we should have 2 more hex digits to play with.
 * According to Apollo, they might use up to 6 hex digits (24 bits) for node
 * id's in the near future (few years), thus using 24 bits is relatively
 * save - i.e. we can be pretty sure that we'll get unique numbers.
 * We will, however, stick with 20 bits (5 hex digits) until Apollo changes
 * it's node id limits.
 */
long g2ext_nsleep(str)
     char *str;
{
  uid_$t my_uid;

  MAYBE_ESTABLISH_CACHE(str);

  (void)proc2_$who_am_i(&my_uid);
  (void)sprintf(str, "%x", (NODE_ID_MASK & my_uid.low));
  return(NSLEEP_SUCCESS);
}
#endif





/********
 * i386 *
 ********/

#if defined(i386) && !defined(_SEQUENT_) && !defined(__WATCOMC__) && !defined(_nst) && !defined(linux)

#include<fcntl.h>
#include <sys/signal.h>

#define SERIESHI 0xc6
#define SERIESLO 0x21

long g2ext_nsleep(str)
char *str;
	{

         MAYBE_ESTABLISH_CACHE(str);

	 strcpy(str,"Gensym");
	 return(NSLEEP_SUCCESS);
/*	int fd, code;
	unsigned char buf[128];
	if((fd = open("/dev/sentinel", O_RDONLY)) == -1)
		{
		sprintf(str, "ERROR: Dev Open");
		printf("ERROR: Dev Open\n");
		return(NSLEEP_SUCCESS);
		}
	ioctl(fd, 0, &code);
	if(code != 828172)
		{
		sprintf(str, "ERROR: Bad Driver");
		printf("ERROR: Bad Driver\n");
		close(fd);
		return(NSLEEP_SUCCESS);
		}
	if(read(fd, buf, 128) != 128)
		{
		close(fd);
		sprintf(str, "ERROR: Dev Read");
		printf("ERROR: Dev Read\n");
		return(NSLEEP_SUCCESS);
		}
	if((buf[126] != SERIESHI) || (buf[127] != SERIESLO))
		{
		close(fd);
		sprintf(str, "ERROR: Foreign Key");
		printf("ERROR: Foreign Key\n");
		return(NSLEEP_SUCCESS);
		}
	close(fd);
	strncpy(str, buf, 31);
	str[31] = '\0';
	return(1);
*/
	}


/*
 * sigfpe_on_386
 */

sigfpe_on_386()
{
	signal(SIGFPE,sigfpe_on_386);
	return(NSLEEP_SUCCESS);
}

#endif







/******************************************
 * DATA GENERAL AVIION - DGUX 4.20 and up *
 ******************************************/

#if defined(DGUX) || defined(motorola) && !defined(i386)

/* mes - 5/13/93: For now, we'll pretend that the motorola is an Aviion with
   minor differences.
 */

#ifdef motorola
#include <unistd.h>
#else
#include <sys/_int_unistd.h>
#endif

#include <sys/m88kbcs.h>
#include <sys/signal.h>

long g2ext_nsleep(str)
char *str;
{
  MAYBE_ESTABLISH_CACHE(str);

  (void)sprintf( str, "%x", sysconf(_SC_BCS_SYS_ID));
  return(NSLEEP_SUCCESS);
}


/*
 * sigfpe_on_aviion
 * The AViion produces a floating point exception instead of returning not a
 * number, or some other IEEE extreme float.  We can recognize extreme floats in
 * the ibcl-extreme-float-p function (in PRIMITIVES), and so are establishing
 * our own error handler here.
 */

sigfpe_on_aviion()
{
	signal(SIGFPE,sigfpe_on_aviion);
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
        sprintf(str, "%x", i);
    return(NSLEEP_SUCCESS);
}
#endif


/*******
 * NEC *
 *******/

#if defined(nec)
#  include <limits.h>
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
        sprintf(str, "%x", i);
    return(NSLEEP_SUCCESS);
}
#endif



/*******
 * NCR *
 *******/

#if defined(_nst)
# include <fcntl.h>
# include <sys/types.h>
# include <sys/inline.h>
# include <sys/stream.h>
# include <sys/stropts.h>
# include <sys/dlpi.h>

# include <sys/xdlpi.h>
# include <sys/ild.h>

long g2ext_nsleep(str)
char *str;
{
  struct strioctl ic;
  int slot;
  int ppa = 0;
  int fd;
  int indx;
  boarddata_t brd[20];
  ushort brdid;
  int ret_stat = -1;

  MAYBE_ESTABLISH_CACHE(str);

  memset(brd,0,sizeof(brd));

  if ((fd=open("/dev/lan",O_RDWR)) < 0) {
    return (ret_stat);
  }

  ic.ic_cmd = ILD_RCONFIG;
  ic.ic_timout = 10;
  ic.ic_len = sizeof(brd);
  ic.ic_dp = (char *)brd;

  if (ioctl(fd,I_STR,&ic) < 0) {
    close(fd);
    return (ret_stat);
  }

  close(fd);

  for (slot = 0; slot < 20; slot++) {
    brdid = (brd[slot].pos[1]<<8 | brd[slot].pos[0]);
    if (brdid != 0) {
      ret_stat = 0;
      sprintf(str, "%02x%02x%02x%02x%02x%02x",
	      brd[slot].bia[0],
	      brd[slot].bia[1],
	      brd[slot].bia[2],
	      brd[slot].bia[3],
	      brd[slot].bia[4],
	      brd[slot].bia[5]);
    }
  }

  return(ret_stat);		/* NSLEEP_SUCCESS reported by
				   any non-negative integer */
}

#endif /* NCR */


/******
 * HP *
 ******/

#ifdef hpux
# ifndef hp9000s800
#  include <stdio.h>
#  include <errno.h>
#  include <sys/ioctl.h>
#  include <fcntl.h>
#  include <sys/hilioctl.h>
# endif
#endif

/* For the msleep() function */
/*  msleep() is no longer used from Lucid 2.15 upward.  -pto 09may89
#ifdef hpux
#  include <signal.h>
#endif
*/





#ifdef __hpux
# ifndef __hp9000s800
/* The series 800 does not have an ID module. */
long g2ext_nsleep(str)
char *str;
{
  unsigned char arg[20], product_let, country;
  int fd, p_num,s_num,s_hi,s_lo;

  MAYBE_ESTABLISH_CACHE(str);

  fd = open ("/dev/hil1", O_RDONLY);

  if (fd < 0)
   {
    /* jh, 1/14/92.  I'm told you can place a non-number here. */
    strcpy(str, "ERROR: No ID module");
    return(NSLEEP_FAILURE);
   }

  if (ioctl(fd, HILID, arg) < 0) return (-2);

  if (ioctl(fd, HILSC, arg) < 0) return (-3);

  p_num = arg[1] | arg [2] << 8 |
             (arg[3] >> 7) << 16;

  product_let = arg[3] & 0x7f;
  s_num = arg[4] | arg [5] << 8 |
             arg[6] << 16 | (arg[7] & 0x3f) << 24;

  s_hi = s_num /100000;
  s_lo = s_num - s_hi * 100000;

  country = arg [8] & 0x7f;

  sprintf(str, "%u%c%.5u", s_hi, country, s_lo);
  close (fd);
  return(NSLEEP_SUCCESS);

}
# endif
#endif





#ifdef __hp9000s800
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






/*
 *	Millisecond Sleep.
 *
 *    Does a process sleep for a specified time.
 *
 *    returns 0
 */

/*
 * Millisecond sleep taken out for G2 1.11C and above.
 */

/*
#ifdef hpux
int alarm_set;
int alarm_handler()
{
 signal (SIGALRM, alarm_handler);
 alarm_set = 0;
 return (1);
}
#endif
*/

/*
 * No longer used:
#ifdef hpux
int msleep (millitime)
int millitime;
{
  int microtime;
  struct itimerval rttimer;
  struct itimerval old_rttimer;


  microtime = 1000 * millitime;
  rttimer.it_value.tv_sec = 0;
  rttimer.it_value.tv_usec = microtime;
  rttimer.it_interval.tv_sec = 0;
  rttimer.it_interval.tv_usec = microtime;

  signal (SIGALRM, alarm_handler);

  alarm_set = 1;

  if (millitime > 10) {
    setitimer (ITIMER_REAL, &rttimer, &old_rttimer);
    if (alarm_set == 1) pause();
  }
  rttimer.it_value.tv_usec = 0;
  rttimer.it_interval.tv_usec = 0;
  setitimer (ITIMER_REAL, &rttimer, &old_rttimer);

  return (0);
}
#endif
*/






/***********************
 * Ultrix and Tru64 Unix (alphaosf) *
 ***********************/

#if defined(ultrix) || defined(__osf__)

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define IFREQCNT 64     /* need enough room for total number of possible
                         * interfaces, including aliases for LAT and DECnet
                         */
long g2ext_nsleep(buf)
char *buf;
{
    int s;
    struct ifdevea ifdv;
    struct ifreq *ifr;
    struct ifreq ifreqs[IFREQCNT];
    struct ifreq tmp_ifr;
    struct ifconf ifc;
    char *maybe = NULL;     /* a device that might be it */

    MAYBE_ESTABLISH_CACHE(buf);

    bzero(&ifdv, sizeof(struct ifdevea));
    if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
     /* perror("socket"); */
        return( -1);
    }

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
                    close(s);
                    return(NSLEEP_FAILURE);
            } else
                    break;  /* check out maybe */
        } else {
            (void) strcpy(tmp_ifr.ifr_name, ifr->ifr_name);
            if (ioctl(s, SIOCGIFFLAGS, &tmp_ifr) < 0) {
                 /* perror("ioctl: SIOCGIFFLAGS"); */
                    close(s);
                    return(NSLEEP_FAILURE);
            }
            if ((tmp_ifr.ifr_flags & (IFF_POINTOPOINT))
                 == (IFF_POINTOPOINT)) {
                continue; /* skip point to point */
            }
#  ifdef ultrix
            if ((tmp_ifr.ifr_flags
                & (IFF_DYNPROTO|IFF_BROADCAST))
                  != (IFF_DYNPROTO|IFF_BROADCAST)) {
                continue;       /* skip CI, etc. */
            }
#  endif /* ultrix */
#  ifdef __osf__
            if ((tmp_ifr.ifr_flags
                & (IFF_MULTICAST|IFF_BROADCAST))
                  != (IFF_MULTICAST|IFF_BROADCAST)) {
                continue;       /* skip CI, etc. */
            }
#  endif /* osf */
            if ((tmp_ifr.ifr_flags & (IFF_UP|IFF_RUNNING))
                 != (IFF_UP|IFF_RUNNING)) {
                /* Save this name, it might be the
                 * right one but just isn't up now.
                 */
                if (maybe == NULL)
                        maybe = ifr->ifr_name;
                continue;   /* not up and running */
            }
            (void)strcpy(ifdv.ifr_name, tmp_ifr.ifr_name);
            maybe = NULL; /* found real one, clear maybe */
            break;
        }
    }

    if (maybe != NULL) {
        (void) strcpy(ifdv.ifr_name, maybe);
    }
    if (ioctl(s, SIOCRPHYSADDR, &ifdv) < 0) {
         /* perror("ioctl: SIOCRPHYSADDR"); */
            close(s);
            return(NSLEEP_FAILURE);
    }

    close(s);

    sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x",
             ifdv.default_pa[0], ifdv.default_pa[1], ifdv.default_pa[2],
             ifdv.default_pa[3], ifdv.default_pa[4], ifdv.default_pa[5]);

    return(NSLEEP_SUCCESS);
}

#endif


/*********
 * LINUX *
 *********/

#ifdef linux

#include <unistd.h>
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
  int err1, err2;

  MAYBE_ESTABLISH_CACHE(string);

  chain_init(&global_chain);

  err2 = enum_phys_addr(&global_chain);

  if (err1 != 0 && err2 != 0)
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
