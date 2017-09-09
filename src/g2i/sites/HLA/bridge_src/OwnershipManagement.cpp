/***************************************************************************
 *
 *		OwnershipManagement.cpp
 *
 *			Contains the G2 to GSI RPC functions related to HLA
 *			Ownership Management.
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

void G2_unconditionalAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_unconditionalAttributeOwnershipDivestiture().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames   = gsi_element_count_of( args[1] );
	attrNamesP     = (const char **) gsi_sym_array_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Getting unconditional attribute ownership divestigure for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->unconditionalAttributeOwnershipDivestiture( hlaObjectHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while unconditional attribute ownership divestigure for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unconditionalAttributeOwnershipDivestiture().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_unconditionalAttributeOwnershipDivestiture().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_negotiatedAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	const char					*tagP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_negotiatedAttributeOwnershipDivestiture().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames	= gsi_element_count_of( args[1] );
	attrNamesP		= (const char **) gsi_sym_array_of( args[1] );
	tagP			= (const char *) gsi_str_of( args[2] );

	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Negotiating attribute ownership divestiture for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->negotiatedAttributeOwnershipDivestiture( hlaObjectHandle, *hlaAttributes, tagP );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while negotiating attribute ownership divestiture for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_negotiatedAttributeOwnershipDivestiture().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_negotiatedAttributeOwnershipDivestiture().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_attributeOwnershipAcquisition(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	const char					*tagP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_attributeOwnershipAcquisition().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames	= gsi_element_count_of( args[1] );
	attrNamesP		= (const char **) gsi_sym_array_of( args[1] );
	tagP			= (const char *) gsi_str_of( args[2] );

	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Getting attribute ownership for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->attributeOwnershipAcquisition( hlaObjectHandle, *hlaAttributes, tagP );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while getting attribute ownership for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipAcquisition().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipAcquisition().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_attributeOwnershipAcquisitionIfAvailable(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_attributeOwnershipAcquisitionIfAvailable().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames   = gsi_element_count_of( args[1] );
	attrNamesP     = (const char **) gsi_sym_array_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Getting attribute ownership (if available) for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->attributeOwnershipAcquisitionIfAvailable( hlaObjectHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while getting attribute ownership (if available) for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipAcquisitionIfAvailable().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipAcquisitionIfAvailable().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_cancelNegotiatedAttributeOwnershipDivestiture(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_cancelNegotiatedAttributeOwnershipDivestiture().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames   = gsi_element_count_of( args[1] );
	attrNamesP     = (const char **) gsi_sym_array_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Cancelling negotiated attribute ownership divestigure for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->cancelNegotiatedAttributeOwnershipDivestiture( hlaObjectHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while cancelling negotiated attribute ownership divestigure for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_cancelNegotiatedAttributeOwnershipDivestiture().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_cancelNegotiatedAttributeOwnershipDivestiture().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_cancelAttributeOwnershipAcquisition(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	long						i, numAttrNames;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_cancelAttributeOwnershipAcquisition().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames   = gsi_element_count_of( args[1] );
	attrNamesP     = (const char **) gsi_sym_array_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Cancelling attribute ownership acquisition for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->cancelAttributeOwnershipAcquisition( hlaObjectHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while cancelling attribute ownership acquisition for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_cancelAttributeOwnershipAcquisition().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_cancelAttributeOwnershipAcquisition().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_queryAttributeOwnership(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					*attrNameP;
	RTI::AttributeHandle		hlaAttrHandle;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_queryAttributeOwnership().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	attrNameP       = (const char *) gsi_sym_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Query attribute '%s' ownership for object with handle %d",
					attrNameP, hlaObjectHandle);


	hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNameP ); 

	try {

		rtiAmbP->queryAttributeOwnership( hlaObjectHandle, hlaAttrHandle );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while cancelling attribute ownership acquisition for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_queryAttributeOwnership().\n\n");

		return;
	}


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_queryAttributeOwnership().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_isAttributeOwnedByFederate(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					*attrNameP;
	RTI::AttributeHandle		hlaAttrHandle;
	HLAClass					*hlaClassP;
	RTI::Boolean				hla_ret;
	gsi_int						gsi_ret = GSI_FALSE;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_isAttributeOwnedByFederate().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	attrNameP       = (const char *) gsi_sym_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Is attribute '%s' of object with handle %d owned by Federate?",
					attrNameP, hlaObjectHandle);


	hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNameP ); 

	try {

		hla_ret = rtiAmbP->isAttributeOwnedByFederate( hlaObjectHandle, hlaAttrHandle );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while 'is attribute '%s' of object %d owned by Federate?'.",
					e._name, e._reason, attrNameP, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_log(local_gsi_itemP[2], gsi_ret);

		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_isAttributeOwnedByFederate().\n\n");

		return;
	}

	if (hla_ret == RTI::RTI_TRUE)
		gsi_ret = GSI_TRUE;

	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_log(		local_gsi_itemP[2], gsi_ret);

	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_isAttributeOwnedByFederate().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_attributeOwnershipReleaseResponse(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	const char					**attrNamesP;
	char						**replyAttrNamesP;
	long						i, sz, numAttrNames, numHandles;
	RTI::AttributeHandle		hlaAttrHandle;
	RTI::AttributeHandleSet		*hlaAttributes;
	HLAClass					*hlaClassP;
	RTI::Handle					attrHandle;
	const char					*attrName;
	RTI::AttributeHandleSet		*replyAttributes;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_attributeOwnershipReleaseResponse().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrNames   = gsi_element_count_of( args[1] );
	attrNamesP     = (const char **) gsi_sym_array_of( args[1] );


	/*
	 *	Add the new class to the cache
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Attribute ownership response for object with handle %d. HLA attributes: ",
					hlaObjectHandle);

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrNames);

	for (i = 0 ; i < numAttrNames ; i++) {

		hlaAttrHandle = hlaClassP->getHlaClassAttribute( attrNamesP[i] ); 
		hlaAttributes->add( hlaAttrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrNamesP[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		replyAttributes = rtiAmbP->attributeOwnershipReleaseResponse( hlaObjectHandle, *hlaAttributes );
	}
	catch ( RTI::Exception& e )
	{
		/*
		 *	Free and deallocate memory
		 */
		hlaAttributes->empty();
		delete hlaAttributes;

		/*
		 *	Report error to log file and G2
		 */
		sprintf(error_msg, "Exception (%s, %s) while sending attribute ownership response for object %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(		local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(		local_gsi_itemP[1], error_msg);
		gsi_set_sym_array(	local_gsi_itemP[2], NULL, 0);
		gsi_set_class_name(	local_gsi_itemP[2], "SYMBOL-ARRAY");

		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipReleaseResponse().\n\n");

		return;
	}


	/*
	 *	Create reply array for G2
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Reply Attribute list: ");

	numHandles  = replyAttributes->size();
	replyAttrNamesP = (char **) malloc( numHandles * sizeof(char *) );

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) replyAttributes->getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		replyAttrNamesP[i] = (char *) malloc(sz * sizeof(char));
		strncpy(replyAttrNamesP[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(		local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(		local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_sym_array(	local_gsi_itemP[2], replyAttrNamesP, numHandles);
	gsi_set_class_name(	local_gsi_itemP[2], "SYMBOL-ARRAY");

	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	/*
	 *	Free and deallocate memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[2] );

	for (i = 0 ; i < numHandles ; i++)
		free(replyAttrNamesP[i]);

	free(replyAttrNamesP);


	hlaAttributes->empty();
	delete hlaAttributes;

	replyAttributes->empty();
	delete replyAttributes;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_attributeOwnershipReleaseResponse().\n\n");
}
