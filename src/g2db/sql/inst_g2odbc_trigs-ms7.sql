/*
** File:	INST_G2ODBC_TRIGS.SQL
**
** Purpose:	A sample script file for creating the components necessary for
**              the G2-ODBC Version 6 bridge to support events with triggers.
**		The user should feel free to modify this so that it works
**		with their particular database.
**
** Note:	This script will work on Microsoft SQL Server Version 6.0 and if
**		appropriate parts are uncommented, it will work on Sybase SQL Server
**		Version 10 or 11.
**
** Copywrite:   August 1997
**		Gensym Corporation
**		125 CambridgePark Drive
**		Cambridge MA 02140
**		(617) 547-2500
*/

/* Create the trigger table */

IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_triggers_tbl')
  DROP TABLE g2_triggers_tbl
go
CREATE TABLE g2_triggers_tbl
( trig_id		NUMERIC IDENTITY PRIMARY KEY ,
  trig_name		VARCHAR(30) NOT NULL,
  trig_msg		VARCHAR(200) NULL,
  trig_datetime		DATETIME NOT NULL 
)
go
-- EXECUTE sp_primarykey g2_triggers_tbl, trig_id
-- go
GRANT ALL ON g2_triggers_tbl TO PUBLIC
go

/*
** Create a procedure that will add an entry to the g2_triggers_tbl table.
** This should be called at the end of any trigger the user wants
** to monitor
*/
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2odbc_ins_trigs')
  DROP PROCEDURE g2odbc_ins_trigs
go
CREATE PROCEDURE g2odbc_ins_trigs
  @t_name    VARCHAR(30),
  @t_msg     VARCHAR(200)
  AS
  INSERT INTO g2_triggers_tbl VALUES( UPPER(@t_name), @t_msg, GETDATE() )
  RETURN @@error
go

/*
** Uncomment the following line for Sybase
**
** sp_procxmode g2odbc_ins_trigs, "anymode"
** go
*/

GRANT EXEC ON g2odbc_ins_trigs TO PUBLIC
go

/*
** Create a procedure to process an entry in the g2_triggers_tbl table.
** One row is selected by "trig_name" and the lowest "trig_id" and then
** that row is deleted. The "trig_msg" and "trig_datetime" of the row selected
** are returned to the caller.
*/ 
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2odbc_proc_trigs')
  DROP PROCEDURE g2odbc_proc_trigs
go
CREATE PROCEDURE g2odbc_proc_trigs
  @t_name VARCHAR(30),
  @t_msg  VARCHAR(200) OUTPUT,
  @t_date VARCHAR(30) OUTPUT,
  @p_status INTEGER OUTPUT
  AS
  DECLARE @t_id NUMERIC
  SET NOCOUNT ON
    SELECT @p_status = 0
    SELECT @t_id=trig_id, @t_msg=trig_msg, @t_date=trig_datetime
      FROM g2_triggers_tbl 
      WHERE trig_id = (SELECT MIN(trig_id) FROM g2_triggers_tbl 
                        WHERE trig_name = @t_name)
    IF @t_id IS NOT NULL
      DELETE FROM g2_triggers_tbl where trig_id = @t_id
    ELSE
      SELECT @p_status = 100
go

/*
** Uncomment the following line for Sybase
**
** sp_procxmode g2odbc_proc_trigs, "unchained"
** go
*/

GRANT EXEC ON g2odbc_proc_trigs TO PUBLIC
go
