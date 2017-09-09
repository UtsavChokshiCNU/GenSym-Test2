/***************************************************************************
 *
 *		Callbacks.c
 *
 *			Contains the required GSI RPC functions. 
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/

#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>
#include	<string.h>

#include	<sys/types.h>
#include	<sys/stat.h>
#if !defined(WIN32)
#include	<sys/wait.h> 
#endif

#include	"G2Agent.h"
#include	"G2AgentMessages.h"

/*-------------------------------------------------------------------------*
 *
 *	Add a source to the registry
 *
 *-------------------------------------------------------------------------*/

void rpc_add_log_event_source (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	DWORD dwData;
	DWORD dwDisp; 
	TCHAR szBuf[MAX_PATH]; 
	LPTSTR pszLogName; // Application log or a custom log
	LPTSTR pszSrcName; // event source name
	LPTSTR pszMsgDLL;  // path for message DLL
	DWORD  dwNum;      // number of categories
	HKEY hk;
	char szFilePath[_MAX_PATH];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_add_log_event_source().\n");

	// Collect arguments 
	pszLogName	= str_of(item_array[0]);
	pszSrcName	= str_of(item_array[1]);
	pszMsgDLL	= str_of(item_array[2]);
	dwNum		= int_of(item_array[3]);

	if (strlen(pszLogName) == 0)
		pszLogName = "Application";

	if (strlen(pszMsgDLL) == 0) {
		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));
		pszMsgDLL = szFilePath;
	}

	// Create the event source as a subkey of the log
	wsprintf(szBuf, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s\\%s", pszLogName, pszSrcName);
 
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,
			szBuf, 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_WRITE, NULL, &hk, &dwDisp))  {
		
    	log_with_timestamp(LOG_MODE_DEBUG, "Could not create the registry key.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
		return;

	} else 
	   	log_with_timestamp(LOG_MODE_DEBUG, "Added registry key: %s.\n", szBuf);

 
	// Set the name of the message file. 
	if (RegSetValueEx(hk,            // subkey handle 
          "EventMessageFile",        // value name 
          0,                         // must be zero 
          REG_EXPAND_SZ,             // value type 
          (LPBYTE) pszMsgDLL,        // pointer to value data 
          (DWORD) (lstrlen(pszMsgDLL)+1) * sizeof(TCHAR))) // data size
	{
		RegCloseKey(hk); 

    	log_with_timestamp(LOG_MODE_DEBUG, "Could not set the event message file.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
		return;

	} else 
	   	log_with_timestamp(LOG_MODE_DEBUG, "Added registry value: EventMessageFile = %s.\n", pszMsgDLL);
 
	// Set the supported event types.  
	dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE; 

	if (RegSetValueEx(hk,     // subkey handle 
           "TypesSupported",  // value name 
           0,                 // must be zero 
           REG_DWORD,         // value type 
           (LPBYTE) &dwData,  // pointer to value data 
           sizeof(DWORD)))    // length of value data
	{

		RegCloseKey(hk); 

    	log_with_timestamp(LOG_MODE_DEBUG, "Could not set the supported types.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
		return;

	} else 
	   	log_with_timestamp(LOG_MODE_DEBUG, "Added registry value: TypesSupported = %d.\n", dwData);

	// Set the category message file and number of categories.
	if (RegSetValueEx(hk,             // subkey handle 
           "CategoryMessageFile",     // value name 
           0,                         // must be zero 
           REG_EXPAND_SZ,             // value type 
           (LPBYTE) pszMsgDLL,        // pointer to value data 
           (DWORD) (lstrlen(pszMsgDLL)+1)*sizeof(TCHAR))) // data size
	{

		RegCloseKey(hk); 

    	log_with_timestamp(LOG_MODE_DEBUG, "Could not set the category message file.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
		return;

	} else 
	   	log_with_timestamp(LOG_MODE_DEBUG, "Added registry value: CategoryMessageFile = %s.\n", pszMsgDLL);
 
	if (RegSetValueEx(hk,     // subkey handle 
           "CategoryCount",   // value name 
           0,                 // must be zero 
           REG_DWORD,         // value type 
           (LPBYTE) &dwNum,   // pointer to value data 
           sizeof(DWORD)))    // length of value data
	{

		RegCloseKey(hk); 

    	log_with_timestamp(LOG_MODE_DEBUG, "Could not set the category count.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
		return;

	} else 
	   	log_with_timestamp(LOG_MODE_DEBUG, "Added registry value: CategoryCount = %d.\n", dwNum);

	RegCloseKey(hk); 

	set_log (local_gsi_itemP[0], GSI_TRUE);
	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_add_log_event_source().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Report Event on a given computer and source
 *
 *-------------------------------------------------------------------------*/

void log_event(gsi_item item_array[], gsi_int count, call_identifier_type call_index, WORD wType)
{
	LPTSTR		pszComputerName;
    LPTSTR		pszSrcName;			// event source name
    DWORD		dwEventID;			// event identifier
    WORD		wCategory;			// event category
    LPCTSTR*	pInserts;			// insert strings
    LPTSTR		pszData;			// data strings
	LPVOID		pData = NULL;
	DWORD		szData = 0;
	WORD		nbInserts = 0;
	int			i;
    HANDLE		h;
	gsi_char	empty[] = "";
	gsi_item	arg, elt;
	gsi_item	*elt_array;

	/// Get arguments
	pszComputerName	= str_of(item_array[0]);
	pszSrcName		= str_of(item_array[1]);
    dwEventID		= (DWORD) int_of(item_array[2]);
    wCategory		= (WORD) int_of(item_array[3]);
    pszData			= str_of(item_array[5]);

    arg = item_array[4];
	pInserts = NULL;
	nbInserts = (WORD) gsi_element_count_of(arg);

	if (nbInserts > 0) {

		elt_array = elements_of(arg);
		pInserts = malloc(sizeof(LPTSTR) * nbInserts);

		for (i = 0 ; i < nbInserts ; i++) {

			elt = elt_array[i];

			if ( !is_item(elt) && type_of(elt) == STRING_TAG) {

				pInserts[i] = gsi_str_of(elt);

			} else {

				pInserts[i] = empty;
			}
		}
	}

	// validate arguments
	if (strlen(pszComputerName) == 0)
		pszComputerName = NULL;

	if (pszData != NULL && strlen(pszData) > 0) {

		szData = strlen(pszData);
		pData = pszData;
	}

    // Get a handle to the event log.
    h = RegisterEventSource(
			pszComputerName,  // use local computer 
            pszSrcName);      // event source name 

    if (h == NULL) 
    {
    	log_with_timestamp(LOG_MODE_DEBUG, "Could not register the event source.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		return;
    }

    // Report the event. 
    if (!ReportEvent(h,           // event log handle 
            wType,	 			  // event type 
            wCategory,            // event category  
            dwEventID,            // event identifier 
            NULL,                 // no user security identifier 
            nbInserts,			  // number of substitution strings 
            szData,               // no data 
            pInserts,			  // pointer to strings 
            pData))               // no data 
    {
    	log_with_timestamp(LOG_MODE_DEBUG, "Could not report the event.\n");

	    DeregisterEventSource(h); 
		if (pInserts != (LPCTSTR*) NULL)
			free((void *) pInserts);

		set_log (local_gsi_itemP[0], GSI_FALSE);
		gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

		return;

    } else {

 	   	log_with_timestamp(LOG_MODE_DEBUG, "Added new event Type = %d, Category: %d, ID: %d, nb text inserts: %d.\n", wType, wCategory, dwEventID, nbInserts);
	}

    DeregisterEventSource(h); 
	if (pInserts != (LPCTSTR*) NULL)
		free((void *) pInserts);

	set_log (local_gsi_itemP[0], GSI_TRUE);
	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());
}


void rpc_log_error_event (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_log_error_event().\n");

	log_event(item_array, count, call_index, EVENTLOG_ERROR_TYPE);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_log_error_event().\n\n");
}


void rpc_log_warning_event (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_log_report_warning_event().\n");

	log_event(item_array, count, call_index, EVENTLOG_WARNING_TYPE);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_log_warning_event().\n\n");
}

void rpc_log_information_event (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	log_indentation = 0;

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_log_information_event().\n");
	log_event(item_array, count, call_index, EVENTLOG_INFORMATION_TYPE);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_log_information_event().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	Return number of records and id of last event for
 *	specified source and computer.
 *
 *-------------------------------------------------------------------------*/

void rpc_get_log_info (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	HANDLE h;
	DWORD nbOfRecords = 0;
	DWORD oldestRecord = 0;
	LPTSTR pszComputerName;
	LPTSTR pszSrcName;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_get_log_info().\n");

	// Get arguments
	pszComputerName	= str_of(item_array[0]);
	pszSrcName	= str_of(item_array[1]);

	if (strlen(pszComputerName) == 0)
		pszComputerName = NULL;

    // Open the desired event log.  
    h = OpenEventLog(pszComputerName, pszSrcName); 

	if (h == NULL) 
	{
		log_with_timestamp(LOG_MODE_DEBUG, "Could not open the System event log.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		set_int (local_gsi_itemP[1], nbOfRecords);
		set_int (local_gsi_itemP[2], oldestRecord);
		gsi_rpc_return_values (local_gsi_itemP, 3, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_get_log_info().\n\n");
		return;
	}
 
	// Display the number of records and the oldest record. 
	if (GetNumberOfEventLogRecords(h, &nbOfRecords))
		log_with_timestamp(LOG_MODE_DEBUG, "Number of records in the %s log: %d\n", pszSrcName, nbOfRecords);

	if (GetOldestEventLogRecord(h, &oldestRecord))
		log_with_timestamp(LOG_MODE_DEBUG, "Oldest record in the log %s: %d\n", pszSrcName, oldestRecord);

	CloseEventLog(h); 
 
	// Return results
	set_log (local_gsi_itemP[0], GSI_TRUE);
	set_int (local_gsi_itemP[1], nbOfRecords);
	set_int (local_gsi_itemP[2], oldestRecord);

	gsi_rpc_return_values (local_gsi_itemP, 3, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_get_log_info().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Get application log entries
 *
 *-------------------------------------------------------------------------*/

#define BUFFER_SIZE 1024*64

void rpc_get_log_entries (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	HANDLE h;
    EVENTLOGRECORD *pevlr; 
    BYTE bBuffer[BUFFER_SIZE]; 
    DWORD dwRead, dwNeeded, dwThisRecord; 
	LPTSTR pszComputerName;
	LPTSTR pszSrcName;
	gsi_char buf[STRSZ];
	gsi_char events[10 * STRSZ];
	gsi_char *pszType;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_get_log_entries().\n");

	// Get arguments
	pszComputerName	= str_of(item_array[0]);
	pszSrcName	= str_of(item_array[1]);

	if (strlen(pszComputerName) == 0)
		pszComputerName = NULL;

    // Open the desired event log.  
    h = OpenEventLog(pszComputerName, pszSrcName); 

    if (h == NULL) 
    {
    	log_with_timestamp(LOG_MODE_DEBUG, "Could not open the Application event log.\n");

		set_log (local_gsi_itemP[0], GSI_FALSE);
		set_str (local_gsi_itemP[1], "");
		gsi_rpc_return_values (local_gsi_itemP, 2, call_index, gsi_current_context());

		log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_get_log_entries().\n\n");
		return;
    }
 
    pevlr = (EVENTLOGRECORD *) &bBuffer; 

	sprintf(events, "Count,Event-ID,Event-type,Event-source");

    // Get the record number of the oldest event log record.
    GetOldestEventLogRecord(h, &dwThisRecord);

    // Opening the event log positions the file pointer for this 
    // handle at the beginning of the log. Read the event log records 
    // sequentially until the last record has been read.  
    while (ReadEventLog(h,                // event log handle 
                EVENTLOG_FORWARDS_READ |  // reads forward 
                EVENTLOG_SEQUENTIAL_READ, // sequential read 
                0,            // ignored for sequential reads 
                pevlr,        // pointer to buffer 
                BUFFER_SIZE,  // size of buffer 
                &dwRead,      // number of bytes read 
                &dwNeeded))   // bytes in next record 
    {
        while (dwRead > 0) 
        { 
            // Print the record number, event identifier, type, 
            // and source name.  

			// Create sequence of structures with attributes
			//	record: dwThisRecord
			//	event-id: pevlr->EventID
			//	event-type: pevlr->EventType (symbol: error, warning, informatiom, audit-success, audit-failure
			//	event-source: (LPSTR) ((LPBYTE) pevlr + sizeof(EVENTLOGRECORD))
            switch(pevlr->EventType)
            {
                case EVENTLOG_ERROR_TYPE:
                    pszType = "EVENTLOG_ERROR_TYPE";
                    break;
                case EVENTLOG_WARNING_TYPE:
                    pszType = "EVENTLOG_WARNING_TYPE";
                    break;
                case EVENTLOG_INFORMATION_TYPE:
                    pszType = "EVENTLOG_INFORMATION_TYPE";
                    break;
                case EVENTLOG_AUDIT_SUCCESS:
                    pszType = "EVENTLOG_AUDIT_SUCCESS";
                    break;
                case EVENTLOG_AUDIT_FAILURE:
                    pszType = "EVENTLOG_AUDIT_FAILURE";
                    break;
                default:
                    pszType = "Unknown";
                    break;
            }

            printf("%03d  Event ID: 0x%08X  Event type: %30s Event source: %s\n",
				dwThisRecord++, pevlr->EventID, pszType, (LPSTR) ((LPBYTE) pevlr + sizeof(EVENTLOGRECORD))); 

			// For now returning a comma separated text (csv format) but eventually should change this
			// to return a sequence of structure, though not the easiest to build in gsi.
			sprintf(buf, "\n%d,%d,%s,%s",
				dwThisRecord++, pevlr->EventID, pszType, (LPSTR) ((LPBYTE) pevlr + sizeof(EVENTLOGRECORD))); 
			strcat(events, buf);

            dwRead -= pevlr->Length; 
            pevlr = (EVENTLOGRECORD *) ((LPBYTE) pevlr + pevlr->Length); 
        } 
 
        pevlr = (EVENTLOGRECORD *) &bBuffer; 
	} 
 
    CloseEventLog(h); 

	set_log (local_gsi_itemP[0], GSI_TRUE);
	set_str (local_gsi_itemP[1], events);
	gsi_rpc_return_values (local_gsi_itemP, 2, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_get_log_entries().\n\n");
}