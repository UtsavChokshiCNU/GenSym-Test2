#ifndef	_G2_HLA_H_
#define	_G2_HLA_H_

/***************************************************************************
 *
 *		G2_HLA.h
 *
 *			Contains global definitions used accros the whole application.
 *
 ***************************************************************************/



extern "C"
{
#include	<gsi_main.h>
}


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
			"G2 HLA Bridge Authorization has FAILED!\nPlease refer to your manual.\n\nContact Gensym at (781) 265 7106 for additional support.", \
			"G2 HLA Bridge",		\
			MB_OK | MB_ICONERROR);

#else

#define	GSI_AUTHORIZATION_ERROR		\
			printf("\n===============================================\n");	\
			printf(" G2 HLA Bridge Authorization has FAILED!\n");			\
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

//default initialization string for G2HLA_VERSION
#define	DEFAULT_G2HLA_VERSION		"V2.0 Rev. 0"

#define	TCPIP_PORT_NUMBER			20000

#define	_NB_LOCAL_GSI_ITEMS			8


#define	LOG_MODE_ENTRY_EXIT			0x0001
#define	LOG_MODE_IO_RCV				0x0002
#define	LOG_MODE_IO_SEND			0x0004
#define	LOG_MODE_DEBUG				0x0008
#define	LOG_MODE_ALARM_EVENT			0x0010

#define	LOG_FILE				0x0100
#define	LOG_STDERR				0x0200


/*-------------------------------------------------------------------------*
 *
 *	Definition of error messages & keywords
 *
 *-------------------------------------------------------------------------*/

#define NO_ERROR_SYM	"NO-ERROR"
#define NO_ERROR_TXT	""

#define	ERROR_EXCEPTION	"ERROR-EXCEPTION"
#define	ERROR_HLA_CLASS	"ERROR-NO-HLA-CLASS"


/*-------------------------------------------------------------------------*
 *
 *	Global Variables
 *
 *-------------------------------------------------------------------------*/

extern	long						log_indentation;


EXT	time_t							Bridge_start_time;
EXT BOOL							is_big_endian;

EXT	gsi_int							G2_Context;
EXT	BOOL							G2_is_paused;
EXT	BOOL							G2_joined_Federation;

EXT	gsi_item						*local_gsi_itemP;

EXT	char							error_msg[2048];

/*
     G2 HLA Bridge version string.
    Initialized by default by DEFAULT_G2HLA_VERSION.
    On Win32 platform G2HLA_VERSION has been initialized from resources.
 */
extern char							*G2HLA_VERSION;
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
EXT gsi_int	G2_synchronizationPointRegistrationSucceeded;
EXT gsi_int	G2_synchronizationPointRegistrationFailed;
EXT gsi_int	G2_announceSynchronizationPoint;
EXT gsi_int	G2_federationSynchronized;
EXT gsi_int	G2_startRegistrationForObjectClass;
EXT gsi_int	G2_stopRegistrationForObjectClass;
EXT gsi_int	G2_turnInteractionsOn;
EXT gsi_int	G2_turnInteractionsOff;
EXT gsi_int	G2_discoverObjectInstance;
EXT gsi_int	G2_removeObjectInstance;
EXT gsi_int	G2_provideAttributeValueUpdate;
EXT gsi_int	G2_turnUpdatesOnForObjectInstance;
EXT gsi_int	G2_turnUpdatesOffForObjectInstance;
EXT gsi_int	G2_reflectAttributeValues;
EXT gsi_int	G2_receiveInteraction;
EXT gsi_int	G2_timeRegulationEnabled;
EXT gsi_int	G2_timeConstrainedEnabled;
EXT gsi_int	G2_timeAdvanceGrant;

EXT gsi_int	G2_requestAttributeOwnershipAssumption;
EXT gsi_int	G2_attributeOwnershipDivestitureNotification;
EXT gsi_int	G2_attributeOwnershipAcquisitionNotification;
EXT gsi_int	G2_attributeOwnershipUnavailable;
EXT gsi_int	G2_requestAttributeOwnershipRelease;
EXT gsi_int	G2_confirmAttributeOwnershipAcquisitionCancellation;
EXT gsi_int	G2_informAttributeOwnership;
EXT gsi_int	G2_attributeIsNotOwned;
EXT gsi_int	G2_attributeOwnedByRTI;

/*-------------------------------------------------------------------------*
 *
 *	G2 to GSI RPC function prototypes
 *
 *-------------------------------------------------------------------------*/

extern void		G2_createAndJoinFederation(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_resignAndDestroyFederation(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_registerFederationSynchronizationPoint(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_synchronizationPointAchieved(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_publishObjectClass(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_unpublishObjectClass(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_subscribeObjectClassAttributes(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_unsubscribeObjectClass(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_disableClassRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_enableClassRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_publishInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_unpublishInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_subscribeInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_unsubscribeInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_registerObjectInstance(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_deleteObjectInstance(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_getObjectInstanceName(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_requestClassAttributeValueUpdate(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_requestObjectAttributeValueUpdate(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_updateAttributeValues(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_sendInteraction(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_disableAttributeRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_enableAttributeRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_enableInteractionRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_disableInteractionRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_EnableTimeRegulation(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_DisableTimeRegulation(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_EnableTimeConstrained(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_DisableTimeConstrained(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_DisableAsynchronousDelivery(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_EnableAsynchronousDelivery(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_TimeAdvanceRequest(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_TimeAdvanceRequestAvailable(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_NextEventRequest(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_NextEventRequestAvailable(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_FlushQueueRequest(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_QueryLBTS(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_QueryFederateTime(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_QueryMinNextEventTime(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_ModifyLookahead(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_QueryLookahead(gsi_item args[], gsi_int count, gsi_int call_index);

extern void		G2_unconditionalAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_negotiatedAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_attributeOwnershipAcquisition(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_attributeOwnershipAcquisitionIfAvailable(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_cancelNegotiatedAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_cancelAttributeOwnershipAcquisition(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_queryAttributeOwnership(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_isAttributeOwnedByFederate(gsi_item args[], gsi_int count, gsi_int call_index);
extern void		G2_attributeOwnershipReleaseResponse(gsi_item args[], gsi_int count, gsi_int call_index);


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
