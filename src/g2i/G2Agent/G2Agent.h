#ifndef	_G2_AGENT_H_
#define	_G2_AGENT_H_

/***************************************************************************
 *
 *		gagent.h
 *
 *			Contains global definitions used accros the whole application.
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 ***************************************************************************/



#ifdef	__cplusplus
extern "C" {
#endif

#include	<gsi_main.h>

#ifdef	__cplusplus
}
#endif


#include	"gsi_misc.h"



#include	"GlbDef.h"		/* Global data type definitions	*/




/*-------------------------------------------------------------------------*
 *
 *	System specific definitons and prototypes
 *
 *-------------------------------------------------------------------------*/

#ifndef	EXT
#define	EXT		extern
#endif


#ifdef WIN32
#define unlink(a)		_unlink(a)
#define access(a,b)		_access(a,b)
#define _sleep(a)		::Sleep(a * 1000)
#else
#include				<unistd.h>
#define _sleep(a)		sleep(a)
#endif


#ifdef WIN32

#define	GSI_AUTHORIZATION_ERROR		\
			(void) MessageBox( NULL,	\
			"G2 Agent Bridge Authorization has FAILED!\nPlease refer to your manual.\n\nContact Gensym at (781) 265 7106 for additional support.", \
			"G2 Agent Bridge",		\
			MB_OK | MB_ICONERROR);

#else

#define	GSI_AUTHORIZATION_ERROR		\
			printf("\n===============================================\n");	\
			printf(" G2 Agent Bridge Authorization has FAILED!\n");			\
			printf(" Please refer to your manual.\n\n");					\
			printf(" Contact Gensym at (781) 265 7106 for additional support.\n");\
			printf("===============================================\n\n");	\
			fflush(NULL);
#endif

/*-------------------------------------------------------------------------*
 *
 *	Global definition of constants
 *
 *-------------------------------------------------------------------------*/

#define	G2AGENT_VERSION				"V1.0 Rev. 0"

#define	TCPIP_PORT_NUMBER			22050

#define	_NB_LOCAL_GSI_ITEMS			10


#define	LOG_MODE_ENTRY_EXIT			0x0001
#define	LOG_MODE_IO_RCV				0x0002
#define	LOG_MODE_IO_SEND			0x0004
#define	LOG_MODE_DEBUG				0x0008
#define	LOG_MODE_ALARM_EVENT		0x0010

#define	LOG_FILE					0x0100
#define	LOG_STDERR					0x0200

#define ERR_MSG_SZ					2048

#define MAX_FPTRS					32
#define FILE_FREE					NULL
#define BAD_OPEN					0
#define OPEN_FAILED					-1

#define STRSZ						(1024 * 4)

/*-------------------------------------------------------------------------*
 *
 *	Definition of error messages & keywords
 *
 *-------------------------------------------------------------------------*/

#define NO_ERROR_SYM		"NO-ERROR"
#define NO_ERROR_TXT		""

#define	ERROR_EXCEPTION		"ERROR-EXCEPTION"
#define	ERROR_AGENT_CLASS	"ERROR-NO-AGENT-CLASS"

/*-------------------------------------------------------------------------*
 *
 *	Global Variables
 *
 *-------------------------------------------------------------------------*/

extern	long						log_indentation;


EXT	time_t							bridge_start_time;
EXT BOOL							is_big_endian;

EXT	gsi_int							G2_Context;
EXT	BOOL							G2_is_paused;

EXT	gsi_item						*local_gsi_itemP;

EXT FILE							*f_ptrs[MAX_FPTRS];

EXT	char							error_msg[2048];



/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/




/*-------------------------------------------------------------------------*
 *
 *	GSI to G2 RPC handler variables and function prototypes
 *
 *-------------------------------------------------------------------------*/

EXT gsi_int	G2_error_handler;

/*-------------------------------------------------------------------------*
 *
 *	G2 to GSI RPC function prototypes
 *
 *-------------------------------------------------------------------------*/

//extern void		G2_xxxx(gsi_item args[], gsi_int count, gsi_int call_index);

extern declare_gsi_rpc_local_fn(rpc_exit);
extern declare_gsi_rpc_local_fn(rpc_ping);

extern declare_gsi_rpc_local_fn(rpc_fopen_append);
extern declare_gsi_rpc_local_fn(rpc_fopen_read);
extern declare_gsi_rpc_local_fn(rpc_fopen_read_write);
extern declare_gsi_rpc_local_fn(rpc_fopen_write);

extern declare_gsi_rpc_local_fn(rpc_fclose);
extern declare_gsi_rpc_local_fn(rpc_fclose_all);
extern declare_gsi_rpc_local_fn(rpc_fread);
extern declare_gsi_rpc_local_fn(rpc_freadline);
extern declare_gsi_rpc_local_fn(rpc_fwrite);
extern declare_gsi_rpc_local_fn(rpc_fseek);
extern declare_gsi_rpc_local_fn(rpc_fstats);
extern declare_gsi_rpc_local_fn(rpc_fdelete);
extern declare_gsi_rpc_local_fn(rpc_frename);

extern declare_gsi_rpc_local_fn(rpc_create_directory);
extern declare_gsi_rpc_local_fn(rpc_directory_exists);

extern declare_gsi_rpc_local_fn(rpc_spawn_process);
extern declare_gsi_rpc_local_fn(rpc_kill_process);
extern declare_gsi_rpc_local_fn(rpc_process_exists);

extern declare_gsi_rpc_local_fn(rpc_add_log_event_source);
extern declare_gsi_rpc_local_fn(rpc_log_error_event);
extern declare_gsi_rpc_local_fn(rpc_log_warning_event);
extern declare_gsi_rpc_local_fn(rpc_log_information_event);
extern declare_gsi_rpc_local_fn(rpc_get_log_info);
extern declare_gsi_rpc_local_fn(rpc_get_log_entries);

/*-------------------------------------------------------------------------*
 *
 *	Internal functions
 *
 *-------------------------------------------------------------------------*/

extern ushort	swap_2byte_quantity( ushort  src);
extern ushort	swap_2byte_quantityP(ushort *srcP);
extern ulong	swap_4byte_quantity( ulong   src);
extern ulong	swap_4byte_quantityP(ulong  *srcP);
extern double	swap_8byte_quantity( double  src);
extern double	swap_8byte_quantityP(double *srcP);



/*-------------------------------------------------------------------------*
 *
 *	Debugging and logging function prototypes
 *
 *-------------------------------------------------------------------------*/

extern char		*bool_str_of(BOOL x);
extern void		log_setup(BOOL log_mode);
extern void		log_with_timestamp(long mode, char *fmt, ...);
extern void		log_without_timestamp(long mode, char *fmt, ...);
extern void		log_without_identation(long mode, char *fmt, ...);
extern void		log_non_zero_terminated_string(long mode, char *sP, long sz);
extern void		log_G2_object(long mode, gsi_item item);


#endif