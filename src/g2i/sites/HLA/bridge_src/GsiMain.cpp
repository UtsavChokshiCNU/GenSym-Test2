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

#include	<RTI.hh>
#include	<fedtime.hh>

#include	"G2Hla.h"

#include	"HLAClass.h"
#include	"HLAClassContainer.h"
#include	"G2FederateAmbassador.h"


/*-------------------------------------------------------------------------*
 *
 *
 *-------------------------------------------------------------------------*/

RTI::FederateHandle				federateId	= NULL;
RTI::RTIambassador				*rtiAmbP	= NULL;
G2FederateAmbassador				*fedAmbP	= NULL;
HLAClassContainer				hlaClassCache;


/*-------------------------------------------------------------------------*
 * G2HLA_VERSION global variable definition and initialization
 *-------------------------------------------------------------------------*/

char *G2HLA_VERSION = DEFAULT_G2HLA_VERSION;

/*-------------------------------------------------------------------------*
 *
 *	main:	main routine.
 *
 *-------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	long			i, j;
	long			_log_mode;
	char			*sP;
	char			bridge_ver[20];   // e.g. V6.0 (only V6 is checked)
	char			bridge_name[15];  // e.g. g2-oracle (don't think this is used for anything)


	/*
	 *	Keep Track of start time of the bridge
	 */
	Bridge_start_time = time(NULL);

	printf("\n------------------------------------------------------\n");
	printf(" Starting G2 HLA Bridge      Version %s\n", G2HLA_VERSION);
	printf("------------------------------------------------------\n\n");


	/*
	 *  Check Authorization (one time check when process starts)
	 */
	strcpy(bridge_name, "G2-HLA");
	strcpy(bridge_ver, G2HLA_VERSION);

	/*
	 *	Initialize variables
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;
	G2_joined_Federation= FALSE;


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

		j = strlen(argv[1]);

		for (i = 0; i < j ; i++) {

			switch( argv[1][i] ) {

				case '?':
					printf("\nG2 HLA Bridge %s.\n\n Compiled on %s, %s.\n\n",
							G2HLA_VERSION, __DATE__, __TIME__);
					printf(" Syntax:     G2_hla  [-{ersdawf}]  [TCP/IP port number]\n");
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
	 * Create RTI objects
	 *
	 * The federate communicates to the RTI through the RTIambassador
	 * object and the RTI communicates back to the federate through
	 * the FederateAmbassador object.
	 */
	RTI::RTIambassador       rtiAmb;         // libRTI provided
	G2FederateAmbassador     fedAmb;         // User-defined


	rtiAmbP = &rtiAmb;
	fedAmbP = &fedAmb;

											 
	/*
	 *	And this is our custom main loop.
	 */
	for ( ;; ) {

		log_indentation = 0;

		try {
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
			try {
				gsi_pause();
				gsi_run_loop();
			}
			catch ( RTI::Exception& e )
			{
				log_with_timestamp(LOG_MODE_DEBUG, "Exception (%s, %s) while in gsi_run_loop.",
						e._name, e._reason);
			}

			/*
			 * Tick will turn control over to the RTI so that it can
			 * process an event.  This will cause an invocation of one
			 * of the federateAmbassadorServices methods.
			 *
			 * Be sure not to invoke the RTIambassadorServices from the
			 * federateAmbassadorServices; otherwise, a ConcurrentAccess
			 * exception will be thrown.
			 */
			try {
/*
	#ifdef _DEBUG_ALL_
				log_without_timestamp(LOG_MODE_DEBUG, "Entering tick(0.01, 0.5)\n");
	#endif
*/
				rtiAmb.tick(0.01, 0.5);
/*
	#ifdef _DEBUG_ALL_
				log_without_timestamp(LOG_MODE_DEBUG, "Leaving  tick()\n\n");
	#endif
*/
			}
			catch ( RTI::Exception& e )
			{
				log_with_timestamp(LOG_MODE_DEBUG, "Exception (%s, %s) while calling tick().",
						e._name, e._reason);
			}
		}
		catch ( RTI::Exception& e )
		{
			log_with_timestamp(LOG_MODE_DEBUG, "Exception (%s, %s) while in main loop.",
					e._name, e._reason);
		}
	}

	return 0;
}

