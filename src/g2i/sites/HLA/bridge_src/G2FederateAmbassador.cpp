/***************************************************************************
 *
 *		G2FederateAmbassador.cpp
 *
 *			Code related to the G2 Federate Ambassador. The methods defined
 *			in this class are not called from within the bridge, but by the
 *			RTI to forward events to the bridge. The bridge will forward the
 *			events to G2. Remember that while in these routines, one cannot
 *			make calles to RTI... For this reason I use a caching system
 *			in the bridge to keep track of class, object and attribute 
 *			handles and names.
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

#include	"G2FederateAmbassador.h"


extern HLAClassContainer		hlaClassCache;




//-----------------------------------------------------------------
// Constructors & Destructors
//-----------------------------------------------------------------

G2FederateAmbassador::G2FederateAmbassador()
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering G2FederateAmbassador().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  G2FederateAmbassador().\n\n");
}

G2FederateAmbassador::~G2FederateAmbassador()
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering ~G2FederateAmbassador().\n");
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  ~G2FederateAmbassador().\n\n");
}




////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

void G2FederateAmbassador::synchronizationPointRegistrationSucceeded (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering synchronizationPointRegistrationSucceeded().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Synchronization point registration '%s' succeeded.\n", label);

	gsi_set_str(local_gsi_itemP[0], (char *) label);
	gsi_rpc_start(G2_synchronizationPointRegistrationSucceeded, local_gsi_itemP, G2_Context);
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  synchronizationPointRegistrationSucceeded().\n\n");
}


void G2FederateAmbassador::synchronizationPointRegistrationFailed (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering synchronizationPointRegistrationFailed().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Synchronization point registration '%s' failed.\n", label);

	gsi_set_str(local_gsi_itemP[0], (char *) label);
	gsi_rpc_start(G2_synchronizationPointRegistrationFailed, local_gsi_itemP, G2_Context);
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  synchronizationPointRegistrationFailed().\n\n");
}

void G2FederateAmbassador::announceSynchronizationPoint (
  const char *label, // supplied C4
  const char *tag)   // supplied C4
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering announceSynchronizationPoint().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Announcing synchronization point '%s' with tag '%s'.\n", label, tag);

	gsi_set_str(local_gsi_itemP[0], (char *) label);
	gsi_set_str(local_gsi_itemP[1], (char *) tag);
	gsi_rpc_start(G2_announceSynchronizationPoint, local_gsi_itemP, G2_Context);
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  announceSynchronizationPoint().\n\n");
}

void G2FederateAmbassador::federationSynchronized (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationSynchronized().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Federation synchronized at point '%s'.\n", label);

	gsi_set_str(local_gsi_itemP[0], (char *) label);
	gsi_rpc_start(G2_federationSynchronized, local_gsi_itemP, G2_Context);
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationSynchronized().\n\n");
}






void G2FederateAmbassador::initiateFederateSave (
  const char *label) // supplied C4
throw (
  RTI::UnableToPerformSave,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering initiateFederateSave().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "initiateFederateSave not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  initiateFederateSave().\n\n");
}


void G2FederateAmbassador::federationSaved ()
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationSaved().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "federationSaved not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationSaved().\n\n");
}


void G2FederateAmbassador::federationNotSaved ()
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationNotSaved().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "federationNotSaved not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationNotSaved().\n\n");
}


void G2FederateAmbassador::requestFederationRestoreSucceeded (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestFederationRestoreSucceeded().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "requestFederationRestoreSucceeded not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestFederationRestoreSucceeded().\n\n");
}


void G2FederateAmbassador::requestFederationRestoreFailed (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestFederationRestoreFailed().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "requestFederationRestoreFailed not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestFederationRestoreFailed().\n\n");
}


void G2FederateAmbassador::requestFederationRestoreFailed (
  const char *label,
  const char *reason) // supplied C4
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestFederationRestoreFailed().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "requestFederationRestoreFailed not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestFederationRestoreFailed().\n\n");
}


void G2FederateAmbassador::federationRestoreBegun ()
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationRestoreBegun().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "federationRestoreBegun not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationRestoreBegun().\n\n");
}


void G2FederateAmbassador::initiateFederateRestore (
  const char               *label,   // supplied C4
        RTI::FederateHandle handle)  // supplied C1
throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::CouldNotRestore,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering initiateFederateRestore().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "initiateFederateRestore not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  initiateFederateRestore().\n\n");
}


void G2FederateAmbassador::federationRestored ()
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationRestored().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "federationRestored not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationRestored().\n\n");
}


void G2FederateAmbassador::federationNotRestored ()
throw (
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering federationNotRestored().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "federationNotRestored not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  federationNotRestored().\n\n");
}





/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

void G2FederateAmbassador::startRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering startRegistrationForObjectClass().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Start registration for object class with handle %d.\n", theClass);

	gsi_set_flt(local_gsi_itemP[0], theClass);
	gsi_rpc_start(G2_startRegistrationForObjectClass, local_gsi_itemP, G2_Context);
	
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  startRegistrationForObjectClass().\n\n");
}


void G2FederateAmbassador::stopRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering stopRegistrationForObjectClass().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Stop registration for object class with handle %d.\n", theClass);

	gsi_set_flt(local_gsi_itemP[0], theClass);
	gsi_rpc_start(G2_stopRegistrationForObjectClass, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  stopRegistrationForObjectClass().\n\n");
}







void G2FederateAmbassador::turnInteractionsOn (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering turnInteractionsOn().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Turn interactions on for interaction class with handle %d.\n", theHandle);

	gsi_set_flt(local_gsi_itemP[0], theHandle);
	gsi_rpc_start(G2_turnInteractionsOn, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  turnInteractionsOn().\n\n");
}

void G2FederateAmbassador::turnInteractionsOff (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering turnInteractionsOff().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Turn interactions off for interaction class with handle %d.\n", theHandle);

	gsi_set_flt(local_gsi_itemP[0], theHandle);
	gsi_rpc_start(G2_turnInteractionsOff, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  turnInteractionsOff().\n\n");
}






////////////////////////////////
// Object Management Services //
////////////////////////////////

void G2FederateAmbassador::discoverObjectInstance (
  RTI::ObjectHandle          theObject,      // supplied C1
  RTI::ObjectClassHandle     theObjectClass, // supplied C1
  const char *          theObjectName)		 // supplied C4
throw (
  RTI::CouldNotDiscover,
  RTI::ObjectClassNotKnown,
  RTI::FederateInternalError)
{
	HLAClass	*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering discoverObjectInstance().\n");


	hlaClassP = hlaClassCache.find(theObjectClass);
	if (hlaClassP != NULL)
		hlaClassP->addHlaObject(theObject);


	log_with_timestamp(LOG_MODE_DEBUG, "Discover object instance with handle %d, named '%s' of HLA class with handle %d\n",
			theObject, theObjectName, theObjectClass);

	gsi_set_flt(local_gsi_itemP[0], theObjectClass);
	gsi_set_flt(local_gsi_itemP[1], theObject);
	gsi_set_str(local_gsi_itemP[2], (char *) theObjectName);
	gsi_rpc_start(G2_discoverObjectInstance, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  discoverObjectInstance().\n\n");
}


void G2FederateAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const RTI::FedTime&              theTime,   // supplied C4
  const char                      *theTag,    // supplied C4
        RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
	HLAClass	*hlaClassP;
	double		tm = (double) ((RTIfedTime&)theTime).getTime();

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering removeObjectInstance().\n");


	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	if (hlaClassP != NULL)
		hlaClassP->removeHlaObject(theObject);

	log_with_timestamp(LOG_MODE_DEBUG, "Remove object instance with handle %d. Time: %f. Tag: %s\n",
			theObject, tm, theTag);

	gsi_set_flt(local_gsi_itemP[0], theObject);
	gsi_set_flt(local_gsi_itemP[1], tm);
	gsi_set_str(local_gsi_itemP[2], (char *) theTag);
	gsi_rpc_start(G2_removeObjectInstance, local_gsi_itemP, G2_Context);


	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  removeObjectInstance().\n\n");
}



void G2FederateAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const char                      *theTag)    // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::FederateInternalError)
{
	HLAClass	*hlaClassP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering removeObjectInstance().\n");



	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	if (hlaClassP != NULL)
		hlaClassP->removeHlaObject(theObject);

	log_with_timestamp(LOG_MODE_DEBUG, "Remove object instance with handle %d. Tag: %s\n",
			theObject, theTag);

	gsi_set_flt(local_gsi_itemP[0], theObject);
	gsi_set_flt(local_gsi_itemP[1], 0.0);
	gsi_set_str(local_gsi_itemP[2], (char *) theTag);
	gsi_rpc_start(G2_removeObjectInstance, local_gsi_itemP, G2_Context);


	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  removeObjectInstance().\n\n");
}





void G2FederateAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const RTI::FedTime&                     theTime,       // supplied C1
  const char                             *theTag,        // supplied C4
        RTI::EventRetractionHandle        theHandle)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
	HLAClass				*hlaClassP;
	RTI::Handle				attrHandle;
	const char				*attrName;
	long					numAttrs, i, sz, j, n;
	char					**attrNames, *attrValueP;
	gsi_item				attrItem;
	gsi_int					lValue, *gsiIntP;
	double					dValue, *gsiDblP;
	char					**strPP;
	unsigned long			attrValuelength, idx;
	double					tm = (double) ((RTIfedTime&)theTime).getTime();
	char					attrValue[ 1024 ];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering reflectAttributeValues().\n");


	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	if (hlaClassP == NULL)
		return;

	gsirtl_free_i_or_v_contents( local_gsi_itemP[2] );
	hlaClassP->getG2Object( local_gsi_itemP[3] );

	numAttrs  = theAttributes.size();
	attrNames = (char **) malloc( numAttrs * sizeof(char *) );

	/*
	 *	Decode attributes
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Reflect attribute values for HLA object with handle %d. Time: %f.\n",
					theObject, tm);
	log_with_timestamp(LOG_MODE_DEBUG, "HLA object attributes (%d) and values:\n", numAttrs);

	try {
		for (i = 0 ; i < numAttrs ; i++ ) {

			attrHandle = theAttributes.getHandle( i );
			attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

			sz = strlen(attrName) + 1;
			attrNames[i] = (char *) malloc(sz * sizeof(char));
			strncpy(attrNames[i], attrName, sz);


			if ((attrItem = gsi_attr_by_name(local_gsi_itemP[3], (char *) attrName)) != NULL) {

				switch ( gsi_type_of(attrItem) ) {
				default:
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s ***** Not supported data type\n", attrName);
					break;

				case GSI_INTEGER_TAG:
					theAttributes.getValue( i, (char *) attrValue, attrValuelength );
					lValue = swap_4byte_quantityP((ulong *) attrValue);
					gsi_set_int(attrItem, lValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INTEGER)     = %d\n", attrName, lValue);
					break;

				case GSI_INTEGER_ARRAY_TAG:
					gsiIntP = (long *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_int_array(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "INTEGER-ARRAY");
					break;

				case GSI_INTEGER_LIST_TAG:
					gsiIntP = (long *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT LIST)    # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_int_list(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "INTEGER-LIST");
					break;

				case GSI_LOGICAL_TAG:
					theAttributes.getValue( i, (char *) attrValue, attrValuelength );
					lValue = swap_4byte_quantityP((ulong *) attrValue);
					gsi_set_log(attrItem, lValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TRUTH-VALUE) = %d\n", attrName, lValue);
					break;

				case GSI_LOGICAL_ARRAY_TAG:
					gsiIntP = (long *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_log_array(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "TRUTH-VALUE-ARRAY");
					break;

				case GSI_LOGICAL_LIST_TAG:
					gsiIntP = (long *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG LIST)    # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_log_list(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "TRUTH-VALUE-LIST");
					break;

				case GSI_FLOAT64_TAG:
					theAttributes.getValue( i, (char *) attrValue, attrValuelength );
					dValue = swap_8byte_quantityP((double *) attrValue);
					gsi_set_flt(attrItem, dValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLOAT)       = %f\n", attrName, dValue);
					break;

				case GSI_FLOAT64_ARRAY_TAG:
					gsiDblP = (double *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(double);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						dValue = swap_8byte_quantityP((double *) &gsiDblP[j]);
						gsiDblP[j] = dValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %f\n", j, dValue);
					}
					gsi_set_flt_array(attrItem, gsiDblP, sz);
					gsi_set_class_name(attrItem, "FLOAT-ARRAY");
					break;

				case GSI_FLOAT64_LIST_TAG:
					gsiDblP = (double *) theAttributes.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(double);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT LIST)    # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						dValue = swap_8byte_quantityP((double *) &gsiDblP[j]);
						gsiDblP[j] = dValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %f\n", j, dValue);
					}
					gsi_set_flt_array(attrItem, gsiDblP, sz);
					gsi_set_class_name(attrItem, "FLOAT-LIST");
					break;

				case GSI_SYMBOL_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					gsi_set_sym(attrItem, attrValueP);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYMBOL)      = %s\n", attrName, attrValueP);
					break;

				case GSI_SYMBOL_ARRAY_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM ARRAY)   # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; j++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_sym_array(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "SYMBOL-ARRAY");

					free(strPP);
					break;

				case GSI_SYMBOL_LIST_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM LIST)    # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; j++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_sym_list(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "SYMBOL-LIST");

					free(strPP);
					break;

				case GSI_STRING_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					gsi_set_str(attrItem, attrValueP);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TEXT)        = %s\n", attrName, attrValueP);
					break;

				case GSI_STRING_ARRAY_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT ARRAY)   # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; j++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_str_array(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "TEXT-ARRAY");

					free(strPP);
					break;

				case GSI_STRING_LIST_TAG:
					attrValueP = theAttributes.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT LIST)    # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; j++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_str_list(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "TEXT-LIST");

					free(strPP);
					break;
				}

			} else {

				log_without_timestamp(LOG_MODE_DEBUG, "  %25s ***** Not defined in G2 object as an attribute.\n", attrName);

			}
		}
		log_without_identation(LOG_MODE_DEBUG, "\n");
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while decoding attribute value list for HLA object with handle %d.",
					e._name, e._reason, theObject);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		for (i = 0 ; i < numAttrs ; i++)
			free( attrNames[i] );

		free(attrNames);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  reflectAttributeValues().\n\n");

		return;
	}

#ifdef _DEBUG_ALL_
	log_without_timestamp(LOG_MODE_DEBUG, "Destination G2 object:\n");
	log_G2_object(LOG_MODE_DEBUG, local_gsi_itemP[3]);
#endif

	/*
	 *	Report information to G2
	 */
	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_flt(		local_gsi_itemP[1], tm);
	gsi_set_sym_array(	local_gsi_itemP[2], attrNames, numAttrs);
	gsi_set_class_name(	local_gsi_itemP[2], "SYMBOL-ARRAY");
	gsi_set_str(		local_gsi_itemP[4], (char *) theTag);

	gsi_rpc_start(G2_reflectAttributeValues, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[2] );
	gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

	for (i = 0 ; i < numAttrs ; i++)
		free( attrNames[i] );

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  reflectAttributeValues().\n\n");
}


void G2FederateAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                             *theTag)        // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::FederateInternalError)
{
	RTIfedTime						theTime(0);
	RTI::EventRetractionHandle      theHandle = { 0 };

	this->reflectAttributeValues(theObject, theAttributes, theTime, theTag, theHandle);
}





void G2FederateAmbassador::provideAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering provideAttributeValueUpdate().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Provide attribute values for HLA object with handle %d.\n", 
		theObject);
	log_without_timestamp(LOG_MODE_DEBUG, "List of attribute names: ");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = theAttributes.size();
	attrNames = (char **) malloc( numHandles * sizeof(char *) );

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) theAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");


	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_provideAttributeValueUpdate, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  provideAttributeValueUpdate().\n\n");
}



void G2FederateAmbassador::turnUpdatesOnForObjectInstance (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering turnUpdatesOnForObjectInstance().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = theAttributes.size();
	attrNames = (char **) malloc( numHandles * sizeof(char *) );

	log_with_timestamp(LOG_MODE_DEBUG, "Turn updates on for the following attributes of HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) theAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_turnUpdatesOnForObjectInstance, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  turnUpdatesOnForObjectInstance().\n\n");
}



void G2FederateAmbassador::turnUpdatesOffForObjectInstance (
        RTI::ObjectHandle        theObject,      // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering turnUpdatesOffForObjectInstance().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = theAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Turn updates off for the following attributes of HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) theAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_turnUpdatesOffForObjectInstance, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  turnUpdatesOffForObjectInstance().\n\n");
}






void G2FederateAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const RTI::FedTime&                     theTime,        // supplied C4
  const char                             *theTag,         // supplied C4
        RTI::EventRetractionHandle        theHandle)      // supplied C1
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
	HLAClass				*hlaClassP;
	RTI::Handle				attrHandle;
	const char				*attrName;
	long					numAttrs, i, sz, n, j;
	char					**attrNames, *attrValueP;
	gsi_item				attrItem;
	gsi_int					lValue, *gsiIntP;
	double					dValue, *gsiDblP;
	char					**strPP;
	unsigned long			attrValuelength, idx;
	double					tm = (double) ((RTIfedTime&)theTime).getTime();
	char					attrValue[ 1024 ];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering receiveInteraction().\n");


	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theInteraction);
	if (hlaClassP == NULL)
		return;

	gsirtl_free_i_or_v_contents( local_gsi_itemP[2] );
	hlaClassP->getG2Object( local_gsi_itemP[3] );

	numAttrs  = theParameters.size();
	attrNames = (char **) malloc( numAttrs * sizeof(char *) );

	/*
	 *	Decode attributes
	 */
	log_with_timestamp(LOG_MODE_DEBUG, "Receiving interaction for HLA interaction with handle %d. Time: %f.\n",
					theInteraction, tm);
	log_with_timestamp(LOG_MODE_DEBUG, "HLA interaction parameters (%d) and values:\n", numAttrs);

	try {
		for (i = 0 ; i < numAttrs ; i++ ) {

			attrHandle = theParameters.getHandle( i );
			attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

			sz = strlen(attrName) + 1;
			attrNames[i] = (char *) malloc(sz * sizeof(char));
			strncpy(attrNames[i], attrName, sz);


			if ((attrItem = gsi_attr_by_name(local_gsi_itemP[3], (char *) attrName)) != NULL) {

				switch ( gsi_type_of(attrItem) ) {
				default:
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s ***** Not supported data type\n", attrName);
					break;

				case GSI_INTEGER_TAG:
					theParameters.getValue( i, (char *) attrValue, attrValuelength );
					lValue = swap_4byte_quantityP((ulong *) attrValue);
					gsi_set_int(attrItem, lValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INTEGER)     = %d\n", attrName, lValue);
					break;

				case GSI_INTEGER_ARRAY_TAG:
					gsiIntP = (long *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_int_array(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "INTEGER-ARRAY");
					break;

				case GSI_INTEGER_LIST_TAG:
					gsiIntP = (long *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (INT LIST)    # %d\n", attrName, sz);

					for (i = 0 ; i < sz ; i++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_int_list(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "INTEGER-LIST");
					break;

				case GSI_LOGICAL_TAG:
					theParameters.getValue( i, (char *) attrValue, attrValuelength );
					lValue = swap_4byte_quantityP((ulong *) attrValue);
					gsi_set_log(attrItem, lValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TRUTH-VALUE) = %d\n", attrName, lValue);
					break;

				case GSI_LOGICAL_ARRAY_TAG:
					gsiIntP = (long *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_log_array(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "TRUTH-VALUE-ARRAY");
					break;

				case GSI_LOGICAL_LIST_TAG:
					gsiIntP = (long *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(long);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (LOG LIST)    # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						lValue = swap_4byte_quantityP((ulong *) &gsiIntP[j]);
						gsiIntP[j] = lValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %d\n", j, lValue);
					}
					gsi_set_log_list(attrItem, gsiIntP, sz);
					gsi_set_class_name(attrItem, "TRUTH-VALUE-LIST");
					break;

				case GSI_FLOAT64_TAG:
					theParameters.getValue( i, (char *) attrValue, attrValuelength );
					dValue = swap_8byte_quantityP((double *) attrValue);
					gsi_set_flt(attrItem, dValue);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLOAT)       = %f\n", attrName, dValue);
					break;

				case GSI_FLOAT64_ARRAY_TAG:
					gsiDblP = (double *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(double);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT ARRAY)   # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						dValue = swap_8byte_quantityP((double *) &gsiDblP[j]);
						gsiDblP[j] = dValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %f\n", j, dValue);
					}
					gsi_set_flt_array(attrItem, gsiDblP, sz);
					gsi_set_class_name(attrItem, "FLOAT-ARRAY");
					break;

				case GSI_FLOAT64_LIST_TAG:
					gsiDblP = (double *) theParameters.getValuePointer(i, attrValuelength);
					sz = attrValuelength / sizeof(double);
					 
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (FLT LIST)    # %d\n", attrName, sz);

					for (j = 0 ; j < sz ; j++) {

						dValue = swap_8byte_quantityP((double *) &gsiDblP[j]);
						gsiDblP[j] = dValue;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %f\n", j, dValue);
					}
					gsi_set_flt_array(attrItem, gsiDblP, sz);
					gsi_set_class_name(attrItem, "FLOAT-LIST");
					break;

				case GSI_SYMBOL_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					gsi_set_sym(attrItem, attrValueP);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYMBOL)      = %s\n", attrName, attrValueP);
					break;

				case GSI_SYMBOL_ARRAY_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM ARRAY)   # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; i++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_sym_array(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "SYMBOL-ARRAY");

					free(strPP);
					break;

				case GSI_SYMBOL_LIST_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (SYM LIST)    # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; i++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_sym_list(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "SYMBOL-LIST");

					free(strPP);
					break;

				case GSI_STRING_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					gsi_set_str(attrItem, attrValueP);
					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TEXT)        = %s\n", attrName, attrValueP);
					break;

				case GSI_STRING_ARRAY_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT ARRAY)   # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; j++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_str_array(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "TEXT-ARRAY");

					free(strPP);
					break;

				case GSI_STRING_LIST_TAG:
					attrValueP = theParameters.getValuePointer(i, attrValuelength);
					sz = 0;
					idx = 0;

					while (idx < attrValuelength) {

						sz++;

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;
					}

					log_without_timestamp(LOG_MODE_DEBUG, "  %25s (TXT LIST)    # %d\n", attrName, sz);

					strPP = (char **) malloc(sz * sizeof(char **));

					for (j = 0, idx = 0 ; j < sz ; i++) {

						strPP[j] = &attrValueP[idx];

						n = strlen(&attrValueP[idx]) + 1;
						idx += n;

						log_without_timestamp(LOG_MODE_DEBUG, "    %[%6d] = %s\n", j, strPP[j]);
					}
					gsi_set_str_list(attrItem, strPP, sz);
					gsi_set_class_name(attrItem, "TEXT-LIST");

					free(strPP);
					break;
				}

			} else {

				log_without_timestamp(LOG_MODE_DEBUG, "  %25s ***** Not defined in G2 object as an attribute.\n", attrName);

			}
		}
		log_without_identation(LOG_MODE_DEBUG, "\n");
	}
	catch ( RTI::Exception& e )
	{
		sprintf(error_msg, "Exception (%s, %s) while decoding parameter value list for HLA interaction with handle %d.",
					e._name, e._reason, theInteraction);

		log_with_timestamp(LOG_MODE_DEBUG, "%s\n", error_msg);

		for (i = 0 ; i < numAttrs ; i++)
			free( attrNames[i] );

		free(attrNames);

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  receiveInteraction().\n\n");

		return;
	}

#ifdef _DEBUG_ALL_
	log_without_timestamp(LOG_MODE_DEBUG, "Destination G2 object:\n");
	log_G2_object(LOG_MODE_DEBUG, local_gsi_itemP[3]);
#endif

	/*
	 *	Report information to G2
	 */
	gsi_set_flt(		local_gsi_itemP[0], theInteraction);
	gsi_set_flt(		local_gsi_itemP[1], tm);
	gsi_set_sym_array(	local_gsi_itemP[2], attrNames, numAttrs);
	gsi_set_class_name(	local_gsi_itemP[2], "SYMBOL-ARRAY");
	gsi_set_str(		local_gsi_itemP[4], (char *) theTag);

	gsi_rpc_start(G2_receiveInteraction, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[2] );
	gsirtl_free_i_or_v_contents( local_gsi_itemP[3] );

	for (i = 0 ; i < numAttrs ; i++)
		free( attrNames[i] );

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  receiveInteraction().\n\n");
}


void G2FederateAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                             *theTag)         // supplied C4
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError)
{
	RTIfedTime						theTime(0);
	RTI::EventRetractionHandle      theHandle = { 0 };

	this->receiveInteraction(theInteraction, theParameters, theTime, theTag, theHandle);
}





void G2FederateAmbassador::attributesInScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributesInScope().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "attributesInScope not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributesInScope().\n\n");
}

void G2FederateAmbassador::attributesOutOfScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributesOutOfScope().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "attributesOutOfScope not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributesOutOfScope().\n\n");
}





///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

void G2FederateAmbassador::requestAttributeOwnershipAssumption (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& offeredAttributes, // supplied C4
  const char                    *theTag)            // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestAttributeOwnershipAssumption().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = offeredAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Requesting Attribute Ownership assumption for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) offeredAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");
	gsi_set_str(		local_gsi_itemP[2], (char *) theTag);

	gsi_rpc_start(G2_requestAttributeOwnershipAssumption, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestAttributeOwnershipAssumption().\n\n");
}


void G2FederateAmbassador::attributeOwnershipDivestitureNotification (
        RTI::ObjectHandle        theObject,          // supplied C1
  const RTI::AttributeHandleSet& releasedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributeOwnershipDivestitureNotification().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = releasedAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Attribute Ownership Divestiture Notification for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) releasedAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_attributeOwnershipDivestitureNotification, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributeOwnershipDivestitureNotification().\n\n");
}


void G2FederateAmbassador::attributeOwnershipAcquisitionNotification (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& securedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributeOwnershipAcquisitionNotification().\n");


	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = securedAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Attribute Ownership Acquisition Notification for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) securedAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_attributeOwnershipAcquisitionNotification, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributeOwnershipAcquisitionNotification().\n\n");
}


void G2FederateAmbassador::attributeOwnershipUnavailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributeOwnershipUnavailable().\n");


	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = theAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Attribute Ownership Unavailable for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) theAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_attributeOwnershipUnavailable, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributeOwnershipUnavailable().\n\n");
}



void G2FederateAmbassador::requestAttributeOwnershipRelease (
        RTI::ObjectHandle        theObject,           // supplied C1
  const RTI::AttributeHandleSet& candidateAttributes, // supplied C4
  const char                    *theTag)              // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestAttributeOwnershipRelease().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = candidateAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Requesting Attribute Ownership Release for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) candidateAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");
	gsi_set_str(		local_gsi_itemP[2], (char *) theTag);

	gsi_rpc_start(G2_requestAttributeOwnershipRelease, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestAttributeOwnershipRelease().\n\n");
}



void G2FederateAmbassador::confirmAttributeOwnershipAcquisitionCancellation (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotCanceled,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	RTI::Handle			attrHandle;
	const char			*attrName;
	long				numHandles;
	char				**attrNames;
	long				i, sz;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering confirmAttributeOwnershipAcquisitionCancellation().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);

	numHandles  = theAttributes.size();
	attrNames = (char **) malloc(numHandles * sizeof(char *));

	log_with_timestamp(LOG_MODE_DEBUG, "Confirm Attribute Ownership Acquisition Cancellation for HLA object with handle %d: ", theObject);

	for (i = 0; i < numHandles; i++ ) {

		attrHandle = (RTI::Handle) theAttributes.getHandle( i );
		attrName   = hlaClassP->getHlaClassAttribute( attrHandle );

		sz = strlen(attrName) + 1;
		attrNames[i] = (char *) malloc(sz * sizeof(char));
		strncpy(attrNames[i], attrName, sz);

		if (i > 0)
			log_without_identation(LOG_MODE_DEBUG, " , ");

		log_without_identation(LOG_MODE_DEBUG, "%s", attrName);
	}
	log_without_identation(LOG_MODE_DEBUG, "\n");

	gsi_set_flt(		local_gsi_itemP[0], theObject);
	gsi_set_sym_array(	local_gsi_itemP[1], attrNames, numHandles);
	gsi_set_class_name(	local_gsi_itemP[1], "SYMBOL-ARRAY");

	gsi_rpc_start(G2_confirmAttributeOwnershipAcquisitionCancellation, local_gsi_itemP, G2_Context);

	/*
	 *	Free memory
	 */
	gsirtl_free_i_or_v_contents( local_gsi_itemP[1] );

	for (i = 0 ; i < numHandles ; i++)
		free(attrNames[i]);

	free(attrNames);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  confirmAttributeOwnershipAcquisitionCancellation().\n\n");
}



void G2FederateAmbassador::informAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute, // supplied C1
  RTI::FederateHandle  theOwner)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	const char			*attrName;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering informAttributeOwnership().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	attrName   = hlaClassP->getHlaClassAttribute( theAttribute );

	log_with_timestamp(LOG_MODE_DEBUG, "Inform Attribute %s Ownership for HLA object with handle %d\n", attrName, theObject);

	gsi_set_flt(	local_gsi_itemP[0], theObject);
	gsi_set_sym(	local_gsi_itemP[1], (char *) attrName);
	gsi_set_flt(	local_gsi_itemP[2], (double) theOwner);

	gsi_rpc_start(G2_informAttributeOwnership, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  informAttributeOwnership().\n\n");
}



void G2FederateAmbassador::attributeIsNotOwned (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	const char			*attrName;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributeIsNotOwned().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	attrName   = hlaClassP->getHlaClassAttribute( theAttribute );

	log_with_timestamp(LOG_MODE_DEBUG, "Attribute %s of HLA object with handle %d is Not Owned.\n", attrName, theObject);

	gsi_set_flt(	local_gsi_itemP[0], theObject);
	gsi_set_sym(	local_gsi_itemP[1], (char *) attrName);

	gsi_rpc_start(G2_attributeIsNotOwned, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributeIsNotOwned().\n\n");
}


void G2FederateAmbassador::attributeOwnedByRTI (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
	HLAClass			*hlaClassP;
	const char			*attrName;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering attributeOwnedByRTI().\n");

	hlaClassP = hlaClassCache.findHlaObjectClassForObject(theObject);
	attrName   = hlaClassP->getHlaClassAttribute( theAttribute );

	log_with_timestamp(LOG_MODE_DEBUG, "Attribute %s of HLA object with handle %d is owned by RTI.\n", attrName, theObject);

	gsi_set_flt(	local_gsi_itemP[0], theObject);
	gsi_set_sym(	local_gsi_itemP[1], (char *) attrName);

	gsi_rpc_start(G2_attributeOwnedByRTI, local_gsi_itemP, G2_Context);


	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  attributeOwnedByRTI().\n\n");
}


//////////////////////////////
// Time Management Services //
//////////////////////////////

void G2FederateAmbassador::timeRegulationEnabled (
 const  RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeRegulationWasNotPending,
  RTI::FederateInternalError)
{
	double		tm = (double) ((RTIfedTime&)theFederateTime).getTime();


	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering timeRegulationEnabled().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Time regulation enabled. Time: %f\n", tm);

	gsi_set_flt(local_gsi_itemP[0], tm);
	gsi_rpc_start(G2_timeRegulationEnabled, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  timeRegulationEnabled().\n\n");
}


void G2FederateAmbassador::timeConstrainedEnabled (
  const RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeConstrainedWasNotPending,
  RTI::FederateInternalError)
{
	double		tm = (double) ((RTIfedTime&)theFederateTime).getTime();

	
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering timeConstrainedEnabled().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Time constrained enabled. Time: %f\n", tm);

	gsi_set_flt(local_gsi_itemP[0], tm);
	gsi_rpc_start(G2_timeConstrainedEnabled, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  timeConstrainedEnabled().\n\n");
}


void G2FederateAmbassador::timeAdvanceGrant (
  const RTI::FedTime& theTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::TimeAdvanceWasNotInProgress,
  RTI::FederateInternalError)
{
	double		tm = (double) ((RTIfedTime&)theTime).getTime();

	
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering timeAdvanceGrant().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "Time advance granted. Time: %f\n", tm);

	gsi_set_flt(local_gsi_itemP[0], tm);
	gsi_rpc_start(G2_timeAdvanceGrant, local_gsi_itemP, G2_Context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  timeAdvanceGrant().\n\n");
}



void G2FederateAmbassador::requestRetraction (
  RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::EventNotKnown,
  RTI::FederateInternalError)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering requestRetraction().\n");

	log_with_timestamp(LOG_MODE_DEBUG, "requestRetraction not supported in FED\n");

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  requestRetraction().\n\n");
}
