#if !defined(WIN32)
#include <stream.h>
#endif

#include <string.h>
#include <stdlib.h>

#if !defined(WIN32)
#include <unistd.h>
#endif

#include <RTI.hh>

#if defined(WIN32)
#include <windows.h>   // for "Sleep"
#include <sys/timeb.h> // for "struct _timeb"
#else
#include <sys/time.h>
#endif

#include "G2DemoFederateAmb.hh"
#include "fedtime.hh"

extern double swap_8byte_quantityP(double *srcP);


///////////////////////////////////////////////////
//
//	Global variables
//
///////////////////////////////////////////////////

RTI::Boolean				timeAdvGrant			= RTI::RTI_FALSE;
RTIfedTime					grantTime(0.0);


const char *				VehicleClassName		= "VEHICLE";
RTI::ObjectClassHandle		VehicleClass			= NULL;

char						VehicleName[80]		= { 0 };
RTI::ObjectHandle			VehicleObject			= NULL;

RTI::Boolean				requestInitialValues	= RTI::RTI_FALSE;

const char *				initialFuelLevelAttrName= "INITIAL-FUEL-LEVEL";
RTI::AttributeHandle        initialFuelLevelHandle	= NULL;
double						initialFuelLevel		= 0.0;

const char *				currentFuelLevelAttrName= "FUEL-LEVEL";
RTI::AttributeHandle        currentFuelLevelHandle	= NULL;
double						currentFuelLevel		= 0.0;
RTI::Boolean				provideCurrentFuelLevel	= RTI::RTI_FALSE;


BOOL	is_big_endian;

int		endFlag = 0;
char	syncPoint[64] = { 0 };

///////////////////////////////////////////////////
//
//	Main program entry point
//
///////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	
   const char*	exeName		= argv[0];				// Name of executable process
   char* const	fedExecName = "G2DemoFederation";	// Name of the Federation Execution
   char* const	fedName		= "CFederation";	// Name of the Federation Execution
	long		i;
	char		*sP;

   int			numberOfTicks( 100 );

	i  = 0x1234;
	sP = (char *) &i;

	if (sP[0] == 0x34)		is_big_endian = FALSE;
	else					is_big_endian = TRUE;

   try
   {
      //------------------------------------------------------
      // Create RTI objects
      //
      // The federate communicates to the RTI through the RTIambassador
      // object and the RTI communicates back to the federate through
      // the FederateAmbassador object.
      //------------------------------------------------------
      RTI::RTIambassador		rtiAmb;         // libRTI provided
      G2DemoFederateAmb			fedAmb;         // User-defined


      // Named value placeholder for the federates handle -
      // we don't really use this in Demo but some
      // services and MOM might need it - if we were to use them.
      RTI::FederateHandle      federateId;

	  char fedName[1024];
	  char *ghlaHomeP;

      //------------------------------------------------------
      // Create federation execution.
      //------------------------------------------------------
      try
      {
         //------------------------------------------------------
         // A successful createFederationExecution will cause
         // the fedex process to be executed on this machine.
         //
         // A "Demo.fed" file must exist in the
         // GHLA_HOME\resources directory. This file specifies the FOM
         // object and interaction class structures as well as 
         // default/initial transport and ordering information for
         // object attributes and interaction classes. In RTI 1.0
         // the name of the file was required to be the same as 
         // the name of the federation execution but in 1.3 a 2nd
         // argument to createFederationExecution exists to specify
         // the FED filename.
         //------------------------------------------------------
		cout << "FED_HW: CREATING FEDERATION EXECUTION" << endl;

		ghlaHomeP = getenv("GHLA_HOME");

		strncpy(fedName, ghlaHomeP, 1024);
		strncat(fedName, "\\resources\\G2DemoFederation.fed", 1024);
        rtiAmb.createFederationExecution( fedExecName, fedName ); 

		cout << "FED_HW: SUCCESSFUL CREATE FEDERATION EXECUTION" << endl;
      }
      catch ( RTI::FederationExecutionAlreadyExists& e )
      {
         cerr << "FED_HW: Note: Federation execution already exists." << &e << endl;
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << &e << endl;
      }


      RTI::Boolean Joined    = RTI::RTI_FALSE;
      int          numTries  = 0;

      //------------------------------------------------------
      // Here we loop around the joinFederationExecution call
      // until we try to many times or the Join is successful.
      // 
      // The federate that successfully CREATES the federation
      // execution will get to the join call before the 
      // FedExec is initializes and will be unsuccessful at
      // JOIN call.  In this loop we catch the
      // FederationExecutionDoesNotExist exception to
      // determine that the FedExec is not initialized and to
      // keep trying. If the JOIN call does not throw an
      // exception then we set Joined to TRUE and that will
      // cause us to exit the loop anf proceed in the execution.
      //------------------------------------------------------
      while( !Joined && (numTries++ < 20) )
      {

         //------------------------------------------------------
         // Join the named federation execution as the named
         // federate type.  Federate types (2nd argument to
         // joinFederationExecution) does not have to be unique
         // in a federation execution; however, the save/restore
         // services use this information but we are not doing
         // save/restore in Demo so we won't worry about it
         // here (best to make the names unique if you do
         // save/restore unless you understand how save/restore
         // will use the information
         //
         //------------------------------------------------------
         try
         {
            cout << "FED_HW: JOINING FEDERATION EXECUTION: " << exeName << endl;

            federateId = rtiAmb.joinFederationExecution( (char* const) 
                                                         fedName,
                                                         fedExecName, 
                                                         &fedAmb);
            Joined = RTI::RTI_TRUE; 
         }
         catch (RTI::FederateAlreadyExecutionMember& e)
         {
            cerr << "FED_HW: ERROR: " << fedName
                 << " already exists in the Federation Execution "
                 << fedExecName << "." << endl;
            cerr << &e << endl;
            return -1;
         }
         catch (RTI::FederationExecutionDoesNotExist&)
         {
            cerr << "FED_HW: ERROR: " << fedExecName << " Federation Execution "
                 << "does not exists."<< endl;
#if defined(WIN32)
			Sleep(2000);
#else
            sleep (2); // sleep 2 seconds 
#endif
         }
         catch ( RTI::Exception& e )
         {
            cerr << "FED_HW: ERROR:" << &e << endl;
         }
      } // end of while

      cout << "FED_HW: JOINED SUCCESSFULLY: " << exeName 
           << ": Federate Handle = " << federateId << endl;


	  
  
	  
      //------------------------------------------------------
      // Publication/Subscription
      //
      //------------------------------------------------------
	  try
	  {
		cout << "FED_HW: CLASS PUBLICATION & SUBSCRIPTION" << endl;

		VehicleClass			= rtiAmb.getObjectClassHandle(VehicleClassName);
		initialFuelLevelHandle	= rtiAmb.getAttributeHandle( initialFuelLevelAttrName, VehicleClass);
		currentFuelLevelHandle	= rtiAmb.getAttributeHandle( currentFuelLevelAttrName, VehicleClass);


		RTI::AttributeHandleSet	*attributes;


		attributes = RTI::AttributeHandleSetFactory::create(2);
		attributes->add( initialFuelLevelHandle );
		attributes->add( currentFuelLevelHandle );

		rtiAmb.subscribeObjectClassAttributes( VehicleClass, *attributes );
		attributes->empty();


		attributes = RTI::AttributeHandleSetFactory::create(1);
		attributes->add( currentFuelLevelHandle );

		rtiAmb.publishObjectClass( VehicleClass, *attributes);
		attributes->empty();


		delete attributes;
	  }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << &e << endl;
      }


      // Set time step to 1
      const RTIfedTime timeStep(10.0);

      timeAdvGrant = RTI::RTI_FALSE;


/*      
	  //------------------------------------------------------
      // Set the Time Management parameters
      //
      // This version of Demo operates as a time-stepped
      // simulation.  This means that it should be constrained
      // and regulating.
      //
      // In the 1.0 version of Demo this section of code
      // was before the publication and subscription.  In 1.3
      // enableTimeConstrained and enableTimeRegulation 
      //------------------------------------------------------
      try
      {
         cout << "FED_HW: ENABLING TIME CONTRAINT" << endl;
         //------------------------------------------------------
         // Turn on constrained status so that regulating
         // federates will control our advancement in time.
         //
         // If we are constrained and sending fderates specify
         // the Vehicle attributes and Communication interaction
         // with timestamp in the Demo.fed file we will
         // receive TimeStamp Ordered messages.
         //------------------------------------------------------
         rtiAmb.enableTimeConstrained();
         timeAdvGrant = RTI::RTI_FALSE;

         //------------------------------------------------------
         // Tick the RTI until we gwt the timeConstrainedEnabled
         // callback with my current time.
         //------------------------------------------------------
         while ( !timeAdvGrant )
         {
            rtiAmb.tick(0.01, 1.0);
         }
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << &e << endl;
      }
*/
      //------------------------------------------------------
      // Must enable attribute relevance advisories in order to 
      // receive turnUpdatesOnForObjectInstance callbacks.
      //------------------------------------------------------
      try
      {
         rtiAmb.enableAttributeRelevanceAdvisorySwitch();
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << &e << endl;
      }



      //------------------------------------------------------
      // Event Loop
      // ----------
      // 
      // 1.) Calculate current state and update to RTI.
      // 2.) Ask for a time advance.
      // 3.) Tick the RTI waiting for the grant and process all
      //     RTI initiated services (especially reflections).
      // 4.) Repeat.
      //------------------------------------------------------
      cout << "FED_HW: STARTING MAIN LOOP" << endl;

      while ( endFlag == 0 )
      {
		 // Request initial values
		 if (requestInitialValues == RTI::RTI_TRUE) 
		 {
			RTI::AttributeHandleSet			*hlaAttributes;

			requestInitialValues = RTI::RTI_FALSE;

			hlaAttributes = RTI::AttributeHandleSetFactory::create(1);
			hlaAttributes->add( initialFuelLevelHandle );

			try
			{
				rtiAmb.requestObjectAttributeValueUpdate(VehicleObject, *hlaAttributes);
			}
			catch ( RTI::Exception& e )
			{
		        cerr << "FED_HW: WHILE REQUESTING INITIAL VALUES. ERROR:" << &e << endl;
			}

			hlaAttributes->empty();

			
			
			hlaAttributes = RTI::AttributeHandleSetFactory::create(1);
			hlaAttributes->add( currentFuelLevelHandle );
			
			
			try {
				rtiAmb.attributeOwnershipAcquisitionIfAvailable( VehicleObject, *hlaAttributes );
			}
			catch ( RTI::Exception& e )
			{
		        cerr << "FED_HW: WHILE ATTRIBUTE OWNERSHIP. ERROR:" << &e << endl;
			}
			hlaAttributes->empty();

			delete hlaAttributes;
		 }


		 // Provide new values
		 if (provideCurrentFuelLevel == RTI::RTI_TRUE) 
		 {
			RTI::AttributeHandleValuePairSet	*valueSetP;
			double								val;

			provideCurrentFuelLevel = RTI::RTI_FALSE;

			currentFuelLevel = currentFuelLevel - 1.0;
	        cerr << "FED_HW: Updated Fuel Level:" << currentFuelLevel << endl;

			val = swap_8byte_quantityP( &currentFuelLevel );

			valueSetP = RTI::AttributeSetFactory::create( 1 );
			valueSetP->add(currentFuelLevelHandle, (char *) &val, sizeof(double));


			try {

				(void) rtiAmb.updateAttributeValues(VehicleObject, *valueSetP, grantTime, "");
			}
			catch ( RTI::Exception& e )
			{
		        cerr << "FED_HW: WHILE UPDATING VALUES. ERROR:" << &e << endl;
			}

			valueSetP->empty();
			delete valueSetP;
		 }


         //------------------------------------------------------
         // 2.) - Ask for a time advance.
         //------------------------------------------------------
         try
         {
            RTIfedTime requestTime(timeStep.getTime());

            requestTime += grantTime;
            timeAdvGrant = RTI::RTI_FALSE;

            rtiAmb.timeAdvanceRequest( requestTime );
         }
         catch ( RTI::Exception& e )
         {
            cerr << "FED_HW: ERROR: " << &e << endl;
         }

         //------------------------------------------------------
         // 3.) Tick the RTI waiting for the grant and process all
         //     RTI initiated services (especially reflections).
         //------------------------------------------------------
         while( timeAdvGrant != RTI::RTI_TRUE )
         {
            //------------------------------------------------------
            // Tick will turn control over to the RTI so that it can
            // process an event.  This will cause an invocation of one
            // of the federateAmbassadorServices methods.
            //
            // Be sure not to invoke the RTIambassadorServices from the
            // federateAmbassadorServices; otherwise, a ConcurrentAccess
            // exception will be thrown.
            //------------------------------------------------------
            rtiAmb.tick(0.01, 1.0);
         }

      } // 5.) - Repeat

      //------------------------------------------------------
      // Ack shutdown synchronization point
      //------------------------------------------------------
	  if (syncPoint[0] != 0) {
		 cout << "FED_HW: SYNCHRONIZATION ACHIEVED" << endl;
		 rtiAmb.synchronizationPointAchieved( syncPoint );
	  }


      //------------------------------------------------------
      // Resign from the federation execution to remove this
      // federate from participation.  The flag provided
      // will instruct the RTI to call deleteObjectInstance
      // for all objects this federate has privilegeToDelete
      // for (which by default is all objects that this federate
      // registered) and to release ownership of any attributes
      // that this federate owns but does not own the
      // privilefeToDelete for.
      //------------------------------------------------------
      try
      {
         cout << "FED_HW: RESIGN FEDERATION EXECUTION CALLED" << endl;
         rtiAmb.resignFederationExecution(
                   RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES ); 
         cout << "FED_HW: SUCCESSFUL RESIGN FEDERATION EXECUTION CALLED" << endl;
      }
      catch ( RTI::Exception& e )
      {
         cerr << "FED_HW: ERROR:" << &e << endl;
         return -1;
      }
   }
   catch (RTI::ConcurrentAccessAttempted& e)
   {
      cerr << "FED_HW: ERROR: Concurrent access to the RTI was attemted.\n"
           << "       Exception caught in main() - PROGRAM EXITING.\n"
           << "\n"
           << "Note:  Concurrent access will result from invoking\n"
           << "       RTIambassadorServices within the scope of\n"
           << "       federateAmbassadorService invocations.\n"
           << "\n"
           << "       e.g. RTI calls provideAttributeValueUpdate() and\n"
           << "       within that method you invoke updateAttributeValues\n"
           << endl;
      cerr << &e << endl;
      return -1;
   }
   catch ( RTI::Exception& e )
   {
      cerr << "FED_HW: ERROR:" << &e << endl;
      return -1;
   }

   cout << "FED_HW: Exiting " << exeName << "." << endl;

   return 0;
}


double swap_8byte_quantityP(double *srcP)
{
	if (is_big_endian == TRUE) {
	
		double	dest;

		memcpy((char *) &dest, (char *) srcP, sizeof(double));
		return( dest );

	} else {

		double			dest;
		double			*destP = &dest;
		long			i;
		unsigned char	*mptr, *iptr;

		mptr = (unsigned char *) srcP;
		iptr = (unsigned char *) (++destP);

		for ( i = 0 ; i < sizeof(double) ; i++)
			*--iptr = *mptr++;

		return(dest);
	}
}
