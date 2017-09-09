--
-- File:	DEINST_G2TRIGS.SQL
-- Purpose:	Delete the table and procedures neccessary to use triggers in
--		the G2-Informix bridge
-- Author:	B. Zhang
-- Date:	04/28/1997
--

-- Delete the trigger table
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
  select count(*) into cnt from sysprocedures where procname = 'g2_process_trigger';
  IF (cnt >0) THEN
    drop procedure g2_process_trigger;
  END IF;
END PROCEDURE
;
GRANT EXECUTE ON gensym_check_proc1 TO PUBLIC
;

CREATE PROCEDURE gensym_check_proc2()
  DEFINE cnt int;
  LET cnt = 0;
  select count(*) into cnt from sysprocedures where procname = 'g2_return_trigger';
  IF (cnt >0) THEN
    drop procedure g2_return_trigger;
  END IF;
END PROCEDURE
;
GRANT EXECUTE ON gensym_check_proc1 TO PUBLIC
;

-- Delete the procedure which drop the table g2_triggers_tbl if it exists
EXECUTE PROCEDURE gensym_check_obj()
;

-- Delete the procedure which drop the procedure g2_process_trigger if it exists
EXECUTE PROCEDURE gensym_check_proc1()
;

-- Delete the procedure which drop the procedure g2_return_trigger if it exists
EXECUTE PROCEDURE gensym_check_proc2()
;

DROP PROCEDURE gensym_check_obj
;
DROP PROCEDURE gensym_check_proc1
;
DROP PROCEDURE gensym_check_proc2
;
