/***************************************************************************
 *
 *		FederationManagement.c
 *
 *			Contains the G2 to GSI RPC functions related to HLA
 *			Federation Management.
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
#include	"G2FederateAmbassador.h"

extern RTI::FederateHandle		federateId;
extern RTI::RTIambassador		*rtiAmbP;
extern G2FederateAmbassador		*fedAmbP;
extern HLAClassContainer		hlaClassCache;


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_createAndJoinFederation(gsi_item args[], gsi_int count, gsi_int call_index)
{
	long			numTries  = 0;
	const char		*federationNameP;
	const char		*federateNameP;
	char *ghlaHomeP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_createAndJoinFederation().\n");

	/*
	 *	Ensure we are not already connected to HLA
	 */
	if (G2_joined_Federation == TRUE) {

		/*
		 *	Return error to G2
		 */
		gsi_set_sym(local_gsi_itemP[0], "ERROR-ALREADY-JOINED");
		gsi_set_str(local_gsi_itemP[1], "The bridge has already joined a federation. Resume from it before connecting.");
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_createAndJoinFederation(). Already joined a Federation.\n\n");

		return;
	}


	/*
	 *	Extract G2 arguments
	 */
	federationNameP = gsi_str_of( args[0] );
	federateNameP   = gsi_str_of( args[1] );

	// Initialize fedName
	ghlaHomeP = getenv("GHLA_HOME");

	const char* fedPath = DIR_SEP "resources" DIR_SEP "G2DemoFederation.fed";

	// Allocate memory on stack
	char* fedName = (char*)_alloca(strlen(fedPath) + strlen(ghlaHomeP) + 1);
	// Initialize
	strcpy(fedName, ghlaHomeP);
	strcat(fedName, fedPath);

	log_with_timestamp(LOG_MODE_DEBUG, "Creating Federation '%s', using config file '%s'\n",
			federationNameP, fedName);


	/*
	 *	Attempt creation of federation
	 */
	try
	{
		rtiAmbP->createFederationExecution( federationNameP, fedName ); 
	}
	catch ( RTI::FederationExecutionAlreadyExists& e )
	{
		log_with_timestamp(LOG_MODE_DEBUG, "Federation '%s' already exists\n", federationNameP);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while creating Federation '%s' using the config file '%s'.",
				e._name, e._reason, federationNameP, fedName);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_createAndJoinFederation().\n\n");

		return;
	}


	/*
	 *	Attempt to join the federation
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Joining Federation as Federate named '%s'\n", federateNameP);

	while ( G2_joined_Federation == FALSE && numTries < 20) {

		//numTries should be incremented
		++numTries;

		try
		{
			federateId = rtiAmbP->joinFederationExecution(federateNameP, federationNameP, fedAmbP);
			G2_joined_Federation = TRUE; 
		}
		catch (RTI::FederateAlreadyExecutionMember& e)
		{
			sprintf(error_msg, "Cannot join the federation. The federate '%s' already exists.",	federateNameP);

			log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


			gsi_set_sym(local_gsi_itemP[0], "ERROR-FEDERATE-EXISTS");
			gsi_set_str(local_gsi_itemP[1], error_msg);
			gsi_set_flt(local_gsi_itemP[2], 0.0);
			gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

			log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_createAndJoinFederation().\n\n");

			return;
		}
		catch (RTI::FederationExecutionDoesNotExist& e)
		{
			_sleep (2); // Wait for a while before retrying
		}
		catch ( RTI::Exception& e )
		{
			log_with_timestamp(LOG_MODE_DEBUG, "Exception (%s,%s) while joining Federate '%s'.\n",
				e._name, e._reason, federateNameP);
		}
	}


	/*
	 *	Ensure we are all set
	 */
	if (G2_joined_Federation == FALSE) {

		sprintf(error_msg, "Federate '%s' cannnot join federation '%s'.",
				federateNameP, federationNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_createAndJoinFederation().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Federation joined with Federate handle %d\n", federateId);



	/*
	 *	Return information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) federateId);
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_createAndJoinFederation().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_resignAndDestroyFederation(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char		*federationNameP;
	const char		*federateNameP;
	gsi_int			doDestroy;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_resignAndDestroyFederation().\n");


	/*
	 *	Ensure we are not already connected to HLA
	 */
	if (G2_joined_Federation == FALSE) {

		/*
		 *	Return error to G2
		 */
		gsi_set_sym(local_gsi_itemP[0], "ERROR-NOT-JOINED");
		gsi_set_str(local_gsi_itemP[1], "The bridge has not joined a federation.");
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_resignAndDestroyFederation(). The bridge has not joined a Federation.\n\n");

		return;
	}


	/*
	 *	Extract G2 arguments
	 */
	federationNameP = gsi_str_of( args[0] );
	federateNameP   = gsi_str_of( args[1] );
	doDestroy		= gsi_log_of( args[2] );


	/*
	 *	Resume Federation
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Federate '%s' is resuming from Federation '%s'\n",
									federateNameP, federationNameP);


	hlaClassCache.empty();
	G2_joined_Federation = FALSE;

	
	try
	{
		rtiAmbP->resignFederationExecution( RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES ); 
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while resuming from Federation '%s'.\n",
				e._name, e._reason, federationNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s.\n", error_msg);
		
		/*
		 *	Return error to G2
		 */
		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_resignAndDestroyFederation().\n\n");

		return;
	}


	/*
	 *	Destroy Federate
	 */
	if (doDestroy == GSI_TRUE) {

		try
		{
			rtiAmbP->destroyFederationExecution( federationNameP ); 
		}
		catch ( RTI::Exception& e )
		{
			sprintf(error_msg, "Exception (%s, %s) while destroying Federate '%s'.\n",
					e._name, e._reason, federateNameP);

			log_with_timestamp(LOG_MODE_DEBUG, "%s.\n", error_msg);
			
			/*
			 *	Return error to G2
			 */
			gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
			gsi_set_str(local_gsi_itemP[1], error_msg);
			gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

			log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_resignAndDestroyFederation().\n\n");

			return;
		}
	}


	/*
	 *	No errors occured
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);


	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_resignAndDestroyFederation().\n\n");
}








/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_registerFederationSynchronizationPoint(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char		*labelP;
	const char		*tagP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_registerFederationSynchronizationPoint().\n");

	/*
	 *	Extract G2 arguments
	 */
	labelP = gsi_str_of( args[0] );
	tagP   = gsi_str_of( args[1] );

	/*
	 *	Register the point with HLA
	 */
	try
	{
		rtiAmbP->registerFederationSynchronizationPoint(labelP, tagP);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while registering synchronization point '%s'.\n",
					e._name, e._reason, labelP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s.\n", error_msg);
		
		/*
		 *	Return error to G2
		 */
		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_registerFederationSynchronizationPoint().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Registering synchronization point '%s' with tag '%s'\n",
			labelP, tagP);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_registerFederationSynchronizationPoint().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_synchronizationPointAchieved(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char		*labelP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_synchronizationPointAchieved().\n");

	/*
	 *	Extract G2 arguments
	 */
	labelP = gsi_str_of( args[0] );

	
	/*
	 *	Forward information to HLA
	 */
	try
	{
		rtiAmbP->synchronizationPointAchieved(labelP);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while sending synchronization point '%s' achieved to HLA.\n",
				e._name, e._reason, labelP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s.\n", error_msg);
		
		/*
		 *	Return error to G2
		 */
		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);
		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_synchronizationPointAchieved().\n\n");

		return;
	}
	
	log_with_timestamp(LOG_MODE_DEBUG, "Synchronization point '%s' achieved\n",
			labelP);
	
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);


	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_synchronizationPointAchieved().\n\n");
}

