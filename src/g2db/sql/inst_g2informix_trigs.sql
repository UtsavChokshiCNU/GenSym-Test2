--
-- File:	INST_G2TRIGS.SQL
-- Purpose:	Create the table and procedures neccessary to use triggers in
--		the G2-Informix bridge
-- Author:	B. Zhang
-- Date:	04/28/97


-- Create the trigger table

CREATE PROCEDURE gensym_check_obj()
  DEFINE cnt int;
  LET cnt =0;
  select count(*) into cnt from systables where tabname = 'g2_triggers_tbl';
  IF (cnt >0) THEN
    drop table g2_triggers_tbl;
  END IF;
END PROCEDURE
;
GRANT EXECUTE ON gensym_check_obj TO PUBLIC
;

CREATE PROCEDURE gensym_check_proc1()
  DEFINE cnt int;
  LET cnt = 0;
  select count(*) into cnt from sysprocedures where procname = 'g2_int_trig_proc';
  IF (cnt >0) THEN
    drop procedure g2_int_trig_proc;
  END IF;
END PROCEDURE
;
GRANT EXECUTE ON gensym_check_proc1 TO PUBLIC
;

CREATE PROCEDURE gensym_check_proc2()
  DEFINE cnt int;
  LET cnt = 0;
  select count(*) into cnt from sysprocedures where procname = 'g2_pro_trig_proc';
  IF (cnt >0) THEN
    drop procedure g2_pro_trig_proc;
  END IF;
END PROCEDURE
;
GRANT EXECUTE ON gensym_check_proc1 TO PUBLIC
;

EXECUTE PROCEDURE gensym_check_obj()
;
CREATE TABLE g2_triggers_tbl
( trig_id		SERIAL PRIMARY KEY,
  trig_name		VARCHAR(30) NOT NULL,
  trig_msg		VARCHAR(200),
  trig_datetime		DATETIME YEAR TO SECOND NOT NULL
)
;
GRANT ALL ON g2_triggers_tbl TO PUBLIC
;
--
-- Create a procedure that will add an entry to the g2_triggers_tbl table.
-- This should be called at the end of any trigger the user wants
-- to monitor
--
EXECUTE PROCEDURE gensym_check_proc1()
;
CREATE PROCEDURE g2_process_trigger (t_name  VARCHAR(18), t_msg  VARCHAR(200))
  INSERT INTO g2_triggers_tbl VALUES( 0, t_name, t_msg, CURRENT );
END PROCEDURE
;
GRANT EXECUTE ON g2_process_trigger TO PUBLIC
;

--
-- Create a procedure to process an entry in the g2_triggers_tbl table.
-- One row is selected by "trig_name" and the lowest "trig_id" and then
-- that row is deleted. The "trig_msg" and "trig_datetime" of the row selected
-- are returned to the caller.
--
EXECUTE PROCEDURE gensym_check_proc2()
;
CREATE PROCEDURE g2_return_trigger(t_name varchar(18))
  RETURNING varchar(200),varchar(30);
   DEFINE err_num int;
   DEFINE t_id  int;
   DEFINE t_msg varchar(200);
   DEFINE t_datetime varchar(30);
   ON EXCEPTION IN (1)
   END EXCEPTION
   SELECT trig_id,trig_msg, trig_datetime INTO t_id,t_msg,t_datetime
      FROM g2_triggers_tbl
      WHERE trig_id = (SELECT MIN(trig_id) FROM g2_triggers_tbl
                         WHERE trig_name = t_name);
    IF t_id IS NOT NULL THEN
      DELETE FROM g2_triggers_tbl where trig_id = t_id;
    ELSE
      RAISE EXCEPTION 1;
    END IF
    RETURN t_msg,t_datetime;
END PROCEDURE
;
GRANT EXECUTE ON g2_return_trigger TO PUBLIC
;

DROP PROCEDURE gensym_check_obj
;

DROP PROCEDURE gensym_check_proc1
;

DROP PROCEDURE gensym_check_proc2
;
