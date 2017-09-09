/
/ $Header: o2fus.msg 24-sep-97.16:50:43 pthiesen Exp $
/
/ Copyright (c) 1995, 1996, 1997, 1998 by Oracle Corporation
/   NAME
/     o2f.msg - <Ots2c typeFile messages>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    pthiesen   05/17/98 -  fix NT diff in to2e24gc
/    pthiesen   09/24/97 -  add IN PACKAGE to INTYPE file
/    pthiesen   01/03/97 -  modify messages 335-337
/    pthiesen   11/23/96 -  generate INITFILE
/    jnewman    11/22/96 -  edit text of OTT Cause and Action statements
/    erohwedd   11/08/96 -  add messages 335-337
/    pthiesen   11/08/96 -  error messages for beta2 features
/    pthiesen   11/07/96 -  use new terminology in error messages
/    erohwedd   11/04/96 -  add internal o2f errors
/    pthiesen   07/02/96 -  tkpoiat bug
/    pthiesen   06/24/96 -  add error messages
/    pthiesen   06/09/96 -  betterMessage
/    pthiesen   06/22/96 -  add error messages
/    pthiesen   05/25/96 -  caps
/    pthiesen   02/21/96 -  caseOption
/    pthiesen   12/01/95 -  name translation
/    pthiesen   09/17/95 -  read TYPEFILE part 2
/    pthiesen   09/12/95 -  Creation
301,0,   "Error attempting to read from the INTYPE file"
// *Cause: An operating system error occurred while attempting to read from
//  the INTYPE file.
// *Action: Try opening the INTYPE file with an editor to make sure you
//  are able to access the file.
302,0,   "Unable to allocate memory"
// *Cause: OTT was unable to allocate memory.
// *Action: Contact ORACLE customer support.
303,0,   "No INTYPE file was specified"
// *Cause: The required option INTYPE was not specified.
// *Action: Set the INTYPE option to the name of the file containing names
//  of types for OTT to translate.  The INTYPE option may be specified on
// the command line or in a CONFIG file.
304,0,   "Invalid filename for the INTYPE file"
// *Cause: The filename specified for the INTYPE file is not syntactically
//  correct.
// *Action: Make sure you spelled the filename of the INTYPE file correctly.
305,0,   "Error opening the INTYPE file for reading"
// *Cause: An operating system error occurred while attempting to open the
//  INTYPE file.
// *Action: Make sure you spelled the filename of the INTYPE file correctly.
//  Try opening the INTYPE file with an editor to make sure you have
//  access to the file.
306,0,   "Unable to close the INTYPE file"
// *Cause: An operating system error occurred while attempting to close the
//  INTYPE file.
// *Action: Try opening the INTYPE file with an editor to make sure you
//  are able to access the file.
307,0,   "Unable to read the INTYPE file"
// *Cause: The first token of the INTYPE file was not read.  Either an operating
//  system error occurred while attempting to read from the INTYPE file, or all
//  lines of the INTYPE file are blank lines or comment lines.
// *Action: Try opening the INTYPE file with an editor to make sure you
//  are able to access the file.  Make sure the INTYPE file contains one or
//  more type specifications.
308,0,  "No type specifications were seen in the INTYPE file"
// *Cause: Either there are no type specifications in the INTYPE file,
//  or the first type specification could not be read due to a previously
//  reported error.
// *Action: Fix any previously reported errors.  Make sure there are one or
//   more type specifications in the INTYPE file.
309,0,  "Name of user-defined type is illegal or missing"
// *Cause: The name of a user-defined type is expected following the keyword
// TYPE at the beginning of a type specification.  No legal type name was seen.
// *Action: Make sure that the type specification is syntactically correct,
//  and that the type name is spelled correctly.
310,0,  "Illegal or missing identifier name"
// *Cause: A legal C or C++ identifier was expected following AS, but was not
//  seen.
// *Action:  Use a legal C or C++ identifier, consisting of letters, digits,
//  and underscores not beginning with a digit.
311,0,  "Illegal or missing file name"
// *Cause: A legal file name was expected, but was not seen.
// *Action: Make sure your TYPE file syntax is correct. Use a correct file name.
312,0,  "Illegal or missing type version string"
// *Cause: A type version name was expected, but was not seen.
// *Action: Make sure your TYPE file syntax is correct. Use a correct version name.
313,0,  "Illegal or missing attribute name"
// *Cause: An attribute name was expected in the INTYPE file, but was not
// *Cause: An attribute name was expected in the INTYPE file, but was not
//  seen.
// *Action: Make sure your TYPE file syntax is correct.  Use a correct
//  attribute name.
314,0,  "AS expected but not seen in the INTYPE file"
// *Cause: Incorrect syntax in the INTYPE file.
// *Action: Make sure your TYPE file syntax is correct.
315,0,  "An attribute of a type is listed twice in a type specification"
// *Cause: An attribute of a user-defined type is listed twice in a type
// specification in the INTYPE file.  The second occurrence is ignored.
// *Action:  Remove one of the two occurrences of the attribute.
316,0,   "An unexpected token was seen at the end of a type specification"
// *Cause: There is a syntax error in the INTYPE file.
// *Action: Check your documentation to make sure the type specifications
//  in the INTYPE file are syntactically correct.
// *Action: Check your documentation to make sure the type specifications
317,0,   "Error opening the ERRTYPE file for writing"
// *Cause: An operating system error occurred while attempting to open the
//  ERRTYPE file for writing.
// *Action: Make sure you spelled the ERRTYPE filename correctly.  Try
//  creating or modifying the ERRTYPE file to make sure you have write access
//  to the file.
318, 0, "Error writing to the OUTTYPE file"
// *Cause: An operating system error occurred when attempting to write to
//  the OUTTYPE file.
// *Action: Make sure you have operating system permission to write to the
//  file.  Also, make sure disk space is available.
319,0,   "No OUTTYPE file specified"
// *Cause: The required option OUTTYPE was not specified.
// *Action: Set the OUTTYPE option to the name of the file to which the
// TYPE file produced by OTT should be written.  The OUTTYPE option
// may be specified on the command line or in a CONFIG file.
320,0,   "Invalid filename for the OUTTYPE file"
// *Cause: The filename specified for the OUTTYPE file is not syntactically
//  correct.
// *Action: Make sure you spelled the filename of the OUTTYPE file correctly.
321,0,   "Error opening the OUTTYPE file for writing"
// *Cause: An operating system error occurred while attempting to open the
//  OUTTYPE file.
// *Action: Make sure you spelled the filename of the OUTTYPE file correctly.
//  Make sure you have operating system permission to open the the file.
322,0,   "Unable to close the OUTTYPE file"
// *Cause: An operating system error occurred while attempting to close the
//  OUTTYPE file.
// *Action: Try opening the OUTTYPE file with an editor to make sure you
//  are able to access the file.
323,0,  "Internal error in OTT facility O2F"
// *Cause: An internal OTT error occurred in the O2F component of OTT.
// *Action: Contact ORACLE customer support.
324,0,  "Unable to convert from the database character set to the compiler character set"
// *Cause: The name of a type, attribute, or method cannot be converted from
//  the client character set in effect when OTT was invoked to the compiler
//  character set (typically ASCII or EBCDIC).
// *Action: A name is translated first from the database character set to
//  the client character set, and then from the client character set to the
//  compiler character set.  The client character set is specified in a
//  platform-dependent manner (On UNIX platforms, the client character set
//  is specified by setting the NLS_LANG environment variable).  Use a
//  client character set that can be translated to the compiler character
//  set.  The compiler character set itself is one such character set.
//  Specify synonyms in the INTYPE file for any names of database objects
//  that cannot be successfully translated to the client character set.
325,0,  "None of the characters in a name were legal identifier characters"
//  *Cause: None of the characters in the name of a database entity could
//   be translated to a character that may begin a C or C++ identifier,
//   such as a letter or an underscore.
//  *Action: Specify an explicit translation for the name in the INTYPE
//   file.
326,0,  "Some characters in this name were not legal identifier characters"
//  *Cause: One or more characters in the name of a database entity could
//   not be translated to a character that may appear in a C or C++
//   identifier, such as a letter, an underscore, or a digit.  The
//   characters that could not be translated were replaced with
//   underscores.
//  *Action: Make sure that the name is spelled correctly, and that it is
//   terminated by a blank, the end of a line, or an equals sign ("=").
//   You may use the translated name with added underscores, or
//   you may specify an explicit translation for the name in the INTYPE
//   file.
327,0, "CASE option has an illegal value"
//  *Cause: The value given for the CASE option in the INTYPE file is
//   not legal.
//  *Action: Change the value given for the CASE option to one of the
//   following legal values: SAME, LOWER, UPPER, or OPPOSITE.
328,0, "Illegal INITFUNC name"
//  *Cause: The function name given for the INITFUNC option in the INTYPE
//   file is not a legal C or C++ identifier.
//  *Action: Specify the name of the INITFUNC function as a legal C or C++
//   identifier.  This name can be given in the INTYPE file, given on the
//  command line, or derived from the INITFILE name.
329,0, "Type or option specification expected"
//  *Cause: A type or option specification was expected in the INTYPE file,
//   but was not seen.
//  *Action: Check the INTYPE file for syntax errors.  Supply a type or
//   option specification.  A type specification begins with the word
//   TYPE.  An option specification begins with the word CASE, INITFILE,
//   or INITFUNC.
330,0, "Name exceeds 265 bytes in length"
//  *Cause: A name seen in the INTYPE file exceeds 265 bytes in length.
//  *Action: Choose a shorter name.
331,0, "A syntactically illegal name was seen in the INTYPE file"
//  *Cause: A syntax error occurred in a name used in the INTYPE file.
//  *Action: If the name is quoted, make sure that the quotes are at the 
//  beginning and at the end of the name.  If a period
//  (which separates a schema name from a type name) 
//  appears, make sure that the schema name and the type name are both
//  present.
332,0, "A database link may not appear in the name of a user-defined type"
//  *Cause: A database link was seen in the name of a user-defined type.  This feature is
//   not yet supported.
//  *Action: Declare the user-defined type in the database to which OTT connects.
333,0, "An unexpected token appeared where a keyword was expected in the INTYPE file"
//  *Cause: A keyword such as TYPE was expected in the INTYPE file, but
//  an incorrect or misspelled keyword was seen.
//  *Action: Verify that your TYPE specification obeys the syntax
//  described in your documentation.  Verify that your keyword is
//  spelled correctly.
334,0, "A user-defined type is listed more than once in the INTYPE file"
//  *Cause: The same name of a user-defined type appears in more than one 
//   type specification.  The duplicate specifications of the type name will
//   be ignored.
//  *Action: Put all of the information about the type, including all type name
//   and attribute name translations, in a single TYPE specification, and
//   eliminate the duplicate TYPE specifications.
335,0, "Internal error in O2F component of OTT"
//  *Cause: A request was made to generate declarations for all the types in the
//   database schema.  An internal error occurred when initiating access to the
//  *Cause: A request was made that all types in the database schema are to 
//   database.
//  *Action: List the types to be processed in an INTYPE file.
//   Contact ORACLE customer support.
336,0, "Error reported by subsystem:\n    "
//  *Cause: A request was made to generate declarations for all the types in a
//   database schema.  An error occurred in a subsystem when accessing the database.
//  *Action: Examine the error message reported by the sybsystem to
//   determine its cause.  List the types to be processed in an INTYPE file. 
337,0, "Schema not found, or no types found in schema"
//  *Cause: A request was made to generate declarations for all the types
//  in a database schema.  Either the schema was not found, no user-declared
//  types  were found in the schema, or unable to connect to Oracle.
//  *Action: Ensure that a login/password string was specified for OTT and that
//   the Oracle database can be accessed with it.  Ensure that the
//   USER_TYPES table contains at least one row.
338,0, "Illegal or missing package name"
// *Cause: A legal Java package name was expected following IN or PACKAGE or
// IN PACKAGE, but was not seen.
// *Action:  Use a legal Java package name.
339,0, "CODE option has an illegal value"
//  *Cause: The value given for the CODE option in the INTYPE file is
//   not legal.
//  *Action: Change the value given for the CODE option to one of the
//   following legal values: C, ANSI_C, KR_C, JAVA, NATIVE_JAVA, ORACLE_JAVA.
340,0, "Name was null"
//  *Cause: A name had a length of 0 characters.
//  *Action: This error should never be reported to the user.  Contact
//  ORACLE customer support.
341, 0, "An error occurred for which no message is available"
//  *Cause: The cause of this error was not reported.
//  *Action: Contact ORACLE customer support.
