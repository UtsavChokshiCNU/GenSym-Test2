/*
** File:	DEINST_G2TRIGS.SQL
** Purpose:	Delete the table and procedures neccessary to use triggers in
**		the G2-Sybase bridge
** Author:	P. Hill
** Date:	31-Jan-1997
*/

/* Delete the trigger table */

IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_triggers_tbl')
  DROP TABLE g2_triggers_tbl
go
 
/* Delete the procedures */
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_insert_trig_proc')
  DROP PROCEDURE g2_insert_trig_proc
go
 
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_process_trig_proc')
  DROP PROCEDURE g2_process_trig_proc
go

IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_proc_trig')
  DROP PROCEDURE g2_proc_trig
go

