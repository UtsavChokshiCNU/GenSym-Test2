# CHARACTER_SET_NAME=SWEDISH_SWEDEN.WE8ISO8859P1
/
/ $Header: o2uus.msg 23-nov-96.12:46:17 jnewman Exp $
/
/ Copyright (c) 1995, 1996, 1997, 1998 by Oracle Corporation
/   NAME
/     o2u.msg - <Ots2c Unparser messages>
/   DESCRIPTION
/     <short description of component this file declares/defines>
/   RETURNS
/
/   NOTES
/     <other useful comments, qualifications, etc.>
/   MODIFIED   (MM/DD/YY)
/    pthiesen   03/02/98 - Improve Cause/Action for 203
/    erohwedd   01/24/97 - Replaced message 211 with actual message text.
/    pthiesen   01/22/97 -
/    pthiesen   11/25/96 -
/    jnewman    11/23/96 -  edit Cause and Action statements
/    pthiesen   11/07/96 -  use new terminology in error messages
/    pthiesen   06/22/96 -  add error messages
/    pthiesen   12/01/95 -  name translation
/    pthiesen   07/31/95 -  No reason specified
/    pthiesen   07/27/95 -  Add new error message
/    pthiesen   10/17/94 -  Creation
/    pthiesen   10/13/94 -  Creation
/
200,0,   "Internt fel i OTT-funktion O2U"
// *Cause: An internal OTT error occurred in the O2U facility of OTT.
// *Action: Contact ORACLE customer support.
201,0,   "Ogiltiga argument för funktionen o2upt()"
// *Cause: Illegal arguments were passed to the function o2upt().
//  This is an internal error that should not be encountered by an
//  end user.
// *Action: Contact ORACLE customer support.
202,0,   "Ogiltiga data överförda till funktion"
// *Cause: Arguments with incorrect values were passed to the function
//  o2upt().  This is an internal error that should not be encountered
//  by the end user.
// *Action: Contact ORACLE customer support.
203,0,   "Typen som ska deklareras måste vara en objekttyp eller en namngiven insamlingstyp"
// *Cause: You have asked OTT to generate code for a type it does not support.
//  When generating Java code, OTT will only generate code for object
//  types.  When generating C declarations, OTT will only generate
//  declarations for object types and named collection types.
// *Action: You are probably asking OTT to declare a built-in type, or, if
//  you are generating Java code, a named collection type.  Do not
//  ask OTT to generate a declaration for this type.
204,0,  "Kan inte konvertera från databasens teckenuppsättning till kompilatorns"
// *Cause: The name of a type, attribute, or method cannot be converted from
//  the client character set in effect when OTT was invoked to the compiler
//  character set (typically ASCII or EBCDIC).
// *Action: A name is translated first from the database character set to
//  the client character set, and then from the client character set to the
//  compiler character set.  The client character set is specified in a
//  platform-dependent manner (On UNIX platforms, the client character set
//  is specified by setting the NLS_LANG environment variable.)  Use a
//  client character set that includes the character set of the INTYPE file and can be
//  translated to the compiler character set.  The database character set is one such
//  character set.  Specify synonyms in the INTYPE file for any names of database objects
//  that cannot be successfully translated to the client character set.
205,0,  "Inga av tecknen i ett typnamn var giltiga identifierartecken"
//  *Cause: None of the characters in the name of a user-defined type could
//   be translated to a character that can begin a C or C++ identifier,
//   such as a letter or an underscore.
//  *Action: Specify an explicit translation for the type name in the
//   INTYPE file.
206,0,  "Vissa tecken i ett typnamn var inte giltiga identifierartecken"
//  *Cause: One or more characters in the name of a user-define type could
//   not be translated to a character that can appear in a C or C++
//   identifier, such as a letter, an underscore, or a digit.  The characters that
//   could not be translated were replaced with underscores.
//  *Action: Specify an explicit translation for the type name in
//   the INTYPE file, or just use the translated type name with added underscores.
207,0,  "Inga av tecknen i ett attributnamn var giltiga identifierartecken"
//  *Cause: None of the characters in the name of an attribute of a type
//   could be translated to a character that can begin a C or C++ identifier,
//   such as a letter or an underscore.  To find the affected attribute, look in
//   the declaration generated for this type for data member names that are
//   obviously incorrect.
//  *Action: Specify an explicit translation for the attribute name in the
//   INTYPE file.
208,0,  "Ett eller flera tecken i ett attributnamn var inte giltiga identifierartecken"
//  *Cause: If an attribute name contains one or more characters that can not
//   be translated to a legal C or C++ identifier character, the characters
//   that can not be translated are replaced with underscores.  To find the
//   affected attribute or attributes, look in
//   the declaration generated for this type for data member names that have
//   extra underscores not present in the original attribute names.
//  *Action: Specify explicit translations for the affected attribute names in
//   the INTYPE file, or just use the translated attribute names with added underscores.
209,0,  "Attribut- eller funktionsnamnet som skulle översättas finns inte"
//  *Cause: This name, for which a translation was requested, is not the
//   name of an attribute or a function of the current type.
//  *Action: Make sure that the name is spelled correctly, and is the name of an
//   attribute or function defined in the current type.
210,0,   "Kan inte allokera minne"
// *Cause: OTT was unable to allocate memory.
// *Action: Contact ORACLE customer support.
211, 0, "En typ utan attribut översattes"
//  *Cause: OTT translated a type without attributes. The corresponding
//   C-type will be a struct without any components, which is not legal C. 
//   The empty type in the database may be the result of an error 
//   during type creation. Additionally, incomplete types may be
//   used temporarily in the creation of types that reference one another.
//  *Action: Re-create a full version of the type in the database and then
//   re-run OTT.
212, 0, "Ett fel, som det inte finns något meddelande för, har inträffat"
//  *Cause: The cause of this error was not reported.
//  *Action: Contact ORACLE customer support.
