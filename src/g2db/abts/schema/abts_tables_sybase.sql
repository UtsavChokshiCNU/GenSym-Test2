 -- clear
PRINT '====================================================================='
PRINT '   ABTS DATABASE TABLES AND TEST DATA FOR Sybase Server              '
PRINT '====================================================================='
set nocount    on
set dateformat mdy

USE master
GO

if exists (select * from master.dbo.sysdatabases where name='abts')
  DROP database abts
GO

CHECKPOINT
GO

CREATE DATABASE abts ON abts = 15 log on abtslog = 15
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
USE master
GO
execute sp_dboption 'abts' ,'trunc. log on chkpt.' ,'true'
execute sp_dboption 'abts','allow nulls by default','true'
GO

USE abts
GO

CHECKPOINT
GO

 -- ====== ABTS_EMP
PRINT ' '
PRINT 'Creating table abts_emp'
 
CREATE TABLE abts_emp (
    empno       integer,                          
    ename       varchar(10),
    job         varchar(9),
    mgr         integer,
    hiredate    datetime,
    sal         decimal(7,2),
    comm        decimal(7,2) null,
    deptno      integer )
GO

PRINT 'Inserting sample data into table abts_emp'    
INSERT INTO abts_emp VALUES
    (7369,'SMITH','CLERK',7902,'12/17/80',1200,800,20) 
INSERT INTO abts_emp VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2/20/1981',1600,300,30) 
INSERT INTO abts_emp VALUES 
    (7521,'WARD','SALESMAN',7698,'2/22/81',1250,500,30) 
INSERT INTO abts_emp VALUES
    (7566,'JONES','MANAGER',7839,'4/02/81',2975,NULL,20) 
INSERT INTO abts_emp VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO abts_emp VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO abts_emp VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO abts_emp VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO abts_emp VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO abts_emp VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO abts_emp VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO abts_emp VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO abts_emp VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO abts_emp VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10)
GO 

 -- ====== ABTS_EMP2

PRINT ' '
PRINT 'Creating table abts_emp2'

CREATE TABLE abts_emp2 (
    empno       integer,                          
    ename       varchar(10),
    job         varchar(9),
    mgr         integer,
    hiredate    datetime,
    sal         decimal(7,2),
    comm        decimal(7,2) null,
    deptno      smallint )
GO 

PRINT ' '
PRINT 'Inserting sample data into table abts_emp2'    
INSERT INTO abts_emp2 VALUES
    (9369,'JONES','MANAGER',9902,'1-12-90',11200,1800,30) 
INSERT INTO abts_emp2 VALUES 
    (9499,'BABCOCK','CLERK',9698,'3-21-91',21600,1300,10) 
INSERT INTO abts_emp2 VALUES 
    (9521,'SMITH','CLERK',9698,'1-15-91',91250,2500,10) 
INSERT INTO abts_emp2 VALUES
    (9566,'ABERCROMBY','MANAGER',9839,'5-12-91',92975,800,30) 
INSERT INTO abts_emp2 VALUES
    (9654,'HEMATOMA','CLERK',9698,'2-18-91',61250,NULL,40) 
INSERT INTO abts_emp2 VALUES
    (9698,'SPAZBOY','MANAGER',9839,'6-13-91',72850,NULL,20) 
INSERT INTO abts_emp2 VALUES
    (9782,'STUDLY','MANAGER',9839,'7-02-91',42450,150,10) 
INSERT INTO abts_emp2 VALUES
    (9788,'BRIDGEBOY','VICE-PRESIDENT',9566,'1-01-83',33000,NULL,10) 
INSERT INTO abts_emp2 VALUES
    (9839,'GENSYM','ANALYST',9999,'3-19-91',45000,1000,20) 
INSERT INTO abts_emp2 VALUES
    (9844,'HOTSHOT','CLERK',9698,'4-03-91',41500,0,20) 
INSERT INTO abts_emp2 VALUES
    (9876,'HUBUB','MANAGER',9788,'5-23-73',31100,NULL,30) 
INSERT INTO abts_emp2 VALUES
    (9900,'SPANKY','MANAGER',9698,'6-23-71',22950,2200,30) 
INSERT INTO abts_emp2 VALUES
    (9902,'BUTCHY','VICE-PRESIDENT',9566,'7-23-71',23000,NULL,30) 
INSERT INTO abts_emp2 VALUES
    (9934,'MY GAL SAL','MANAGER',9782,'8-11-93',31300,150,40)
GO 

 -- ====== ABTS_BIG_TABLE

PRINT ' '          
PRINT 'Creating table abts_many_columns'
 
CREATE TABLE abts_many_columns (
    c1          decimal,
    c2          decimal,
    c3          decimal,
    c4          decimal,
    c5          decimal,
    c6          decimal,
    c7          decimal,
    c8          decimal,
    c9          decimal,
    c10         decimal,
    c11         decimal,
    c12         decimal,
    c13         decimal,
    c14         decimal,
    c15         decimal,
    c16         decimal,
    c17         decimal,
    c18         decimal,
    c19         decimal,
    c20         decimal,
    c21         decimal,
    c22         decimal,
    c23         decimal,
    c24         decimal,
    c25         decimal,
    c26         decimal,
    c27         decimal,
    c28         decimal,
    c29         decimal,
    c30         decimal,
    c31         decimal,
    c32         decimal,
    c33         decimal,
    c34         decimal,
    c35         decimal,
    c36         decimal,
    c37         decimal,
    c38         decimal,
    c39         decimal,
    c40         decimal,
    c41         decimal,
    c42         decimal,
    c43         decimal,
    c44         decimal,
    c45         decimal,
    c46         decimal,
    c47         decimal,
    c48         decimal,
    c49         decimal,
    c50         decimal,
    c51         decimal,
    c52         decimal,
    c53         decimal,
    c54         decimal,
    c55         decimal,
    c56         decimal,
    c57         decimal,
    c58         decimal,
    c59         decimal,
    c60         decimal,
    c61         decimal,
    c62         decimal,
    c63         decimal,
    c64         decimal,
    c65         decimal,
    c66         decimal,
    c67         decimal,
    c68         decimal,
    c69         decimal,
    c70         decimal,
    c71         decimal,
    c72         decimal,
    c73         decimal,
    c74         decimal,
    c75         decimal,
    c76         decimal,
    c77         decimal,
    c78         decimal,
    c79         decimal,
    c80         decimal,
    c81         decimal,
    c82         decimal,
    c83         decimal,
    c84         decimal,
    c85         decimal,
    c86         decimal,
    c87         decimal,
    c88         decimal,
    c89         decimal,
    c90         decimal,
    c91         decimal,
    c92         decimal,
    c93         decimal,
    c94         decimal,
    c95         decimal,
    c96         decimal,
    c97         decimal,
    c98         decimal,
    c99         decimal,
    c100        decimal )
GO 

 -- ====== ABTS_DATATYPES

PRINT ' '          
PRINT 'Create table 
S'

CREATE TABLE abts_datatypes
  (dch             char(20),
   dvc             varchar(20),
   dln             decimal(10),
   ddbl            decimal(15,3),
   ddate           datetime )
GO
 
PRINT ' '          
PRINT 'Inserting sample data into table abts_datatypes'    
INSERT INTO abts_datatypes VALUES ('1234567','1234567',1234567,1234567.123, 
    '4-01-96 12:34:56') 

INSERT INTO abts_datatypes VALUES ('-1234567','-1234567',-1234567,-1234567.123, 
    '4-01-96 12:34:56')
GO 


 -- ====== ABTS_TOOBIG_DATA

PRINT ' '          
PRINT 'Create table abts_toobig_data'
 
CREATE TABLE abts_toobig_data
  (tbi             decimal(28),
   tbf             decimal )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table abts_toobig_data'    
INSERT INTO abts_toobig_data VALUES (536870911,536870911) 
INSERT INTO abts_toobig_data VALUES (536870912,536870912)
GO 

 -- ====== ABTS_FUNCTION_DATA

PRINT ' '          
PRINT 'Create table abts_function_data'
 
CREATE TABLE abts_function_data
  (fename          varchar(10),
   fsal            decimal(7,2),
   fdate           datetime )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table abts_function_data'
INSERT INTO abts_function_data VALUES
    ('SMITH',1200,'12-17-80') 
INSERT INTO abts_function_data VALUES
    ('ALLEN',1600,'2-20-81')
GO 

 -- ====== ABTS_EMPTY_TABLE

PRINT ' '          
PRINT 'Create table abts_empty_table'
  
CREATE TABLE abts_empty_table
  (ename           varchar(10),
   sal             decimal(7,2),
   dept            integer,
   state           char(2),
   hiredate        datetime ) 
GO

 -- ====== abts_personnel

PRINT ' '          
PRINT 'Create table abts_personnel'

CREATE TABLE abts_personnel (
   last_name       varchar(14),
   first_name      char(10) not null,
   mid_init        char(1)  null,
   city            char(20) not null,
   state           char(2)  not null,
   zip             char(6)  not null,   
   sex             char(1)  not null)
GO 

PRINT ' '          
PRINT 'Inserting sample data into table abts_personnel'    
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
GO

INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
GO

INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
GO

INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
GO

INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
GO

INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Toliver','Alvin','A','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Terry','D','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F') 
INSERT INTO abts_personnel VALUES
    ('Nash','Norman',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Gray','Susan','O','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F') 
INSERT INTO abts_personnel VALUES
    ('Peters','Janis','K','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Dean','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Daniel','V','Bennington','MA','03442','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','George',NULL,'Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Hastings','Norman','M','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Dallas','Meg',NULL,'Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Canonica','Rick','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Reynolds','Louis','E','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Iacobone','Eloi','N','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Nash','Walter','V','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Frydman','Louie','T','Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Stadecker','Hope','E','Alton','NH','03809','F') 
INSERT INTO abts_personnel VALUES
    ('Watters','Cora',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Stan','P','Acworth','NH','03601','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Karen','G','Jefferson','NH','03583','F') 
INSERT INTO abts_personnel VALUES
    ('Lengyel','Peter','A','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('OSullivan','Rick','G','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Reitchel','Charles','N','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Emery','Daniel','P','Wilmot','NH','03287','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Nunez','Larry','B','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ziemke','Al','F','Winnisquam','NH','03289','M') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F') 
INSERT INTO abts_personnel VALUES
    ('Harrington','Margaret','V','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Gaudet','Johanna','I','Fremont','NH','03044','F') 
INSERT INTO abts_personnel VALUES
    ('Myotte','Charles','K','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','Marty','J','Jefferson','NH','03583','M') 
INSERT INTO abts_personnel VALUES
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M') 
INSERT INTO abts_personnel VALUES
    ('Sciacca','Joe','V','Munsonville','NH','03457','M') 
INSERT INTO abts_personnel VALUES
    ('Smith','Roger','R','Bristol','NH','03222','M') 
INSERT INTO abts_personnel VALUES
    ('Dietrich','Alan','J','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M') 
INSERT INTO abts_personnel VALUES
    ('Clarke','Roy','C','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Mercier','Len','F','Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Siciliano','James','X','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('Villari','Christine',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Gehr','Janis',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Sullivan','Len','R','Sandown','NH','03873','M') 
INSERT INTO abts_personnel VALUES
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Foote','Rick','B','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Manning','Kevin','G','Troy','NH','03465','M') 
INSERT INTO abts_personnel VALUES
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F') 
GO

INSERT INTO abts_personnel VALUES
    ('Boyd','James','Q','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F') 
INSERT INTO abts_personnel VALUES
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Tom','A','Fremont','NH','03044','M') 
INSERT INTO abts_personnel VALUES
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M') 
INSERT INTO abts_personnel VALUES
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F') 
INSERT INTO abts_personnel VALUES
    ('Mathias','Susan','N','Milan','NH','03588','F') 
INSERT INTO abts_personnel VALUES
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F') 
INSERT INTO abts_personnel VALUES
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Gramby','Ruth','N','Etna','NH','03750','F') 
INSERT INTO abts_personnel VALUES
    ('Burton','Frederick','Z','Penacook','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Johnson','Bill','R','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M') 
INSERT INTO abts_personnel VALUES
    ('Vormelker','Daniel','F','Rochester','NH','03867','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Larry','T','Etna','NH','03750','M') 
INSERT INTO abts_personnel VALUES
    ('Boyd','Ann','B','Acworth','NH','03601','F') 
INSERT INTO abts_personnel VALUES
    ('Roberts','Norman','U','Chocorua','NH','03817','M') 
INSERT INTO abts_personnel VALUES
    ('Lonergan','Peter','V','Meadows','NH','03587','M') 
INSERT INTO abts_personnel VALUES
    ('Ulrich','Christine','L','Whitefield','NH','03598','F') 
INSERT INTO abts_personnel VALUES
    ('Klein','Franklin','Q','Milford','NH','03055','M') 
INSERT INTO abts_personnel VALUES
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M') 
INSERT INTO abts_personnel VALUES
    ('Watters','Christine','D','Colebrook','NH','03576','F') 
INSERT INTO abts_personnel VALUES
    ('Brown','Nancy',NULL,'Milton','NH','03851','F') 
INSERT INTO abts_personnel VALUES
    ('Silver','Glenn','S','Colebrook','NH','03576','M') 
INSERT INTO abts_personnel VALUES
    ('Stornelli','James','S','Whitefield','NH','03598','M') 
INSERT INTO abts_personnel VALUES
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F') 
INSERT INTO abts_personnel VALUES
    ('Crain','Jesse',NULL,'Milan','NH','03588','M') 
INSERT INTO abts_personnel VALUES
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F') 
INSERT INTO abts_personnel VALUES
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M') 
INSERT INTO abts_personnel VALUES
    ('Dement','Alvin','B','Sanbornton','NH','03269','M') 
INSERT INTO abts_personnel VALUES
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F') 
INSERT INTO abts_personnel VALUES
    ('Ames','Louie','A','Alton','NH','03809','M') 
INSERT INTO abts_personnel VALUES
    ('Blount','Peter',NULL,'Alstead','NH','03602','M') 
INSERT INTO abts_personnel VALUES
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F') 
INSERT INTO abts_personnel VALUES
    ('Herbener','James','Q','Penacook','NH','03301','M')
GO 

 -- ====== ABTS_UNSUPPORTED_DTYPES

PRINT ' '          
PRINT 'Creating table abts_unsup_dtypes'
 
CREATE TABLE abts_unsup_dtypes (
    d_image       image,
    d_text        text,
    d_binary      binary(5) )
GO 

 -- ====== ABTS_TEXT

PRINT ' '          
PRINT 'Creating table abts_text'
 
CREATE TABLE abts_text (
    ename       varchar(10),
    job         varchar(9),
    hiredate    datetime,
    sex         char(2) null )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table abts_text'    
INSERT INTO abts_text VALUES
    ('SMITH','CLERK','12-17-80','M') 
INSERT INTO abts_text VALUES 
    ('ALLEN','SALESMAN','2-20-81','M') 
INSERT INTO abts_text VALUES 
    ('WARD','SALESMAN','2-22-81','F') 
INSERT INTO abts_text VALUES
    ('JONES','MANAGER','4-02-81','M') 
INSERT INTO abts_text VALUES
    ('MARTIN','SALESMAN','9-28-81',NULL) 
INSERT INTO abts_text VALUES
    ('BLAKE','MANAGER','5-01-81','F') 
INSERT INTO abts_text VALUES
    ('CLARK','MANAGER','6-09-81','M')
GO 

 -- ====== ABTS_FLOAT

PRINT ' '          
PRINT 'Creating table abts_float'
 
CREATE TABLE abts_float (
    sal         decimal(8,3),
    comm        decimal (10,4) ) 
GO

PRINT ' '          
PRINT 'Inserting sample data into table abts_float'
INSERT INTO abts_float VALUES (7.5,-333.34) 
INSERT INTO abts_float VALUES (-7.5,333.34) 
INSERT INTO abts_float VALUES (7.545,38383.33) 
INSERT INTO abts_float VALUES (555.667,-333333) 
INSERT INTO abts_float VALUES (3838.33,-383888.3) 
INSERT INTO abts_float VALUES (999.4,333.33) 
INSERT INTO abts_float VALUES (-99875.43,-333.3555)
GO 
              
 -- ====== ABTS_INT

PRINT ' '          
PRINT 'Creating table abts_int'
 
CREATE TABLE abts_int (
    empno         int,
    deptno        int ) 
GO

PRINT ' '          
PRINT 'Inserting sample data into table abts_int'
INSERT INTO abts_int VALUES (7,-333) 
INSERT INTO abts_int VALUES (-7,333) 
INSERT INTO abts_int VALUES (7,38383) 
INSERT INTO abts_int VALUES (555,-333333) 
INSERT INTO abts_int VALUES (3838,-383888) 
INSERT INTO abts_int VALUES (999,333) 
INSERT INTO abts_int VALUES (-99875,-9933555)
GO 
              

 -- ====== ABTS_EMP_X2

PRINT ' '          
PRINT 'Creating table abts_emp_x2'
 
CREATE TABLE abts_emp_x2 (
    empno       integer,                          
    ename       varchar(10),
    job         varchar(9),
    mgr         integer,
    hiredate    datetime,
    sal         decimal(7,2),
    comm        decimal(7,2) null,
    deptno      smallint )
GO 

PRINT ' '          
PRINT 'Inserting sample data into table abts_emp_x2'
INSERT INTO abts_emp_x2 VALUES
    (7369,'SMITH','CLERK',7902,'12-17-80',1200,800,20) 
INSERT INTO abts_emp_x2 VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2-20-81',1600,300,30) 
INSERT INTO abts_emp_x2 VALUES 
    (7521,'WARD','SALESMAN',7698,'2-22-81',1250,500,30) 
INSERT INTO abts_emp_x2 VALUES
    (7566,'JONES','MANAGER',7839,'4-02-81',2975,NULL,20) 
INSERT INTO abts_emp_x2 VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO abts_emp_x2 VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO abts_emp_x2 VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO abts_emp_x2 VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO abts_emp_x2 VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO abts_emp_x2 VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO abts_emp_x2 VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO abts_emp_x2 VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO abts_emp_x2 VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO abts_emp_x2 VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10) 
INSERT INTO abts_emp_x2 VALUES
    (7369,'SMITH','CLERK',7902,'12-17-80',1200,800,20) 
INSERT INTO abts_emp_x2 VALUES 
    (7499,'ALLEN','SALESMAN',7698,'2-20-81',1600,300,30) 
INSERT INTO abts_emp_x2 VALUES 
    (7521,'WARD','SALESMAN',7698,'2-22-81',1250,500,30) 
INSERT INTO abts_emp_x2 VALUES
    (7566,'JONES','MANAGER',7839,'4-02-81',2975,NULL,20) 
INSERT INTO abts_emp_x2 VALUES
    (7654,'MARTIN','SALESMAN',7698,'9-28-81',1250,1400,30) 
INSERT INTO abts_emp_x2 VALUES
    (7698,'BLAKE','MANAGER',7839,'5-01-81',2850,NULL,30) 
INSERT INTO abts_emp_x2 VALUES
    (7782,'CLARK','MANAGER',7839,'6-09-81',2450,10,10) 
INSERT INTO abts_emp_x2 VALUES
    (7788,'SCOTT','ANALYST',7566,'8-10-93',3000,20,20) 
INSERT INTO abts_emp_x2 VALUES
    (7839,'KING','PRESIDENT',7999,'11-17-81',5000,1000,10) 
INSERT INTO abts_emp_x2 VALUES
    (7844,'TURNER','SALESMAN',7698,'9-08-81',1500,0,30) 
INSERT INTO abts_emp_x2 VALUES
    (7876,'ADAMS','CLERK',7788,'9-13-93',1100,500,20) 
INSERT INTO abts_emp_x2 VALUES
    (7900,'JAMES','CLERK',7698,'12-03-81',950,200,30) 
INSERT INTO abts_emp_x2 VALUES
    (7902,'FORD','ANALYST',7566,'12-03-81',3000,NULL,20) 
INSERT INTO abts_emp_x2 VALUES
    (7934,'MILLER','CLERK',7782,'1-23-83',1300,50,10)
GO 

 -- ====== ABTS_ROWS10K

PRINT ' '          
PRINT 'Creating table abts_rows10k'
 
CREATE TABLE abts_rows10k (
   v1       decimal,
   v2       decimal,
   v3       decimal,
   v4       decimal,
   v5       decimal,
   v6       decimal,
   v7       decimal
)
GO 

CREATE PROCEDURE load_abts_rows10k AS
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
          INSERT INTO abts_rows10k VALUES (@val,@val,@val,@val,@val,@val,@val)
          select @i = @i + 1 
        end
      select @cnt = @cnt + 1000
      select @j = @j + 1
    end
GO

EXECUTE load_abts_rows10k
GO
 
DROP PROCEDURE load_abts_rows10k
GO 


 -- ====== ABTS_SCRATCH

PRINT ' '          
PRINT 'Creating table abts_scratch'
 
CREATE TABLE abts_scratch (
    empno       integer,                          
    ename       varchar(10),
    job         varchar(9),
    mgr         integer,
    hiredate    datetime,
    sal         decimal(7,2),
    comm        decimal(7,2),
    deptno      smallint ) 
GO

 -- =========================================
 --    STORED PROCEDURES
 -- =========================================


 -- ====== ABTS_ADD_NAME
 
CREATE PROCEDURE abts_add_name @input_name VARCHAR(30)
  AS
  insert into abts_scratch(ename) values (@input_name) 

GO
 
GRANT execute ON abts_add_name TO public
GO

 -- =========================================
 --    TRIGGERS
 -- =========================================


 -- ====== ABTS_TRIGGER_TABLE

PRINT ' '
PRINT 'Creating table abts_trigger_table'
 
CREATE TABLE abts_trigger_table (
    message       varchar(128))
GO 

 -- ====== ABTS_TRIG_TEST1

CREATE TRIGGER abts_trig_test1 ON abts_trigger_table
FOR INSERT, UPDATE
AS
  EXECUTE g2_insert_trig_proc 'ABTS_TRIG_PIPE1', 'Trigger Alert INSERT'
GO 

PRINT ' '
PRINT 'Granting Permissions'

grant all on abts_emp to public
grant all on abts_emp2 to public
grant all on abts_many_columns to public
grant all on abts_datatypes to public
grant all on abts_toobig_data to public
grant all on abts_function_data to public
grant all on abts_empty_table to public
grant all on abts_personnel to public
grant all on abts_unsup_dtypes to public
grant all on abts_text to public
grant all on abts_float to public
grant all on abts_int to public
grant all on abts_emp_x2 to public
grant all on abts_rows10k to public
grant all on abts_scratch to public
grant all on abts_trigger_table to public
go

grant create table to public
grant create view to public
grant create rule to public
grant create default to public
grant create procedure to public
go

update statistics abts_emp 
update statistics abts_emp2 
update statistics abts_many_columns 
update statistics abts_datatypes 
update statistics abts_toobig_data 
update statistics abts_function_data 
update statistics abts_empty_table 
update statistics abts_personnel 
update statistics abts_unsup_dtypes 
update statistics abts_text 
update statistics abts_float 
update statistics abts_int 
update statistics abts_emp_x2 
update statistics abts_rows10k 
update statistics abts_scratch 
update statistics abts_trigger_table 
go
PRINT ' '
PRINT 'All Done!'
