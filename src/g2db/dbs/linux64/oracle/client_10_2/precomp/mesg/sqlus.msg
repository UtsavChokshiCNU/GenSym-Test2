/ 
/ $Header: sqlus.msg 24-nov-96.14:04:31 jnewman Exp $ 
/ 
/ Copyright (c) 1991, 1995, 1996, 1998, 1999 by Oracle Corporation 
/   NAME
/     sqlerr.msg 
/   DESCRIPTION
/     Precompiler runtime library (SQLLIB) error msgs
/   NOTES
/       ** Important **
/       If this file is updated, you must contact the appropriate technical
/       writer to inform him/her of the changes.  As of 7.2 production,
/       this file now matches the Error Messages and Codes Manual.
/
/       Message text should be limited to a maximum of 76 characters.
/	Messages containing embedded % directives should not overrun
/	the 76 character limit unless they signal unusual errors
/	which do not occur as part of user applications.  For example,
/	startup errors and system-dependent errors can probably get
/	away with longer message text.
/   MODIFIED   (MM/DD/YY)
/    lvbcheng   03/09/99 - bug 638805: use generic reference
/    lvbcheng   01/12/99 - Add null lob error msg
/    gturk      10/28/98 - spelling corrections
/    gturk      11/11/97 - [SQL92]errors for dynamic client descriptors
/    nikeda     05/20/98 - Add new collections message
/    nikeda     05/14/98 - Add error message for a null collection
/    nikeda     04/28/98 - Add collections error messages
/    nikeda     04/08/98 - Add external procedures error messages
/    jnewman    11/24/96 - edit cause and action statements
/    nikeda     11/27/96 -  Update 2136 error message
/    gturk      09/17/96 -  Added error mesg for unable to set date format
/    nikeda     09/12/96 -  NCHAR enhancement
/    nikeda     01/05/96 -  Reword some sqllib messages
/    gdas       10/11/95 -  Rename  sqlerr.msg to sqlus.msg
/    nikeda     05/12/95 -  Add new threads-related error messages
/    nikeda     01/28/95 -  Sync with the 7.2 production version of manual
/    jbasu      09/08/94 -  Remove message for 1002 (kernel error)
/    jbasu      08/02/94 -  Add message for 1002 error
/    nikeda     05/24/94 -  Add 2130 - Returned if callbacks not regd
/    nikeda     05/10/94 -  NTT/MIA - New error 2129 (odd # bytes for MIA)
/    losborne   01/11/94 -  New XA error msg 2128
/    rhari      06/16/93 -  add error message 2127 
/    losborne   02/22/93 - #(149318) Keep track of state of connection 
/    rhari      02/20/93 - #(150827) new error message 2126 for negative count
/    losborne   11/24/92 -  Change msg for err 2115 
/    losborne   11/16/92 -  Add 'No connect, can't get msg error' 
/    losborne   07/17/92 -  Correct 2134 to 2124 
/    losborne   07/16/92 -  Err when NULL value frm TOOLS stmt and no indic 
/    losborne   07/13/92 -  EXEC TOOLS error msgs 
/    losborne   05/11/92 -  Add msg 2122 
/    losborne   01/17/92 -  New err msgs for XA support functions 
/    losborne   04/18/91 - file renamed from error.msg to sqlerr.msg
/  Olkin      01/25/91 - add error 2118, invalid rowid on where current of
/  Olkin      01/09/91 - add cursor already opened error
/  Olkin      11/20/90 - add reentrant error messages
/  Olkin      11/15/90 - add message 1405
/
/ List of Precompiler SQL Runtime errors
/
/ ?? This file is converted to header/message files using lmsgen.c.
/
/ The first col is the ORACLE error number.
/ The second column is reserved and must (for now) be x00000
/ The remainder of the line is the error text
/ There also needs to be on the 2 following lines after the error number
/ and message and line for the "cause" and a line for the "action".
/
/ Adding an error for PCC:
/    Check out this file, add the error, and check it back in.	Error numbers
/    should always be ordered.	The second column should always be x00000.
/
/ The following error messages, numbered less than 2100, are nonetheless SQLLIB
/ error messages: they can be issued by SQLLIB.
/
00100, 0, "no data found" 
// *Cause: 
// *Action: 
01001, 0, "invalid cursor" 
// *Cause: 
// *Action: 
01012, 0, "not logged on" 
// *Cause: 
// *Action: 
01057, 0, "invalid or ambiguous block.field reference in user exit" 
// *Cause: 
// *Action: 
01075,  0, "you are currently logged on" 
// *Cause: There is already a connection on this host. 
// *Action: Do not attempt the second connection. 
01403, 0, "no data found" 
// *Cause: 
// *Action: 
01405, 0, "fetched column value is NULL" 
// *Cause: 
// *Action: 
01454, 0, "cannot convert column into numeric datatype" 
// *Cause: 
// *Action: 
01460, 0, "unimplemented or unreasonable conversion requested" 
// *Cause: 
// *Action: 
/ 
/ 2100 .. 2139 - Reserved for precompiler runtime (SQLLIB) 
/ 
02100, 00000, "Out of memory (i.e., could not allocate)" 
// *Cause:  SQLLIB was unable to allocate enough memory to execute 
//          the program.
// *Action: Allocate more memory to the user session, then rerun the program.
//          If the error persists, call customer support for assistance. 
02101, 00000, "Inconsistent cursor cache. Unit cursor/global cursor mismatch" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02102, 00000, "Inconsistent cursor cache.  No global cursor entry." 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02103, 00000, "Inconsistent cursor cache. Out of range cursor cache reference"
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02104, 00000, "Inconsistent host cache.  No cursor cache available" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02105, 00000, "Inconsistent cursor cache.  Global cursor not found" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02106, 00000, "Inconsistent cursor cache.  Invalid Oracle cursor number" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02107, 00000, "Program too old for runtime library; please re-precompile it" 
// *Cause:  The program was precompiled by an older version of the Oracle
//          Precompilers, which is incompatible with this release of SQLLIB. 
// *Action: Precompile the program with a newer version of the Oracle
//          Precompilers.
02108, 00000, "Invalid descriptor passed to run-time library" 
// *Cause:  This internal error typically indicates a memory-related error.
// *Action: Check the program for memory-related errors, such as invalid
//          pointers or array-bounds violations.
02109, 00000, "Inconsistent host cache.  Host reference is out of range" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02110, 00000, "Inconsistent host cache.  Invalid host cache entry type" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02111, 00000, "Heap consistency error" 
// *Cause:  This internal error typically indicates a memory-related 
//          error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02112, 00000, "SELECT..INTO returns too many rows" 
// *Cause: A SELECT...INTO statement returned more rows than can be stored 
//         in the host variable provided. 
// *Action: There are 3 possible solutions: 
//          1. Use the precompiler option select_error=no. 
//          2. Declare a host variable with a larger array dimension.
//          3. Declare a cursor or cursor variable for the select statement. 
/ The following is a fake error message in the sense that it is never retrieved 
/ from this file (it is hard coded into the SQLLIB). 
/ Leave it here as a place holder! 
02113, 00000, "Unable to open message file" 
// *Cause: SQLLIB was unable to find or open the sqllib message file
//  sql*.msb
// *Action: Check that the file exists in the mesg directory and that
// it is readable
02114, 00000, "Invalid SQL Cursor usage: trying to CLOSE a CLOSEd cursor" 
// *Cause: An attempt was made to CLOSE a cursor that was already CLOSEd with
//         MODE={ANSI|ANSI14}.  A CLOSEd cursor can be re-CLOSEd only when
//         MODE={ORACLE|ANSI13}.
// *Action: When MODE={ANSI|ANSI14}, verify that a cursor is not already CLOSEd
//          before trying to CLOSE it.  Specify MODE={ORACLE|ANSI13} if a
//          CLOSEd cursor is to be re-CLOSEd.  
02115, 00000, "Code interpretation problem -- check COMMON_NAME usage" 
// *Cause: With PRO*FORTRAN, this error occurs if the precompiler option
//         COMMON_NAME is specified incorrectly.  With other Oracle
//         Precompilers, this error occurs when the precompiler cannot
//         generate a section of code.
// *Action: With Pro*FORTRAN, when using COMMON_NAME to precompile two or
//          more source modules, make sure to specify a different common name
//          for each module.  With other Oracle Precompilers, if the error
//          persists, call customer support for assistance.
02116, 00000, "FATAL ERROR: Reentrant code generator gave invalid context" 
// *Cause: This internal error typically indicates a memory-related 
//         error. 
// *Action: Check the program for memory-related errors, such as invalid 
//          pointers or array-bounds violations. 
02117, 00000, "Invalid SQL Cursor usage: trying to OPEN an OPENed cursor" 
// *Cause: An attempt was made to OPEN a cursor that was already OPENed with
//         MODE={ANSI|ANSI14|ANSI13}.  An open cursor can be re-OPENed only 
//         when MODE=ORACLE.
// *Action: When MODE={ANSI|ANSI14|ANSI13}, verify that a cursor is not 
//          already OPENed before trying to OPEN it.  Specify 
//          MODE=ORACLE if an OPENed cursor is to be re-OPENed.  
02118, 00000, "Invalid row for a WHERE CURRENT OF operation" 
// *Cause: An attempt was made to reference a nonexistent row using the 
//         CURRENT OF clause in an UPDATE or DELETE statement. 
//         This happens when no FETCH has been  executed or when FETCH
//         returns a "no data found" error that the program fails to trap.  
// *Action: Check that the last cursor operation succeeded and that the 
//         current row of the cursor is valid. The outcome of a cursor 
//         operation can be checked in two ways: implicit checking with the
//         WHENEVER statement or explicit checking of SQLCODE in the SQLCA. 
02119, 00000, "Invalid HSTDEF argument" 
// *Cause: A non-null ptr was given for a hstdef as the second argument to 
//         a call to sqlrcn when the first argument was also used.  Either
//         the first or the second argument to SQLRCN must be null.
// *Action: Pass a null pointer in either the first or second argument to 
//          SQLRCN. 
// *Note: This error *msg* is never actually used.  The error *number* is 
//        used, given as the return value of sqlrcn if this error occurs. 
02120, 00000, "First and second arguments to SQLRCN both null" 
// *Cause: Both the first and second arguments to sqlrcn were null.  
//         An HSTDEF must be passed into SQLRCN in either the form of 
//         an OCI lda (first argument) or as an HSTDEF pointer itself 
//         (second argument). 
// *Action: Pass in either an OCI LDA or an HSTDEF, but not both. 
// *Note: This error *msg* is never actually used.  The error *number* is 
//        used, given as the return value of sqlrcn if this error occurs. 
02121, 00000, "Invalid host name" 
// *Cause: The host name passed into a SQLFCN call was not used in a previous 
//         call to SQLRCN. 
// *Action: Use the same identifier used in the corresponding SQLRCN 
//          call. 
// *Note: This error *msg* is never actually used.  The error *number* is 
//        used, given as the return value of sqlfcn if this error occurs. 
02122, 00000, "Invalid OPEN or PREPARE for this database connection" 
// *Cause:  An attempt was made to execute an OPEN or a PREPARE statement 
//          using a cursor that is currently open for another database
//          connection and, therefore, cannot be used for this connection.
// *Action: Close the cursor to make it available for this connection or use
//          a different cursor for this connection.
02123, 00000, "Context referenced in EXEC TOOLS GET CONTEXT statement not found" 
// *Cause: The context name given in the EXEC TOOLS GET CONTEXT statement 
//         was never stored with an EXEC TOOLS SET CONTEXT statement. 
// *Action: Use the EXEC TOOLS SET CONTEXT statement to save any contexts 
//          to be retrieved later. 
02124, 00000, "NULL value returned by EXEC TOOLS statement" 
// *Cause: A NULL value was returned by EXEC TOOLS for a host variable that
//         lacks an indicator variable.  This error is returned only when  
//         MODE=ANSI.  When MODE=ORACLE, although the value of the host
//         variable is indeterminate, no error is generated.
// *Action: Associate an indicator variable with each host variable to which
//          nulls might be returned.
02125, 00000, "Connect error, can't get error text"
// *Cause: No connection (not even to the default host) was available,
//         so SQLLIB could not get the message text for the Oracle error that
//         occurred.  However, SQLLIB returns the Oracle error number, which
//         can be used to look up the message.
// *Action: Look up the appropriate message in the Oracle7 Server Messages
//          manual, and follow the Cause and Action information provided.
02126, 00000, "Count of array elements cannot be negative (i.e. < 0)" 
// *Cause: The precompiler found a negative number of array elements in the
//         the N or F element of the SQLDA (SQL Descriptor Area, which is
//         used with dynamic SQL Method 4).  Before executing the 
//         DESCRIBE statement, N must be set to the dimension of the
//         descriptor arrays.  After executing the DESCRIBE statement,
//         N must be reset to the actual number of variables DESCRIBEd, which
//         is stored in the F variable.
// *Action: Check that the N or F variables are set to non-negative values.
02127, 00000, "Precompiler/SQLLIB version mismatch" 
// *Cause: The program was linked to an older version of SQLLIB, which is
//         incompatible with this release of the Oracle Precompilers.
// *Action: Relink the program with a newer version of SQLLIB 
02128, 00000, "Sessions still exist, not logged off" 
// *Cause: A host was not removed ("logged off") from SQLLIB because XA still
//         has sessions associated with that host.
// *Action: Before calling SQLXDH to drop a host, XA must either drop all
//          sessions for that host or set the "doit_anyway" flag.
// *Note: This error *msg* is never actually used.  The error *number* is 
//         used, given as a possible return value to the sqllib xa function 
//         sqlxdh. 
02129, 00000, "Fetched number of bytes is odd." 
// *Cause: The program tried to FETCH an invalid column value into a 
//         multi-byte NLS host variable.  Specifically, the column did not
//         contain valid double-byte data.
// *Action: Make sure the column contains only double-byte data.  To verify
//          this, use SQL*Plus or Server Manager.
02130, 00000, "EXEC TOOLS interface is not available." 
// *Cause: An attempt was made to link with a version of an Oracle tool
//         that does not support the EXEC TOOLS interface.
//         EXEC TOOLS interface.   
// *Action: Either upgrade the Oracle tool, or use the EXEC IAF interface.
02131, 00000, "Runtime context in use"
// *Cause: Your application attempted to execute a SQL statement using a 
//         runtime context that is already in use.
// *Action: Rewrite the application to either wait for one thread to complete
//          before executing another SQL statement with the same runtime
//          context, or to allocate and use a separate runtime context for
//          each thread.
02132, 00000, "Unable to allocate runtime context sdfla asdjklfajs jfja ajsdf"
// *Cause: An attempt to allocate a runtime context failed.
// *Action: This error typically occurs when the process memory is low.
//          Allocate more memory and run the application again.
02133, 00000, "Unable to initialize process for use with threads"
// *Cause: This is an internal error.
// *Action: Call customer support.
02134, 00000, "Invalid runtime context"
// *Cause: The runtime context associated with this statement has not
//         been properly allocated.
// *Action: Rewrite the application to execute the EXEC SQL CONTEXT ALLOCATE
//          statement before executing any SQL statements.
02135, 00000, "Unable to initialize date format using supplied mask"
// *Cause: The runtime library was unable to issue a set date format 
//         statement with the date format mask supplied.
// *Action: Check the validity of the date format and correct if necessary. 
//          Check the ORA error number for further information.
02136, 00000, "Invalid NCHAR character set id"
// *Cause: An attempt was made to bind or define an NCHAR host variable,
//         and the NLS_NCHAR variable was not set correctly.
// *Action: Set the NLS_NCHAR environment variable to a valid fixed width
//          character set id and run the application again.
02137, 00000, "Multi-threaded agent with no RETURNING clause present"
// *Cause:  The EXEC SQL REGISTER CONNECT statement does not contain a
//          RETURNING clause and the agent is running in threaded mode.
// *Action: Re-code the statement to use a RETURNING clause that references
//          a declared sql_context host variable.
02138, 00000, "No external procedure context exists"
// *Cause:  The external procedure context passed in the 
//          EXEC SQL REGISTER CONNECT statement is not valid.
// *Action: Ensure that you have done the following:
//          1. Created the PL/SQL procedure/function with a CONTEXT parameter.
//          2. Included OCIExtProcContext in the formal parameter list
//             of the external procedure
//          3. Correctly passed the OCIExtProcContext to the
//             EXEC SQL REGISTER CONNECT statement.
02139, 00000, "Unable to get the OCI handles"
// *Cause:  The call to OCIExtProcGetEnv failed.  
// *Action: Ensure that the OCIExtProcContext that the external procedure
//          has been created with a CONTEXT parameter and that this context
//          is correctly referenced in the EXEC SQL REGISTER CONNECT statement.
02140, 00000, "An unnamed connection already exists"
// *Cause:  An attempt to register an external procedure context was made
//          when an unnamed connection already exists for the runtime context.
// *Action: Do not attempt to establish any connections with the
//          EXEC SQL CONNECT statement from external procedures.
02141, 00000, "Collection descriptor has not been allocated"
// *Cause:  An unallocated collection descriptor was referenced in a 
//          COLLECTION SET or COLLECTION GET statement.
// *Action: Allocate the collection descriptor with the EXEC SQL ALLOCATE
//          statement.  e.g. EXEC SQL ALLOCATE :coldesc_p;
02142, 00000, "Collection is NULL"
// *Cause:  The collection referenced in an EXEC SQL COLLECTION statement
//          is null. 
// *Action: Check the status of the associated indicator variable prior
//          to executing an EXEC SQL COLLECTION statement.
02143, 00000, "Target object has not been properly allocated"
// *Cause:  An attempt was made to retrieve elements from a collection
//          into an unallocated object pointer.
// *Action: Allocate the object pointer with the EXEC SQL ALLOCATE statement.
02144, 00000, "Invalid ANSI dynamic usage"
// *Cause: An ANSI allocate, deallocate, get or set descriptor statement was
//         encountered when dynamic option was not set.
// *Action: Precompile your source with option dynamic=ansi.
02145, 00000, "Invalid dynamic descriptor"
// *Cause: An attempt to access an unallocated or invalid descriptor was
//         encountered.
// *Action: For ANSI descriptors, check that descriptor name is valid and
//          descriptor has been allocated and not previously deallocated.
//          Or if using Oracle descriptors (sqlda) with mode=ansi also use
//          dynamic=oracle.
02146, 00000, "Attempt to allocate an existing descriptor"
// *Cause: An attempt allocated a descriptor which has previously been
//         allocated was encountered.
// *Action: Use and unique descriptor name or deallocate the descriptor  
//          before attempting to reallocate it.
02147, 00000, "ANSI Dynamic occurrence value out of range"
// *Cause: The value clause in a dynamic GET or SET statement is less than one
//         or greater than MAX given for descriptor allocation.
// *Action: Supply a number for the VALUE clause between 1 and the MAX   
//          occurrences supplied when the descriptor was allocated.
02148, 00000, "ANSI Dynamic count value out of range"
// *Cause: The count in a dynamic GET or SET statement is less than one
//         or greater than MAX given for descriptor allocation.
// *Action: Supply a number for the COUNT clause between 1 and the MAX   
//          occurrences supplied when the descriptor was allocated.
02149, 00000, "ANSI Dynamic insufficient item descriptor areas"
// *Cause: The SQL statement being described contains more output
//         items (or columns) than were allocated in the descriptor.
// *Action: Increase the MAX number of occurrences when allocating   
//          the descriptor.
02150, 00000, "Encountered zero length in ANSI dynamic SET statement"
// *Cause: An invalid length of zero was encountered in an ANSI 
//         dynamic statement.
// *Action: Set the length to a non-zero value 
02151, 00000, "Invalid host variable for exact numeric SET statement item"
// *Cause: An host variable with an invalid type or length was used to get 
//         or set an exact numeric item in an ANSI dynamic statement.
// *Action: Make sure your host variable is and int or short for C or for 
//        COBOL, S9(4) or S9(9) binary/comp/display sign leading separate.
02152, 00000, "Invalid numeric variable for use in an array GET/SET statement"
// *Cause: An host variable with type other than int or short for C or 
//         S9(4) or S9(9) binary or comp was used for an exact numeric 
//         with and array size > 1.
// *Action: Use only int or short for C or S9(4) or S(9) binary or comp 
//        for COBOL when supplying an exact numeric in conjunction with
//        the for clause to indicate arrays.  Specifically, display sign
//        leading separate is not allowed in this context.
02153, 00000, "Invalid character variable for use in a GET/SET statement"
// *Cause: An host variable with type other than character, string or 
//         varchar was found as an item name (other than DATA item) in
//         an ANSI Dynamic GET or SET descriptor statement.
// *Action: Host variable types for character items (other than the DATA
//        item) in ANSI dynamic GET or SET descriptor statements must not 
//        be of type LONG or LONG VARCHAR.  Redeclare the variable
//        to be character, string or varchar type
02154, 00000, "Invalid or unset data type for host variable in ANSI Dynamic"
// *Cause: An ANSI Dynamic SET statement with item name DATA was encountered
//         with out a valid TYPE having been previously set and option
//         mode=ansi was used
// *Action: With mode=ansi, you must set the TYPE before setting the DATA.
//        Issue a SET statement with correct item TYPE or, for output issue a
//        DESCRBE to set the item type.  Or use mode=oracle which allows the
//        type to default to the type of the bind/define host variable
02155, 00000, "Date Time Interval only valid with Dynamic=ANSI"
// *Cause: An attempt to access the datetime interval code or precision
//         was encountered when type_code option not set to ANSI
// *Action: Use precompiler option type_code=ansi to access the date time 
//        interval code or date time interval precision
02156, 00000, "Invalid type for Indicator or Returned Length"
// *Cause: A host variable associated with the item Indicator or Returned
//         Length must be of type short or s9(4) comp. If value semantics
//         and scalar they may also be gotten into display sign leading 
//         separate host variables
// *Action: Use signed short for indicator, ref indicator and returned length,
//         ref returned length host variables in C. For COBOL use s9(4) comp.  
//         for GETs only with non-arrays and you may use display sign leading
//         separate host variables
02157, 00000, "Source or destination lob is invalid"
// *Cause: One of the lobs used in the lob append call is invalid or possibly
//	   null.
// *Action: Make sure the lobs used in the append call are non-null.
/ End of PCC SQL Runtime Error Messages 

