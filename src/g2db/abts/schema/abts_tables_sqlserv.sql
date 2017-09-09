 -- clear
PRINT '====================================================================='
PRINT '   ABTS DATABASE TABLES AND TEST DATA FOR Microsoft SQL Server'
PRINT '====================================================================='
set nocount    on
set dateformat mdy

USE master
GO

if exists (select * from sysdatabases where name='abts')
  DROP database abts
GO

CHECKPOINT
GO

CREATE DATABASE abts
   on master = 5
GO

CHECKPOINT
GO

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

 -- ====== ABTS_EMP
PRINT ' '
PRINT 'Creating table ABTS_EMP'
 
CREATE TABLE ABTS_EMP (
    EMPNO       INTEGER,                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         INTEGER,
    HIREDATE    DATETIME,
    SAL         DECIMAL(10,2),
    COMM        DECIMAL(7,2) NULL,
    DEPTNO      INTEGER )
GO

PRINT 'Inserting sample data into table ABTS_EMP'    
INSERT INTO ABTS_EMP VALUES
    (7369,'SMITH','CLERK',7902,'12/17/80',1200,800,20) 
INSERT INTO ABTS_EMP VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2/20/1981',1600,300,30) 
INSERT INTO ABTS_EMP VALUES 
    (7521,'WARD','SALESMAN',7698,'2/22/81',1250,500,30) 
INSERT INTO ABTS_EMP VALUES
    (7566,'JONES','MANAGER',7839,'4/02/81',2975,NULL,20) 
INSERT INTO ABTS_EMP VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO ABTS_EMP VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO ABTS_EMP VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO ABTS_EMP VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO ABTS_EMP VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO ABTS_EMP VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO ABTS_EMP VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO ABTS_EMP VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO ABTS_EMP VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO ABTS_EMP VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10)
GO 

 -- ====== ABTS_EMP2

PRINT ' '
PRINT 'Creating table ABTS_EMP2'

CREATE TABLE ABTS_EMP2 (
    EMPNO       INTEGER,                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         INTEGER,
    HIREDATE    DATETIME,
    SAL         DECIMAL(10,2),
    COMM        DECIMAL(7,2) NULL,
    DEPTNO      SMALLINT )
GO 

PRINT ' '
PRINT 'Inserting sample data into table ABTS_EMP2'    
INSERT INTO ABTS_EMP2 VALUES
    (9369,'JONES','MANAGER',9902,'1-12-90',11200,1800,30) 
INSERT INTO ABTS_EMP2 VALUES 
    (9499,'BABCOCK','CLERK',9698,'3-21-91',21600,1300,10) 
INSERT INTO ABTS_EMP2 VALUES 
    (9521,'SMITH','CLERK',9698,'1-15-91',91250,2500,10) 
INSERT INTO ABTS_EMP2 VALUES
    (9566,'ABERCROMBY','MANAGER',9839,'5-12-91',92975,800,30) 
INSERT INTO ABTS_EMP2 VALUES
    (9654,'HEMATOMA','CLERK',9698,'2-18-91',61250,NULL,40) 
INSERT INTO ABTS_EMP2 VALUES
    (9698,'SPAZBOY','MANAGER',9839,'6-13-91',72850,NULL,20) 
INSERT INTO ABTS_EMP2 VALUES
    (9782,'STUDLY','MANAGER',9839,'7-02-91',42450,150,10) 
INSERT INTO ABTS_EMP2 VALUES
    (9788,'BRIDGEBOY','VICE-PRESIDENT',9566,'1-01-83',33000,NULL,10) 
INSERT INTO ABTS_EMP2 VALUES
    (9839,'GENSYM','ANALYST',9999,'3-19-91',45000,1000,20) 
INSERT INTO ABTS_EMP2 VALUES
    (9844,'HOTSHOT','CLERK',9698,'4-03-91',41500,0,20) 
INSERT INTO ABTS_EMP2 VALUES
    (9876,'HUBUB','MANAGER',9788,'5-23-73',31100,NULL,30) 
INSERT INTO ABTS_EMP2 VALUES
    (9900,'SPANKY','MANAGER',9698,'6-23-71',22950,2200,30) 
INSERT INTO ABTS_EMP2 VALUES
    (9902,'BUTCHY','VICE-PRESIDENT',9566,'7-23-71',23000,NULL,30) 
INSERT INTO ABTS_EMP2 VALUES
    (9934,'MY GAL SAL','MANAGER',9782,'8-11-93',31300,150,40)
GO 

 -- ====== ABTS_BIG_TABLE

PRINT ' '          
PRINT 'Creating table ABTS_MANY_COLUMNS'
 
CREATE TABLE ABTS_MANY_COLUMNS (
    C1          DECIMAL,
    C2          DECIMAL,
    C3          DECIMAL,
    C4          DECIMAL,
    C5          DECIMAL,
    C6          DECIMAL,
    C7          DECIMAL,
    C8          DECIMAL,
    C9          DECIMAL,
    C10         DECIMAL,
    C11         DECIMAL,
    C12         DECIMAL,
    C13         DECIMAL,
    C14         DECIMAL,
    C15         DECIMAL,
    C16         DECIMAL,
    C17         DECIMAL,
    C18         DECIMAL,
    C19         DECIMAL,
    C20         DECIMAL,
    C21         DECIMAL,
    C22         DECIMAL,
    C23         DECIMAL,
    C24         DECIMAL,
    C25         DECIMAL,
    C26         DECIMAL,
    C27         DECIMAL,
    C28         DECIMAL,
    C29         DECIMAL,
    C30         DECIMAL,
    C31         DECIMAL,
    C32         DECIMAL,
    C33         DECIMAL,
    C34         DECIMAL,
    C35         DECIMAL,
    C36         DECIMAL,
    C37         DECIMAL,
    C38         DECIMAL,
    C39         DECIMAL,
    C40         DECIMAL,
    C41         DECIMAL,
    C42         DECIMAL,
    C43         DECIMAL,
    C44         DECIMAL,
    C45         DECIMAL,
    C46         DECIMAL,
    C47         DECIMAL,
    C48         DECIMAL,
    C49         DECIMAL,
    C50         DECIMAL,
    C51         DECIMAL,
    C52         DECIMAL,
    C53         DECIMAL,
    C54         DECIMAL,
    C55         DECIMAL,
    C56         DECIMAL,
    C57         DECIMAL,
    C58         DECIMAL,
    C59         DECIMAL,
    C60         DECIMAL,
    C61         DECIMAL,
    C62         DECIMAL,
    C63         DECIMAL,
    C64         DECIMAL,
    C65         DECIMAL,
    C66         DECIMAL,
    C67         DECIMAL,
    C68         DECIMAL,
    C69         DECIMAL,
    C70         DECIMAL,
    C71         DECIMAL,
    C72         DECIMAL,
    C73         DECIMAL,
    C74         DECIMAL,
    C75         DECIMAL,
    C76         DECIMAL,
    C77         DECIMAL,
    C78         DECIMAL,
    C79         DECIMAL,
    C80         DECIMAL,
    C81         DECIMAL,
    C82         DECIMAL,
    C83         DECIMAL,
    C84         DECIMAL,
    C85         DECIMAL,
    C86         DECIMAL,
    C87         DECIMAL,
    C88         DECIMAL,
    C89         DECIMAL,
    C90         DECIMAL,
    C91         DECIMAL,
    C92         DECIMAL,
    C93         DECIMAL,
    C94         DECIMAL,
    C95         DECIMAL,
    C96         DECIMAL,
    C97         DECIMAL,
    C98         DECIMAL,
    C99         DECIMAL,
    C100        DECIMAL )
GO 

 -- ====== ABTS_DATATYPES

PRINT ' '          
PRINT 'Create table ABTS_DATATYPES'

CREATE TABLE ABTS_DATATYPES
  (DCH             CHAR(20),
   DVC             VARCHAR(20),
   DLN             DECIMAL(10),
   DDBL            DECIMAL,
   DDATE           DATETIME )
GO
 
PRINT ' '          
PRINT 'Inserting sample data into table ABTS_DATATYPES'    
INSERT INTO ABTS_DATATYPES VALUES ('1234567','1234567',1234567,1234567.123, 
    '4-01-96 12:34:56') 

INSERT INTO ABTS_DATATYPES VALUES ('-1234567','-1234567',-1234567,-1234567.123, 
    '4-01-96 12:34:56')
GO 


 -- ====== ABTS_TOOBIG_DATA

PRINT ' '          
PRINT 'Create table ABTS_TOOBIG_DATA'
 
CREATE TABLE ABTS_TOOBIG_DATA
  (TBI             DECIMAL(28),
   TBF             DECIMAL )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_TOOBIG_DATA'    
INSERT INTO ABTS_TOOBIG_DATA VALUES (536870911,536870911) 
INSERT INTO ABTS_TOOBIG_DATA VALUES (536870912,536870912)
GO 

 -- ====== ABTS_FUNCTION_DATA

PRINT ' '          
PRINT 'Create table ABTS_FUNCTION_DATA'
 
CREATE TABLE ABTS_FUNCTION_DATA
  (FENAME          VARCHAR(10),
   FSAL            DECIMAL(10,2),
   FDATE           DATETIME )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_FUNCTION_DATA'
INSERT INTO ABTS_FUNCTION_DATA VALUES
    ('SMITH',1200,'12-17-80') 
INSERT INTO ABTS_FUNCTION_DATA VALUES
    ('ALLEN',1600,'2-20-81')
GO 

 -- ====== ABTS_EMPTY_TABLE

PRINT ' '          
PRINT 'Create table ABTS_EMPTY_TABLE'
  
CREATE TABLE ABTS_EMPTY_TABLE
  (ENAME           VARCHAR(10),
   SAL             DECIMAL(10,2),
   DEPT            INTEGER,
   STATE           CHAR(2),
   HIREDATE        DATETIME ) 
GO

 -- ====== ABTS_PERSONNEL

PRINT ' '          
PRINT 'Create table ABTS_PERSONNEL'

CREATE TABLE ABTS_PERSONNEL (
   LAST_NAME       VARCHAR(14),
   FIRST_NAME      CHAR(10),
   MID_INIT        CHAR(1) NULL,
   CITY            CHAR(20),
   STATE           CHAR(2),
   ZIP             CHAR(6),   
   SEX             CHAR(1) )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_PERSONNEL'    
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO ABTS_PERSONNEL VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M')
GO 

 -- ====== ABTS_UNSUPPORTED_DTYPES

PRINT ' '          
PRINT 'Creating table ABTS_UNSUP_DTYPES'
 
CREATE TABLE ABTS_UNSUP_DTYPES (
    D_IMAGE       IMAGE,
    D_TEXT        TEXT,
    D_BINARY      BINARY(5) )
GO 

 -- ====== ABTS_TEXT

PRINT ' '          
PRINT 'Creating table ABTS_TEXT'
 
CREATE TABLE ABTS_TEXT (
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    HIREDATE    DATETIME,
    SEX         CHAR(1) NULL )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_TEXT'    
INSERT INTO ABTS_TEXT VALUES
    ('SMITH','CLERK','12-17-80','M') 
INSERT INTO ABTS_TEXT VALUES 
    ('ALLEN','SALESMAN','2-20-81','M') 
INSERT INTO ABTS_TEXT VALUES 
    ('WARD','SALESMAN','2-22-81','F') 
INSERT INTO ABTS_TEXT VALUES
    ('JONES','MANAGER','4-02-81','M') 
INSERT INTO ABTS_TEXT VALUES
    ('MARTIN','SALESMAN','9-28-81',NULL) 
INSERT INTO ABTS_TEXT VALUES
    ('BLAKE','MANAGER','5-01-81','F') 
INSERT INTO ABTS_TEXT VALUES
    ('CLARK','MANAGER','6-09-81','M')
GO 

 -- ====== ABTS_FLOAT

PRINT ' '          
PRINT 'Creating table ABTS_FLOAT'
 
CREATE TABLE ABTS_FLOAT (
    SAL         DECIMAL(10,2),
    COMM        DECIMAL(10,4) ) 
GO

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_FLOAT'
INSERT INTO ABTS_FLOAT VALUES (7.5,-333.34) 
INSERT INTO ABTS_FLOAT VALUES (-7.5,333.34) 
INSERT INTO ABTS_FLOAT VALUES (7.545,38383.33) 
INSERT INTO ABTS_FLOAT VALUES (555.667,-333333) 
INSERT INTO ABTS_FLOAT VALUES (3838.33,-383888.3) 
INSERT INTO ABTS_FLOAT VALUES (999.4,333.33) 
INSERT INTO ABTS_FLOAT VALUES (-99875.43,-333.3555)
GO 
              
 -- ====== ABTS_INT

PRINT ' '          
PRINT 'Creating table ABTS_INT'
 
CREATE TABLE ABTS_INT (
    EMPNO         DECIMAL(7),
    DEPTNO        INT ) 
GO

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_INT'
INSERT INTO ABTS_INT VALUES (7,-333) 
INSERT INTO ABTS_INT VALUES (-7,333) 
INSERT INTO ABTS_INT VALUES (7,38383) 
INSERT INTO ABTS_INT VALUES (555,-333333) 
INSERT INTO ABTS_INT VALUES (3838,-383888) 
INSERT INTO ABTS_INT VALUES (999,333) 
INSERT INTO ABTS_INT VALUES (-99875,-9933555)
GO 
              

 -- ====== ABTS_EMP_X2

PRINT ' '          
PRINT 'Creating table ABTS_EMP_X2'
 
CREATE TABLE ABTS_EMP_X2 (
    EMPNO       INTEGER,                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         INTEGER,
    HIREDATE    DATETIME,
    SAL         DECIMAL(10,2),
    COMM        DECIMAL(7,2) NULL,
    DEPTNO      SMALLINT )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table ABTS_EMP_X2'
INSERT INTO ABTS_EMP_X2 VALUES
    (7369,'SMITH','CLERK',7902,'12-17-80',1200,800,20) 
INSERT INTO ABTS_EMP_X2 VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2-20-81',1600,300,30) 
INSERT INTO ABTS_EMP_X2 VALUES 
    (7521,'WARD','SALESMAN',7698,'2-22-81',1250,500,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7566,'JONES','MANAGER',7839,'4-02-81',2975,NULL,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7369,'SMITH','CLERK',7902,'12-17-80',1200,800,20) 
INSERT INTO ABTS_EMP_X2 VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2-20-81',1600,300,30) 
INSERT INTO ABTS_EMP_X2 VALUES 
    (7521,'WARD','SALESMAN',7698,'2-22-81',1250,500,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7566,'JONES','MANAGER',7839,'4-02-81',2975,NULL,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO ABTS_EMP_X2 VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10)
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


 -- ====== ABTS_SCRATCH

PRINT ' '          
PRINT 'Creating table ABTS_SCRATCH'
 
CREATE TABLE ABTS_SCRATCH (
    EMPNO       INTEGER,                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         INTEGER,
    HIREDATE    DATETIME,
    SAL         DECIMAL(10,2),
    COMM        DECIMAL(10,4),
    DEPTNO      SMALLINT,
    MESSAGE     VARCHAR(128)
 ) 
GO

 -- =========================================
 --    STORED PROCEDURES
 -- =========================================


 -- ====== ABTS_ADD_NAME
 
CREATE PROCEDURE ABTS_ADD_NAME @input_name VARCHAR(30)
  AS
  insert into abts_scratch (ename) values (@input_name) 

GO
 
GRANT execute ON ABTS_ADD_NAME TO public
GO

 -- =========================================
 --    TRIGGERS
 -- =========================================


 -- ====== ABTS_TRIGGER_TABLE

PRINT ' '
PRINT 'Creating table ABTS_TRIGGER_TABLE'
 
CREATE TABLE ABTS_TRIGGER_TABLE (
    MESSAGE       VARCHAR(128))
GO 

 -- ====== ABTS_TRIG_TEST1

CREATE TRIGGER ABTS_TRIG_TEST1 ON ABTS_TRIGGER_TABLE
FOR INSERT, UPDATE
AS
  EXECUTE g2odbc_ins_trigs 'ABTS_TRIG_PIPE1', 'Trigger Alert INSERT'
GO 

PRINT ' '
PRINT 'Granting Permissions'

GRANT ALL ON ABTS_EMP TO PUBLIC
GRANT ALL ON ABTS_EMP2 TO PUBLIC
GRANT ALL ON ABTS_MANY_COLUMNS TO PUBLIC
GRANT ALL ON ABTS_DATATYPES TO PUBLIC
GRANT ALL ON ABTS_TOOBIG_DATA TO PUBLIC
GRANT ALL ON ABTS_FUNCTION_DATA TO PUBLIC
GRANT ALL ON ABTS_EMPTY_TABLE TO PUBLIC
GRANT ALL ON ABTS_PERSONNEL TO PUBLIC
GRANT ALL ON ABTS_UNSUP_DTYPES TO PUBLIC
GRANT ALL ON ABTS_TEXT TO PUBLIC
GRANT ALL ON ABTS_FLOAT TO PUBLIC
GRANT ALL ON ABTS_INT TO PUBLIC
GRANT ALL ON ABTS_EMP_X2 TO PUBLIC
GRANT ALL ON ABTS_ROWS10K TO PUBLIC
GRANT ALL ON ABTS_SCRATCH TO PUBLIC
GRANT ALL ON ABTS_TRIGGER_TABLE TO PUBLIC
GO

GRANT CREATE TABLE TO PUBLIC
GRANT CREATE VIEW TO PUBLIC
GRANT CREATE RULE TO PUBLIC
GRANT CREATE DEFAULT TO PUBLIC
GRANT CREATE PROCEDURE TO PUBLIC
GO

UPDATE STATISTICS ABTS_EMP 
UPDATE STATISTICS ABTS_EMP2 
UPDATE STATISTICS ABTS_MANY_COLUMNS 
UPDATE STATISTICS ABTS_DATATYPES 
UPDATE STATISTICS ABTS_TOOBIG_DATA 
UPDATE STATISTICS ABTS_FUNCTION_DATA 
UPDATE STATISTICS ABTS_EMPTY_TABLE 
UPDATE STATISTICS ABTS_PERSONNEL 
UPDATE STATISTICS ABTS_UNSUP_DTYPES 
UPDATE STATISTICS ABTS_TEXT 
UPDATE STATISTICS ABTS_FLOAT 
UPDATE STATISTICS ABTS_INT 
UPDATE STATISTICS ABTS_EMP_X2 
UPDATE STATISTICS ABTS_ROWS10K 
UPDATE STATISTICS ABTS_SCRATCH 
UPDATE STATISTICS ABTS_TRIGGER_TABLE 
GO
PRINT ' '
PRINT 'All Done!'
