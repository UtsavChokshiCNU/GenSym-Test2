/ 
/ $Header: pcfus.msg,v 1.1 1995/06/13 18:49:30 jbasu Exp $
/ 
/ Copyright (c) 1991, 1997, 1998 by Oracle Corporation 
/   NAME
/     pcfus.msg - <one-line expansion of the name>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    mchiocca   02/09/98 -  [COLL] FIPS Flag all Collections Statements
/    mchiocca   01/19/98 -  [LOB] FIPS Flag All LOB Statements
/    mchiocca   05/13/97 -  [NAV] FIPS Flag all Navigational Statements
/    mchiocca   05/08/97 -  Update FIPS Report and Messages
/    jbasu      06/13/95 -  Rename pcferr.msg to pcfus.msg
/    mchiocca   04/28/95 -  [278793] Add FIPS flagging for CREATE <PL/SQL>
/    mchiocca   06/29/94 -  Result Sets - Add FIPS Flagging
/    mchiocca   03/03/94 -  [200320] Clean up FIPS error messages
/    jweisz     02/25/94 -  [199633] flag non-ansi funcs
/    jweisz     09/24/93 -  [181786] add DROP TABLE msg
/    jweisz     04/30/93 -  Base fips msgs from 250 
/    jweisz     01/07/93 -  Add many more fips messages
/    pdufour    05/14/92 -  Creation 
/
1,0,	"Oracle FIPS Flagging Report Version %d.%d - %s\n\n"
2,0,	"This report lists extensions to ANSI SQL document %s\n"
3,0,	"No extensions were detected.\n"
4,0,	"The following extensions were detected:\n\n"
5,0,	"Violation\tLine Number\tDescription\n"
6,0,	"The following non-standard usages were detected:\n\n"
7,0,	"The following extensions which will become standard in a future\n"
8,0,	"release of the SQL standard were detected:\n\n"
9,0,	"Violation\tRevision   \tLine Number\tDescription\n"
10,0,	"---------\t-----------\t---------------------------------------\n"
11,0,	"---------\t-----------\t-----------\t--------------------------\n"
12,0,	"Found %d violations of ANSI SQL standard %s.\n\n"
13,0,	"This application conforms 100%% to ANSI SQL standard %s.\n\n"
14,0,	"ANSI SQL document comparison cross-reference by line number:\n\n"
15,0,	"The Oracle FIPS Flagger was active for all lines in the source.\n\n"
16,0,	"Violations may have occurred on lines notated with 'none'.\n\n"
17,0,	"\n%d - %d\t\t"
18,0,	"X3.168-1989"
19,0,	"X3.135-1992"
20,0,	"Development"
21,0,	"Alpha"
22,0,	"Beta"
23,0,	"Production"
24,0,	"\n"
25,0,	"\t\t"
26,0,	"\t\t"
27,0,	"The following deprecated features were detected:\n\n"
28,0,	"none"
29,0,	"\n%d - end\t\t"
30,0,	"Line Numbers\tDocument Referenced\n"
31,0,	"------------\t-------------------"
32,0,	"\t"
/
/ FIPS Flagger violations section
/
251,0,	"SQLCODE is a deprecated feature"
252,0,	"use of the C preprocessor within SQL"
253,0,	"use of the AT clause"
254,0,	"use of the FOR clause"
255,0,	"use of the CONNECT statement"
256,0,	"SQLCODE returns non-standard values"
257,0,	"keyword WORK required after COMMIT"
258,0,	"keyword WORK required after ROLLBACK"
259,0,  "use of TO SAVEPOINT clause"
260,0,  "use of RELEASE clause"
261,0,  "use of dynamic SQL"
262,0,  "use of PL/SQL"
263,0,  "use of SQLWARN within WHENEVER clause"
264,0,  "use of NOTFOUND within WHENEVER clause"
265,0,  "use of COMMENT clause with COMMIT"
266,0,  "use of STOP within WHENEVER clause"
267,0,  "use of FORCE TRANSACTION clause"
268,0,  "use of DO within WHENEVER clause"
269,0,  "use of DECLARE TABLE statement"
270,0,  "use of DECLARE DATABASE statement"
271,0,  "use of EXEC SQL INCLUDE"
272,0,  "use of datatype equivalencing"
273,0,  "use of SQL FORMS statement"
274,0,  "use of EXEC ORACLE statement"
275,0,  "invalid datatype"
276,0,  "use of DROP TABLE statement"
277,0,  "use of non-ANSI function"
278,0,  "use of the ALLOCATE statement"
279,0,  "use of CREATE to build PL/SQL objects"
280,0,	"use of OBJECT Navigational Interface"
281,0,  "use of LOB statement"
282,0,	"use of COLLECTION statement"
