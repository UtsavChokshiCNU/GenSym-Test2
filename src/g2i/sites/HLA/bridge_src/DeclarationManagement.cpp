/***************************************************************************
 *
 *		DeclarationManagement.c
 *
 *			Contains the G2 to GSI RPC functions related to HLA
 *			Declaration Management.
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


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_publishObjectClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char					*hlaClassNameP;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::ObjectClassHandle		hlaClassHandle;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	double						*attrHandlesP;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_publishObjectClass().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaClassNameP = gsi_str_of( args[0] );
	numAttrNames  = gsi_element_count_of( args[2] );
	attrNamesP    = (const char **) gsi_sym_array_of( args[2] );


	/*
	 *	Assign a HLA handle for this new class
	 */
	try {
		hlaClassHandle = rtiAmbP->getObjectClassHandle( hlaClassNameP );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting handle for HLA object class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishObjectClass().\n\n");

		return;
	}

	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP == NULL) {

		hlaClassP = new HLAClass(hlaClassNameP, hlaClassHandle, FALSE);
		hlaClassP->setMasterG2Object(args[1]);
		hlaClassP->setHlaClassAttributes(numAttrNames, attrNamesP);


		hlaClassCache.add( hlaClassP );
	}

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Publishing HLA Object Class '%s' with HLA attributes: ",
					hlaClassNameP);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);
	attrHandlesP  = new double[numAttrNames];

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		attrHandlesP[i] = (double) hlaAttrHandle;

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->publishObjectClass( hlaClassHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
		delete [] attrHandlesP;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while publishing HLA object class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishObjectClass().\n\n");

		return;
	}


	log_with_timestamp(LOG_MODE_DEBUG, "Published HLA Object Class '%s' with handle %d.\n",
					hlaClassNameP, hlaClassHandle);

	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(		local_gsi_itemP[2], hlaClassHandle);
	gsi_set_flt_array(	local_gsi_itemP[3], attrHandlesP, numAttrNames);
	gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");

	gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
	delete [] attrHandlesP;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishObjectClass().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_unpublishObjectClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectClassHandle	hlaClassHandle;
	HLAClass					*hlaClassP;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_unpublishObjectClass().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle = (RTI::ObjectClassHandle) gsi_flt_of( args[0] );


	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP != NULL)
		hlaClassCache.remove( hlaClassP );


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->unpublishObjectClass( hlaClassHandle );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while unpublishing HLA object class with handle '%d'.",
					e._name, e._reason, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unpublishObjectClass().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Unpublished HLA Object Class with handle %d.\n",
					hlaClassHandle);
	
	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unpublishObjectClass().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_subscribeObjectClassAttributes(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char					*hlaClassNameP;
	const char					**attrNamesP;
	long						i, numAttrNames;
	gsi_int						activeG2;
	RTI::Boolean				activeHLA;
	RTI::ObjectClassHandle		hlaClassHandle;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	double						*attrHandlesP;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_subscribeObjectClassAttributes().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaClassNameP = gsi_str_of( args[0] );
	numAttrNames  = gsi_element_count_of( args[2] );
	attrNamesP    = (const char **) gsi_sym_array_of( args[2] );
	activeG2      = gsi_log_of(args[3] );
	

	/*
	 *	Assign a HLA handle for this new class
	 */
	try {
		hlaClassHandle = rtiAmbP->getObjectClassHandle( hlaClassNameP );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting handle for HLA object class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeObjectClassAttributes().\n\n");

		return;
	}

	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP == NULL) {

		hlaClassP = new HLAClass(hlaClassNameP, hlaClassHandle, FALSE);
		hlaClassP->setMasterG2Object(args[1]);
		hlaClassP->setHlaClassAttributes(numAttrNames, attrNamesP);

		hlaClassCache.add( hlaClassP );
	}

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Subscribing to HLA Object Class '%s' with HLA attributes: ",
					hlaClassNameP);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);
	attrHandlesP  = new double[numAttrNames];

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		attrHandlesP[i] = (double) hlaAttrHandle;

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	if (activeG2 == GSI_TRUE) 		activeHLA = RTI::RTI_TRUE;
	else							activeHLA = RTI::RTI_FALSE;


	try {

		rtiAmbP->subscribeObjectClassAttributes( hlaClassHandle, *hlaAttributes, activeHLA );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
		delete [] attrHandlesP;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while subscribing to HLA object class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeObjectClassAttributes().\n\n");

		return;
	}


	log_with_timestamp(LOG_MODE_DEBUG, "Subscribed to HLA Object Class '%s' with handle %d.\n",
					hlaClassNameP, hlaClassHandle);


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(		local_gsi_itemP[2], hlaClassHandle);
	gsi_set_flt_array(	local_gsi_itemP[3], attrHandlesP, numAttrNames);
	gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");

	gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
	delete [] attrHandlesP;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeObjectClassAttributes().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_unsubscribeObjectClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectClassHandle	hlaClassHandle;
	HLAClass					*hlaClassP;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_unsubscribeObjectClass().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle = (RTI::ObjectClassHandle) gsi_flt_of( args[0] );



	hlaClassP = hlaClassCache.find(hlaClassHandle);
	hlaClassCache.remove( hlaClassP );


	/*
	 *	Assign a HLA handle for this new class
	 */
	try {

		rtiAmbP->unsubscribeObjectClass( hlaClassHandle );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while unsubscribing HLA object class with handle '%d'.",
					e._name, e._reason, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unsubscribeObjectClass().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Unsubscribed to HLA Object Class with handle %d.\n",
					hlaClassHandle);

	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unsubscribeObjectClass().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_disableClassRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_disableClassRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableClassRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling class relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableClassRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Disabling class relevance advisory switch.");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableClassRelevanceAdvisorySwitch().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_enableClassRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_enableClassRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->enableClassRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling class relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableClassRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Enabling class relevance advisory switch.\n");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableClassRelevanceAdvisorySwitch().\n\n");
}





/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_publishInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char					*hlaClassNameP;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::InteractionClassHandle	hlaClassHandle;
	RTI::AttributeHandle		hlaAttrHandle;
	double						*attrHandlesP;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_publishInteractionClass().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaClassNameP = gsi_str_of( args[0] );
	numAttrNames  = gsi_element_count_of( args[2] );
	attrNamesP    = (const char **) gsi_sym_array_of( args[2] );


	/*
	 *	Assign a HLA handle for this new class
	 */
	try {
		hlaClassHandle = rtiAmbP->getInteractionClassHandle( hlaClassNameP );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting handle for HLA interaction class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishInteractionClass().\n\n");

		return;
	}

	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP == NULL) {

		hlaClassP = new HLAClass(hlaClassNameP, hlaClassHandle, TRUE);
		hlaClassP->setMasterG2Object(args[1]);
		hlaClassP->setHlaClassAttributes(numAttrNames, attrNamesP);


		hlaClassCache.add( hlaClassP );
	}

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Publishing HLA Object Class '%s' with HLA attributes: ",
					hlaClassNameP);

	attrHandlesP  = new double[numAttrNames];

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		attrHandlesP[i] = (double) hlaAttrHandle;

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {
		rtiAmbP->publishInteractionClass( hlaClassHandle );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
		delete [] attrHandlesP;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while publishing HLA object class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishInteractionClass().\n\n");

		return;
	}


	log_with_timestamp(LOG_MODE_DEBUG, "Published HLA Interaction Class '%s' with handle %d.\n",
					hlaClassNameP, hlaClassHandle);

	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(		local_gsi_itemP[2], hlaClassHandle);
	gsi_set_flt_array(	local_gsi_itemP[3], attrHandlesP, numAttrNames);
	gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");

	gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
	delete [] attrHandlesP;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_publishInteractionClass().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_unpublishInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::InteractionClassHandle	hlaClassHandle;
	HLAClass					*hlaClassP;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_unpublishInteractionClass().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle = (RTI::InteractionClassHandle) gsi_flt_of( args[0] );


	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP != NULL)
		hlaClassCache.remove( hlaClassP );


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->unpublishInteractionClass( hlaClassHandle );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while unpublishing HLA interaction class with handle '%d'.",
					e._name, e._reason, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unpublishInteractionClass().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Unpublished HLA Interaction Class with handle %d.\n",
					hlaClassHandle);
	
	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unpublishInteractionClass().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_subscribeInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	const char					*hlaClassNameP;
	const char					**attrNamesP;
	long						i, numAttrNames;
	gsi_int						activeG2;
	RTI::Boolean				activeHLA;
	RTI::InteractionClassHandle	hlaClassHandle;
	RTI::AttributeHandle		hlaAttrHandle;
	double						*attrHandlesP;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_subscribeInteractionClass().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaClassNameP = gsi_str_of( args[0] );
	numAttrNames  = gsi_element_count_of( args[2] );
	attrNamesP    = (const char **) gsi_sym_array_of( args[2] );
	activeG2      = gsi_log_of(args[3] );
	

	/*
	 *	Assign a HLA handle for this new class
	 */
	try {
		hlaClassHandle = rtiAmbP->getInteractionClassHandle( hlaClassNameP );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while requesting handle for HLA interaction class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeInteractionClass().\n\n");

		return;
	}

	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP == NULL) {

		hlaClassP = new HLAClass(hlaClassNameP, hlaClassHandle, TRUE);
		hlaClassP->setMasterG2Object(args[1]);
		hlaClassP->setHlaClassAttributes(numAttrNames, attrNamesP);

		hlaClassCache.add( hlaClassP );
	}

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Subscribing to HLA Interaction Class '%s' with HLA attributes: ",
					hlaClassNameP);

	attrHandlesP  = new double[numAttrNames];

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		attrHandlesP[i] = (double) hlaAttrHandle;

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	if (activeG2 == GSI_TRUE) 		activeHLA = RTI::RTI_TRUE;
	else							activeHLA = RTI::RTI_FALSE;


	try {

		rtiAmbP->subscribeInteractionClass( hlaClassHandle, activeHLA );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
		delete [] attrHandlesP;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while subscribing to HLA interaction class '%s'.",
					e._name, e._reason, hlaClassNameP);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_set_flt_array(	local_gsi_itemP[3], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");
		gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

		gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeInteractionClass().\n\n");

		return;
	}


	log_with_timestamp(LOG_MODE_DEBUG, "Subscribed to HLA Interaction Class '%s' with handle %d.\n",
					hlaClassNameP, hlaClassHandle);


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(		local_gsi_itemP[2], hlaClassHandle);
	gsi_set_flt_array(	local_gsi_itemP[3], attrHandlesP, numAttrNames);
	gsi_set_class_name(	local_gsi_itemP[3], "FLOAT-ARRAY");

	gsi_rpc_return_values(local_gsi_itemP, 4, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	gsirtl_free_i_or_v_contents(local_gsi_itemP[3]);
	delete [] attrHandlesP;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_subscribeInteractionClass().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_unsubscribeInteractionClass(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::InteractionClassHandle	hlaClassHandle;
	HLAClass					*hlaClassP;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_unsubscribeInteractionClass().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle = (RTI::InteractionClassHandle) gsi_flt_of( args[0] );



	hlaClassP = hlaClassCache.find(hlaClassHandle);
	hlaClassCache.remove( hlaClassP );


	/*
	 *	Assign a HLA handle for this new class
	 */
	try {

		rtiAmbP->unsubscribeInteractionClass( hlaClassHandle );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while unsubscribing HLA interaction class with handle '%d'.",
					e._name, e._reason, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unsubscribeInteractionClass().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Unsubscribed to HLA Interaction Class with handle %d.\n",
					hlaClassHandle);

	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unsubscribeInteractionClass().\n\n");
}





