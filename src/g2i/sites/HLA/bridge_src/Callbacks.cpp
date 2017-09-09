/***************************************************************************
 *
 *		Callbacks.c
 *
 *			Contains the required GSI callback functions. Several are
 *			not used in this project, but must be implemented in order
 *			to keep the compiler and linker happy.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/



#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>

#include	<RTI.hh>
#include	"G2Hla.h"

#include	"HLAClass.h"
#include	"HLAClassContainer.h"

extern RTI::RTIambassador		*rtiAmbP;
extern HLAClassContainer		hlaClassCache;



extern "C" {

	gsi_int gsi_get_tcp_port(void);
	void gsi_set_up(void);
	gsi_int gsi_initialize_context(char *remote_process_init_string, gsi_int length);
	void gsi_shutdown_context(void);
	void gsi_pause_context(void);
	void gsi_resume_context(void);
	void gsi_receive_registration(gsi_registration item_registration);
	void gsi_receive_deregistrations(gsi_registered_item registered_items[], gsi_int count);
	void gsi_get_data(gsi_registered_item registered_items[], gsi_int count);
	void gsi_set_data(gsi_registered_item registered_items[], gsi_int count);
	void gsi_g2_poll(void);
	void gsi_receive_message(char *message, gsi_int length);
}    


/*-------------------------------------------------------------------------*
 *
 *	This is our GSI error handler. We can use it to log all errors.
 *
 *-------------------------------------------------------------------------*/

void G2_ip_error_handler(gsi_int error_context,
						 gsi_int error_code, char *error_message)
{
	gsi_item	*itemP		= gsi_make_items(2);
	char		b[2048];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_ip_error_handler().\n");

	sprintf(b, "Error in context %d ; code = %d, Message = %s\n", error_context, error_code, error_message);
	log_with_timestamp(LOG_MODE_DEBUG, "GSI INTERNAL ERROR. %s\n", b);

	if (G2_Context >= 0 && G2_is_paused == FALSE) {

		gsi_set_sym( itemP[0], "GSI-INTERNAL-ERROR");
		gsi_set_str( itemP[1], b);

		gsi_rpc_start(G2_error_handler, itemP, G2_Context);
	}

	gsi_reclaim_items(itemP);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_ip_error_handler().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	This is our default RPC call receiver. It does peform any task
 *
 *-------------------------------------------------------------------------*/

void G2_rpc_call_receiver(gsi_item args[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering g2_rpc_call_receiver().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  g2_rpc_call_receiver().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Called upon startup to query the desired TCP/IP port
 *	GSI should be listen on.
 *
 *-------------------------------------------------------------------------*/

gsi_int gsi_get_tcp_port(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_get_tcp_port().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_get_tcp_port(). Returning: %d\n\n", TCPIP_PORT_NUMBER);

    return(TCPIP_PORT_NUMBER);
}



/*-------------------------------------------------------------------------*
 *
 *	Called upon startup for an initial setup after some internal
 *	GSI information has been setup.
 *
 *-------------------------------------------------------------------------*/

void gsi_set_up(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_set_up().\n");

	/*
	 *	Setup some default and re-usage variables
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;
	G2_joined_Federation= FALSE;

	local_gsi_itemP		= gsi_make_items( _NB_LOCAL_GSI_ITEMS );

	/*
	 *	Define our GSI error handler and select the single mode
	 */
	gsi_install_error_handler( G2_ip_error_handler );
	gsi_set_option( GSI_ONE_CYCLE );
	gsi_set_pause_timeout(50);

	/*
	 *	Declare the local Remote Procedure Calls G2 may call
	 */
	gsi_rpc_declare_local(G2_createAndJoinFederation,				"_HLA-CREATE-AND-JOIN-FEDERATION");
	gsi_rpc_declare_local(G2_resignAndDestroyFederation,			"_HLA-RESIGN-AND-DESTROY-FEDERATION");
	gsi_rpc_declare_local(G2_registerFederationSynchronizationPoint,"_HLA-REGISTER-FEDERATION-SYNCHRONIZATION-POINT");
	gsi_rpc_declare_local(G2_synchronizationPointAchieved,			"_HLA-SYNCHRONIZATION-POINT-ACHIEVED");

	gsi_rpc_declare_local(G2_publishObjectClass,					"_HLA-PUBLISH-OBJECT-CLASS");
	gsi_rpc_declare_local(G2_unpublishObjectClass,					"_HLA-UNPUBLISH-OBJECT-CLASS");
	gsi_rpc_declare_local(G2_subscribeObjectClassAttributes,		"_HLA-SUBSCRIBE-OBJECT-CLASS-ATTRIBUTES");
	gsi_rpc_declare_local(G2_unsubscribeObjectClass,				"_HLA-UNSUBSCRIBE-OBJECT-CLASS");

	gsi_rpc_declare_local(G2_disableClassRelevanceAdvisorySwitch,	"_HLA-DISABLE-CLASS-RELEVANCE-ADVISORY-SWITCH");
	gsi_rpc_declare_local(G2_enableClassRelevanceAdvisorySwitch,	"_HLA-ENABLE-CLASS-RELEVANCE-ADVISORY-SWITCH");

	gsi_rpc_declare_local(G2_publishInteractionClass,				"_HLA-PUBLISH-INTERACTION-CLASS");
	gsi_rpc_declare_local(G2_unpublishInteractionClass,				"_HLA-UNPUBLISH-INTERACTION-CLASS");
	gsi_rpc_declare_local(G2_subscribeInteractionClass,				"_HLA-SUBSCRIBE-INTERACTION-CLASS");
	gsi_rpc_declare_local(G2_unsubscribeInteractionClass,			"_HLA-UNSUBSCRIBE-INTERACTION-CLASS");

	gsi_rpc_declare_local(G2_registerObjectInstance,				"_HLA-REGISTER-OBJECT-INSTANCE");
	gsi_rpc_declare_local(G2_deleteObjectInstance,					"_HLA-DELETE-OBJECT-INSTANCE");
	gsi_rpc_declare_local(G2_getObjectInstanceName,					"_HLA-GET-OBJECT-INSTANCE-NAME");
	gsi_rpc_declare_local(G2_requestClassAttributeValueUpdate,		"_HLA-REQUEST-CLASS-ATTRIBUTE-VALUE-UPDATE");
	gsi_rpc_declare_local(G2_requestObjectAttributeValueUpdate,		"_HLA-REQUEST-OBJECT-ATTRIBUTE-VALUE-UPDATE");
	gsi_rpc_declare_local(G2_updateAttributeValues,					"_HLA-UPDATE-ATTRIBUTE-VALUES");

	gsi_rpc_declare_local(G2_sendInteraction,						"_HLA-SEND-INTERACTION");

	gsi_rpc_declare_local(G2_disableAttributeRelevanceAdvisorySwitch,"_HLA-DISABLE-ATTRIBUTE-RELEVANCE-ADVISORY-SWITCH");
	gsi_rpc_declare_local(G2_enableAttributeRelevanceAdvisorySwitch,"_HLA-ENABLE-ATTRIBUTE-RELEVANCE-ADVISORY-SWITCH");

	gsi_rpc_declare_local(G2_enableInteractionRelevanceAdvisorySwitch, "_HLA-ENABLE-INTERACTION-RELEVANCE-ADVISORY-SWITCH");
	gsi_rpc_declare_local(G2_disableInteractionRelevanceAdvisorySwitch,"_HLA-DISABLE-INTERACTION-RELEVANCE-ADVISORY-SWITCH");

	gsi_rpc_declare_local(G2_EnableTimeRegulation,					"_HLA-ENABLE-TIME-REGULATION");
	gsi_rpc_declare_local(G2_DisableTimeRegulation,					"_HLA-DISABLE-TIME-REGULATION");
	gsi_rpc_declare_local(G2_EnableTimeConstrained,					"_HLA-ENABLE-TIME-CONSTRAINED");
	gsi_rpc_declare_local(G2_DisableTimeConstrained,				"_HLA-DISABLE-TIME-CONSTRAINED");
	gsi_rpc_declare_local(G2_DisableAsynchronousDelivery,			"_HLA-DISABLE-ASYNCHRONOUS-DELIVERY");
	gsi_rpc_declare_local(G2_EnableAsynchronousDelivery,			"_HLA-ENABLE-ASYNCHRONOUS-DELIVERY");
	gsi_rpc_declare_local(G2_TimeAdvanceRequest,					"_HLA-TIME-ADVANCE-REQUEST");
	gsi_rpc_declare_local(G2_TimeAdvanceRequestAvailable,			"_HLA-TIME-ADVANCE-REQUEST-AVAILABLE");
	gsi_rpc_declare_local(G2_NextEventRequest,						"_HLA-NEXT-EVENT-REQUEST");
	gsi_rpc_declare_local(G2_NextEventRequestAvailable,				"_HLA-NEXT-EVENT-REQUEST-AVAILABLE");
	gsi_rpc_declare_local(G2_FlushQueueRequest,						"_HLA-FLUSH-QUEUE-REQUEST");
	gsi_rpc_declare_local(G2_QueryLBTS,								"_HLA-QUERY-LBTS");
	gsi_rpc_declare_local(G2_QueryFederateTime,						"_HLA-QUERY-FEDERATE-TIME");
	gsi_rpc_declare_local(G2_QueryMinNextEventTime,					"_HLA-QUERY-MIN-NEXT-EVENT-TIME");
	gsi_rpc_declare_local(G2_ModifyLookahead,						"_HLA-MODIFY-LOOKAHEAD");
	gsi_rpc_declare_local(G2_QueryLookahead,						"_HLA-QUERY-LOOKAHEAD");

	gsi_rpc_declare_local(G2_unconditionalAttributeOwnershipDivestiture,	"_HLA-UNCONDITIONAL-ATTR-OWNERSHIP-DIVESTITURE");
	gsi_rpc_declare_local(G2_negotiatedAttributeOwnershipDivestiture,		"_HLA-NEGOTIATE-ATTR-OWNERSHIP-DIVESTITURE");
	gsi_rpc_declare_local(G2_attributeOwnershipAcquisition,					"_HLA-ATTR-OWNERSHIP-ACQUISITION");
	gsi_rpc_declare_local(G2_attributeOwnershipAcquisitionIfAvailable,		"_HLA-ATTR-OWNERSHIP-ACQUISITION-IF-AVAILABLE");
	gsi_rpc_declare_local(G2_cancelNegotiatedAttributeOwnershipDivestiture,	"_HLA-CANCEL-NEGOTIATED-ATTR-OWNERSHIP-DIVESTITURE");
	gsi_rpc_declare_local(G2_cancelAttributeOwnershipAcquisition,			"_HLA-CANCEL-ATTR-OWNERSHIP-ACQUISITION");
	gsi_rpc_declare_local(G2_queryAttributeOwnership,						"_HLA-QUERY-ATTR-OWNERSHIP");
	gsi_rpc_declare_local(G2_isAttributeOwnedByFederate,					"_HLA-IS-ATTR-OWNED-BY-FEDERATE");
	gsi_rpc_declare_local(G2_attributeOwnershipReleaseResponse,				"_HLA-ATTR-OWNERSHIP-RELEASE-RESPONSE");

	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_set_up().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time a G2 KB requests a connections to this GSI
 *
 *-------------------------------------------------------------------------*/

gsi_int gsi_initialize_context(char *remote_process_init_string, gsi_int length)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_initialize_context().\n");

	/*
	 *	In this application, we only accept one conenction per bridge.
	 */
	if (G2_Context >= 0) {

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_initialize_context(). Denied additional G2 connection.\n\n");
		return (GSI_REJECT);
	}

	/*
	 *	And ensure the desired conenction context is valid
	 */
	if ((G2_Context = gsi_current_context()) < -1) {

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_initialize_context(). Denied G2 connection with invalid context.\n\n");
		return (GSI_REJECT);
	}


	/*
	 *	Declate the Remote Procedure Calls GSI may call
	 */
	gsi_rpc_declare_remote(	&G2_error_handler,
							"_HLA-CB-ERROR-HANDLER",
							G2_rpc_call_receiver, 2, 0, G2_Context);

	gsi_rpc_declare_remote(	&G2_synchronizationPointRegistrationSucceeded,
							"_HLA-CB-SYNCHRONIZATION-POINT-REGISTRATION-SUCCEEDED",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_synchronizationPointRegistrationFailed,
							"_HLA-CB-SYNCHRONIZATION-POINT-REGISTRATION-FAILED",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_announceSynchronizationPoint,
							"_HLA-CB-ANNOUNCE-SYNCHRONIZATION-POINT",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_federationSynchronized,
							"_HLA-CB-FEDERATION-SYNCHRONIZED",
							G2_rpc_call_receiver, 1, 0, G2_Context);

	gsi_rpc_declare_remote(	&G2_turnInteractionsOn,
							"_HLA-CB-TURN-INTERACTIONS-ON",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_turnInteractionsOff,
							"_HLA-CB-TURN-INTERACTIONS-OFF",
							G2_rpc_call_receiver, 1, 0, G2_Context);

	gsi_rpc_declare_remote(	&G2_startRegistrationForObjectClass,
							"_HLA-CB-START-REGISTRATION-FOR-OBJECT-CLASS",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_stopRegistrationForObjectClass,
							"_HLA-CB-STOP-REGISTRATION-FOR-OBJECT-CLASS",
							G2_rpc_call_receiver, 1, 0, G2_Context);

	gsi_rpc_declare_remote(	&G2_discoverObjectInstance,
							"_HLA-CB-DISCOVER-OBJECT-INSTANCE",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_removeObjectInstance,
							"_HLA-CB-REMOVE-OBJECT-INSTANCE",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_provideAttributeValueUpdate,
							"_HLA-CB-PROVIDE-ATTRIBUTE-VALUE-UPDATE",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_turnUpdatesOnForObjectInstance,
							"_HLA-CB-TURN-UPDATES-ON-FOR-OBJECT-INSTANCE",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_turnUpdatesOffForObjectInstance,
							"_HLA-CB-TURN-UPDATES-OFF-FOR-OBJECT-INSTANCE",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_reflectAttributeValues,
							"_HLA-CB-REFLECT-ATTRIBUTE-VALUES",
							G2_rpc_call_receiver, 5, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_receiveInteraction,
							"_HLA-CB-RECEIVE-INTERACTION",
							G2_rpc_call_receiver, 5, 0, G2_Context);

	gsi_rpc_declare_remote(	&G2_timeRegulationEnabled,
							"_HLA-CB-TIME-REGULATION-ENABLED",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_timeConstrainedEnabled,
							"_HLA-CB-TIME-CONSTRAINED-ENABLED",
							G2_rpc_call_receiver, 1, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_timeAdvanceGrant,
							"_HLA-CB-TIME-ADVANCE-GRANT",
							G2_rpc_call_receiver, 1, 0, G2_Context);


	gsi_rpc_declare_remote(	&G2_requestAttributeOwnershipAssumption,
							"_HLA-CB-REQUEST-ATTR-OWNERSHIP-ASSUMPTION",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_attributeOwnershipDivestitureNotification,
							"_HLA-CB-ATTR-OWNERSHIP-DIVESTITURE-NOTIFICATION",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_attributeOwnershipAcquisitionNotification,
							"_HLA-CB-ATTR-OWNERSHIP-ACQUISITION-NOTIFICATION",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_attributeOwnershipUnavailable,
							"_HLA-CB-ATTR-OWNERSHIP-UNAVAILABLE",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_requestAttributeOwnershipRelease,
							"_HLA-CB-REQUEST-ATTR-OWNERSHIP-RELEASE",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_confirmAttributeOwnershipAcquisitionCancellation,
							"_HLA-CB-CONFIRM-ATTR-OWNERSHIP-ACQUISITION-CANCELLATION",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_informAttributeOwnership,
							"_HLA-CB-INFORM-ATTR-OWNERSHIP",
							G2_rpc_call_receiver, 3, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_attributeIsNotOwned,
							"_HLA-CB-ATTR-IS-NOT-OWNED",
							G2_rpc_call_receiver, 2, 0, G2_Context);
	gsi_rpc_declare_remote(	&G2_attributeOwnedByRTI,
							"_HLA-CB-ATTR-OWNED-BY-RTI",
							G2_rpc_call_receiver, 2, 0, G2_Context);

	/*
	 *	And accept the connection
	 */
	log_with_timestamp(LOG_MODE_ENTRY_EXIT,
		"Leaving  gsi_initialize_context(). Accepted new G2 connection. Context: %d\n",
		G2_Context);


	return (GSI_ACCEPT);
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time a G2 KB requests a disconnect from this GSI
 *
 *-------------------------------------------------------------------------*/

void gsi_shutdown_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_shutdown_context().\n");

	if (G2_Context != gsi_current_context()) {

		log_with_timestamp(LOG_MODE_DEBUG,      "Shutdown for not connected and current context.\n");
		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_shutdown_context().\n\n");
		return;
	}


	/*
	 *	Try at leat to resign from federation. Maybe it has already been done
	 *	if G2 called the resign rpc. We do it here again in case the communication
	 *	breaks
	 */
	if (G2_joined_Federation == TRUE) {

		hlaClassCache.empty();
		G2_joined_Federation = FALSE;

		try
		{
			rtiAmbP->resignFederationExecution( RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES ); 
		}
		catch ( RTI::Exception& e )
		{
			log_with_timestamp(LOG_MODE_DEBUG, "Exception (%s, %s) while resigning from federation from within gsi_shutdown_context().\n",
					e._name, e._reason);
		}
	}


	/*
	 *	Reset context status
	 */
	G2_Context			= -1;
	G2_is_paused		= FALSE;
	G2_joined_Federation= FALSE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_shutdown_context().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time the G2 KB is paused
 *
 *-------------------------------------------------------------------------*/

void gsi_pause_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_pause_context().\n");

	G2_is_paused = TRUE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_pause_context().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Called each time the G2 KB is resumed
 *
 *-------------------------------------------------------------------------*/

void gsi_resume_context(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_resume_context().\n");

	G2_is_paused = FALSE;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_resume_context().\n\n");
}






/*-------------------------------------------------------------------------*
 *
 *	The following GSI callbacks are not used in this application.
 *	Only stub functions are defined to keep the compiler/linker happy.
 *
 *-------------------------------------------------------------------------*/

void gsi_receive_registration(gsi_registration item_registration)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_registration().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_registration().\n\n");
}


void gsi_receive_deregistrations(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_deregistrations().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_deregistrations().\n\n");
}


void gsi_get_data(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_get_data().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_get_data().\n\n");
}


void gsi_set_data(gsi_registered_item registered_items[], gsi_int count)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_set_data().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_set_data().\n\n");
}


void gsi_g2_poll(void)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_g2_poll().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_g2_poll().\n\n");
}


void gsi_receive_message(char *message, gsi_int length)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering gsi_receive_message().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  gsi_receive_message().\n\n");
}
