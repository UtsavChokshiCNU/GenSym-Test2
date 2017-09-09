/ 
/ $Header: pcsus.msg 21-sep-2001.07:33:13 ardesai Exp $
/ 
/ Copyright (c) 1991, 1996, 1997, 1998 by Oracle Corporation 
/   NAME
/     pcsus.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    ardesai    09/21/01  - Error messages for scrollable cursor.
/    losborne   10/28/98 -  Correct max descriptor error
/    losborne   05/13/98 -  [UCS2] Add UTEXT, UVARCHAR, and LONG_UVARCHAR types
/    mchiocca   04/06/98 -  Flag Alter Authorization with Connect Mode
/    mchiocca   03/19/98 -  External Procedures and Threads Context Changes
/    mchiocca   03/11/98 -  [SQL92] Implement ANSI Dynamic SQL Methods
/    mchiocca   02/25/98 -  [LOB] Miscellaneous LOB Corrections
/    mchiocca   02/10/98 -  [COLL] Add Collection Feature Error Messages
/    mchiocca   01/21/98 -  [LOB] Add Error Messages for LOB Support
/    mchiocca   08/05/97 -  Implement User Settable Runtime Context Options
/    mchiocca   07/30/97 -  [Optima] Fixed String Tables for Unparsing
/    mchiocca   06/25/97 -  [506520] Allow SQL hints on INSERT statements
/    mchiocca   06/09/97 -  [501631] Add space to 'connect by ' message
/    mchiocca   05/20/97 -  Flag 'Incomplete type specification' error
/    mchiocca   05/20/97 -  [NAV] A few more miscellaneous errors
/    mchiocca   05/13/97 -  [NAV] Object and REF Array Size Match Testing
/    mchiocca   04/28/97 -  [NAV] Add Type Conversion Error Message
/    mchiocca   04/27/97 -  [OBJECT] Implement DECLARE for Object Table
/    mchiocca   04/18/97 -  [NAV] Implement Navigational GET and SET
/    mchiocca   04/16/97 -  [NAV] Add ERRORS for OBJECT CREATE and DEREF
/    mchiocca   04/15/97 -  [NAV] Add certain Navigational Syntax
/    jbasu      04/14/97 -  [OBJECT] Error messages for collections and REFs
/    mchiocca   03/26/97 -  [471039] Using SQL Hints in DELETE statements
/    mchiocca   03/22/97 -  [OBJECT] Add new datatypes for DECLARE TABLE
/    mchiocca   03/17/97 -  Add some Translation Instructions and Comments
/    mchiocca   03/13/97 -  Change all set commands to pure DDL syntax
/    mchiocca   03/05/97 -  [454727] Implement PARTITION clause on table names
/    mchiocca   02/27/97 -  Implement DECLARE TYPE for PL/SQL type checking
/    mchiocca   02/22/97 -  [454733] WITH READ ONLY/WITH CHECK OPTION
/    jbasu      01/04/97 -  [OBJECTS] More error handling
/    erohwedd   12/10/96 -  modify MIA V6_CHAR message: complain about CHAR_MAP
/    jnewman    11/24/96 -  edit Cause and Error statements
/    jbasu      11/07/96 -  [OBJECT] Add errors for new object types
/    erohwedd   10/30/96 -  [CHAR_MAP] add warning PCSERRV6CHAR
/    mchiocca   10/15/96 -  Implement indicators for ADTs in Alloc/Free
/    mchiocca   09/20/96 -  [NCHAR] Proper semantic analysis for NCHAR
/    mchiocca   07/02/96 -  [309090] Error if VARCHAR in a #included file
/    sylin      06/14/96 -  [365771] ARRAYLEN must be a 4-byte integer
/    mchiocca   07/10/96 -  [OBJECT] Implement collection MULTISET subqueries
/    mchiocca   06/26/96 -  [OBJECT] Implement CAST expressions
/    mchiocca   06/18/96 -  [OBJECT] Implement Collection Syntax in Pro*C
/    sylin      02/27/96 -  [317858] Bad error message when can't open files
/    mchiocca   01/24/96 -  Arrays of Structs - Initial Implementation
/    mchiocca   08/15/95 -  [257051] Correct problem when INAME = ONAME
/    mchiocca   07/23/95 -  Bundle [263167] [260289] [257551] [233995]
/    jbasu      06/13/95 -  Rename pcserr.msg to pcsus.msg
/    mchiocca   05/16/95 -  [250965] Enum not allowed as bind variable
/    mchiocca   05/12/95 -  [261377] Allow varchars to be passed by value
/    jbasu      04/24/95 -  [275985] Add error msgs 344, 388, 389
/    gdas       04/21/95 -  merge changes from branch 1.38.720.5
/    mchiocca   02/14/95 -  Add some thread safety error conditions
/    gdas       03/03/95 -  Added Cause/Action Text for some errors	
/    mchiocca   02/01/95 -  [248822] PL/SQL semantic checks for declared cursor
/    mchiocca   10/05/94 -  [241240] Indicator/Host array size comparison
/    mchiocca   08/16/94 -  [231358] Enable varchar decl initialization
/    mchiocca   07/26/94 -  NTT MIA - Clarify a couple MIA error messages
/    mchiocca   07/07/94 -  [224731] Oracle Option Abbreviations on LHS/RHS
/    mchiocca   06/27/94 -  Add/modify Result Sets error messages
/    mchiocca   06/13/94 -  Add Result Sets error conditions
/    mchiocca   05/14/94 -  NTT MIA - Errors for correct NLS_CHAR usage
/    mchiocca   05/14/94 -  NTT MIA - Reallow host varchars as struct/union mem
/    mchiocca   05/14/94 -  [215929] char x[] declaration usage
/    mchiocca   04/27/94 -  NTT MIA - Error for arrays of NLS_CHAR variables
/    mchiocca   04/27/94 -  NTT MIA - Message regarding NLS_CHARs more general
/    mchiocca   04/27/94 -  NTT MIA - Disallow host varchars in structs
/    mchiocca   04/27/94 -  [213187] #line directives with varchar decls
/    mchiocca   04/05/94 -  NTT MIA - No MIA bind variables in PL/SQL blocks
/    mchiocca   04/05/94 -  NTT MIA - nls_char=, nls_local= usage errors
/    mchiocca   04/04/94 -  NTT MIA - Error to have array of MIA varchars
/    mchiocca   04/02/94 -  NTT MIA - Add def_sqlcode= support
/    mchiocca   03/17/94 -  code=cpp - Eliminate IAP Messages
/    mchiocca   03/10/94 -  Msg for SQL outside function body when PARSE=FULL
/    jweisz     02/17/94 -  [198401] msg for ansi sqliem proto
/    jweisz     02/08/94 -  [196636] inline sqlcheck error
/    jweisz     01/18/94 -  [194677] varchar typedef has unsigned components
/    jweisz     01/18/94 -  [194612] add set role
/    jweisz     01/14/94 -  [193779] add ANALYZE, TRUNCATE, EXPLAIN
/    jweisz     01/13/94 -  [194164] bad decl in DECLARE SECTION
/    jweisz     12/14/93 -  [190999] bad FOR clause
/                           [190998] FOR clause in SELECT stmt
/    jweisz     12/04/93 -  [189592] Messages for TOOLS errors
/    jweisz     11/11/93 -  Clean up some messages
/    jweisz     10/25/93 -  Add explanations
/    jweisz     10/12/93 -  [183742] equal sign must be ASC_EQUAL (61)
/    mchiocca   09/29/93 -  Add "work " - PCSUWORK
/    jweisz     05/18/93 -  Add PRIOR 
/    jweisz     04/01/93 -  [158085] Support set trans use rollback segment 
/    jweisz     03/25/93 -  [156329] strings for ansi_c, kr_c, sql2, sql89 
/    jweisz     03/25/93 -  [155805] Indicator not declared as short 
/    jweisz     03/25/93 -  Add error for dbms=V6 mode=ANSI 
/    jweisz     02/22/93 -  Add msg for bind, indic array size mismatch
/    jweisz     02/21/93 -  Two msgs for ind. struct errors
/    jweisz     02/02/93 -  Add decl outside SQL DECLARE error
/    jweisz     02/01/93 -  Misnumbered last error
/    jweisz     02/01/93 -  Add 4 msgs for ARRAYLEN errors
/    jweisz     01/21/93 -  Add function as host var error
/    jweisz     01/19/93 -  varchar decls now same as pcc15
/    jweisz     12/18/92 -  Handle warnings, obsolete options
/    jweisz     12/17/92 -  Defs for generic err msg, #include error msg
/    jweisz     12/16/92 -  Change text of varchar decl msg
/    jweisz     08/07/92 -  Add lowercase varchar
/    pdufour    05/14/92 -  Creation 
/
301,0,	"cannot reopen input file for reading"
// *Cause: The semantic analysis phase of the precompiler could not reopen
//  the input file to generate the output code.  
// *Action: Check that the input file and it's directory protection and 
//  priveleges do not change 
//  during precompilation.
302,0,	"cannot open code generation output file \"%s\""
// *Cause:  Pro*C was unable to open one or both temporary files required for
//  code generation. The user executing the precompiler must have write
//  permission (and/or the appropriate 
//  privileges) on the current directory.
// *Action: Check that permission exists to create files in the the directory
//  where you precompile.
303,0,	"cannot open include file"
// *Cause:  The precompiler was not able to open a header file specified 
//  using the #INCLUDE preprocessor 
//  directive or the EXEC SQL INCLUDE statement. This can happen if 
//  the file specification is 
//  inaccurate or if read permission or read-access rights on the 
//  file or on one or more of the directories 
//  in the path have not been granted.
// *Action: Recheck that the file specification is correct, that the 
//  file exists, and that read permission has been 
//  granted so that the file can be read.
304,0,	"invalid declaration of C function"
// *Cause:  A C function using invalid syntax was declared.
// *Action: Consult a C programming manual and correct the declaration. 
305,0,	"illegal mixing of new and old style C function declarations"
// *Cause:  All C functions using either the traditional style (K&R style)
//  function declarations or the new (ANSI) style must be declared; the two
//  styles cannot be mixed.
// *Action: Adopt a consist declaration style for functions. 
306,0,	"illegal name of C function"
// *Cause:  A C function was declared with a name that is not a legal C
//  identifier.
// *Action: Use legal C identifiers for all function names. 
307,0,	"void can only be used when single parameter"
// *Cause:  A function can be declared or defined using the following syntax:
//  int func1(void)   
//  to indicate that the function has no parameters. void can be used only
//  once in this case.
// *Action: Remove the extra voids in the function definition or declaration.
308,0,	"identifier required in this function declaration"
// *Cause:  A function definition written in ANSI C must have both the name
//  and the type for all parameters.
// *Action: Rewrite the function definition so that it contains the name of
//  each parameter.
309,0,	"illegal formal parameter declaration"
// *Cause:  A formal parameter to a function was specified without giving 
//  its type.
// *Action: Rewrite the function declaration and include types of all
//  parameters in function declarations.
310,0,	"formal parameter VARCHARs should be declared as pointers"
// *Cause:  Many C compilers allow structures to be passed to and returned
//  from functions. Although a VARCHAR is implemented as a C struct,
//  VARCHARs must be passed to a function as pointers. 
// *Action: Take the address of a VARCHAR when it is passed to a function.
//  See the example in the section "Referencing VARCHAR Variables" in the
//  Programmer's Guide to the Oracle Precompilers.
311,0,	"cannot have VARCHAR bit fields"
// *Cause:  Host variables cannot contain bit fields.
// *Action: Recode the application to remove the bit fields.
312,0,	"arrays of VARCHAR greater than 2 dimensions not allowed"
// *Cause:  A VARCHAR variable having more that 2 dimensions was declared.
//  Multidimensional arrays are not supported as host variables.
// *Action: Recode the application to remove multidimensional array usage. 
313,0,	"malformed VARCHAR declaration - missing length"
// *Cause:  When a VARCHAR is declared, a length specification is mandatory.
//  For example, the following VARCHAR declaration is meaningless, hence
//  illegal: 
//  VARCHAR v1[];
// *Action: Specify the length for each declared VARCHAR.
314,0,	"cannot evaluate constant sizeof expression"
// *Cause:  A SIZEOF operator was used where a precompiler expression was
//  expected.
//  For example, as the length of a varchar.
// *Action: Eliminate the SIZEOF operator in this instance.
315,0,	"cannot evaluate expression as constant"
// *Cause:  The specified expression does not evaluate to a constant.  Such
//  expressions are required, for example, as the length of a VARCHAR.
// *Action: Replace the expression with one that does evaluate
//  to a constant integer.
316,0,	"illegal operator in constant expression"
// *Cause:  A non-arithmetic operator was present in a constant expression.
// *Action: Rewrite the expression to eliminate the non-arithmetic operator.
317,0,	"illegal cast type expression"
// *Cause:  An illegal cast is present in the expression.
// *Action: Remove the illegal cast.
318,0,	"missing type expression"
// *Cause:  The specified expression is missing the declaration of a type.
// *Action: Specify a type for the expression.
319,0,	"expression type does not match usage"
// *Cause:  The type of a variable does not match is usage.  For example,
//  in dynamic SQL, a host variable containing the text of a SQL statement
//  must be declared as a C character type or be equivalenced to the SQL type 
//  STRING.
// *Action: Remove the declaration. 
320,0,	"arithmetic expression does not have correct operand types"
// *Cause:  The arithmetic expression must be specified with integral types.
// *Action: Rewrite the expression using integral types.
321,0,	"only subtraction between two pointers is permitted"
// *Cause:  Pointer values cannot be added, multiplied, or divided. The only
//   arithmetic operation permitted with pointers is subtraction. 
// *Action: Recode to avoid this error message.
322,0,	"found undefined identifier"
// *Cause:  An identifier used in a SQL statement was not defined. For
//  example, a cursor name was referenced that had not been declared, or in
//  a DECLARE CURSOR statement, a statement name was used that had not been
//  PREPAREd. 
// *Action: Check that all SQL identifiers, such as cursor names and 
//  statement names, have been defined before use. 
// *Action: Provide a declaration for the variable and/or its type identifier.
323,0,	"found typedef name used in an expression (expecting a value)"
// *Cause:  The name of a typedef was found where a variable was expected.
// *Action: Rewrite the expression and remove the reference to the typedef.
324,0,	"found variable name used as a typedef name"
// *Cause:  The name of a variable was found where a typedef was expected.
// *Action: Rewrite the expression and specify the correct typedef reference.
325,0,	"illegal indirection operation"
// *Cause:  An attempt was made to use a non-pointer type as a pointer.
// *Action: Rewrite the expression.
326,0,	"illegal structure reference operation"
// *Cause:  A structure component using invalid syntax was referenced. 
//  For example, a -> operator was used instead of a required `.' operator.
// *Action: Correct the invalid reference.
327,0,	"struct or struct pointer required"
// *Cause:  A scalar host variable was used in a context where a structure 
//  (or its pointer) is required. 
// *Action: Make the host variable a structure or add more scalar host
//   variables to satisfy the SQL syntax requirements.
328,0,	"undefined struct member"
// *Cause:  A structure component was referenced that was not declared as 
//  part of the structure. 
// *Action: Redefine the structure member.
329,0,	"found reference to undeclared function"
// *Cause:  A function was referenced that was not declared. All function
//   references must be declared.
// *Action: Declare the function.
330,0,	"expecting an expression of integer type"
// *Cause:  The expression does not evaluate to an integer.  For example, a
//  SQL FOR expression must evaluate to an integral type.
// *Action: Rewrite the expression.
331,0,	"undefined SQL identifier"
// *Cause:  All SQL identifiers must be declared before they are used. This
//  message can result when a CURSOR or STATEMENT is not declared 
// (defined) before being referenced.
// *Action: Define the SQL identifier before it is used.
332,0,	"attempted to redefine SQL identifier"
// *Cause:  A SQL identifier (such as a cursor name) can be defined only once.
// *Action: Do not redefine the SQL identifier.Use a different name.
333,0,	"SQL identifier was not declared as a statement"
// *Cause:  A SQL statement identifier was referenced in a 
//  DECLARE... CURSOR statement that was not PREPAREd. 
// *Action: Check that all SQL statement names have been declared. 
//  Remember that SQL statement names are identifiers, not variables, and 
//  that they are local to the precompilation unit. 
334,0,	"SQL identifier was not declared as a cursor"
// *Cause:  A cursor name was used in an OPEN, FETCH, or CLOSE statement
//   that had not been DECLAREd.
// *Action: Check that all SQL cursor names have been declared. Remember
//  that cursors are identifiers, not variables, and that they are local 
//  to the precompilation unit. 
335,0,	"body of cursor must name statement identifier"
// *Cause:  In a Dynamic SQL Method 4 application, the 
//  DECLARE... CURSOR statement must name a statement identifier 
//  that has been PREPAREd in a preceding statement. The PREPARE 
//  statement must physically (not logically) precede the DECLARE command. 
// *Action: This error message is followed by another message that 
//  gives the line and column of the reference to the statement. Recode 
//  the application.
336,0,	"host variable expression has invalid type"
// *Cause:  The host variable was declared using a C type that is not
//   permitted as a host variable. See the Programmer's Guide to the 
//  Oracle Precompilers for a list of the permissible C types for 
//  host variables.
// *Action: Use a permissible host variable type.
337,0,	"cannot declare multi-dimensioned array for this type"
// *Cause:  Host variable arrays of scalars with more than 1 dimension
//  cannot be declared.The only host variables allowed to be 
//  multi-dimensioned are CHAR and VARCHAR.
// *Action: Rewrite the variable declaration.
338,0,	"structure contains a nested struct or union"
// *Cause:  A structure used as a host variable may not have structures or
//  unions nested within it.
// *Action: Rewrite the variable declaration.
339,0,	"host variables cannot be of union types"
// *Cause:  A C union as a host variable cannot be used. 
// *Action: This error message is followed by another message that 
//  gives the line and column of the reference to the illegal union. 
//  Recode, using a struct or individual scalar host variables.
340,0,	"structure contains a bit field"
// *Cause:  Bit fields are not allowed in host variables because 
//  they are meaningless for database DML operations. 
// *Action: This error message is followed by another message that 
//  gives the line and column of the reference to the offending host 
//  variable. Recode the application. 
341,0,	"host variable has illegal type"
// *Cause:  A host variable has an unpermitted type (i.e.; enum, void, etc).
// *Action: Rewrite the host variable declaration, using a permissible 
//  host variable type.
342,0,	"using WHERE CURRENT OF on cursor defined without FOR UPDATE clause"
// *Cause:  When MODE=Oracle, a cursor defined with a WHERE CURRENT OF
//  clause must also have a FOR UPDATE clause.
// *Action: Rewrite the cursor definition.
343,0,	"body of cursor must be a query expression"
// *Cause:  A cursor definition must be a SELECT statement.
// *Action: Rewrite the cursor definition.
344,0,	"Host variable array size mismatch. Using minimum: %ld"
// *Cause:  Host variable arrays in a single statement should all be of 
//          equal size.
// *Action: Redefine the bind variable array lengths to all be the same size.
345,0,	"SQLCHECK=SEMANTICS must be given when embedded PL/SQL blocks are used"
// *Cause:  Embedded PL/SQL blocks require that the command-line flag
//  SQLCHECK=SEMANTICS is used.
// *Action: Use the SQLCHECK=SEMANTICS option. This also requires 
//  that the USERID connect option be given.
346,0,	"PL/SQL found semantic errors"
// *Cause:  A database entity, such as a table or column name, was 
//  referenced, that does not exist. This is a compile time error, not 
//  a runtime error. 
// *Action: Check that all referenced objects in PL/SQL statements 
//  actually exist and that the necessary access permission on them 
//  have been granted.
347,0,	"PL/SQL found syntax errors"
// *Cause: A PL/SQL statement was used illegally.  
// *Action: Check the PL/SQL User's Guide and Reference for the
//          correct syntax.
348,0,	"indicators are not allowed in EXEC IAF statements"
// *Cause: Indicator variables associated with host variables cannot be used 
//         in EXECIAF statements such as GET and PUT in a user exit.
// *Action: Eliminate the indicator variabls. If feasible (for example with 
//          Forms V4), use EXEC TOOLS statements, which do allow indicator
//          variables. See the Programmer's Guide to the Oracle Precompilers
//          for more information of EXECIAF and EXEC TOOLS statements.
349,0,	"precision must be specified for this type"
// *Cause: In a VAR or TYPE statement, certain Oracle types require that the
//         precision be specified. For example, VARCHAR2 or CHAR.
// *Action: Indicate the precision. 
350,0,	"cannot equivalence this SQL type"
// *Cause:  Datatype or variable equivalencing to the datatypes 
//  NUMBER or DECIMAL cannot be used. See the "Datatype Equivalencing" 
//  section in the Programmer's Guide to the Oracle Precompilers 
//  for more information.
// *Action: Use the appropriate datatype for the application.
351,0,	"illegal datatype equivalencing operation"
// *Cause:  The datatype specified could not be equivalenced, or the 
// syntax was incorrect in the VAR or TYPE statement.
// *Action: See the Programmer's Guide to the Oracle Precompilers 
//  for a list of the datatypes that can be equivalenced and 
//  the correct syntax of the VAR or TYPE statement.
352,0,	"out of bounds bind position from PL/SQL"
// *Cause:  PL/SQL requested a bind position that does not exist.
// *Action: Contact ORACLE customer support.
353,0,  "Semantic error at line %d, column %d, file %s:\n"
// *Cause: This error message precedes a more specific error message.  
// *Action: No action required. Correct the error(s) reported in the 
//          following message(s).
354,0,	"A file included with #include may not contain SQL statements"
// *Cause:  The Pro*C Precompiler reads header files referenced 
//  in #INCLUDE directives and uses the values defined in them. 
//  But the precompiler never generates code using statements in header 
//  files, so use of SQL statements in these files is illegal. 
// *Action: Move the SQL statement(s) into the main body of the 
//  application or use EXEC SQL INCLUDE to check that the included 
//  file is precompiled.
355,0,  "Invalid or obsolete option, ignored"
// *Cause: A command-line option that is not used in Pro*C Release 2.0 was
//         specified. For example, the option AREASIZE is no longer valid
//         with precompilers used with the Oracle7 Server.
// *Action: No action required. This is an informational message. 
356,0,  "Warning at line %d, column %d, file %s:\n"
// *Cause: This is a generic warning message. It precedes a more specific
//         warning.
// *Action: No action required. Correct the error(s) indicated in 
//  the following
//          message(s).
357,0,  "Function calls may not be used as host variable expressions"
// *Cause: Only objects that are lvalues (that resolve to an address) can be
//         host variables. Because a function call is not an lvalue, one 
//         cannot be used in place of a host variable.
// *Action: Recode the application. 
358,0,  "Identifier following ARRAYLEN must be the name of an array"
// *Cause: A declared array must be specified as the argument for an 
//         ARRAYLEN statement. Declare the array textually before the ARRAYLEN
//         statement. See the Programmer's Guide to the Oracle Precompilers
//         for the syntax of the ARRAYLEN statement.
// *Action: Correct the statement, specifying a host array as the argument. 
359,0,	"Identifier specifying ARRAYLEN must be a 4-byte integer"
// *Cause: The expression that specifies the ARRAYLEN dimension must 
//         evaluate to an integer. For example, the statement
//              EXEC SQL ARRAYLEN my_array(1,3)
//         cannot be parsed.
// *Action: Correct the statement, using an integral dimesnsion. 
360,0,  "This array type is invalid for use with ARRAYLEN statement"
// *Cause:  Arrays of some host variables types are not allowed and hence 
//  also cannot be used in ARRAYLEN statements. VARCHAR  and DATE 
//  are examples.
// *Action: Specify an array with a datatype that can be used in host arrays.
361,0,  "Use of ARRAYLEN with SQL bind arrays is ignored"
// *Cause:  ARRAYLEN is only valid with arrays that can be bound 
//  in PL/SQL blocks.
// *Action: Use an appropriate array type. 
362,0,  "Host variable not declared within SQL DECLARE section"
// *Cause:  When MODE=ANSI is specified at precompile time, all host 
//  variables must be declared inside Declare Sections. Remember 
//  that MODE=ANSI refers to ANSI SQL, not ANSI C. 
// *Action: Add the EXEC SQL BEGIN DECLARE SECTION... EXEC SQL END 
//  DECLARE SECTION statements around all host variable declarations.
363,0,  "Indicator variable must be a structure"
// *Cause:  If a host variable is a structure, the associated 
//  indicator variable must also be a structure. 
// *Action: Recode the application to create an indicator 
//  variable as a structure.
364,0,  "Host struct and its indicator must have the same number of fields"
// *Cause:  When a structure containing indicator variables is declared 
// and associated with a host structure, the indicator structure must
// contain the same number of fields as the host structure. This is so 
// even when some of the indicators will not be used or even when it would 
// not make sense to do so (for fields constrained as NON NULL, for 
// example).
// *Action: Redeclare the indicator variable with the correct 
// number of fields.
365,0,  "Indicator array size cannot be smaller than host array size"
// *Cause:  An indicator array must have dimension greater than or equal
//  to the corresponding host variable array dimension.
// *Action: Change the dimension of the indicator array.
366,0,  "Command line argument MODE=ANSI may not be used with DBMS=V6"
// *Cause: The semantics of certain operations (such as character comparison)
//         in Oracle version ^ are not 100% compliant with the ANSI/ISO  SQL
//         standards. When V6 semantics are requested, using the DBMS=V6 or
//         DBMS=V6_CHAR option, precompilation with MODE=ANSI is not
//         permitted.
// *Action: Do not use ANSI mode with V6 options. 
367,0,  "This indicator variable must be declared as type short"
// *Cause: An indicator for a host variable of this type must have the C type
//         short. An array of such indicators must be an array of shorts.
// *Action: Declare the indicator variable or indicator array as type short.
368,0,	"An EXEC TOOLS host variable context name is not type char"
// *Cause: If a host variable is used to define a context name in an
//  EXEC TOOLS GET CONTEXT or EXEC TOOLS SET CONTEXT statement, that host
//  variable must be of a character type.
// *Action: Redeclare the context name to a host variable of a char type.
369,0,	"An EXEC TOOLS host pointer variable is not a pointer"
// *Cause: The host variable specifying an EXEC TOOLS context must be a
//  pointer type.
// *Action: Redeclare the variable, making sure that it is a pointer.
370,0, 	"An EXEC TOOLS MESSAGE host variable is not type char"
// *Cause: f a host variable is used to define a context name in an 
//  EXEC TOOLS GET CONTEXT or EXEC TOOLS SET CONTEXT statement, that 
//  host variable must be of a character type.
// *Action: Declare the message to a host variable of a char type.
371,0,	"Illegal FOR clause"
// *Cause: The argument of a FOR clause must be specified as an integer 
//  or as an identifier containing an integer.
// *Action: Rewrite the FOR clause.
372,0,	"FOR clause not allowed in SELECT statement"
// *Cause: A SQL statement containing a SELECT command cannot contain a 
//  FOR clause. The meaning of such a statement would be unclear.
// *Action: Rephrase the SELECT statement, removing the FOR clause.
373,0,	"Invalid declaration in EXEC SQL DECLARE section"
// *Cause: An improper declaration was placed in a Declare Section. 
//  This message is usually caused by including an EXEC SQL TYPE or 
//  EXEC SQL VAR declaration in a Declare Section.
// *Action: Move the declaration outside of the SQL DECLARE section.
374,0,	"SQLCHECK value exceeds command line value"
// *Cause:  The value given to the SQLCHECK option in an EXEC ORACLE statement
//          in a program was greater than the value given either on
//          the command line or greater than the default value if 
//          no SQLCHECK option was given on the command line.    
//
//          The order of the option values is SEMANTICS>SYNTAX>NONE.
//
//          When this warning message is issued, the original value of
//          SQLCHECK (the default or the command-line value) stays in 
//          effect.
// *Action: Remove or recode the EXEC Oracle option(s) in the .pc 
//  source file to avoid this warning message. 
375,0,  "SQL statement found outside the body of a function"
// *Cause:  A SQL statement other than a declarative, datatype equivalence
//          or WHENEVER statement was found outside the body of a function
//          when PARSE=FULL.
// *Action: Move the SQL statement inside the body of a function.
376,0,  "You may not declare SQLCODE when DEF_SQLCODE = TRUE"
// *Cause:  The DEF_SQLCODE option may not be specified if a SQLCODE
//          declaration already explicitely appears in the program.
// *Action: Remove the SQLCODE declaration from the program or specify
//          DEF_SQLCODE=NO (the default).
377,0,  "Arrays of implicit varchars are not permitted"
// *Cause:  An array of implicit VARCHARS was declared when HOST_VARCHAR=TRUE.
// *Action: Rewrite the implicit VARCHAR declaration without using arrays.
378,0,  "Invalid type for National Language character variable"
// *Cause:  A variable declared as a National Language character using the
//          NLS_CHAR option was not declared as a char or implicit VARCHAR.
// *Action: Declare the variable as a char or implicit VARCHAR or do not
//          specify using the NLS_CHAR option.
379,0,  "Cannot equivalence National Language character variables"
// *Cause:  A National Language character variable (specified using the
//          NLS_CHAR option) has undergone datatype equivalencing using
//          either the EXEC SQL VAR or TYPE statements.
// *Action: Do not equivalence National Language character variables.
380,0,  "Cannot specify a connect mode when altering a user password"
// *Cause: An attempt was made to connect in either SYSOPER or SYSDBA mode
//    while at the same time trying to change passwords using the ALTER
//    AUTHORIZATION clause in the same CONNECT statement.
// *Action: Changing passwords while connecting in SYSOPER or SYSDBA mode
//    is prohibited.  Rewrite the connect statement by either removing the
//    ALTER AUTHORIZATION cluase or the CONNECT MODE clause.
382,0,  "You must specify MODE=ANSI when using NLS_LOCAL=YES"
// *Cause: NLS_CHAR was used to specify NLS multi-byte character 
//    variables without specifying MODE=ANSI.
// *Action: Specify MODE=ANSI on the command line when using NLS_LOCAL=TRUE.
383,0,  "Expecting an expression of type OCIExtProcContext"
// *Cause: The type of the bind variable given in a REGISTER CONNECT USING
//    statement was not (pointer to) OCIExtProcContext.
// *Action: Declare a variable having type (pointer to) OCIExtProcContext
//    and use it in the REGISTER CONNECT USING statement.
384,0,  "Missing array length specifier"
// *Cause:  An array declaration was given without an array length specifier.
// *Action: Provide the length for the array declaration.
385,0,  "CHAR_MAP disallowed when using NLS_CHAR and NLS_LOCAL=TRUE"
// *Cause: The CHAR_MAP option was specified while indicating which host
//         variables are to be treated by the precompiler as NLS multi-byte
//         character variables. This mapping cannot be performed with the
//         option NLS_LOCAL=TRUE.
//         This error also occurs when DBMS=V6 is used in conjunction with
//         NLS_CHAR and NLS_LOCAL=TRUE.
// *Action: Remove either the CHAR_MAP option or set NLS_LOCAL=FALSE.
//          Ensure that DBMS is not set to V6.
386,0,  "Use of the AT clause is not permitted here"
// *Cause:  An explicit AT clause was used with an ALLOCATE statement or a 
//          FETCH/CLOSE statement also using a SQL_CURSOR declaration.
// *Action: Remove the AT clause.
387,0,  "Expecting an expression of type sql_cursor"
// *Cause:  A host bind variable was used in an ALLOCATE, FETCH or CLOSE
//          statement that was not declared as a result set SQL_CURSOR.
// *Action: Declare the variable to be of type sql_cursor.
388,0,  "Arrays not allowed in FROM/WHERE clause of SELECT statement"
// *Cause: A host array was used in the WHERE clause of a SELECT-INTO 
//         statement.
// *Action: Rewrite the SELECT statement without using arrays or use a cursor.
389,0,  "Arrays not allowed as input bind variables in SELECT list"
// *Cause: A host array was used in the SELECT list of a SELECT-INTO statement.
// *Action: Rewrite the SELECT statement without using arrays in SELECT list.
390,0,	"No EXEC SQL CONTEXT USE statement encountered"
// *Cause:  No EXEC SQL CONTEXT USE statement was encountered and the 
//          option threads=yes was requested. 
// *Action: Ensure that the necessary context variable (of type sql_context)
//          has been declared and that has been ALLOCATEd and USEd prior to 
//          any executable SQL statements.
391,0,  "Runtime context variable not of correct type"
// *Cause: The host variable in a EXEC SQL CONTEXT USE statement or in the
//    RETURNING clause of a REGISTER CONNECT statement was not declared to
//    be of type SQL_CONTEXT.
// *Action: Declare the runtime context variable to be of type SQL_CONTEXT.
392,0,  "You are already in an EXEC SQL DECLARE SECTION"
// *Cause:  A SQL DECLARE SECTION appears nested inside another one.
// *Action: Do not nest DECLARE SECTIONS.  Remove any nested inner ones.
393,0,  "SQL statement found inside an EXEC SQL DECLARE SECTION"
// *Cause:  An executable SQL statement appears inside a DECLARE SECTION.
// *Action: Move the SQL statement into the body of a function.
394,0,  "Input file name and output filename are identical"
// *Cause:  The values of INAME and ONAME are the same or the default
//          output filename is the same as that specified by ONAME.
// *Action: Use ONAME to specify a different filename for the output file.
395,0,  "Using arrays of structs requires that the struct be named"
// *Cause:  An array of some unnamed struct was used as a host variable.
//          When using arrays of structs, the struct requires a name or tag.
// *Action: Provide a name for the struct.
396,0,  "Illegal use of arrays inside an array of structs"
// *Cause:  An array of a struct that contained arrays of scalars or
//          two-dimensional char or VARCHAR fields was used as a host
//          variable.
// *Action: Rewrite the struct so that there are no scalar arrays or
//          two-dimensional char or VARCHAR fields.
397,0,  "VARCHAR declarations not permitted in #include file"
// *Cause:  A VARCHAR declaration was found in a file included using
//          a #include form.
// *Action: Use the EXEC SQL INCLUDE form to include files with VARCHAR
//          declarations instead.
398,0,  "Indicator ignored in this statement for this type"
// *Cause:  An indicator variable was used in a host/indicator variable pair
//          for some type in a statement that did not require or need one.
//	    Typically, indicator variables are not used in ALLOCATE and FREE
//          statements for types other than object or collection types.  They
//          are also not used in OBJECT CREATE/DEREF statements for REF types.
// *Action: Remove the use of the indicator for the type in the
//          specified statement.  It will be ignored otherwise.
399,0,  "Illegal CHAR_MAP option value for DBMS=V6.  Option ignored."
// *Cause:  A CHAR_MAP option other than CHAR_MAP=VARCHAR2 was specified
//          inline. Since DBMS=V6, this option is ignored for a character
//          or string variable in the offending statement.
// *Action: Either set DBMS to something other than V6, or specify
//          CHAR_MAP=VARCHAR2.
400,0,  "This host variable must be declared as a pointer type"
// *Cause:  The specified host variable was not declared as a pointer type.
// *Action: Declare the host variable to be a pointer type.
401,0,  "Host variable arrays of this type are currently not supported"
// *Cause:  Host variable arrays of the specified type are not supported.
// *Action: Rewrite your program so that there are no arrays of this type.
402,0,  "Pro*C option OBJECTS=YES is required when using the object cache"
// *Cause:  The object cache will be used for this host variable, but 
//          OBJECTS=NO was specified on the Pro*C command line.
// *Action: Specify OBJECTS=YES on the Pro*C command line when using the 
//          object cache.
403,0,  "Invalid indicator variable type for this host variable"
// *Cause:  The type of the indicator variable is not appropriate for the
//          specified host variable.
// *Action: Change the type of the indicator variable to a valid type.
//          Refer to the "Programmer's Guide to the ORACLE Pro*C/C++
//          Precompiler" for a discussion of appropriate indicator
//          variable declarations.
404,0,  "This indicator variable must be declared as a pointer type"
// *Cause:  The specified indicator variable was not declared as pointer type.
// *Action: Declare the indicator variable to be a pointer type.
405,0,  "Variable is of undefined type"
// *Cause:  No declaration was found for the type identifier of the variable.
// *Action: Provide a valid declaration for the type of the host variable.
//          If using objects in your program, check that the OTT-generated 
//          header for the object type was #included and that the typefile 
//          was specified in the INTYPE option on the Pro*C command line.
406,0,	"Expecting the form 'RETURN[ING] REF INTO :<ref>' only"
// *Cause:  When using the RETURNING clause in an OBJECT CREATE statement,
//          only a single 'REF INTO :<host variable>' is expected.  This
//          error occurs if the expression list to which REF belongs is
//          greater than one or if there are more than one host variables
//          supplied in the into list.
// *Action: Rewrite the RETURNING clause as per the given specification.
407,0,	"Object and REF types do not match"
// *Cause:  In an OBJECT CREATE or DEREF statement, the types of the given
//          Object and its associated REF do not match.
// *Action: Make sure that the Object and its REF have the same type.  The
//          type information is generated by OTT and should appear in the
//          header file which OTT creates.
408,0,	"Expecting an expression of some Object type"
// *Cause:  The expression is not an Object type.  For example, many host
//          variable expressions in the Navigational statements require that
//          the variable be declared of some Object type.
// *Action: Rewrite the expression or declare the variable to be an Object.
409,0,	"Expecting an expression of some REF type"
// *Cause:  The expression is not a REF type.  For example, some host
//          variables in the Navigational CREATE and DEREF statements are
//          required to be declared of some REF type.
// *Action: Rewrite the expression or declare the variable to be a REF.
410,0,  "Expecting an expression of some Collection type."
// *Cause:  The expression is not a Collection type.  A VARRAY or Nested
//    Table object was expected, but the given host variable did not resolve
//    to a valid Collection type.
// *Action: Check that the OTT-generated header for the Collection type was
//    properly #included in the Pro*C/C++ program and that the typefile was
//    specified in the INTYPE option on the Pro*C/C++ command line.
411,0,  "Invalid type for INDICATOR descriptor item host variable"
// *Cause: The type of the host variable paired with the INDICATOR descriptor
//    item was invalid.  The only permissable types for the INDICATOR item
//    are a signed 2 byte numeric type or an indicator struct generated by
//    the Object Type Translator for a user defined object type.
// *Action: Either replace the INDICATOR host variable with a valid one 
//    having an acceptable type or redeclare the existing host variable to
//    be of a valid type.
412,0,	"FOR clause not permitted in OBJECT GET or SET statement"
// *Cause: An explicit FOR clause was used in an OBJECT GET or OBJECT SET
//         statement.  Use of the FOR clause is illegal for these statements.
// *Action: Remove the FOR clause. 
413,0,	"Number of attributes does not match number of host variables"
// *Cause:  The number of attributes supplied in the attribute list of an 
//          OBJECT SET of GET statement does not match the total number of
//          host variables also supplied in that statement.
// *Action: Either remove some attributes or remove some host variables from
//          the statement in order to make the total count for each the same.
414,0,	"This attribute does not exist in the specified Object"
// *Cause:  An attribute given in the attribute list of an OBJECT SET or
//          GET statement is not a member of the specified object in that
//          statement.
// *Action: Remove the attribute from the list.
415,0,	"Cannot manipulate Object attributes in an OBJECT GET or SET"
// *Cause:  An attempt was made to either GET or SET an attribute of an
//          Object that itself was an Object or REF type.
// *Action: Remove the attribute from the attribute list in the statement.
416,0,	"The Object in an OBJECT GET or SET must not be an array"
// *Cause:  The Object specified in an OBJECT GET or SET statement is an
//          array which is illegal.
// *Action: Redeclare the Object so that it is not an array or subscript
//          the Object so that only a single element of the Object array is 
//          specified.
417,0,	"Illegal type conversion between attribute and host variable"
// *Cause:  An illegal type conversion was attempted in a Navigational GET
//          or SET statement between the type of the Attribute and the type
//          of the Host Variable.
// *Action: Change the type of either the Attribute or the Host Variable.
418,0,	"Array size mismatch between Object and REF host variables"
// *Cause:  The array sizes of the Object and REF variables in an OBJECT
//          CREATE or DEREF do not match.
// *Action: Adjust the array dimensions of the two host variables so that
//          they are equal to one another.
419,0,	"Host variable arrays not allowed in an OBJECT SET or GET"
// *Cause:  An array was found in the host variable list of an OBJECT SET
//    or GET statement.
// *Action: Only scalars are allowed (except for single dimensioned char
//    or varchar variables) in the host variable list of an OBJECT SET or
//    GET.  Make sure to use only scalars in these statements.
420,0,	"Incomplete (or missing) type specification"
// *Cause:  An incomplete or perhaps missing type specification was given
//    when declaring a host variable used in some SQL statement.
// *Action: Provide a complete type definition when declaring host
//    variables intended for use inside any SQL statements.
421,0,	"This host variable requires the use of an indicator variable"
// *Cause:  No indicator variable was provided (or matched) with a specific
//    host variable where one was explicitely required.
// *Action: Provide an indicator variable for use with the specified host
//    variable in the given SQL statement.
422,0,  "Invalid value specified for the given context option"
// *Cause:  An illegal value was given for the specified runtime context
//    option in the CONTEXT <option> OPTION SET (or GET) statement.
// *Action: Use a valid option value in the statement for the specified
//    option being manipulated by the statement.
423,0,  "Host variable has an invalid type for this option value"
// *Cause:  The type of the host variable corresponding to a specific option
//    value in a CONTEXT <option> OPTION SET (or GET) statement is invalid 
//    for that particular value.
// *Action: Use a type suitable for the specific value being manipulated.
424,0,  "The number of values and host variables does not match"
// *Cause:  There is a mismatch between the number of values specified and
//    the number of valid host variables given in a CONTEXT <option> OPTION
//    SET (or GET) statement.
// *Action: Use the same number of host variables as there are values given
//    in that particular statement.
425,0,  "An indicator variable is not required with this attribute"
// *Cause:  In a LOB or Collection DESCRIBE, an Indicator Variable was used
//    with a Host Variable when retrieving a LOB attribute that doesn't
//    require one.
// *Action: Remove the Indicator Variable.
426,0,  "Incompatible LOB types"
// *Cause: A LOB operation was attempted between LOBs whose types were not
//    compatible.  For example, When ASSIGNing one LOB to another, both
//    LOBs must be of the same type.  If they are not, this error results.
// *Action: Correct the LOB operation by having it function between LOBs of 
//    the same type.  This may require a redeclaration of one of the LOBs
//    used in the LOB statement performing the specified operation.
427,0,  "Expression is not of the correct character string type"
// *Cause: The given host variable expression was not declared to be of
//    the required character type.  In this case, one of several possible
//    character types would have been accepted.  However, the host variable
//    type did not match any of them.
// *Action: Redeclare the problematic host variable, using one of the
//    permitted character types.
428,0,  "Buffer type is incompatible with LOB type"
// *Cause: This error can occur in either of the following situations
//    1. An attempt to READ from a LOB into a buffer whose type was not
//       compatible with the LOB type.
//    2. An attempt to WRITE a buffer into a LOB whose type was not
//       compatible with the buffer type.
// *Action: Either the LOB type or the buffer type needs to be changed so
//    that the LOB and buffer types become compatible for the specified
//    operation.
429,0,  "Expecting an expression of some internal LOB type"
// *Cause: The given host variable was not declared to be an Internal LOB.
//    BLOB, CLOB or NCLOB would have been accepted, however, the type of
//    the host variable did not match any of these.
// *Action: Redeclare the host variable using one of the Internal LOB types.
430,0,  "Expecting an expression of some arbitrary LOB type"
// *Cause: The given host variable was not declared to be any type of LOB,
//    Internal or External.  In addition to any Internal LOB type, BFILE
//    would also have been accepted, however, the type of the host variable
//    did not match any of these.
// *Action: Redeclare the host variable using any of the LOB types, Internal
//    or External.
431,0,  "Expecting an expression of type external LOB (BFILE)"
// *Cause: The given host variable was not declared to be an External LOB.
//    Only BFILE would have been accepted in this case.
// *Action: Redeclare the host variable using an External LOB type (BFILE).
432,0,  "Cannot open an external LOB (BFILE) in READ WRITE mode"
// *Cause: An attempt was made to OPEN a BFILE in READ WRITE mode.  Writable
//    BFILEs are currently not supported so this operation is considered
//    erroneous.
// *Action: Do not open BFILEs using READ WRITE mode.  BFILEs can only be
//    OPENed in READ ONLY mode.
433,0,  "Invalid host variable and attribute pairing"
// *Cause: The host variable and attribute pairing in a LOB or Collection
//    DESCRIBE is invalid.  Most likely, this was due to some problem with
//    the host variable.  For example, this error could occur if the host
//    variable was not declared or is otherwise not provided.
// *Action: Usually, other, more specific, errors will accompany this one.
//    Correcting some or all of those problems should resolve this error.
434,0,  "FOR clause not permitted in any LOB statement"
// *Cause: An explicit FOR clause was used in some LOB statement.  The use
//    of the FOR clause in LOB statements is erroneous.
// *Action: Remove the FOR clause.
435,0,  "This attribute is only valid for internal LOB types"
// *Cause: A request for a LOB attribute was made in a LOB DESCRIBE
//    statement in which the given LOB was not of some Internal LOB
//    type.
// *Action: Replace the LOB host variable in the LOB DESCRIBE with one
//    that was declared to be an Internal LOB.
436,0,  "This attribute is only valid for external LOB types (BFILEs)"
// *Cause: A request for a LOB attribute was made in a LOB DESCRIBE
//    statement in which the given LOB was not an External LOB type
//    (BFILE).
// *Action: Use an External LOB (BFILE) host variable in the LOB 
//    DESCRIBE statement.
437,0,  "Expecting an expression having binary integral type"
// *Cause: A host variable was given that was not declared to be of some
//    acceptable binary numberic integral type.  Generally, when this error
//    occurs, a signed or unsigned integral type was expected.  Floating
//    point or otherwise imprecise numeric types are considered erroneous.
// *Action: Replace the problematic host variable with one that was 
//    declared using a proper exact numeric integral type.
438,0,	"Arrays of collection objects are not allowed"
// *Cause: An array of collections was given in a COLLECTION statement.
//    Only scalar (non-array) collection objects are allowed in any of the
//    COLLECTION statements.
// *Action: Change the declaration of the Collection host variable so that
//    it is not an array.
439,0,	"FOR clause not allowed in this COLLECTION statement"
// *Cause: An illegal FOR clause was used in a COLLECTION statement that
//    did not allow one, particularly, one of either the TRIM or DESCRIBE
//    COLLECTION statements.
// *Action: Remove the FOR clause from the statement.
440,0,  "This attribute is valid for either internal or external LOBs"
// *Cause: A request for a LOB attribute was made in a LOB DESCRIBE
//    statement in which the given LOB host variable was neither an
//    Internal an External LOB (BFILE) type.
// *Action: Use either an Internal or External LOB host variable in
//    the LOB DESCRIBE statement.
441,0,  "Number of attributes does not match number of host variables"
// *Cause: There is a mismatch between the number of attributes and the
//    number of valid host variables in the LOB or Collection DESCRIBE.
// *Action: Make sure that for each attribute being requested there is
//    at most a single valid host variable given to hold its value.
442,0,  "Expecting a value between 1 and 65535 inclusive"
// *Cause: The value specified in the WITH MAX clause of an ALLOCATE
//    DESCRIPTOR statement or the VALUE clause of a GET/SET DESCRIPTOR
//    statement was either less than 1 or greater than 65535.
// *Action: Specify a value between 1 and 65535 inclusive.
443,0,  "This usage is only valid when DYNAMIC=ANSI is specified"
// *Cause: One of the following statements was used without specifying
//    a DYNAMIC=ANSI command line option setting
//      o EXEC SQL ALLOCATE/DEALLOCATE/GET/SET DESCRIPTOR
//      o EXEC SQL DESCRIBE OUTPUT/INPUT ... USING ... <descriptor>
//      o EXEC SQL EXECUTE ... INTO ...
//      o EXEC SQL EXECUTE ... USING ... <descriptor>
//      o EXEC SQL OPEN ... INTO ...
//      o EXEC SQL OPEN ... USING ... <descriptor>
// *Action: Specify DYNAMIC=ANSI or remove statements like those above 
//    from the program.
444,0,  "Invalid combination of descriptor and non-descriptor clauses"
// *Cause: There was a mixing of descriptor and non-descriptor clauses
//    in an ANSI Dynamic SQL statement.
// *Action: Do not mix descriptors and non-descriptors in the ANSI
//    statement in question.
445,0,  "USING clause valid only on a PREPAREd dynamic statement"
// *Cause: The USING clause was used with an OPEN cursor statement
//    where the cursor declaration was not for a PREPAREd statement.
//    The correct sequence of statements should be as follows
//       EXEC SQL PREPARE s FROM :stmt;
//       EXEC SQL DECLARE c CURSOR FOR s;
//       EXEC SQL OPEN c USING ...;
// *Action: Use the PREPARE statement for the SQL statement and use
//    that in the DECLARE CURSOR statement.
446,0,  "FOR clause not allowed in a DEALLOCATE statement"
// *Cause: An explicit FOR clause was used in a DEALLOCATE DESCRIPTOR
//    statement.
// *Action: Remove the FOR clause from the statement.
447,0,  "Cannot specify destination offset in a LOB WRITE APPEND"
// *Cause: A destination offset was specified in a LOB WRITE APPEND
//    statement.  The destination offset is assumed to be the end of
//    the LOB so specifying an explicit destination offset is
//    erroneous.
// *Action: Remove the destination offset from the LOB WRITE APPEND
//    statement.
448,0,  "Cannot specify a UCS2 variable in the NLS_NCHAR option"
// *Cause: A variable declared as utext, uvarchar, or longuvarchar was
//    specified in the NLS_NCHAR command line option.
// *Action: Re-precompile without specifying the variable in an
//    NLS_NCHAR command line option.
449,0,  "Cannot type equivalence a UCS2 type"
// *Cause: A UCS2 type has been type equivalenced in an EXEC SQL TYPE
//    statement or a variable of UCS2 type has been type equivalenced
//    in an EXEC SQL VAR statement.
// *Action: Remove the EXEC SQL TYPE or EXEC SQL VAR statement.
450,0,  "Cursor was not declared in scrollable mode"
// *Cause: A cursor which was not DECLAREd in SCROLL mode was used in scrollable mode
//    in the FETCH statement. 
// *Action: Declare the cursor in scroll mode using the SCROLL keyword.
451,0,  "Value of offset cannot be negative in ABSOLUTE orientation mode"
// *Cause:  The offset for the FETCH ABSOLUTE statement is negative.
// *Action: Value of offset should be positive.

