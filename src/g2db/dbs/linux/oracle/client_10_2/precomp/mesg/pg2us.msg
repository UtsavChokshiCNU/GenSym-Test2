/ 
/ $Header: pg2us.msg 23-nov-96.14:38:51 jnewman Exp $
/ 
/ Copyright (c) 1991, 1996 by Oracle Corporation 
/   NAME
/     pg2us.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    jnewman    11/23/96 -  edit Cause and Action statements
/    mchiocca   09/16/96 -  [NCHAR] Implement N quoted literals
/    jbasu      06/13/95 -  Rename pgperr.msg to pg2us.msg
/    gdas       04/21/95 -  merge changes from branch 1.8.720.1
/    gdas       03/03/95 -  Added Cause/Action Text
/    mchiocca   05/24/94 -  merge changes from branch 1.5.710.3
/    mchiocca   05/24/94 -  NTT MIA - Error for N'<string>' and NLS_LOCAL = NO
/    mchiocca   04/27/94 -  NTT MIA - Error if N'<sql string>' inside PL/SQL
/    jweisz     11/04/93 -  [186346] mesgs for EOF during sql/pls
/    jweisz     05/17/93 -  add msg for nl in C string 
/    jweisz     04/01/93 -  Add error, warning messages 
/    jweisz     12/09/92 -  Change wording of syntax error msg
/    jweisz     10/26/92 -  Handle unterminated comment
/    pdufour    05/14/92 -  Creation 
10,0,	"found end-of-file while scanning string literal"
//   *Cause:  A string in a SQL statement, which should be delimited by
//            single quotation marks, was not terminated properly.
//   *Action:  Check that all strings are delimited.
11,0,	"found identifier greater than 128 characters (truncated)"
//   *Cause: The precompiler found an identifier that was too long.
//   *Action: Shorten the identifier. SQL identifiers should be limited to
//            18 characters.
12,0,	"did not find matching quote for char constant"
//   *Cause:  A character constant with a single quotation mark was not
//            terminated.
//   *Action: Terminate the character constant.
13,0,	"unknown escape sequence"
//   *Cause:  The precompiler found an escape sequence that it could not
//            process inside a string literal. This error can arise when
//            multibyte character strings that can contain shift-in or
//            shift-out escape sequences are used.
//   *Action: Correct the string representation.
14,0,	"Syntax error at line %d, column %d, file %s:\n"
//   *Cause: The precompiler detected an errorin C or embedded SQL syntax.
//           This message is followd by a more specific error message.
//   *Action: Correct the syntax error.
15,0,	"unable to open include file"
//   *Cause: The precompiler could not open a header file that was specified
//           using the #include preprocessor directive or the EXEC SQL
//           INCLUDE statement. This can happen if the file specification
//           is inaccurate or if read permission or read access rights on the
//           file or on one or more of the directories in the path were not
//           granted.
//   *Action: Recheck that the file specification is correct, that the file
//            exists, and that read permission has been granted so that the
//            file can be read.
16,0,	"include file pathname is too long"
//   *Cause: The pathname for include files exceeded the maximum length of 80
//           characters.
//   *Action: Move the include file, or create an environment variable or
//            logical to shorten the pathname.
17,0,	"unable to open output file"
//   *Cause: The precompiler could not open an output file. This could be a
//           generated code output file(.c file) or a listing file. This
//           message can result from many causes. For example:
//               o) A pathname for a specified output file contains a
//                  non-exixtent directory.
//               o) An operating-system error occured because the file system
//                  or disk is full.
//               o) Write permission on the specified directory or directories
//                  in the path do not exist.
//   *Action: Track down the cause of the error, as suggested above, and
//            correct it.
18,0,   "found end-of-file while scanning comment"
//   *Cause: A C comment either in C code or in an embedded SQL statement,
//           was not terminated.
//   *Action: Find the unterminated comment and terminate it with */ .
19,0,	"Preprocessor warning at line %d, column %d, file %s:\n"
//   *Cause: This message indicates that a warning condition occured as the
//           precompiler was doing the preprocessor pass. A more specific 
//           warning message will follow this message.
//   *Action: Correct the condition according to the action specified for 
//            the message that follows.
20,0,	"Preprocessor error at line %d, column %d, file %s:\n"
//   *Cause: This message indicates that an error condition occured as the
//           precompiler was in the preprocessing phase. A more specific
//           error message will follow this message.
//   *Action: Correct the error according to the action specified for the
//            message that follows.
21,0,	"Found newline while scanning string literal"
//   *Cause: A string constant contains a newline character, For example
//           char x[] = "Hello
//                       world";
//   *Action: Remove the newline character.
22,0,   "Found end of file while scanning a SQL statement"
//   *Cause: The precompiler encountered an end of file while parsing an EXEC
//           SQL statement.
//   *Action: Add statement terminator(;) or complete the EXEC SQL statement.
23,0,   "Found end of file while scanning a PL/SQL statement"
//   *Cause: The precompiler encountered an end of file while parsing a
//           PL/SQL statement (EXEC SQL EXECUTE ...).
//   *Action: Complete the PL/SQL statement.
