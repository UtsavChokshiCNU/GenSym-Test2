/*
** File:	DEINST_G2ODBC_TRIGS.SQL
** Purpose:	A sample script file for deleting the components necessary for
**              the G2-ODBC Version 6 bridge to support events with triggers.
**		The user should feel free to modify this so that it works
**		with their particular database.
**
** Note:	This script will work on Microsoft SQL Server Version 6.0 and
**		Sybase SQL Server Version 10 or 11.
**
** Copywrite:   August 1997
**		Gensym Corporation
**		125 CambridgePark Drive
**		Cambridge MA 02140
**		(617) 547-2500
*/

/* Delete the trigger table */

IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_triggers_tbl')
  DROP TABLE g2_triggers_tbl
go
 
/* Delete the procedures */
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2odbc_ins_trigs')
  DROP PROCEDURE g2odbc_ins_trigs
go
 
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2odbc_proc_trigs')
  DROP PROCEDURE g2odbc_proc_trigs
go

