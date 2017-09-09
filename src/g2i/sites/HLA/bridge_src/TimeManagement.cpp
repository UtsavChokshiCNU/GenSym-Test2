/***************************************************************************
 *
 *		TimeManagement.cpp
 *
 *			Contains the G2 to GSI RPC functions related to HLA
 *			Time Management.
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
#include	<fedtime.hh>

#include	"G2Hla.h"

extern RTI::RTIambassador		*rtiAmbP;

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_EnableTimeRegulation(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theFederateTime,
					_theLookahead;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_EnableTimeRegulation().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theFederateTime = gsi_flt_of( args[0] );
	_theLookahead	 = gsi_flt_of( args[1] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theFederateTime( _theFederateTime);
	RTIfedTime theLookahead( _theLookahead);

	try {

		rtiAmbP->enableTimeRegulation( theFederateTime, theLookahead);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling time regulation.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableTimeRegulation().\n\n");

		return;
	}
	
	log_with_timestamp(LOG_MODE_DEBUG, "Time regulation enabled.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableTimeRegulation().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_DisableTimeRegulation(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_DisableTimeRegulation().\n");

	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableTimeRegulation();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling time regulation.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableTimeRegulation().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Time regulation disabled.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableTimeRegulation().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_EnableTimeConstrained(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_EnableTimeConstrained().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->enableTimeConstrained();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling time constrains.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableTimeConstrained().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Enabling Time constrained.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableTimeConstrained().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_DisableTimeConstrained(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_DisableTimeConstrained().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableTimeConstrained();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling time constrains.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableTimeConstrained().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Time constrained disabled.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableTimeConstrained().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_DisableAsynchronousDelivery(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_DisableAsynchronousDelivery().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableAsynchronousDelivery();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling asynchronous delivery.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableAsynchronousDelivery().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Asynchronous delivery disabled.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_DisableAsynchronousDelivery().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_EnableAsynchronousDelivery(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_EnableAsynchronousDelivery().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->enableAsynchronousDelivery();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling asynchronous delivery.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableAsynchronousDelivery().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Asynchronous delivery enabled.\n");


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_EnableAsynchronousDelivery().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_TimeAdvanceRequest(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_TimeAdvanceRequest().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theTime( _theTime);

	try {

		rtiAmbP->timeAdvanceRequest( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting time advance.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_TimeAdvanceRequest().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Time advance request to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_TimeAdvanceRequest().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_TimeAdvanceRequestAvailable(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_TimeAdvanceRequestAvailable().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theTime( _theTime);

	try {

		rtiAmbP->timeAdvanceRequestAvailable( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting time advance available.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_TimeAdvanceRequestAvailable().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Time advance request available to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_TimeAdvanceRequestAvailable().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_NextEventRequest(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_NextEventRequest().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theTime( _theTime);

	try {

		rtiAmbP->nextEventRequest( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting next event.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_NextEventRequest().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Next event request to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_NextEventRequest().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_NextEventRequestAvailable(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_NextEventRequestAvailable().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theTime( _theTime);

	try {

		rtiAmbP->nextEventRequestAvailable( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting next event available.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_NextEventRequestAvailable().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Next event request available to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_NextEventRequestAvailable().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_FlushQueueRequest(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_FlushQueueRequest().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );
	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime theTime( _theTime);

	try {

		rtiAmbP->flushQueueRequest( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while sending flush queue request.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_FlushQueueRequest().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Flush queue request to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_FlushQueueRequest().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_QueryLBTS(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTIfedTime	theTime;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_QueryLBTS().\n");

	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->queryLBTS( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting LBTS time.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryLBTS().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "LBTS Time = %f.\n", (double) theTime.getTime());


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) theTime.getTime());
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryLBTS().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_QueryFederateTime(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTIfedTime	theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_QueryFederateTime().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->queryFederateTime( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting Federate time.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryFederateTime().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "LBTS Time = %f.\n", (double) theTime.getTime());


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) theTime.getTime());
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryFederateTime().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_QueryMinNextEventTime(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTIfedTime	theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_QueryMinNextEventTime().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->queryMinNextEventTime( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting min next event time.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryMinNextEventTime().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Min next event time = %f.\n", (double) theTime.getTime());


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) theTime.getTime());
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryMinNextEventTime().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_ModifyLookahead(gsi_item args[], gsi_int count, gsi_int call_index)
{
	double			_theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_ModifyLookahead().\n");


	/*
	 *	Extract G2 arguments
	 */
	_theTime = gsi_flt_of( args[0] );	

	/*
	 *	Forward information to HLA
	 */
	RTIfedTime	theTime( _theTime);

	try {

		rtiAmbP->modifyLookahead( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting lookahead.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_ModifyLookahead().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Setting lookahead to %f.\n", _theTime);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_ModifyLookahead().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_QueryLookahead(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTIfedTime	theTime;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_QueryLookahead().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->queryLookahead( theTime );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting lookahead.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryLookahead().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Lookahead = %f.\n", (double) theTime.getTime());


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) theTime.getTime());
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_QueryLookahead().\n\n");
}

