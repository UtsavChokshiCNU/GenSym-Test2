/***************************************************************************
 *
 *		ObjectManagement.cpp
 *
 *			Contains the G2 to GSI RPC functions related to HLA
 *			Object Management.
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

#include	"HLAClass.h"
#include	"HLAClassContainer.h"


extern RTI::RTIambassador		*rtiAmbP;
extern HLAClassContainer		hlaClassCache;


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_registerObjectInstance(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle		hlaObjectHandle;
	RTI::ObjectClassHandle	hlaClassHandle;
	const char				*hlaObjectNameP;
	HLAClass				*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_registerObjectInstance().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle = (RTI::ObjectClassHandle) gsi_flt_of( args[0] );
	hlaObjectNameP =					      gsi_str_of( args[1] );
	
	/*
	 *	Forward information to HLA
	 */
	try {

		hlaObjectHandle = rtiAmbP->registerObjectInstance( hlaClassHandle, hlaObjectNameP);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while registering HLA object '%s' with HLA class handle '%d'.",
					e._name, e._reason, hlaObjectNameP, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_registerObjectInstance().\n\n");

		return;
	}

	/*
	 *	Register new object within bridge
	 */
	hlaClassP = hlaClassCache.find(hlaClassHandle);
	if (hlaClassP != NULL)
		hlaClassP->addHlaObject(hlaObjectHandle);


	log_with_timestamp(LOG_MODE_DEBUG, "Registered HLA Object '%s' handle %d of HLA class handle %d.\n",
				hlaObjectNameP, hlaObjectHandle, hlaClassHandle);


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], hlaObjectHandle);
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_registerObjectInstance().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_deleteObjectInstance(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	double						time;
	const char					*tagP;
	RTI::EventRetractionHandle	retractionHandle;
	HLAClass					*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_deleteObjectInstance().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );
	time			= gsi_flt_of( args[1] );
	tagP			= gsi_str_of( args[2] );

	/*
	 *	Deregister new object within bridge
	 */
	hlaClassP = hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);
	if (hlaClassP != NULL)
		hlaClassP->removeHlaObject(hlaObjectHandle);

	/*
	 *	Forward information to HLA
	 */
	const RTIfedTime	theTime( time );

	try {

		retractionHandle = rtiAmbP->deleteObjectInstance( hlaObjectHandle, theTime, tagP);
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while deleting HLA object with handle '%d'. Time: %f",
					e._name, e._reason, hlaObjectHandle, time);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_deleteObjectInstance().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Deletion of HLA Object with handle %d and tag '%s'. Time: %f\n",
				hlaObjectHandle, tagP, time);

	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], (double) 0.0);

	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_deleteObjectInstance().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_getObjectInstanceName(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle			hlaObjectHandle;
	char						*nameP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_getObjectInstanceName().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle = (RTI::ObjectHandle) gsi_flt_of( args[0] );


	/*
	 *	Forward information to HLA
	 */
	try {

		nameP = rtiAmbP->getObjectInstanceName( hlaObjectHandle );
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while getting object name of  HLA object with handle '%d'.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_str(local_gsi_itemP[2], "");
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_getObjectInstanceName().\n\n");

		return;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "HLA object name for handle %d: '%s'.\n",
				hlaObjectHandle, nameP);

	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_str(local_gsi_itemP[2], nameP);
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_deleteObjectInstance().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_requestClassAttributeValueUpdate(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectClassHandle			hlaClassHandle;
	long							i, numAttrs;
	char							**attrNames;
	RTI::AttributeHandleSet			*hlaAttributes;
	RTI::Handle						attrHandle;
	HLAClass						*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_requestClassAttributeValueUpdate().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaClassHandle	= (RTI::ObjectClassHandle) gsi_flt_of( args[0] );
	numAttrs		= gsi_element_count_of( args[1] );
	attrNames		= gsi_sym_array_of( args[1] );

	hlaClassP		= hlaClassCache.find(hlaClassHandle);


	/*
	 *	Forward the information to HLA
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Requesting class attribute value update for HLA object class with handle %d.\n",
					hlaClassHandle);
	log_without_timestamp(LOG_MODE_DEBUG, "HLA attributes: ");

	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrs);

	for (i = 0 ; i < numAttrs ; i++) {

		attrHandle = hlaClassP->getHlaClassAttribute( attrNames[i] );
		hlaAttributes->add( attrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");
	
		log_without_identation(LOG_MODE_DEBUG, "%s", attrNames[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	
	try {

		rtiAmbP->requestClassAttributeValueUpdate(hlaClassHandle, *hlaAttributes);
	}
	catch ( RTI::Exception& e )
	{
		hlaAttributes->empty();
		delete hlaAttributes;

		sprintf(error_msg, "Exception (%s, %s) while requesting class attribute value update for HLA object class with handle %d.",
					e._name, e._reason, hlaClassHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_requestClassAttributeValueUpdate().\n\n");

		return;
	}

	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_requestClassAttributeValueUpdate().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_requestObjectAttributeValueUpdate(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle				hlaObjectHandle;
	long							i, numAttrs;
	char							**attrNames;
	RTI::AttributeHandleSet			*hlaAttributes;
	RTI::Handle						attrHandle;
	HLAClass						*hlaClassP;
	

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_requestObjectAttributeValueUpdate().\n");

	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle	= (RTI::ObjectHandle) gsi_flt_of( args[0] );
	numAttrs		= gsi_element_count_of( args[1] );
	attrNames		= gsi_sym_array_of( args[1] );

	hlaClassP		= hlaClassCache.findHlaObjectClassForObject( hlaObjectHandle );

	if (hlaClassP == NULL) {

		sprintf(error_msg, "HLA Class handle %d is not defined.", hlaObjectHandle);
		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_HLA_CLASS);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_requestObjectAttributeValueUpdate().\n\n");

		return;
	}

	/*
	 *	Forward the information to HLA
	 */

	log_with_timestamp(LOG_MODE_DEBUG, "Requesting object attribute value update for HLA object with handle %d.\n",
					hlaObjectHandle);
	log_without_timestamp(LOG_MODE_DEBUG, "HLA attributes: ");


	hlaAttributes = RTI::AttributeHandleSetFactory::create(numAttrs);

	for (i = 0 ; i < numAttrs ; i++) {

		attrHandle = hlaClassP->getHlaClassAttribute( attrNames[i] );
		hlaAttributes->add( attrHandle );

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");
	
		log_without_identation(LOG_MODE_DEBUG, "%s", attrNames[i]);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	try {

		rtiAmbP->requestObjectAttributeValueUpdate(hlaObjectHandle, *hlaAttributes);
	}
	catch ( RTI::Exception& e )
	{
		hlaAttributes->empty();
		delete hlaAttributes;

		sprintf(error_msg, "Exception (%s, %s) while requesting object attribute value update for HLA object class with handle %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_requestObjectAttributeValueUpdate().\n\n");

		return;
	}


	/*
	 *	Free and deallocate memory
	 */
	hlaAttributes->empty();
	delete hlaAttributes;


	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_requestObjectAttributeValueUpdate().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_updateAttributeValues(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::ObjectHandle		hlaObjectHandle;
	double					hlaTime;
	long					i, numAttrs, sz, idx;
	char					**attrNames;
	RTI::Handle				attrHandle;
	long					lValue, lNbElts, lOfs;
	unsigned long			ulValue, ulLength;
	double					dValue;
	char					*sValue;
	gsi_item				attrItem;
	gsi_int					*gsiIntP;
	double					*gsiDblP;
	char					**gsiStrP;
	char					*tagP;
	RTI::AttributeHandleValuePairSet	*valueSetP;
	HLAClass				*hlaClassP;
	RTI::EventRetractionHandle	retractionHandle;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_updateAttributeValues().\n");


	/*
	 *	Extract G2 arguments
	 */
	hlaObjectHandle	= (RTI::ObjectHandle) gsi_flt_of( args[0] );
	hlaTime			= gsi_flt_of( args[1] );
	numAttrs		= gsi_element_count_of( args[2] );
	attrNames		= gsi_sym_array_of( args[2] );
	tagP			= gsi_str_of( args[4] );

	hlaClassP		= hlaClassCache.findHlaObjectClassForObject(hlaObjectHandle);

	if (hlaClassP == NULL) {

		sprintf(error_msg, "HLA Class handle %d is not defined.", hlaObjectHandle);
		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_HLA_CLASS);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_updateAttributeValues().\n\n");

		return;
	}

	/*
	 *	Decode attributes
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Updating attribute values for HLA object with handle %d. Time: %f.\n",
					hlaObjectHandle, hlaTime);
	log_without_timestamp(LOG_MODE_DEBUG, "HLA object attributes and values:\n");
	
	const RTIfedTime	theTime( hlaTime );

	valueSetP = RTI::AttributeSetFactory::create( numAttrs );

	try {

		for (i = 0 ; i < numAttrs ; i++ ) {

			attrHandle = hlaClassP->getHlaClassAttribute( attrNames[i] );

			if ((attrItem = gsi_attr_by_name(args[3], attrNames[i])) != NULL) {

				switch ( gsi_type_of(attrItem) ) {
				default:
					break;

				case GSI_INTEGER_TAG:
					lValue = gsi_int_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INTEGER)     =  %d\n", attrNames[i], lValue);

					ulValue = swap_4byte_quantity( lValue );
					valueSetP->add(attrHandle, (char *) &ulValue, sizeof(long));
					break;

				case GSI_INTEGER_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_int_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_INTEGER_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_int_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_LOGICAL_TAG:
					lValue = gsi_log_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TRUTH-VALUE) = %d\n", attrNames[i], lValue);

					ulValue = swap_4byte_quantity( lValue );
					valueSetP->add(attrHandle, (char *) &ulValue, sizeof(long));
					break;

				case GSI_LOGICAL_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_log_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_LOGICAL_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_log_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_FLOAT64_TAG:
					dValue = gsi_flt_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLOAT)       = %f\n", attrNames[i], dValue);

					dValue = swap_8byte_quantity( dValue );
					valueSetP->add(attrHandle, (char *) &dValue, sizeof(double));
					break;

				case GSI_FLOAT64_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiDblP	= gsi_flt_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						dValue = gsiDblP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %f\n", idx, dValue);

						dValue = swap_8byte_quantity( dValue );

						gsiDblP[idx] = dValue;
					}

					ulLength = lNbElts * sizeof(double);
					valueSetP->add(attrHandle, (char *) gsiDblP, ulLength);

					break;

				case GSI_FLOAT64_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiDblP	= gsi_flt_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						dValue = gsiDblP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %f\n", idx, dValue);

						dValue = swap_8byte_quantity( dValue );

						gsiDblP[idx] = dValue;
					}

					ulLength = lNbElts * sizeof(double);
					valueSetP->add(attrHandle, (char *) gsiDblP, ulLength);

					break;

				case GSI_SYMBOL_TAG:
					sValue = gsi_sym_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYMBOL)      = %s\n", attrNames[i], sValue);

					sz     = strlen(sValue) + 1;
					valueSetP->add(attrHandle, sValue, sz);
					break;

				case GSI_SYMBOL_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_sym_array_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM ARRAY)   # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_SYMBOL_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_sym_list_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM LIST)    # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_STRING_TAG:
					sValue = gsi_str_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TEXT)        = %s\n", attrNames[i], sValue);

					sz     = strlen(sValue) + 1;
					valueSetP->add(attrHandle, sValue, sz);
					break;

				case GSI_STRING_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_str_array_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT ARRAY)   # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_STRING_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_str_list_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT LIST)    # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;
				}
			}
		}
		log_without_identation(LOG_MODE_DEBUG, "\n");
	}
	catch ( RTI::Exception& e )
	{
		valueSetP->empty();
		delete valueSetP;

		sprintf(error_msg, "Exception (%s, %s) while creating attribute value list for HLA object class with handle %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_updateAttributeValues().\n\n");

		return;
	}

#ifdef _DEBUG_ALL_
	log_without_timestamp(LOG_MODE_DEBUG, "Source G2 object was:\n");
	log_G2_object(LOG_MODE_DEBUG, args[3]);
#endif


	try {

		retractionHandle = rtiAmbP->updateAttributeValues(hlaObjectHandle, *valueSetP, theTime, tagP);
	}
	catch ( RTI::Exception& e )
	{
		valueSetP->empty();
		delete valueSetP;

		sprintf(error_msg, "Exception (%s, %s) while updating object attribute value for HLA object class with handle %d.",
					e._name, e._reason, hlaObjectHandle);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_updateAttributeValues().\n\n");

		return;
	}

	valueSetP->empty();
	delete valueSetP;

	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], 0.0);
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_updateAttributeValues().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_disableAttributeRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_disableAttributeRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableClassRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling attribute relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableAttributeRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Disabling attribute relevance advisory switch.");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableAttributeRelevanceAdvisorySwitch().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_enableAttributeRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_enableAttributeRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->enableAttributeRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling attribute relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableAttributeRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Enabling attribute relevance advisory switch.\n");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableAttributeRelevanceAdvisorySwitch().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/
void G2_sendInteraction(gsi_item args[], gsi_int count, gsi_int call_index)
{
	RTI::InteractionClassHandle	theInteraction;
	double						hlaTime;
	long						i, numAttrs, sz, idx;
	char						**attrNames;
	RTI::Handle					attrHandle, *attrHandlesP;
	long						lValue, lNbElts, lOfs;
	unsigned long				ulValue, ulLength;
	double						dValue;
	char						*sValue;
	gsi_item					attrItem;
	gsi_int						*gsiIntP;
	double						*gsiDblP;
	char						**gsiStrP;
	char						*tagP;
	RTI::ParameterHandleValuePairSet	*valueSetP;
	HLAClass					*hlaClassP;
	RTI::EventRetractionHandle	retractionHandle;


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_sendInteraction().\n");


	/*
	 *	Extract G2 arguments
	 */
	theInteraction	= (RTI::InteractionClassHandle) gsi_flt_of( args[0] );
	hlaTime			= gsi_flt_of( args[1] );
	tagP			= gsi_str_of( args[3] );

	hlaClassP		= hlaClassCache.findHlaObjectClassForObject(theInteraction);

	if (hlaClassP == NULL) {

		sprintf(error_msg, "HLA Interaction Class handle %d is not defined.", theInteraction);
		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_HLA_CLASS);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_sendInteraction().\n\n");

		return;
	}


	numAttrs = hlaClassP->getAttributeList(&attrNames, &attrHandlesP);


	/*
	 *	Decode attributes
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Sending Interaction for HLA interaction class with handle %d. Time: %f.\n",
					theInteraction, hlaTime);
	log_without_timestamp(LOG_MODE_DEBUG, "HLA interaction parameters and values:\n");
	
	const RTIfedTime	theTime( hlaTime );

	valueSetP = RTI::ParameterSetFactory::create( numAttrs );

	try {

		for (i = 0 ; i < numAttrs ; i++ ) {

			attrHandle = attrHandlesP[i];

			if ((attrItem = gsi_attr_by_name(args[2], attrNames[i])) != NULL) {

				switch ( gsi_type_of(attrItem) ) {
				default:
					break;

				case GSI_INTEGER_TAG:
					lValue = gsi_int_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INTEGER)     =  %d\n", attrNames[i], lValue);

					ulValue = swap_4byte_quantity( lValue );
					valueSetP->add(attrHandle, (char *) &ulValue, sizeof(long));
					break;

				case GSI_INTEGER_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_int_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_INTEGER_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_int_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_LOGICAL_TAG:
					lValue = gsi_log_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TRUTH-VALUE) = %d\n", attrNames[i], lValue);

					ulValue = swap_4byte_quantity( lValue );
					valueSetP->add(attrHandle, (char *) &ulValue, sizeof(long));
					break;

				case GSI_LOGICAL_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_log_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_LOGICAL_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiIntP	= gsi_log_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						lValue = gsiIntP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %d\n", idx, lValue);

						ulValue = swap_4byte_quantity( lValue );

						gsiIntP[idx] = ulValue;
					}

					ulLength = lNbElts * sizeof(gsi_int);
					valueSetP->add(attrHandle, (char *) gsiIntP, ulLength);

					break;

				case GSI_FLOAT64_TAG:
					dValue = gsi_flt_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLOAT)       = %f\n", attrNames[i], dValue);

					dValue = swap_8byte_quantity( dValue );
					valueSetP->add(attrHandle, (char *) &dValue, sizeof(double));
					break;

				case GSI_FLOAT64_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiDblP	= gsi_flt_array_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT ARRAY)   # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						dValue = gsiDblP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %f\n", idx, dValue);

						dValue = swap_8byte_quantity( dValue );

						gsiDblP[idx] = dValue;
					}

					ulLength = lNbElts * sizeof(double);
					valueSetP->add(attrHandle, (char *) gsiDblP, ulLength);

					break;

				case GSI_FLOAT64_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiDblP	= gsi_flt_list_of(attrItem);

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT LIST)    # %f\n", attrNames[i], lNbElts);

					for (idx = 0 ; idx < lNbElts ; idx++) {

						dValue = gsiDblP[idx];
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %f\n", idx, dValue);

						dValue = swap_8byte_quantity( dValue );

						gsiDblP[idx] = dValue;
					}

					ulLength = lNbElts * sizeof(double);
					valueSetP->add(attrHandle, (char *) gsiDblP, ulLength);

					break;

				case GSI_SYMBOL_TAG:
					sValue = gsi_sym_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYMBOL)      = %s\n", attrNames[i], sValue);

					sz     = strlen(sValue) + 1;
					valueSetP->add(attrHandle, sValue, sz);
					break;

				case GSI_SYMBOL_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_sym_array_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM ARRAY)   # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_SYMBOL_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_sym_list_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM LIST)    # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_STRING_TAG:
					sValue = gsi_str_of(attrItem);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TEXT)        = %s\n", attrNames[i], sValue);

					sz     = strlen(sValue) + 1;
					valueSetP->add(attrHandle, sValue, sz);
					break;

				case GSI_STRING_ARRAY_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_str_array_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT ARRAY)   # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;

				case GSI_STRING_LIST_TAG:
					lNbElts = gsi_element_count_of(attrItem);
					gsiStrP	= gsi_str_list_of(attrItem);

					for (idx = 0, ulLength = 0 ; idx < lNbElts ; idx++) {

						ulLength += strlen( gsiStrP[idx] ) + 1;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT LIST)    # %f (# Bytes = %d)\n", attrNames[i], lNbElts, ulLength);

					sValue = (char *) malloc(ulLength * sizeof(char));

					for (idx = 0, lOfs = 0 ; idx < lNbElts ; idx++) {

						lValue = strlen(gsiStrP[idx] ) + 1;
						log_without_timestamp(LOG_MODE_DEBUG, "    [%6d] = %s\n", idx, gsiStrP[idx]);

						memcpy( &sValue[lOfs], gsiStrP[idx], lValue);

						lOfs += lValue;
					}

					valueSetP->add(attrHandle, sValue, ulLength);
					break;
				}
			}
		}
		log_without_identation(LOG_MODE_DEBUG, "\n");
	}
	catch ( RTI::Exception& e )
	{
		valueSetP->empty();
		delete valueSetP;

		sprintf(error_msg, "Exception (%s, %s) while creating parameter value list for HLA interaction class with handle %d.",
					e._name, e._reason, theInteraction);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_sendInteraction().\n\n");

		return;
	}

#ifdef _DEBUG_ALL_
	log_without_timestamp(LOG_MODE_DEBUG, "Source G2 object was:\n");
	log_G2_object(LOG_MODE_DEBUG, args[2]);
#endif


	try {

		retractionHandle = rtiAmbP->sendInteraction(theInteraction, *valueSetP, theTime, tagP);
	}
	catch ( RTI::Exception& e )
	{
		valueSetP->empty();
		delete valueSetP;

		sprintf(error_msg, "Exception (%s, %s) while sending interaction for HLA interaction class with handle %d.",
					e._name, e._reason, theInteraction);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_set_flt(local_gsi_itemP[2], 0.0);
		gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_sendInteraction().\n\n");

		return;
	}

	valueSetP->empty();
	delete valueSetP;

	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);
	gsi_set_flt(local_gsi_itemP[2], 0.0);
	gsi_rpc_return_values(local_gsi_itemP, 3, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_sendInteraction().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_enableInteractionRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_enableInteractionRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->enableInteractionRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while enabling interaction relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableAttributeRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Enabling interaction relevance advisory switch.\n");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_enableInteractionRelevanceAdvisorySwitch().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	
 *
 *-------------------------------------------------------------------------*/

void G2_disableInteractionRelevanceAdvisorySwitch(gsi_item args[], gsi_int count, gsi_int call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2_disableInteractionRelevanceAdvisorySwitch().\n");


	/*
	 *	Forward information to HLA
	 */
	try {

		rtiAmbP->disableInteractionRelevanceAdvisorySwitch();
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while disabling interaction relevance advisory switch.",
					e._name, e._reason);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);


		gsi_set_sym(local_gsi_itemP[0], ERROR_EXCEPTION);
		gsi_set_str(local_gsi_itemP[1], error_msg);
		gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableInteractionRelevanceAdvisorySwitch().\n\n");

		return;
	}

	
	log_with_timestamp(LOG_MODE_DEBUG, "Disabling interaction relevance advisory switch.\n");


	/*
	 *	Return the information to G2
	 */
	gsi_set_sym(local_gsi_itemP[0], NO_ERROR_SYM);
	gsi_set_str(local_gsi_itemP[1], NO_ERROR_TXT);

	gsi_rpc_return_values(local_gsi_itemP, 2, call_index, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2_disableInteractionRelevanceAdvisorySwitch().\n\n");
}
