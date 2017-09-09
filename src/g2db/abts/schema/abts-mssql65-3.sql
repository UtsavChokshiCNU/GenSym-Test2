 -- clear
PRINT '====================================================================='
PRINT '   ABTS DATABASE TABLES AND TEST DATA FOR Microsoft SQL Server'
PRINT '====================================================================='
set nocount    on
set dateformat mdy

USE abts
GO

if db_name() = 'abts'
   PRINT '''abts'' database created, and context now in use.'
else
   PRINT 'Error in abts_tables_mssql.SQL, ''USE abts'' failed!  Killing the SPID now.'
GO

PRINT 'Now at the create table section ....'
execute sp_dboption 'abts' ,'trunc. log on chkpt.' ,'true'
execute sp_dboption 'abts' ,'ANSI null default' ,'true'
GO

 -- ====== ABTS_ROWS10K

PRINT ' '          
PRINT 'Creating table ABTS_ROWS10K'
 
CREATE TABLE ABTS_ROWS10K (
   V1       FLOAT,
   V2       FLOAT,
   V3       FLOAT,
   V4       FLOAT,
   V5       FLOAT,
   V6       FLOAT,
   V7       FLOAT
)
GO 

CREATE PROCEDURE LOAD_ABTS_ROWS10K AS
DECLARE @i int
DECLARE @j int
DECLARE @cnt int
DECLARE @val int
  select @cnt = 0
  select @j = 0
  while ( @j <= 9 )
    begin
      select @i = 1
      while ( @i <= 1000 )
        begin
          select @val = @i + @cnt
          INSERT INTO ABTS_ROWS10K VALUES (@val,@val,@val,@val,@val,@val,@val)
          select @i = @i + 1 
        end
      select @cnt = @cnt + 1000
      select @j = @j + 1
    end
GO

EXECUTE LOAD_ABTS_ROWS10K
GO
 
DROP PROCEDURE LOAD_ABTS_ROWS10K
GO 

PRINT ' '
PRINT 'Step 3 Done - ABTS_ROWS10K created'
