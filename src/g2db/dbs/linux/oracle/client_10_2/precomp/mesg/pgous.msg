/ 
/ $Header: pgous.msg 07-jul-2004.10:05:37 rkoti Exp $ 
/ 
/ Copyright (c) 1991, 1995, 1996, 1997, 2000 by Oracle Corporation 
/   NAME
/     pgomsg.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    rkoti      07/07/04  - [3650151]check length of command line arguments
/    apopat     05/08/00 -  [1106176] TAG DO-NOT-TRANSLATE
/    erohwedd   03/11/97 -  [400907] warning #81 when option list not closed
/    jnewman    11/23/96 -  edit Cause and Action statements
/    losborne   05/13/96 -  XREF option list now shows where option set
/    sarnold    04/16/96 -  Adding file list file systems source file open mess
/    gturk      04/12/96 -  Added unable to open include file error
/    gturk      04/02/96 -  Added error subsystem error messages
/    sarnold    11/28/95 -  Fix bug 281779. No blanks around =
/    gdas       10/11/95 -  rename message file pgomsg.msg to pgous.msg
/    jbasu      07/03/95 -  [274828] Add strings #1030, 1031
/    gdas       04/21/95 -  merge changes from branch 1.7.720.1
/    gdas       03/03/95 -  Added Cause/Action text
/    mchiocca   07/06/94 -  [224731] Oracle Option Abbreviations on LHS/RHS
/    mchiocca   02/22/94 -  Add unable to open config file message
/    mchiocca   02/18/94 -  Shorten system config file message
/    rhari      02/04/94 -  Add error 45
/    cracicot   06/04/92 -  change wording of 'default values taken...' 
/    cracicot   05/18/92 -  change 1015 to not document 1,0 
/    tolkin     01/27/92 -  Creation 
/
35 , 0, "CMD-LINE:  CONFIG= option is invalid in a config file"
//    *Cause: A user configuration file inside a user configuration file 
//            cannot be specified. That is, nested configuration files 
//            cannot be nested.
//    *Action: If there are nested configuration files, move the options 
//             from the nested files to the top levels.
40 , 0, "CMD-LINE:  Option selected, but no value provided"
//    *Cause: An option on the command line was specified, but a value for it
//            was not included. For example, the offending code might look
//            like:
//               proc iname=sample1.pc oname=
//    *Action: Provide a value for the option.
41 , 0, "CMD-LINE:  Option does not exist:  "
//    *Cause: A non existent option on the command line was specified.
//    *Action: See the Programmer's Guide to the Oracle Precompilers,
//             Release 2.2 for a list of the valid command line options
//             and their possible values.
43 , 0, "CMD-LINE:  Option syntax is incorrect"
//    *Cause: A value for a command line option was incorrectly specified.
//    *Action: See the Programmer's Guide to the Oracle Precompilers,
//             Release 2.2 for the correct syntax for specifying command
//             line option values.
44 , 0, "CMD-LINE:  Illegal or out of range value for option:  "
//    *Cause: A value specified for a command line option was not within the
//            accepted range. For example,, the range for the MAXOPENCURSORS
//            option is 5 to 256. If a value outside the range is specified,
//            the message is triggered.
//    *Action: See the Programmer's Guide to the Oracle Precompilers for the
//             ranges that option values can take.
45 , 0, "CMD-LINE:  Option is not unique:  "
//    *Cause: An option name was partially specified on the command line
//            that made it non unique. For example,
//                % proc in=t.pc
//            the "in" option can imply either the INAME or INCLUDE
//            option.
//    *Action: Provide sufficient characters on the command line to make the
//             option name unique.
46 , 0, "CMD-LINE:  Unable to open config file:  "
//    *Cause: A non-existent user configuration file was specified on the 
//            command line with the config option.
//    *Action: Provide a valid filename for the configuration file.
47 , 0, "CMD-LINE:  Option is not allowed inline:  "
//    *Cause: An option was entered inline that can only be entered on the
//            command line or in a configuration file. For example, the 
//            offending code might look like
//                 EXEC ORACLE OPTION (NLS_CHAR=<name>);
//            The NLS_CHAR option can only be entered on the command line or
//            in a configuration file.
//    *Action: Remove the option from the source file, and specify it on the 
//             command line.
66 , 0, "CMD-LINE:  Could not find or could not open system config file"
//    *Cause: The system configuration file has a standard name (pmscfg.h)
//            and a location that is operating system dependent. On UNIX
//            systems, it is located in the ORACLE_HOME/proc directory. If
//            a file named pmscfg.h is not found in the standard location,
//            this warning message is issued.
//    *Action: Create a system configuration file in the standard location. 
//             The file can be empty. See also the operating system specific
//             Oracle documentation.
81 , 0, "CMD-LINE:  Unterminated option value list or value list was truncated."
//    *Cause: An option that takes a list of values was entered. The value
//            list did not have a closing parenthesis.
//            This error may also occur if the list of values entered
//            on a single line was too long and Pro*C truncated it.
//   *Action: Ensure that all value lists are terminated with a closing
//            parenthesis. Split long value lists into individual entries.
129, 0, "CMD-LINE:  Client supplied static options table is invalid"
//    *Cause: This is an internal error message not usually issued.
//    *Action: Call Oracle customer support.
132, 0, "CMD-LINE:  Could not allocate memory"
//    *Cause: This is an internal error message not usually issued.
//    *Action: Call Oracle customer support.
133, 0, "CMD-LINE:  Error in string processing function"
//    *Cause: This is an internal error message not usually issued. It
//            indicates that a C string function, such as strcpy or strlen,
//            returned an error.
//    *Action: Call Oracle customer support.
134, 0, "CMD-LINE:  Null option supplied"
//    *Cause: A zero length option was specified on the command line.
//    *Action: Re-enter the command line with a valid option.
135, 0, "CMD-LINE:  User asked for help"
//    *Cause: This is a final message that the precompiler issues when 
//            information about the command line options has been requested.
//            For example, if the command
//                proc ?
//            is issued  to get a list of current default values for the 
//            command line options, this message appears at the end of the
//            list.
//    *Action: No action required.
138, 0, "CMD-LINE:  Internal consistency error"
//    *Cause: This is an internal message for program exceptions.
//             An unexpected condition was encountered by 
//             the command-line processor and a consistency check failed. 
//             Some possible causes of this 
//             message include: 
//                 --invalid command-line options
//                 --memory corruption
//    *Action: Report this error to Worldwide Support after gathering 
//             the following information: 
//                 --the events that led to the error  
//                 --the attempted operations that led to the error 
//                 --any unusual circumstances prior to this error
144, 0, "CMD-LINE: Blank characters are not allowed on either side of an equal sign (=)"
//    *Cause: An equal sign (=) was either immediately preceded or followed
//    by a blank character.
//    *Action: Precompile your program again without blank characters on either
//     side of any equal sign (=) on the command line.
146, 0, "CMD-LINE: value of option too long"
//   *Cause: The length of the user option exceeded 1023 bytes
//   *Action: Reduce the length of the user option
150, 0, "Error at line %d, column %d in file %s"
//   *Cause: An error was encounter at the given location.
//   *Action: Check the named source file and correct the error using the
//            additional information which follows this error message.
151, 0, "Line %d column %d file %s:"
//    *Cause: An error was encounter at the given location.
//    *Action: Check the listed source file and correct the error using the
//            additional information which follows this error message.
152, 0, "Unable to open file %s to display or list the source line %d"
//    *Cause: The file contains an error, but could not be reopened to
//            list or display the incorrect line.
//    *Action: Check that the file is intact and it has read permission.
//             Then rerun the operation.
153, 0, "Open file: %s"
//     *Cause: A new source file was opened while producing the list file.
//     *Action: No action required; this is an  informational message.
154, 0, "Close file: %s"
//     *Cause: A source file was closed while producing the list file.
//     *Action: No action required; this is an informational message.

1000, 0, "Option name   :  "
1001, 0, "Description   :  "
1002, 0, "Current value :  "
1003, 0, "Restrictions  :  "
1004, 0, "string "
1005, 0, "number "
1006, 0, "boolean "
1007, 0, "*none*"
1008, 0, "range "
1009, 0, " - "
1010, 0, ", "
1011, 0, "one of:  "
1012, 0, "(string,...) "
1013, 0, "(number,...) "
1014, 0, "\n"
1015, 0, "yes, no, true, false"
1016, 0, "yes"
/         ***
1017, 0, "no"
/         **
1018, 0, "\""
1019, 0, " "
1020, 0, "Option Name"
1021, 0, "Current Value"
1022, 0, "Allowed Values"
1023, 0, "Description"
1024, 0, "System default option values taken from: "
1025, 0, "="
1026, 0, "*OR* "
1027, 0, "("
1028, 0, ")"
1029, 0, "*empty string*"
1030, 0, "Precompiler Options"
1031, 0, "-"
1032, 0, "Where set"
1033, 0, "default"
1034, 0, "command line"
1035, 0, "inline"
