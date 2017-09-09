/***************************************************************************
 *
 *		Gsi_Main.c
 *
 *			Contains main() function called upon startup to start
 *			GSI and the event dispatcher.
 *
 *
 *		Compilation Define Flags:
 *			_DEBUG_ALL_
 *					if defined additional debugging & tracing
 *					messages are added to the log files.
 *
 *			WIN32
 *					Needs to be defined in order to compile the bridge
 *					for Windows NT.
 *
 *			__STDC__
 *					Needs to be defined at all times in order to properly
 *					build the bridge.
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/




/*
 *	The global variables in G2_Ip.h as extern by default, If EXT is
 *	defined before including this file, we will declare the variables
 *	and therefore allocate space for them. We use this technique to
 *	avoid typing the names several times and generate typo errors.
 */
#define		EXT	

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>

#include	"G2Agent.h"



/*-------------------------------------------------------------------------*
 *
 *
 *-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*
 *
 *	main:	main routine.
 *
 *-------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	long			i, j, n;
	long			_log_mode;
	char			*sP;
	char			bridge_ver[20];   // e.g. V6.0 (only V6 is checked)
	char			bridge_name[15];  // e.g. g2-oracle (don't think this is used for anything)


	/*
	 *	Keep Track of start time of the bridge
	 */
	bridge_start_time = time(NULL);

	printf("\n");
	printf("---------------------------------------------------\n");
	printf(" Starting G2 Agent Bridge    Version %s\n", G2AGENT_VERSION);
	printf("---------------------------------------------------\n\n");


	/*
	 *  Check Authorization (one time check when process starts)
	 */
	strcpy(bridge_name, "G2-AGENT");
	strcpy(bridge_ver, G2AGENT_VERSION);

	/*
	 *	Initialize variables
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;

	for (i = 1 ; i < MAX_FPTRS ; i++) {
		f_ptrs[i] = FILE_FREE;
	}

	/*
	 *	Determine if we are running on a little or big Endian machine
	 */
	i  = 0x1234;
	sP = (char *) &i;

	if (sP[0] == 0x34)		is_big_endian = FALSE;
	else					is_big_endian = TRUE;



	/*
	 *	Extract command line arguments
	 */
	_log_mode = 0;

	if (argc > 1) {

		for (j = 1 ; j < argc ; j++) {

			n = strlen(argv[j]);

			if (n > 0 && argv[j][0] == '-') {

				for (i = 0; i < n ; i++) {

					switch( argv[j][i] ) {

						case '?':
							printf("\nG2 Agent Bridge %s.\n\n Compiled on %s, %s.\n\n",
								G2AGENT_VERSION, __DATE__, __TIME__);
							printf(" Syntax:     gagent [TCP/IP port number] [-{ersdawf}]\n");
							printf(" Options:\n");
							printf("  e    enable entry/exit logging\n");
							printf("  r    enable receive I/O logging\n");
							printf("  s    enable send I/O logging\n");
							printf("  d    enable debug logging\n");
							printf("  a    enable alarm logging\n");
							printf("  w    log messages to stdout\n");
							printf("  f    log messages to file\n\n");

							exit(0);

							break;
						case 'e':
							_log_mode |= LOG_MODE_ENTRY_EXIT;
							break;
						case 'r':
							_log_mode |= LOG_MODE_IO_RCV;
							break;
						case 's':
							_log_mode |= LOG_MODE_IO_SEND;
							break;
						case 'd':
							_log_mode |= LOG_MODE_DEBUG;
							break;
						case 'a':
							_log_mode |= LOG_MODE_ALARM_EVENT;
							break;
						case 'f':
							_log_mode |= LOG_FILE;
							break;
						case 'w':
							_log_mode |= LOG_STDERR;
							break;
						case '-':
							break;
					}
				} 
			}

		}
	}
	
	/*
	 *	Setup the bridge operation mode
	 */
	log_setup(_log_mode);



	/*
	 *  Set the version control variables to the values defined in gsi_main.h. 
	 *  Though optional, this is recommended to ensure version consistency between
	 *  the GSI object libraries, and the include file used to compile your
	 *  application code.
	 */
#if GSI_INCLUDE_MAJ_VER_NUM > 4L

	gsi_set_include_file_version(		GSI_INCLUDE_MAJ_VER_NUM, 
										GSI_INCLUDE_MIN_VER_NUM,
										GSI_INCLUDE_REV_VER_NUM);
	GSI_SET_OPTIONS_FROM_COMPILE();
	GSI_INITIALIZE_DLL_CALLBACKS;

#else

	gsi_include_file_major_version		= GSI_INCLUDE_MAJ_VER_NUM;
	gsi_include_file_minor_version		= GSI_INCLUDE_MIN_VER_NUM;

#ifdef GSI_INCLUDE_REV_VER_NUM
	gsi_include_file_revision_version	= GSI_INCLUDE_REV_VER_NUM;
#endif

#endif


	/*
	 *  Initialize GSI. Since we are going to select the GSI signal mode
	 *	in gsi_set_up(), gsi_start() is going to return and we can build
	 *	our own main loop. This is necessary to dispatch and process G2
	 *	and DecMsgQ messages.
	 */
	gsi_start(argc,argv);


											 
	/*
	 *	And this is our custom main loop.
	 */
	for ( ;; ) {

		log_indentation = 0;

		/*
		 *	Check the heap
		 */
#ifdef _DEBUG_ALL_

		i = _heapchk();

		switch( i )   {
			default:
				log_with_timestamp(LOG_MODE_DEBUG, "**ERROR** Heap corruption detected. Error code %d.\n", i);
				break;
			case _HEAPOK:
				break;
			case _HEAPEMPTY:
				log_with_timestamp(LOG_MODE_DEBUG, "**ERROR** Heap corruption detected. Error code %d - heap is empty.\n", i);
				break;
			case _HEAPBADBEGIN:
				log_with_timestamp(LOG_MODE_DEBUG, "**ERROR** Heap corruption detected. Error code %d - bad start of heap.\n", i);
				break;
			case _HEAPBADNODE:
				log_with_timestamp(LOG_MODE_DEBUG, "**ERROR** Heap corruption detected. Error code %d - bad node in heap\n", i);
				break;
		}
#endif

		/*
		 *	Wait for G2 events and dispatch them
		 */
		gsi_pause();
		gsi_run_loop();
	}

	return 0;
}

