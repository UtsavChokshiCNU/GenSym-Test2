/  
/ $Header: readme.txt 09-dec-2003.11:30:43 subanerj Exp $
/  
/ Copyright (c) 1991, 1997, 1998, 1999, 2003 by Oracle Corporation  
/ PRODUCT VERSION DESCRIPTION 
  
Product/release:    PRO* 1.8 
Version:	    1.8.78   (released with 10BETA1)
Status: 	    Beta
History: 
 
   09-Dec-03   Update for 1.8.78 with 10.1.0.2.0 - Production
   10-Apr-03   Update for 1.8.78 with 10i Beta-1 (10.1.0.0) 
   09-Aug-02   [2425918] To clarify CHARACTER*(*) usage restriction in PROFOR.
   09-Jan-02   Update for 1.8.77 with beta 9.2.0 
   19-Oct-99   Update for 1.8.51 with production 8.1.6.
   09-Feb-99   Update for 1.8.50 with production 8.1.5.
   29-Apr-98   Update for 1.8.27 with 8.0.5 production.
   29-Dec-97   FORTRAN optimization NOT supported with Pro*Fortran.
   05-Dec-97   Update for 1.8.26 production
   18-Dec-95   Update for 1.8.2/1.6.26 production.
   09-Sep-95   Included bugs for 1.7.3/1.6.9 production. 
 
 
-------------------------------------------------------------------------- 
 
Important Notification:
----------------------

Starting version 10.1, version 1.x of Pro*COBOL has been replaced with
Pro*COBOL 10.1.

-------------------------------------------------------------------------- 

o Overview 
  -------- 
  Starting with version 10.1, the precompiler version 1.x set includes 
  only Pro*Fortran.
 
  Pro*Fortran is now in maintenance mode.  Serious deficiencies will 
  be corrected, but no new features will be added.

o Version Matrix 
  -------------- 
  STATUS         RDBMS      PRO*FOR
  Production     10.1.0.2   1.8.78.0

  STATUS         RDBMS  PRO*COB, PRO*FOR
  Production     9.2.0      1.8.77
  Beta           9.2.0      1.8.77
  Beta           9.0.0      1.8.75
  Production     8.1.7      1.8.52
  Production     8.1.6      1.8.51
  Production     8.1.5      1.8.50
  Production     8.0.5      1.8.27
  Production     8.0.4      1.8.26
  Production     8.0.3      1.8.25
  Production     7.3.4      1.8.4  
 
o Desupport Notification for V6 Compatibility behavior
  ----------------------------------------------------
  With Oracle7, Oracle offered a Version 6 [V6] Compatibility flag that 
  allowed application developers developing Oracle7 applications to 
  emulate Oracle6 behavior. With the release of Oracle8.0.3, users are 
  cautioned that the Version 6 compatibility flag is being desupported 
  effective immediately in all of the Oracle8 products including PL/SQL8, 
  all the Oracle Precompilers, the Oracle8 Oracle Call Interface, 
  SQL*Module, and SQL*PLUS. The desupport of the V6 compatibility flag 
  is consistent with Oracle?s policy of supporting backwards compatibility 
  and behavior from one version release upgrade to another i.e. from 
  Oracle6 to Oracle7 but not for more than one version release upgrade.
 
  Specifically, the V6 Compatibility flag emulated the following aspects of
  Oracle6 behavior with Oracle7:
 
  o String literals are fixed length in Oracle7 but are treated as variable
    length with the V6 flag
  o PL/SQL Local char variables are fixed length in Oracle7 but are treated
    as variable length with the V6 flag.
  o Return value of SQL Functions (e.g. USER) are fixed length characters    
    in Oracle7 but are treated as variable length characters with the V6 flag.
  o Select/Fetch of a NULL with no indicator raises an ORA-1405 error with
    Oracle7 but returns no error with the V6 flag.
  o SQL group function is called at FETCH time with Oracle7 but is called at
    query execution time with the V6 flag.
  o Describe of a fixed length string returns Type=96 with Oracle7 but returns
    Type=1 with the V6 flag.
 
  All of these behaviors are being desupported with the desupport of the V6
  Compatibility Flag with Oracle8.

o New Features for Version 1.8.52
  None.  

o New Features for Version 1.8.51
  None.  

o New Features for Version 1.8.50
  None.  

o New Features for Version 1.8.25
  -------------------------------
 
  Support for NCHAR data in Pro*COBOL

  NCHAR data is now fully supported by the kernel.  Previous releases
  of the precompiler supported this datatype with the NLS_LOCAL option.
  For new applications, users are strongly encouraged to rely on the
  database support and accordingly set NLS_LOCAL=NO during precompilation.

* Note: In all the following bug descriptions, when the product name 
        (e.g. Pro*COBOL or Pro*FORTRAN, etc.) is not mentioned the fix
        is applicable to generic Pro* version 1.


o Changes for version 1.8.78
  --------------------------

3100988  PROFOR crashed on some platforms due to insufficient CUD buffer size.
         PROFOR crashed on some platforms due to insufficient CUD buffer size.

2425918  Use of CHARACTER*(*) as a host variable generated bad code
         Use of CHARACTER*(*) as a host variable generated bad code. This 
         is a restriction of PRO*FOR.

2370012  PROFOR/F90 application at runtime generated core dump
         When F90 compiler was used for PROFOR application (i.e. it is
         happening for the first time), at runtime core dump occurred.
         Core dump happened due to misaligned literal value while calling
         SQLBF1.


o Changes for version 1.8.75
  --------------------------

746347  Dynamic sql method-4 generated wrong sqlerrd[4] value
 	to point to erroneous column number.  With the fix, correct 
	value is getting assigned to sqlerrd[4]. 

1175132 Unnecessary parsing for INSERT caused performance degradation.
	When INSERT statement caused an ORA-0001 error, it triggered 
	reparsing of INSERT statement everytime, causing performance 
	degradation.  Reparsing was not done only for ORA-1403, ORA-1405 
	and ORA-1406.  With the fix, reparsing will never be done unless 
	parse errors occurs.        

1416079 Performance degraded for array fetch when missing indicator variables.
	For the array fetch without indicator variable, the fetching was done 
	with single row, making more roundtrips to server for data fetching 
	in 8i. With the fix, the number of fetch calls is the same as 
	in 8.0.6.

1508116 SQLMOV was always generated enclosed within QUOTEs.
	Some platforms use APOST(') to enclose the call to 
	particular procedures.  But, SQLMOV was always 
	enclosed within QUOTEs ("), generating an error. 
	With the fix, by default and when litdelim=quote, 
	SQLMOV will be enclosed within ("), whereas if
        litdelim=apost, SQLMOV will be enclosed within (').

1576145 Performance degraded from 8.0 to 8.1 due to unnecessary defines.
	For the single FETCH statement in the loop, performance degraded 
	from 8.0 to 8.1.  This was due to unnecessary define calls for 
	each host variable for every iterations.  With the fix, the same 
	FETCH statement after it gets parsed, and defined all its host 
	variables, will not call defines for any next iterations.           

o Changes for version 1.8.52
  --------------------------

819158  PROCOB generated wrong code, giving compiler error. 
	PROCOB generated wrong code, while generating VARCHAR variables. 
	This generated compiler error. With the fix, correct code 
	with the appropriate indentation is being generated.                        

968261  Use of mode=ansi in PROCOB generated wrong code. 
	When mode=ansi was used, procob generated redefines and 	
	global clause incorrectly for some compilers. With the 
	fix, correct code is being generated.                                       

973363  Wrong generated code produced compiler error. 
	When a group name (having FILLER as one of the element) is used 
	as a host-variable in INTO clause, PROCOB generated wrong code. 
	This wrong code produced compiler error.  With the fix, correct 
	code is being generated. 

o Changes for version 1.8.51
  --------------------------

936178  Application using XA to CONNECT and precompiled with RELEASE_CURSOR=YES
        caused memory leak.

913475  Application with multiple connections where fetching data within the
        non-lst connect/diconnect loop could result in ORA-01002 fetch out of
        sequence error.

909020  EXEC SQL DESCRIBE SELECT LIST with none query sql statement gets
        ORA-24338: statement handle not executed runtime error.

904273  Dynamic Method 4 application with DESCRIBE BIND VARIABLES statement
        and using host arrays in a FOR clause in the EXECUTE statements would
        get core dump at runtime.

869146  When precompiled application with mode=ansi13, procob18 generated code
        to have cursor closed after commit and caused ORA-01001: invalid cursor
        at run-time.

821874  Whenever "AT" clause was used during CONNECT, sqlus.msb error
        handle was getting opened, which was not necessary.  With the
        fix, opening of sqlus.msb has been delayed until the error occurs.

792409  PROFOR generated bad code when long source file name was used.
        DATA SQLFNM is generated with the source file name.  When the file
        name is very long, which required the name to be split across the
        lines after 72nd column, the continuation on next line was not done
        correctly.  With the fix, the correct code is being generated.

791384  Append of a lob to a null lob is an error. However, the error
        message returned by sqllib did not describe the situation.

772411  Generated core dump at run-time for a close cursor statement in a
        dynamic method 4 application.

772048  Core dump occurred during Pro*Cobol precompilation.
        Appropriate condition check has been made to fix this
        core dump.

720030  Large value was generated for cursor variable when precompiled with
        AUTO_CONNECT=YES

716236  Pro*For generated extra code for SAVE statement

693939  Character, ANSI varying character and ANSI fix character types
        were not blank padded when used in ANSI dynamic programs.  They
        are now blank padded and the returned length field is undefined.

650069  When long config file name was used with the CONFIG option or
        when the system default config file was used from the location
        of long absolute path name, precompiler generated a core dump.
        With this fix, the long file name will be trucated before it gets
        printed in listing file.

638805  Message text for SQL-2113 was specific to VMS and needed to be made
        generic.

o Changes for version 1.8.50
  --------------------------

764952  Dml returning did not properly return an array of column values
        when an array of indicators was also requested.

754066  When an embedded sql dml returning statement had more than two columns,
        erroneous behavior occurred.

752463  Memory leak occured when NCHAR host variable was used and precompiled
        with NLS_LOCAL=YES

735298  Memory used for EXEC TOOLS GET statement did not get freed after use.

729969  procob18 used to generate size 1 for the temporary indicators variable
        regardless of the size of the array variables, which caused memory
        problem such as attempt to access item beyond bounds.

717698  Executing embedded PL/SQL with indicator set to -1 created
        memory problem or run-time error.

709191  When type equivalencing a varying (varchar) type host variable
        was used, procob18 generated core dump.

704985  When NLS_LOCAL=YES was used, multi-byte character host variable,
        specifying <=2 bytes length, could not be fetched.

652497  Pro*COBOL generated the wrong code for shift-based multi-byte character
        set applications.

644711  Incorrect code was generated when PREPARE or EXECUTE IMMEDIATE
        used an unquoted string.  All the spaces used as a separation
        of words in a string were removed.


        For example,
           EXEC SQL PREPARE S1 FROM
              DECLARE
                CURSOR C1 IS SELECT 0 FROM DUAL;
              BEGIN
                FOR R1 IN C1 LOOP
                  NULL;
                END LOOP;
              END;
           END-EXEC.

        generated incorrect code as:
        01  SQ0001.
            02  FILLER PIC X(68) VALUE "DECLARECURSORC1ISSELECT0FROMDUAL;
        -        "BEGINFORR1INC1LOOPNULL;ENDLOOP;END;".

        which generated runtime errors.

        With the fix, following correct code is being generated:

        01  SQ0001.
            02  FILLER PIC X(82) VALUE "DECLARE CURSOR C1 IS SELECT 0 FRO
        -        "M DUAL;BEGIN FOR R1 IN C1 LOOP NULL;END LOOP;END;".

606918  Pro*COBOL generated incorrect code for VARYING variables when an
        element of the generated group item exceeded one line.  In a
        multi-byte environment, the line break could have occurred between
        bytes of a multi-byte character, causing compile time errors.

602746  Due to lack of specific clear informations in any documents, this bug
        was reported for  Pro*FORTRAN. We have NEVER supported the use of
        FORTRAN compiler optimization with Pro*FORTRAN.  We expected users to
        turn off any FORTRAN compiler optimization.  This is actually a DOC
        bug, but since there are NO NEW Pro*FORTRAN DOC coming out, this is
        clarified in this readme.txt file.

596907  procob18 generated core dump at precompile-time when a declare table
        statement was used.

563793  Due to mismatch of number of options available and the allocated
        space, a core dump was occurring on some platforms.  The number
        of table entries for available options have been corrected.

422430  Pro*FORTRAN: Due to Fortran compiler restriction on MVS, subscripted
        variables needed to be declared as INTEGER*4.  SQCNT is a generated
        subscripted  variable, which was always declared as INTEGER*2.
        Now, for MVS, SQCNT is being declared as INTEGER*4.

414298  If the statement text for an EXEC SQL EXECUTE IMMEDIATE was supplied
        in a host variable, e.g. EXEC SQL EXECUTE IMMEDIATE :create_as_select;
        Then the rows processed count in the sqlca.sqlerrd was not updated.
        The sqlca.sqlcode was updated to accurately reflect the results of
        the statement execution.

o Changes for version 1.8.27
  --------------------------

644711  Incorrect code was generated when PREPARE or EXECUTE IMMEDIATE 
        used an unquoted string.  All the spaces used as a separation
        of words in a string were removed.  

        For example, 
            EXEC SQL PREPARE S1 FROM
               DECLARE
                  CURSOR C1 IS SELECT 0 FROM DUAL;
               BEGIN
                 FOR R1 IN C1 LOOP
                   NULL;
                 END LOOP;
               END;
            END-EXEC.

        generated incorrect code as:

       01  SQ0001.
           02  FILLER PIC X(68) VALUE "DECLARECURSORC1ISSELECT0FROMDUAL;
      -        "BEGINFORR1INC1LOOPNULL;ENDLOOP;END;".

        which generated runtime errors. 
        
        With the fix, following correct code is being generated:

       01  SQ0001.
           02  FILLER PIC X(82) VALUE "DECLARE CURSOR C1 IS SELECT 0 FRO
      -        "M DUAL;BEGIN FOR R1 IN C1 LOOP NULL;END LOOP;END;".

642112  When the connection was not made through embedded sql connect
        statement, sqllib returned ORA-01012 error message.

622811  A memory leak occurred when a cursor was closed.

606918  Pro*COBOL generated incorrect code for VARYING variables when an
        element of the generated group item exceeded one line.  In a 
        multi-byte environment, the line break could have occurred between
        bytes of a multi-byte character, causing compile time errors.

602746  Due to lack of specific clear informations in any documents, this bug
        was reported for  Pro*FORTRAN. We have NEVER supported the use of 
        FORTRAN compiler optimization with Pro*FORTRAN.  We expected users to 
        turn off any FORTRAN compiler optimization.  This is actually a DOC 
        bug, but since there are NO NEW Pro*FORTRAN DOC coming out, this is 
        clarified in this readme.txt file.

583044  VARCHAR host variables in CALL statements were not properly expanded 
        and were eliminated by the optimization process of the COBOL compiler.
  
        This resulted in incorrect execution of SQL statement.
       
553658  Core dump was seen on NT platform with an application that used the 
        precompiler options nls_char and nls_local.  In NT multi-threaded  
        applications the global runtime context did not get correct  
        nls_char and nls_local information, leading to a core dump.   

549812  Pro* core dumped when three or more names(e.g., x x x) were given as
        file names. When Pro* processes command line options, it expects one
        input file name and one output file name.  Pro* has been modified to
        allow more than two filenames on command line with the appropriate
        error message.

480085  Pro*COBOL: Did not issue an error message when include file did not 
        exist.  When the file to be included did not exist in any of the 
        include directories or in the local directory, following error message
        is being generated:

        PCC-S-0013:  Unable to open include file "..." at line ... 
                     in file sample.pco

422430  Pro*FORTRAN: Due to Fortran compiler restriction on MVS, subscripted 
        variables needed to be declared as INTEGER*4.  SQCNT is a generated
        subscripted  variable, which was always declared as INTEGER*2.
        Now, for MVS, SQCNT is being declared as INTEGER*4.

o Changes for version 1.8.26
  --------------------------
  None. 
 
o Changes for version 1.8.25
  --------------------------

480085  Pro*COBOL did not issue error message when include file did not exist.

397677  Pro*COBOL generated incorrect code for type equivalenced implicit
        varchar host variables.  This resulted in an ORA-1465 error at runtime.

383782  Pro*COBOL sometimes generated code for cursor declarations that
        went beyond column 72.

372681  Pro*COBOL generated incorrect code when the END-EXEC was 
        followed by spaces instead of a period (.).

369874  Pro*COBOL generated incorrect code when a host variable had
        no value in the VALUE clause.  e.g.
                01  PASSWD   PIC X(8) VALUE.

369866  EXEC SQL EXECUTE IMMEDIDATE with LITDELIM=QUOTE resulted in an
        apostrophe used a the delimiter.

369862  The wrong value for MAXLITERAL appeared in the listing file.

369858  Pro*COBOL ignored inline specification of the LITDELIM option.

366790  Pro*COBOL seg faulted when sequence numbers appeared on a line with
        a varchar (PIX VARYING) declaration.

345014  Pro*COBOL generated incorrect code for embedded SQL statements of
        exactly 33 characters when FORMAT=TERMINAL.  This resulted in
        compilation errors.

319845  Pro*COBOL seg faulted when input file name length exceeded 100 
        characters.  If user provided an input filename (which includes 
        the input filename path) and it happened to be over 100 characters 
        long, the precompiler seg faulted due to an internal limit of 
        100 characters.


o Changes for version 1.8.2/1.6.26
  --------------------------------
46734   The precompiler was not producing an error message when there was
        a syntax error after the USING clause in the EXECUTE statement.
        The error was not detected at precompile time but resulted in an
        error at runtime.

63012   Unless the application uses release_cursor=yes when a cursor is closed,
        subsequent fetches did not return an error and the data was successfully
        retrieved.

161029  Pro*Cobol was wrongly producing an error when the USAGE IS DISPLAY 
        clause was being used with PIC X(n) declarations.

228054  Pro*Cobol did not preserve the user's indentation of the varchar
        (varying) declarations.  This enhancement will now preserve the
        user's indentation in the generated code.

244692  Pro*COBOL seg faulted when the CURRENT OF clause was misspelled.

259033  Pro*Fortran produced lines which extended past column 72 when the
        size of the variable name was long and the indentation was high
        but less than 20.

272453  Precompiler help screen was too crowded and the syntax for the
        values for sqlcheck was not clear.  Help screen has been reformatted.

277841  If no connection could be established, a generic error message was
        returned in the sqlca.  This could happen if, for example, the
        TWO_TASK environment variable is set to an incorrect value.
        Now, a generic error message will only be returned if no connection
        can be established and no message files exist on the client side.

280423  Pro*Cobol generated incorrect PIC X declarations.  Both the size of
        PIC X variable and the length of the string value were incorrect
        when the maxliteral was specified.

282450  Pro*Fortran closed the .pc0 file twice which caused memory exception
	problems on some platforms.

282466  The precompiler was generating bind vars for the plain EXECUTE statement
        (which does not have the USING clause).  The problem was occurring when
        the same statement name was used in an EXECUTE USING statement then
        in the plain EXECUTE statement such as:
          ...
          EXEC SQL EXECUTE S USING :a, :b;
          ...
          EXEC SQL EXECUTE S;
          ...

286704  Pro*Cobol was generating the SQLCTX initialization with a very large
        value, too large for the size of the variable.  SQLCTX is declared
        of type S9(9) and the value being assigned into it was 10 digits.

286765  When binding host arrays to PL/SQL tables through dynamic SQL, runtime
        errors would result.

287771  Upon a disconnect, the shadow process remained alive until either a
        reconnect or process termination.

288212  The included files for dynamic method 4 bind and select descriptors need
        port specific changes for 64 bit architecture machines.

289201  Runtime errors were generated for precompiler applications generated
        from very large (~> 100,000 lines) pro* source files.

291358  Pro*Cob did not comment out the conditional precompilation statements
        (EXEC ORACLE IFDEF/DEFINE/ELSE/ENDIF) when the "." (period) was missing
        from  the END-EXEC of those statements, thus creating a compile-time 
	error.

293284  When an exec tools message in Pro*Fortran or Pro*Cobol extended beyond
        the end of coding area (column 72) an internal error message was issued.

297549  The error messages on the screen showed the incorrect error line, 
	usually the line following the actual line which contained the error.  
	This problem only occurred in Pro*Cobol and Pro*Fortran.

299716  Pro*Cobol was changing the / (slash) in column 7 to * (asterisk) when
        the line(s) followed any EXEC SQL statements, varchar declarations,
        or comment lines that follow any EXEC SQL stmt or varchar declarations.

308436  The precompiler did not allow input file names exceeding 30 characters.
	This problem effected 1.6.8+ and 1.8 beta versions.

308877  Pro*COBOL could not handle comment entries properly in the IDENTICATION
        DIVISION.  Comment entries can include any of the ASCII characters and
        are only allowed in the IDENTIFICATION DIVISION.

309750  Pro*Fortran generated code which could cause an access violation or 
	failure to compile when the program used both dynamic method 4 and 
	a host variable as the database base name in the connect and declare 
	statement statements.

315856  Pro*Fortran looped infinitely when END statement is missing.


o  Changes for version 1.7.3/1.6.9 
   ------------------------------- 
234550  Pro*Cobol generated wrong string continuation with format=terminal. 

264560  Using EXEC SQL INCLUDE SQLCA with FORMAT=TERMINAL did not work when 
        COMP5=YES was also used. 

265143  Pro*Cobol did string continuation based on columns instead of bytes, 
        which caused problems for COBOL compilers that limit the line 
        length to 72 *bytes* not columns. 

275498  Precompilers seg faulted when statement had undeclared SQL identifier 
        instead of giving an error.  For example, in the following statement 
        "exec sql update emp set sal = 8000 where current of S;", if S was 
        not a declared cursor, the precompilers seg faulted instead of giving 
        and undeclared SQL identifier error. 
277265  Precompiler host option values needed to be language specific. 

278919  Reusing the same statement identifier sometimes resulted in ORA-2117. 
        The following sequence of statements resulted in an ORA-2117 error if 
        application precompiled with mode=ansi: 
         PREPARE s for . . . (e.g. an insert) 
         EXECUTE s 
         PREPARE s for select . . . 
         DECLARE c1 cursor for s 
         OPEN c1 

280423  Pro*Cobol generated incorrect PIC X declarations for multi-byte input 
        when maxliteral was specified.  Both the size of PIC X variables and 
        the length of the string value were incorrect. 

286704  Pro*Cobol was generating the SQLCTX initialization with a very large 
        value, too large for the size of the variable.  SQLCTX is declared 
        of type S9(9) and the value being assigned into it was 10 digits. 

289201  Runtime errors were generated for precompiler applications generated 
        from very large (~> 100,000 lines) pro* source files. 
 
o  Selected bug fixes for version 1.7.2/1.6.8 
   ------------------------------------------ 
159536  PRO* did not FIPS flag CREATE TRIGGER/PROCEDURE/etc. when FIPS=YES
187108  Error in sample10.ppl caused process crash on VMS platform.
208483  EXECUTE IMMEDIATE of string literal in PRO*Pascal applications failed
227880  sample10.pco needed changes to work on 64 bit architectures.
227882  sample10.pco needed changes to work on 64 bit architectures.
232998  A Pro*Pascal A.V. occurred when large indentation before EXEC SQL
234392  Pro*FORTRAN generated incorrect code for EXECUTE USING DESCRIPTOR.
240736  Unable to use type long varchar for host variable in PREPARE stmt.
241616  Pro*FORTRAN produced multiple SQCNT declarations when many SQL stmts.
241962  Pro*Fortran looped infinitely when source was missing an END stmt.
249976  The saved statement text in the ORACA (ORASTXTC) was not always correct.
250474  Parse errors occurred with long SQL statements and AUTO_CONNECT=YES
252217  Prototypes in sqlcpr.h were different from those in generated code.
252492  ANSI-style prototypes were missing from the public header sqlcpr.h
252654  PRO*1.6 did not use SQLCODE var when not declared in DECLARE SECTION
257248  Pro*Fortran went into infinite loop when END was missing from source.
258928  The function gensqf was not callable from Pro*Fortran applications.
259349  An error was not given when the filename length > maximum length.
260457  The oracle_forms.message procedure did not always complete successfully.
261282  The usage of precompiler command line options was not properly checked.
262332  Pro* did not prompt for password when not given in userid option
264068  EXEC SQL IFDEF of EXEC TOOLS statements did not work correctly
265136  Pro*Cobol generated bad sql statement when given maxlit in multibyte env
265424  Spurious precompilation errors given sometimes using SQL functions
267024  Pro*FORTRAN did not properly indent generated code when format=terminal.
270254  ORA-2100 error generated if number of open cursors exceeded MaxCur.

o Selected bug fixes for version 1.6.7 or prior 
  --------------------------------------------- 
273548  code=ansi_c gives incorrect type of sqlstm.stmt (Pro*C) 
256436  Exec SQL TYPE Varchar gets zero length in generated code (Pro*C) 
240736  Error 2108 when preparing a statement from a long varchar host variable 
227634  Program dumps core if run without a valid database connection 
226183  Pro*Cobol seg faults with sqlcheck=full and undeclared host variable 
224364  Pro*Fortran precompiler does not preprocess if stmt starts at column 9 
219215  Reprepare/reexecute after reconnect on timeout results in ORA-1012/1001 
217245  Cursors were marked as open even if the open failed. 
216274  Pro*Fortran was not generating declaration for I when multi=no. 
212820  Pro*Fortran generated bad code if source had an 'A' in the 99th column 
210998  Access violation when multisubprog=no and no DECLARE section in input 
209717  No error given if the dimensions of host and indicator arrays differ 
206153  Cursor status not maintained correctly for dynamic SQL in ANSI mode. 
199380  Programs with COMMIT WORK got ORA-2114 errors if mode=ansi&hold_cur=yes 
198808  Bad code generated when quote falls at the end of the line (Pro*Cobol) 
192959  Pro*for pgms errored with multisub=no and reconnected to database. 
191554  Compiler errors occurred in PRO*COB terminal format apps using ORACA 
189568  PRO* runtime library generated more calls to the database than needed. 
187443  Pro*Ada always re-parsed SQL statements, even with hold_cursor=yes. 
184461  PRO*FOR generated empty COMMON statements when LANGUAGE=nationalcharst 
183591  Use of pointers to VARCHAR arrays could cause various problems. 
168678  SQLCHECK=SEMANTICS without userid ignores DECLARE TABLE statements 
149317  Precompiler ignored errors in FETCH statements even when SQLCHECK=FULL. 
147034  XA appl's could get ORA-1001 on 2nd exec of dynamic cursor. 
135528  Attempts to reconnect failed if COMMIT/ROLLBACK work RELEASE failed. 


o Restriction in PROFOR
  ---------------------

2425918 To clarify CHARACTER*(*) usage restriction in PROFOR.

        Since we ship PROFOR DOC manual with our existing libraries only, 
        PROFOR manual is no longer updated. Instead, this README gets updated.

        The following changes should be noted: 

        CHARACTER(*)  variable type as described in Table 1-3 of the 
        Pro*Fortran manuals should be deleted. 

        Note 2 for Table 1-3 should be read as: 

        CHARACTER*(*) variables have no predetermined length. They are used 
        to specify dummy arguments in a subroutine declaration. The  maximum 
        length of an actual argument is returned by the LEN intrinsic function.
        Though, CHARACTER*(*) variables are valid FORTRAN variable names, 
        these are not supported as a host variable. 
