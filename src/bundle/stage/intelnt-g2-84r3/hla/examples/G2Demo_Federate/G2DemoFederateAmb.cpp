//-----------------------------------------------------------------
// System Include Files
//-----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------
// Project Include Files
//-----------------------------------------------------------------
#include "G2DemoFederateAmb.hh"
#include "fedtime.hh"


extern double swap_8byte_quantityP(double *srcP);

//-----------------------------------------------------------------
// Bad C like global variables being externed - bad boy!!!
//-----------------------------------------------------------------
extern RTI::Boolean				timeAdvGrant;
extern RTIfedTime				grantTime;

extern const char *				VehicleClassName;
extern RTI::ObjectClassHandle	VehicleClass;

extern char						VehicleName[80];
extern RTI::ObjectHandle		VehicleObject;

extern RTI::Boolean				requestInitialValues;

extern const char *				initialFuelLevelAttrName;
extern RTI::AttributeHandle		initialFuelLevelHandle;
extern double					initialFuelLevel;

extern const char *				currentFuelLevelAttrName;
extern RTI::AttributeHandle		currentFuelLevelHandle;
extern double					currentFuelLevel;
extern RTI::Boolean				provideCurrentFuelLevel;

extern int	endFlag;
extern char	syncPoint[64];



G2DemoFederateAmb::G2DemoFederateAmb()
{
}

G2DemoFederateAmb::~G2DemoFederateAmb()
throw(RTI::FederateInternalError)
{
   cerr << "FED_HW: G2DemoFederateAmb::~G2DemoFederateAmb destructor called in FED" << endl;
}

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

void G2DemoFederateAmb::synchronizationPointRegistrationSucceeded (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: synchronizationPointRegistrationSucceeded not supported in FED"
        << endl;
}

void G2DemoFederateAmb::synchronizationPointRegistrationFailed (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: synchronizationPointRegistrationFailed not supported in FED"
        << endl;
}

void G2DemoFederateAmb::announceSynchronizationPoint (
  const char *label, // supplied C4
  const char *tag)   // supplied C4
throw (
  RTI::FederateInternalError)
{
	endFlag = 1;

	strncpy(syncPoint, label, 64);
	syncPoint[63] = 0;

	cerr << "FED_HW: announceSynchronizationPoint in FED. Setting flags." << endl;
}

void G2DemoFederateAmb::federationSynchronized (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationSynchronized in FED" << endl;
}


void G2DemoFederateAmb::initiateFederateSave (
  const char *label) // supplied C4
throw (
  RTI::UnableToPerformSave,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: initiateFederateSave not supported in FED" << endl;
}


void G2DemoFederateAmb::federationSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationSaved not supported in FED" << endl;
}


void G2DemoFederateAmb::federationNotSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotSaved not supported in FED" << endl;
}


void G2DemoFederateAmb::requestFederationRestoreSucceeded (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreSucceeded not supported in FED" << endl;
}


void G2DemoFederateAmb::requestFederationRestoreFailed (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void G2DemoFederateAmb::requestFederationRestoreFailed (
  const char *label,
  const char *reason) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void G2DemoFederateAmb::federationRestoreBegun ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestoreBegun not supported in FED" << endl;
}


void G2DemoFederateAmb::initiateFederateRestore (
  const char               *label,   // supplied C4
        RTI::FederateHandle handle)  // supplied C1
throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::CouldNotRestore,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: initiateFederateRestore not supported in FED" << endl;
}


void G2DemoFederateAmb::federationRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestored not supported in FED" << endl;
}


void G2DemoFederateAmb::federationNotRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotRestored not supported in FED" << endl;
}


/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

void G2DemoFederateAmb::startRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: startRegistrationForObjectClass not supported in FED" << endl;
}


void G2DemoFederateAmb::stopRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: stopRegistrationForObjectClass not supported in FED" << endl;
}


void G2DemoFederateAmb::turnInteractionsOn (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnInteractionsOn not supported in FED" << endl;
}

void G2DemoFederateAmb::turnInteractionsOff (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnInteractionsOff not supported in FED" << endl;
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

void G2DemoFederateAmb::discoverObjectInstance (
  RTI::ObjectHandle          theObject,      // supplied C1
  RTI::ObjectClassHandle     theObjectClass, // supplied C1
  const char *          theObjectName)  // supplied C4
throw (
  RTI::CouldNotDiscover,
  RTI::ObjectClassNotKnown,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Discovered object " << theObject << endl;

   if ( VehicleObject == NULL && VehicleClass == theObjectClass)
   {
		VehicleObject	= theObject;

		strncpy(VehicleName, theObjectName, 80);
		VehicleName[79] = 0;

		requestInitialValues	= RTI::RTI_TRUE;
   }
   else
   {
      cerr << "FED_HW: Discovered object already exists or class unknown." << endl;
   }
}

void G2DemoFederateAmb::reflectAttributeValues (
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
	this->reflectAttributeValues(theObject, theAttributes, theTag);
}

void G2DemoFederateAmb::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                             *theTag)        // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::FederateInternalError)
{
   RTI::AttributeHandle attrHandle;
   unsigned long		sz = sizeof(double);
   double				val;

   for ( unsigned int i = 0; i < theAttributes.size(); i++ )
   {
      attrHandle = theAttributes.getHandle( i );

      if ( attrHandle ==  initialFuelLevelHandle)
      {
         theAttributes.getValue( i, (char *) &val, sz);

		 initialFuelLevel = swap_8byte_quantityP( &val );
		 currentFuelLevel = initialFuelLevel;
      }
   }
}

void G2DemoFederateAmb::receiveInteraction (
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
   cerr << "FED_HW: receiveInteraction not supported in FED" << endl;
}

void G2DemoFederateAmb::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                             *theTag)         // supplied C4
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: receiveInteraction not supported in FED" << endl;
}

void G2DemoFederateAmb::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const RTI::FedTime&              theTime,   // supplied C4
  const char                      *theTag,    // supplied C4
        RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
	cout << "FED_HW: Removed object " << theObject << endl;

	if (theObject == VehicleObject) {

		VehicleObject  = NULL;
		VehicleName[0] = 0;
	}
}


void G2DemoFederateAmb::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const char                      *theTag)    // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::FederateInternalError)
{
	cout << "FED_HW: Removed object " << theObject << endl;

	if (theObject == VehicleObject) {

		VehicleObject  = NULL;
		VehicleName[0] = 0;
	}
}

void G2DemoFederateAmb::attributesInScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesInScope not supported in FED" << endl;
}

void G2DemoFederateAmb::attributesOutOfScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesOutOfScope not supported in FED" << endl;
}

void G2DemoFederateAmb::provideAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	RTI::AttributeHandle attrHandle;

	for (unsigned int i = 0; i < theAttributes.size(); i++ )
	{
		attrHandle = theAttributes.getHandle( i );

		if ( attrHandle == currentFuelLevelHandle )
        {
			provideCurrentFuelLevel = RTI::RTI_TRUE;
        }
   }
}


void G2DemoFederateAmb::turnUpdatesOnForObjectInstance (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnUpdatesOnForObjectInstance not supported in FED" << endl;
}

void G2DemoFederateAmb::turnUpdatesOffForObjectInstance (
        RTI::ObjectHandle        theObject,      // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnUpdatesOffForObjectInstance not supported in FED" << endl;
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

void G2DemoFederateAmb::requestAttributeOwnershipAssumption (
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
   cerr << "FED_HW: requestAttributeOwnershipAssumption not supported in FED" << endl;
}

void G2DemoFederateAmb::attributeOwnershipDivestitureNotification (
        RTI::ObjectHandle        theObject,          // supplied C1
  const RTI::AttributeHandleSet& releasedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipDivestitureNotification not supported in FED"
        << endl;
}

void G2DemoFederateAmb::attributeOwnershipAcquisitionNotification (
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
   cerr << "FED_HW: attributeOwnershipAcquisitionNotification not supported in FED"
        << endl;
}

void G2DemoFederateAmb::attributeOwnershipUnavailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipUnavailable not supported in FED" << endl;
}

void G2DemoFederateAmb::requestAttributeOwnershipRelease (
        RTI::ObjectHandle        theObject,           // supplied C1
  const RTI::AttributeHandleSet& candidateAttributes, // supplied C4
  const char                    *theTag)              // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestAttributeOwnershipRelease not supported in FED" << endl;
}

void G2DemoFederateAmb::confirmAttributeOwnershipAcquisitionCancellation (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotCanceled,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: confirmAttributeOwnershipAcquisitionCancellation not"
        << " supported in FED" << endl;
}

void G2DemoFederateAmb::informAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute, // supplied C1
  RTI::FederateHandle  theOwner)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: informAttributeOwnership not supported in FED" << endl;
}

 void G2DemoFederateAmb::attributeIsNotOwned (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeIsNotOwned not supported in FED" << endl;
}

void G2DemoFederateAmb::attributeOwnedByRTI (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnedByRTI not supported in FED" << endl;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

void G2DemoFederateAmb::timeRegulationEnabled (
 const  RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeRegulationWasNotPending,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeRegulationEnabled) to: "
        << ((RTIfedTime&)theFederateTime).getTime() << endl;

   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
}

void G2DemoFederateAmb::timeConstrainedEnabled (
  const RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeConstrainedWasNotPending,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeConstrainedEnabled) to: "
        << ((RTIfedTime&)theFederateTime).getTime() << endl;

   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
}

void G2DemoFederateAmb::timeAdvanceGrant (
  const RTI::FedTime& theTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::TimeAdvanceWasNotInProgress,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeAdvanceGrant) to: "
        << ((RTIfedTime&)theTime).getTime() << endl;

   grantTime = theTime;
   timeAdvGrant = RTI::RTI_TRUE;
}

void G2DemoFederateAmb::requestRetraction (
  RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::EventNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestRetraction not supported in FED" << endl;
}
