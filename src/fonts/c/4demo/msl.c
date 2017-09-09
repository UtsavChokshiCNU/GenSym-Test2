#include "spdo_prv.h"               /* General definitions for Speedo    */
#include "fino.h"
#include "type1.h"
#include "finfotbl.h"
#include "ufe.h"					/* Unified Front End definitions */
#include "pcl5fnt.h"

typedef	struct
	{
	fix15		fileIndex;
	ufix16	charID;
	} pclEntry;


boolean  BSearch PROTO((fix15 STACKFAR*indexPtr, fix15 (*ComparisonTo)(fix31, void STACKFAR *),
					void STACKFAR *theValue, fix31 nElements));

boolean  MSLtoIndex PROTO((ufix16 STACKFAR *intPtr));

fix15    MSLCompare PROTO(( fix31 idx, void STACKFAR *keyValue));

void BuildSortedMSLIDList();

static   fix15    numAdded;

boolean  gListSorted = FALSE;

static   pclEntry gSortedMSLList[256];

extern   PC5HEAD  pcl5head;


fix15    MSLCompare ( idx, keyValue)
fix31 idx;
void STACKFAR *keyValue;
{
fix15 NumComp(), result;
ufix16 theMSLID;
	theMSLID = gSortedMSLList[idx].charID;
	result = NumComp( (ufix16 STACKFAR *)keyValue, (ufix16 STACKFAR*)&theMSLID);
	return(result);
}

boolean MSLtoIndex(intPtr)
ufix16 STACKFAR *intPtr;
{
ufix16 outValue;
boolean success = FALSE;
	outValue = 0;
	success = BSearch ( (fix15 STACKFAR*)&outValue, MSLCompare,
						(void STACKFAR *)intPtr, (fix31)numAdded );
	if (success)
		*intPtr = gSortedMSLList[outValue].fileIndex;
	return(success);
}

void BuildSortedMSLIDList()
{
   fix15 i, j, k, theSlot;
   ufix16   STACKFAR theMSL;
   boolean  result, found;

   if (gListSorted)
      return;
   if (pcl5head.size != 80)
   {
      printf("do not support unbound pcl font\n");
      exit(1);
   }
   if ( (result = fi_select_symbol_set( PARAMS2 pcl5head.symbol_set )) == TRUE )
   {
      numAdded = 0;
      for (i=0; i < 256; i++)
      {
         if ( sp_globals.gCurrentSymbolSet[i] != UNKNOWN )
         {
      		result = fi_CharCodeXLate  ( (void STACKFAR *)&sp_globals.gCurrentSymbolSet[i],
               			   					(void STACKFAR *)&theMSL,
	   		            	   				protoBCID, protoMSL);
            if (result == TRUE)
            {
               theSlot = numAdded;
               found = FALSE;
               for (j=0; !found && (j < numAdded); j++)
               {
                  if (gSortedMSLList[j].charID > theMSL)
                  {
                     theSlot = j;
                     found = TRUE;
                  }
               }
               for (k=numAdded; k > theSlot; k--)
                  gSortedMSLList[k] = gSortedMSLList[k-1];
         		gSortedMSLList[theSlot].charID = theMSL;
         		gSortedMSLList[theSlot].fileIndex = i;
               numAdded++;
            }
         }
      }
   }         
   else
   {
      printf("could not find symbol set ID %d\n", pcl5head.symbol_set);
      exit(1);
   }
   gListSorted = TRUE;
}      

