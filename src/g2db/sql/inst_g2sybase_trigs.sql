/*
** File:	INST_G2TRIGS.SQL
** Purpose:	Create the table and procedures neccessary to use triggers in
**		the G2-Sybase bridge
** Author:	P. Hill
** Date:	16-Jan-1997
*/

/* Create the trigger table */

IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_triggers_tbl')
  DROP TABLE g2_triggers_tbl
go
CREATE TABLE g2_triggers_tbl
( trig_id		NUMERIC IDENTITY,
  trig_name		VARCHAR(30) NOT NULL,
  trig_msg		VARCHAR(200) NULL,
  trig_datetime		DATETIME NOT NULL 
)
go
EXECUTE sp_primarykey g2_triggers_tbl, trig_id
go
GRANT ALL ON g2_triggers_tbl TO PUBLIC
go

/*
** Create a procedure that will add an entry to the g2_triggers_tbl table.
** This should be called at the end of any trigger the user wants
** to monitor
*/
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_insert_trig_proc')
  DROP PROCEDURE g2_insert_trig_proc
go
CREATE PROCEDURE g2_insert_trig_proc
  @t_name    VARCHAR(30),
  @t_msg     VARCHAR(200)
  AS
  INSERT INTO g2_triggers_tbl VALUES( UPPER(@t_name), @t_msg, GETDATE() )
  RETURN @@error
go
sp_procxmode g2_insert_trig_proc, "anymode"
go
GRANT EXEC ON g2_insert_trig_proc TO PUBLIC
go

/*
** Create a procedure to process an entry in the g2_triggers_tbl table.
** One row is selected by "trig_name" and the lowest "trig_id" and then
** that row is deleted. The "trig_msg" and "trig_datetime" of the row selected
** are returned to the caller.
*/ 
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_process_trig_proc')
  DROP PROCEDURE g2_process_trig_proc
go
CREATE PROCEDURE g2_process_trig_proc
  @t_name VARCHAR(30),
  @t_msg  VARCHAR(200) OUTPUT,
  @t_date VARCHAR(30) OUTPUT
  AS
  DECLARE @t_id NUMERIC
  DECLARE @rslts VARCHAR(10)
    SELECT @t_id=trig_id, @t_msg=trig_msg, @t_date=trig_datetime
      FROM g2_triggers_tbl 
      WHERE trig_id = (SELECT MIN(trig_id) FROM g2_triggers_tbl 
                        WHERE trig_name = upper(@t_name))
	 IF @t_id IS NOT NULL
      		DELETE FROM g2_triggers_tbl where trig_id = @t_id
         COMMIT
go
sp_procxmode g2_process_trig_proc, "unchained"
go
GRANT EXEC ON g2_process_trig_proc TO PUBLIC
go

/*
** Create a procedure to process an entry in the g2_triggers_tbl table.
** One row is selected by "trig_name" and the lowest "trig_id" and then
** that row is deleted. The "trig_msg" and "trig_datetime" of the row selected
** are returned to the caller.  Reports success or failure of finding entry.
*/ 
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'g2_proc_trig')
  DROP PROCEDURE g2_proc_trig
go
CREATE PROCEDURE g2_proc_trig
  @t_name VARCHAR(30),
  @t_msg  VARCHAR(200) OUTPUT,
  @t_date VARCHAR(30) OUTPUT,
  @t_success BIT OUTPUT
  AS
  DECLARE @t_id NUMERIC
    SELECT @t_id=trig_id, @t_msg=trig_msg, @t_date=trig_datetime
      FROM g2_triggers_tbl 
      WHERE trig_id = (SELECT MIN(trig_id) FROM g2_triggers_tbl 
                        WHERE trig_name = upper(@t_name))
	 IF @t_id IS NULL
	 	SELECT @t_success = 0
	 ELSE
	  	BEGIN
      		DELETE FROM g2_triggers_tbl where trig_id = @t_id
		SELECT @t_success= 1 
		END
    COMMIT
go
sp_procxmode g2_proc_trig, "anymode"
go
GRANT EXEC ON g2_process_trig_proc TO PUBLIC
go
