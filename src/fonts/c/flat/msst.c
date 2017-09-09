/******************************************************************************
 *                                                                            *
 *  Copyright 1992, as an unpublished work by Bitstream Inc., Cambridge, MA   *
 *                               Patent Pending                               *
 *                                                                            *
 *         These programs are the sole property of Bitstream Inc. and         *
 *           contain its proprietary and confidential information.            *
 *                           All rights reserved                              *
 *                                                                            *
 * $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/flat/msst.c,v 1.1 1995-10-03 01:01:58 jra Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1995/03/14 00:30:48  mhd
 * Have this be up to date with my sandbox.  This is for me just an offline
 * version of the font files in /bt/.../ext/c, for offline testing and
 * development.
 *
 * Revision 1.1  1993/05/04  20:14:19  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:50  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 2.19  93/03/15  13:57:46  roberte
 * Release
 * 
 * Revision 2.9  93/03/10  17:15:53  roberte
 * metric_resolution moved from union struct to common area. Oops!
 * 
 * Revision 2.8  93/02/25  15:41:26  roberte
 * Changed logic of checking for exception list terminator. Now check
 * the charID field for BAD_BCID.
 * 
 * Revision 2.7  93/02/23  16:56:52  roberte
 * 
 * 
 * Added #include of finfotbl.h before #include of ufe.h.
 * Changed code to deal with new data organization for symbol sets.  Now looks
 * for terminator flag in the exception list, rather than using the old "count"
 * field of the Master Symbol Set Table.  Also, whenever "parent" set is found,
 * gMasterSymbolSet[] array is filled with UNKNOWN, eliminating the need
 * to store many UNKNOWN entries for the parent sets.  Beware of trying to
 * remove UNKNOWN entries from child sets!  It won't work.
 * 
 * Revision 2.6  93/02/19  12:22:37  roberte
 * Changed interface to fi_check_ssd() function.  Now passed a pclHdrType pointer.
 * Needs this info to detect "bound" or "unbound" fonts for compatibility test.
 * Also uses least significant bit of complement to detect TrueType emulators,
 * and for these does additional check for the TT_OK bit in the symbol set
 * tables' flags field.
 * 
 * Revision 2.5  93/02/04  13:45:53  roberte
 * Added new front end function fi_check_ssd() to verify
 * symbol set/resident font compatability.
 * 
 * Revision 2.4  93/01/29  08:57:23  roberte
 * Added reentrant code macros PARAMS1 and PARAMS2 to support REENTRANT_ALLOC.
 * Added function comment headers and FUNCTION macro before each definition.
 * 
 * Revision 2.3  93/01/06  13:47:47  roberte
 * Changed references to processor_type, gCharProtocol, gDestProtocol, gMustTranslate, gCurrentSymbolsSet, numChars
 * and gSortedBCIDList.  These are now a part of sp_globals.
 * 
 * Revision 2.2  92/12/29  14:29:50  roberte
 * Return to arcane K&R function declartions.
 * 
 * Revision 2.1  92/12/02  12:28:08  laurar
 * include fino.h.
 * 
 * Revision 2.0  92/11/19  15:40:57  roberte
 * Release
 * 
 * Revision 1.9  92/11/03  13:56:12  laurar
 * Include type1.h for CHARACTERNAME declaration.
 * 
 * Revision 1.8  92/11/02  18:33:36  laurar
 * Add STACKFAR to fi_CharCodeXLate parameter list (for DLL).
 * 
 * Revision 1.7  92/10/15  17:37:02  roberte
 * Added support for PROTOS_AVAIL compile time option.
 * 
 * Revision 1.6  92/10/07  17:20:58  roberte
 * Added line of code to set the gMasterSymbolSet[1].symSetID from
 * the ssid parameter in fi_set_cset().  Now the custom set may be
 * selected using a normal fi_select_symbol_set() call.
 * 
 * Revision 1.5  92/09/25  14:54:02  weili
 * Fixed archive comment
 * 
 * Revision 1.4  92/09/25  14:20:39  weili
 * Removed the macros for selecting encoding arrays and put them into ufe.h
 * 
 * Revision 1.3  92/09/25  14:12:18  roberte
 * Added RCS header and copyright notice.
 * 
******************************************************************************/
#include "spdo_prv.h"               /* General definitions for Speedo    */
#include "fino.h"
#include "type1.h"
#include "finfotbl.h"
#include "ufe.h"

extern SymbolSetType	gMasterSymbolSets[];


/*************************************************************************************
*	set_exceptionList()
*		selects a current symbol set with ssid 0 in Entry0_Ptr
*	RETURNS:	
*			 nothing
*************************************************************************************/
FUNCTION void	set_exceptionList (PARAMS2 Entry0_Ptr)
GDECL
ssEntryPtr	Entry0_Ptr;
{
    gMasterSymbolSets[0].exceptionList = Entry0_Ptr;
    fi_select_symbol_set (PARAMS2 0);
}



/*************************************************************************************
*	fi_select_symbol_set()
*		
*	RETURNS:	
*		TRUE on success
*		FALSE on failure
*************************************************************************************/
FUNCTION boolean	fi_select_symbol_set (PARAMS2 ssid)
GDECL
ufix16 ssid;
{
    boolean    found_symbol = FALSE, found_parent = FALSE;
    fix15      symbol_entry = 0, parent_entry = 0;
    fix15      i;
    ssEntryPtr parentPtr, symbolPtr;

    while ( !found_symbol && symbol_entry < ss_TABLE_SIZE )
    {
      if ( gMasterSymbolSets[symbol_entry].symSetID == ssid )
      {
         found_symbol = TRUE;
         for (i=0; i<ss_MAX_ENTRY; i++) 
			sp_globals.gCurrentSymbolSet[i] = UNKNOWN;
         if ( gMasterSymbolSets[symbol_entry].parentSymSetID == UNKNOWN )
         {
			found_parent = TRUE;
            symbolPtr = gMasterSymbolSets[symbol_entry].exceptionList;
			while (symbolPtr->charID != BAD_BCID)
			{
               sp_globals.gCurrentSymbolSet[symbolPtr->ssIndex]=symbolPtr->charID;
               symbolPtr++;
			}
         }
         else
         {
            while ( !found_parent && parent_entry < ss_TABLE_SIZE )
            {
               if ( gMasterSymbolSets[parent_entry].symSetID == gMasterSymbolSets[symbol_entry].parentSymSetID )
               {
                  found_parent = TRUE;
                  parentPtr = gMasterSymbolSets[parent_entry].exceptionList;
				  while (parentPtr->charID != BAD_BCID)
				  {
               		sp_globals.gCurrentSymbolSet[parentPtr->ssIndex]=parentPtr->charID;
               		parentPtr++;
				  }

                  symbolPtr = gMasterSymbolSets[symbol_entry].exceptionList;
				  while (symbolPtr->charID != BAD_BCID)
				  {
               		sp_globals.gCurrentSymbolSet[symbolPtr->ssIndex]=symbolPtr->charID;
               		symbolPtr++;
				  }
               }
               else
                   parent_entry++;
            }
         }     
      }
      else
         symbol_entry++;
    }
	if (found_symbol && found_parent && (sp_globals.metric_resolution == 2048))
		{
		if ((ssid == SSID_PC8TK) || (ssid == SSID_PC8DN) || (ssid == SSID_PC8)) 
			{
			sp_globals.gCurrentSymbolSet[94] = 94;
			sp_globals.gCurrentSymbolSet[126] = 4744;
			}
		if ((ssid == SSID_PC8) || (ssid == SSID_PC8TK) || (ssid == SSID_PC8DN) || (ssid == SSID_PC850) || (ssid == SSID_PC852_Lat2))
			{
			sp_globals.gCurrentSymbolSet[7] = 575;
			sp_globals.gCurrentSymbolSet[254] = 5410;
			}
		}
    return ( found_symbol && found_parent );
}


/*************************************************************************************
*	fi_set_cset()
*		Define a custom symbol set (in slot 1 of gMasterSymbolSets[])
*	RETURNS:	
*			 TRUE on success
*			 FALSE on failure
*************************************************************************************/
FUNCTION boolean	fi_set_cset (PARAMS2 ssid, userList, inProtocol, 
		     first_code, last_code)
GDECL
ufix16 ssid;			/* ID to tag the symbol set with (for later selection) */
void *userList[];		/* input list in whatever protocol desired */
ufix16 inProtocol;		/* the input protocol */
ufix16 first_code;		/* first index in the userList[] */
ufix16 last_code;		/* last index in the userList[]  */
{
    fix15       index = 2;
    ssEntryPtr  currentPtr;
    ufix16      outProtocol;
    fix15       bcidValue;
    int         i;

    while ( index < ss_TABLE_SIZE )
    {
      if ( gMasterSymbolSets[index].symSetID == ssid )
	  return (FALSE);
      else
	  index++;
    }

    currentPtr = gMasterSymbolSets[1].exceptionList;
    outProtocol = protoBCID;
    for (index = 0; index < ss_MAX_ENTRY; index++)
      	currentPtr++->charID = UNKNOWN;
    currentPtr = gMasterSymbolSets[1].exceptionList + first_code;
    for ( index = first_code, i=0; index <= last_code; index++, i++ )
    {
       if ((fi_CharCodeXLate(userList[i], &bcidValue, inProtocol, outProtocol))
           == TRUE)
       	   currentPtr++->charID = bcidValue;
       else
            currentPtr++->charID = UNKNOWN;
    }

    /* currentPtr = gMasterSymbolSets[1].exceptionList; */

	gMasterSymbolSets[1].symSetID = ssid;	/* set the tag field */

    return ( TRUE );
}

/*************************************************************************************
*	fi_check_ssd()
*		Checks whether symbol set "ssid" is compatible with character complement
*		Pass in values from char_complement_?sw from the FIT table of resident fonts.
*	RETURNS:	
*			 TRUE on success
*			 FALSE on failure (additionally found_ssd FALSE if this is cause of failure)
*************************************************************************************/
FUNCTION boolean	fi_check_ssd (lfontHdr, ssid, found_ssd)
pclHdrType *lfontHdr;
ufix16 ssid;
boolean *found_ssd;
{
fix15       index = 0;
ufix32		requirementMSW, requirementLSW;
boolean 	success = FALSE; /* assume the worst! */
boolean		bound;	 /* bound or unbound font */

	bound = (lfontHdr->size < 88);
	*found_ssd = FALSE;
    while ( !(*found_ssd) && ( index < ss_TABLE_SIZE ) )
    {/* walk through looking for the ssid: */
    	if ( gMasterSymbolSets[index].symSetID == ssid )
			*found_ssd = TRUE; /* bingo-schmingo! */
		else
			index++;
    }
	if (*found_ssd)
	{
		if (bound) /* see if the lfontHdr->symbol_set matches the ssid param: */
			success = (lfontHdr->symbol_set == ssid);
		else
			{ /* now let's compare complements and requirements: */
			requirementMSW = gMasterSymbolSets[index].char_requirement_msw;
			requirementLSW = gMasterSymbolSets[index].char_requirement_lsw;
			success =	(
							((requirementMSW & (requirementMSW ^ lfontHdr->char_complement_msw)) == requirementMSW) &&
							((requirementLSW & (requirementLSW ^ lfontHdr->char_complement_lsw)) == requirementLSW)
						);
			if (success && !(lfontHdr->char_complement_lsw % 2) )
				success = (gMasterSymbolSets[index].flags & TT_OK);
			}
	}
	return(success);
}
/* EOF msst.c */
