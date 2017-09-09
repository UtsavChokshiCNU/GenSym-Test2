SET TERMOUT ON
SET FEEDBACK OFF

prompt =====================================================================
prompt     ABTS DATABASE TABLES AND TEST DATA FOR ORACLE
prompt =====================================================================

REM ====== ABTS_EMP

prompt Creating table ABTS_EMP
DROP TABLE ABTS_EMP;
CREATE TABLE ABTS_EMP (
    EMPNO       NUMBER(4),                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         NUMBER(4),
    HIREDATE    DATE,
    SAL         NUMBER(7,2),
    COMM        NUMBER(7,2),
    DEPTNO      NUMBER(2) );

prompt Inserting sample data into table ABTS_EMP    
INSERT INTO ABTS_EMP VALUES -
    (7369,'SMITH','CLERK',7902,to_date('17-DEC-1980','DD-MON-YYYY'),1200,800,20);
INSERT INTO ABTS_EMP VALUES - 
    (7499,'ALLEN','SALESMAN',7698,to_date('20-FEB-1981','DD-MON-YYYY'),1600,300,30);
INSERT INTO ABTS_EMP VALUES - 
    (7521,'WARD','SALESMAN',7698,to_date('22-FEB-1981','DD-MON-YYYY'),1250,500,30);
INSERT INTO ABTS_EMP VALUES
    (7566,'JONES','MANAGER',7839,to_date('02-APR-1981','DD-MON-YYYY'),2975,NULL,20);
INSERT INTO ABTS_EMP VALUES -
    (7654,'MARTIN','SALESMAN',7698,to_date('28-SEP-1981','DD-MON-YYYY'),1250,1400,30);
INSERT INTO ABTS_EMP VALUES -
    (7698,'BLAKE','MANAGER',7839,to_date('01-MAY-1981','DD-MON-YYYY'),2850,NULL,30);
INSERT INTO ABTS_EMP VALUES -
    (7782,'CLARK','MANAGER',7839,to_date('09-JUN-1981','DD-MON-YYYY'),2450,10,10);
INSERT INTO ABTS_EMP VALUES -
    (7788,'SCOTT','ANALYST',7566,to_date('10-AUG-1993','DD-MON-YYYY'),3000,20,20);
INSERT INTO ABTS_EMP VALUES -
    (7839,'KING','PRESIDENT',7999,to_date('17-NOV-1981','DD-MON-YYYY'),5000,1000,10);
INSERT INTO ABTS_EMP VALUES -
    (7844,'TURNER','SALESMAN',7698,to_date('08-SEP-1981','DD-MON-YYYY'),1500,0,30);
INSERT INTO ABTS_EMP VALUES -
    (7876,'ADAMS','CLERK',7788,to_date('13-SEP-1993','DD-MON-YYYY'),1100,500,20);
INSERT INTO ABTS_EMP VALUES -
    (7900,'JAMES','CLERK',7698,to_date('03-DEC-1981','DD-MON-YYYY'),950,200,30);
INSERT INTO ABTS_EMP VALUES -
    (7902,'FORD','ANALYST',7566,to_date('03-DEC-1981','DD-MON-YYYY'),3000,NULL,20);
INSERT INTO ABTS_EMP VALUES -
    (7934,'MILLER','CLERK',7782,to_date('23-JAN-1983','DD-MON-YYYY'),1300,50,10);
COMMIT;

REM ====== ABTS_EMP2

prompt Creating table ABTS_EMP2
DROP TABLE ABTS_EMP2;
CREATE TABLE ABTS_EMP2 (
    EMPNO       NUMBER(4),                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         NUMBER(4),
    HIREDATE    DATE,
    SAL         NUMBER(7,2),
    COMM        NUMBER(7,2),
    DEPTNO      NUMBER(2) );

prompt Inserting sample data into table ABTS_EMP2    
INSERT INTO ABTS_EMP2 VALUES -
    (9369,'JONES','MANAGER',9902,to_date('12-JAN-1990','DD-MON-YYYY'),11200,1800,30);
INSERT INTO ABTS_EMP2 VALUES - 
    (9499,'BABCOCK','CLERK',9698,to_date('21-MAR-1991','DD-MON-YYYY'),21600,1300,10);
INSERT INTO ABTS_EMP2 VALUES - 
    (9521,'SMITH','CLERK',9698,to_date('15-JAN-1991','DD-MON-YYYY'),91250,2500,10);
INSERT INTO ABTS_EMP2 VALUES
    (9566,'ABERCROMBY','MANAGER',9839,to_date('12-MAY-1991','DD-MON-YYYY'),92975,800,30);
INSERT INTO ABTS_EMP2 VALUES -
    (9654,'HEMATOMA','CLERK',9698,to_date('18-FEB-1991','DD-MON-YYYY'),61250,NULL,40);
INSERT INTO ABTS_EMP2 VALUES -
    (9698,'SPAZBOY','MANAGER',9839,to_date('13-JUN-1991','DD-MON-YYYY'),72850,NULL,20);
INSERT INTO ABTS_EMP2 VALUES -
    (9782,'STUDLY','MANAGER',9839,to_date('02-JUL-1991','DD-MON-YYYY'),42450,150,10);
INSERT INTO ABTS_EMP2 VALUES -
    (9788,'BRIDGEBOY','VICE-PRES',9566,to_date('01-JAN-1983','DD-MON-YYYY'),33000,NULL,10);
INSERT INTO ABTS_EMP2 VALUES -
    (9839,'GENSYM','ANALYST',9999,to_date('19-MAR-1991','DD-MON-YYYY'),45000,1000,20);
INSERT INTO ABTS_EMP2 VALUES -
    (9844,'HOTSHOT','CLERK',9698,to_date('03-APR-1991','DD-MON-YYYY'),41500,0,20);
INSERT INTO ABTS_EMP2 VALUES -
    (9876,'HUBUB','MANAGER',9788,to_date('23-MAY-1973','DD-MON-YYYY'),31100,NULL,30);
INSERT INTO ABTS_EMP2 VALUES -
    (9900,'SPANKY','MANAGER',9698,to_date('23-JUN-1971','DD-MON-YYYY'),22950,2200,30);
INSERT INTO ABTS_EMP2 VALUES -
    (9902,'BUTCHY','VICE-PRES',9566,to_date('23-JUL-1971','DD-MON-YYYY'),23000,NULL,30);
INSERT INTO ABTS_EMP2 VALUES -
    (9934,'MY GAL SAL','MANAGER',9782,to_date('11-AUG-1993','DD-MON-YYYY'),31300,150,40);
COMMIT;

REM ====== ABTS_BIG_TABLE
          
prompt Creating table ABTS_MANY_COLUMNS
DROP TABLE ABTS_MANY_COLUMNS;
CREATE TABLE ABTS_MANY_COLUMNS (
    C1          NUMBER,
    C2          NUMBER,
    C3          NUMBER,
    C4          NUMBER,
    C5          NUMBER,
    C6          NUMBER,
    C7          NUMBER,
    C8          NUMBER,
    C9          NUMBER,
    C10         NUMBER,
    C11         NUMBER,
    C12         NUMBER,
    C13         NUMBER,
    C14         NUMBER,
    C15         NUMBER,
    C16         NUMBER,
    C17         NUMBER,
    C18         NUMBER,
    C19         NUMBER,
    C20         NUMBER,
    C21         NUMBER,
    C22         NUMBER,
    C23         NUMBER,
    C24         NUMBER,
    C25         NUMBER,
    C26         NUMBER,
    C27         NUMBER,
    C28         NUMBER,
    C29         NUMBER,
    C30         NUMBER,
    C31         NUMBER,
    C32         NUMBER,
    C33         NUMBER,
    C34         NUMBER,
    C35         NUMBER,
    C36         NUMBER,
    C37         NUMBER,
    C38         NUMBER,
    C39         NUMBER,
    C40         NUMBER,
    C41         NUMBER,
    C42         NUMBER,
    C43         NUMBER,
    C44         NUMBER,
    C45         NUMBER,
    C46         NUMBER,
    C47         NUMBER,
    C48         NUMBER,
    C49         NUMBER,
    C50         NUMBER,
    C51         NUMBER,
    C52         NUMBER,
    C53         NUMBER,
    C54         NUMBER,
    C55         NUMBER,
    C56         NUMBER,
    C57         NUMBER,
    C58         NUMBER,
    C59         NUMBER,
    C60         NUMBER,
    C61         NUMBER,
    C62         NUMBER,
    C63         NUMBER,
    C64         NUMBER,
    C65         NUMBER,
    C66         NUMBER,
    C67         NUMBER,
    C68         NUMBER,
    C69         NUMBER,
    C70         NUMBER,
    C71         NUMBER,
    C72         NUMBER,
    C73         NUMBER,
    C74         NUMBER,
    C75         NUMBER,
    C76         NUMBER,
    C77         NUMBER,
    C78         NUMBER,
    C79         NUMBER,
    C80         NUMBER,
    C81         NUMBER,
    C82         NUMBER,
    C83         NUMBER,
    C84         NUMBER,
    C85         NUMBER,
    C86         NUMBER,
    C87         NUMBER,
    C88         NUMBER,
    C89         NUMBER,
    C90         NUMBER,
    C91         NUMBER,
    C92         NUMBER,
    C93         NUMBER,
    C94         NUMBER,
    C95         NUMBER,
    C96         NUMBER,
    C97         NUMBER,
    C98         NUMBER,
    C99         NUMBER,
    C100        NUMBER );
COMMIT;

REM ====== ABTS_DATATYPES

prompt Create table ABTS_DATATYPES
DROP TABLE ABTS_DATATYPES;
CREATE TABLE ABTS_DATATYPES
  (DCH             CHAR(20),
   DVC             VARCHAR(20),
   DLN             NUMBER(10),
   DDBL            NUMBER,
   DDATE           DATE );

prompt Inserting sample data into table ABTS_DATATYPES    
INSERT INTO ABTS_DATATYPES VALUES ('1234567','1234567',1234567,1234567.123, - 
    TO_DATE('01-APR-1996 12:34:56','DD-MON-YYYY HH:MI:SS'));

INSERT INTO ABTS_DATATYPES VALUES ('-1234567','-1234567',-1234567,-1234567.123, - 
    TO_DATE('01-APR-1996 12:34:56','DD-MON-YYYY HH:MI:SS'));
COMMIT;

REM ====== ABTS_TOOBIG_DATA

prompt Create table ABTS_TOOBIG_DATA
DROP TABLE ABTS_TOOBIG_DATA;
CREATE TABLE ABTS_TOOBIG_DATA
  (TBI             NUMBER(38),
   TBF             NUMBER );

prompt Inserting sample data into table ABTS_TOOBIG_DATA    
INSERT INTO ABTS_TOOBIG_DATA VALUES (536870911,536870911);
INSERT INTO ABTS_TOOBIG_DATA VALUES (536870912,536870912);
COMMIT;

REM ====== ABTS_FUNCTION_DATA

prompt Create table ABTS_FUNCTION_DATA
DROP TABLE ABTS_FUNCTION_DATA;
CREATE TABLE ABTS_FUNCTION_DATA
  (FENAME          VARCHAR(10),
   FSAL            NUMBER(7,2),
   FDATE           DATE );

prompt Inserting sample data into table ABTS_FUNCTION_DATA
INSERT INTO ABTS_FUNCTION_DATA VALUES -
    ('SMITH',1200,TO_DATE('17-DEC-1980 00:00:00','DD-MON-YYYY HH24:MI:SS'));
INSERT INTO ABTS_FUNCTION_DATA VALUES -
    ('ALLEN',1600,to_date('20-FEB-1981 00:00:00','DD-MON-YYYY HH24:MI:SS'));
COMMIT;

REM ====== ABTS_EMPTY_TABLE

prompt Create table ABTS_EMPTY_TABLE
DROP TABLE ABTS_EMPTY_TABLE; 
CREATE TABLE ABTS_EMPTY_TABLE
  (ENAME           VARCHAR(10),
   SAL             NUMBER(7,2),
   DEPT            NUMBER(4),
   STATE           CHAR(2),
   HIREDATE        DATE );
COMMIT

REM ====== ABTS_PERSONNEL

prompt Create table ABTS_PERSONNEL
DROP TABLE ABTS_PERSONNEL;
CREATE TABLE ABTS_PERSONNEL (
   LAST_NAME       VARCHAR(14),
   FIRST_NAME      CHAR(10),
   MID_INIT        CHAR(1),
   CITY            CHAR(20),
   STATE           CHAR(2),
   ZIP             CHAR(6),   
   SEX             CHAR(1) );

prompt Inserting sample data into table ABTS_PERSONNEL    
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Toliver','Alvin','A','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Terry','D','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Rick',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kilpatrick','Janet',NULL,'Marlow','NH','03456','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Norman',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gray','Susan','O','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Wood','Brian',NULL,'Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('DAmico','Aruwa',NULL,'Sandown','NH','03873','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Peters','Janis','K','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Dean','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Daniel','V','Bennington','MA','03442','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','George',NULL,'Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hastings','Norman','M','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Kinmonth','Louis',NULL,'Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Goldstone','Neal',NULL,'Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dallas','Meg',NULL,'Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Canonica','Rick','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reynolds','Louis','E','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Iacobone','Eloi','N','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nash','Walter','V','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Frydman','Louie','T','Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stadecker','Hope','E','Alton','NH','03809','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Cora',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Stan','P','Acworth','NH','03601','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Karen','G','Jefferson','NH','03583','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lengyel','Peter','A','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('OSullivan','Rick','G','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Pfeiffer','Karen','I','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Connolly','Christine',NULL,'Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Reitchel','Charles','N','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Morrison','MaryLou','R','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Emery','Daniel','P','Wilmot','NH','03287','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Mary',NULL,'Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Danzig','Chris',NULL,'Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Leslie',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Nunez','Larry','B','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ziemke','Al','F','Winnisquam','NH','03289','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Marjorie','T','Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrington','Margaret','V','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gaudet','Johanna','I','Fremont','NH','03044','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Myotte','Charles','K','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Bartlett','Wes',NULL,'Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','Marty','J','Jefferson','NH','03583','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Babbin','Joseph','Y','Sanbornville','CT','38720','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sciacca','Joe','V','Munsonville','NH','03457','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Smith','Roger','R','Bristol','NH','03222','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dietrich','Alan','J','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gutierrez','Ernest','F','Farmington','MA','03835','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clarke','Roy','C','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mercier','Len','F','Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mellace','Dean',NULL,'Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Siciliano','James','X','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Hall','Lawrence',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Villari','Christine',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gehr','Janis',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sullivan','Len','R','Sandown','NH','03873','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lasch','Norman',NULL,'Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Foote','Rick','B','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Manning','Kevin','G','Troy','NH','03465','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Jackson','Mary',NULL,'Wonalancet','NH','03897','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','James','Q','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnston','Carol',NULL,'Wolfeboro','NH','03894','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Harrison','Lisa',NULL,'Boston','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Tom','A','Fremont','NH','03044','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Tarbassian','Louis',NULL,'Keene','NH','03431','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clairmont','Rick',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('McElroy','Mary',NULL,'Cambridge','MA','00000','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mathias','Susan','N','Milan','NH','03588','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Robinson','Kathleen',NULL,'Keene','NH','03431','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Clinton','Kathleen','Q','Penacook','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Gramby','Ruth','N','Etna','NH','03750','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Burton','Frederick','Z','Penacook','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Flynn','Peter',NULL,'Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Sarkisian','Dean',NULL,'Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Johnson','Bill','R','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Keisling','Edward','X','Twin Mountain','NH','03595','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Vormelker','Daniel','F','Rochester','NH','03867','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Larry','T','Etna','NH','03750','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Boyd','Ann','B','Acworth','NH','03601','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Roberts','Norman','U','Chocorua','NH','03817','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lonergan','Peter','V','Meadows','NH','03587','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ulrich','Christine','L','Whitefield','NH','03598','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Klein','Franklin','Q','Milford','NH','03055','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Rodrigo','Lisa',NULL,'Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Saninocencio','Roger','H','Boscawen','NH','03301','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Watters','Christine','D','Colebrook','NH','03576','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Brown','Nancy',NULL,'Milton','NH','03851','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Silver','Glenn','S','Colebrook','NH','03576','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Stornelli','James','S','Whitefield','NH','03598','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Belliveau','Paul',NULL,'Milton','NH','03851','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','JoAnn','C','Chocorua','NH','03817','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Crain','Jesse',NULL,'Milan','NH','03588','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Lapointe','Hope',NULL,'Boscawen','NH','03301','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Andriola','Leslie','Q','Salisbury','NH','03268','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Dement','Alvin','B','Sanbornton','NH','03269','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Mistretta','Kathleen','G','Bennington','MA','03442','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Ames','Louie','A','Alton','NH','03809','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Blount','Peter',NULL,'Alstead','NH','03602','M');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('MacDonald','Johanna','P','Marlborough','MA','03455','F');
INSERT INTO ABTS_PERSONNEL VALUES -
    ('Herbener','James','Q','Penacook','NH','03301','M');
COMMIT;

REM ====== ABTS_UNSUP_DTYPES

prompt Creating table ABTS_UNSUP_DTYPES
DROP TABLE ABTS_UNSUP_DTYPES;
CREATE TABLE ABTS_UNSUP_DTYPES (
    D_LABEL       MLSLABEL,
    D_ROWID       ROWID,
    D_RAW         RAW(100),
    D_LONG        LONG );
COMMIT;

REM ====== ABTS_TEXT

prompt Creating table ABTS_TEXT
DROP TABLE ABTS_TEXT;
CREATE TABLE ABTS_TEXT (
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    HIREDATE    DATE,
    SEX         CHAR(1) );
COMMIT;

prompt Inserting sample data into table ABTS_TEXT    
INSERT INTO ABTS_TEXT VALUES -
    ('SMITH','CLERK',to_date('17-DEC-1980','DD-MON-YYYY'),'M');
INSERT INTO ABTS_TEXT VALUES - 
    ('ALLEN','SALESMAN',to_date('20-FEB-1981','DD-MON-YYYY'),'M');
INSERT INTO ABTS_TEXT VALUES - 
    ('WARD','SALESMAN',to_date('22-FEB-1981','DD-MON-YYYY'),'F');
INSERT INTO ABTS_TEXT VALUES
    ('JONES','MANAGER',to_date('02-APR-1981','DD-MON-YYYY'),'M');
INSERT INTO ABTS_TEXT VALUES -
    ('MARTIN','SALESMAN',to_date('28-SEP-1981','DD-MON-YYYY'),NULL);
INSERT INTO ABTS_TEXT VALUES -
    ('BLAKE','MANAGER',to_date('01-MAY-1981','DD-MON-YYYY'),'F');
INSERT INTO ABTS_TEXT VALUES -
    ('CLARK','MANAGER',to_date('09-JUN-1981','DD-MON-YYYY'),'M');
COMMIT;

REM ====== ABTS_FLOAT

prompt Creating table ABTS_FLOAT
DROP TABLE ABTS_FLOAT;
CREATE TABLE ABTS_FLOAT (
    SAL         NUMBER(7,2),
    COMM        NUMBER );

COMMIT;

prompt Inserting sample data into table ABTS_FLOAT
INSERT INTO ABTS_FLOAT VALUES (7.5,-333.34);
INSERT INTO ABTS_FLOAT VALUES (-7.5,333.34);
INSERT INTO ABTS_FLOAT VALUES (7.545,38383.33);
INSERT INTO ABTS_FLOAT VALUES (555.667,-333333);
INSERT INTO ABTS_FLOAT VALUES (3838.33,-383888.3);
INSERT INTO ABTS_FLOAT VALUES (999.4,333.33);
INSERT INTO ABTS_FLOAT VALUES (-99875.43,-333.3555);
COMMIT;              

REM ====== ABTS_INT

prompt Creating table ABTS_INT
DROP TABLE ABTS_INT;
CREATE TABLE ABTS_INT (
    EMPNO         NUMBER(7),
    DEPTNO        NUMBER(38) );

COMMIT;

prompt Inserting sample data into table ABTS_INT
INSERT INTO ABTS_INT VALUES (7,-333);
INSERT INTO ABTS_INT VALUES (-7,333);
INSERT INTO ABTS_INT VALUES (7,38383);
INSERT INTO ABTS_INT VALUES (555,-333333);
INSERT INTO ABTS_INT VALUES (3838,-383888);
INSERT INTO ABTS_INT VALUES (999,333);
INSERT INTO ABTS_INT VALUES (-99875,-9933555);
COMMIT;              

REM ====== ABTS_EMP_X2

prompt Creating table ABTS_EMP_X2
DROP TABLE ABTS_EMP_X2;
CREATE TABLE ABTS_EMP_X2 (
    EMPNO       NUMBER(4),                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         NUMBER(4),
    HIREDATE    DATE,
    SAL         NUMBER(7,2),
    COMM        NUMBER(7,2),
    DEPTNO      NUMBER(2) );

prompt Inserting sample data into table ABTS_EMP_X2
INSERT INTO ABTS_EMP_X2 VALUES -
    (7369,'SMITH','CLERK',7902,to_date('17-DEC-1980','DD-MON-YYYY'),1200,800,20);
INSERT INTO ABTS_EMP_X2 VALUES - 
    (7499,'ALLEN','SALESMAN',7698,to_date('20-FEB-1981','DD-MON-YYYY'),1600,300,30);
INSERT INTO ABTS_EMP_X2 VALUES - 
    (7521,'WARD','SALESMAN',7698,to_date('22-FEB-1981','DD-MON-YYYY'),1250,500,30);
INSERT INTO ABTS_EMP_X2 VALUES
    (7566,'JONES','MANAGER',7839,to_date('02-APR-1981','DD-MON-YYYY'),2975,NULL,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7654,'MARTIN','SALESMAN',7698,to_date('28-SEP-1981','DD-MON-YYYY'),1250,1400,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7698,'BLAKE','MANAGER',7839,to_date('01-MAY-1981','DD-MON-YYYY'),2850,NULL,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7782,'CLARK','MANAGER',7839,to_date('09-JUN-1981','DD-MON-YYYY'),2450,10,10);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7788,'SCOTT','ANALYST',7566,to_date('10-AUG-1993','DD-MON-YYYY'),3000,20,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7839,'KING','PRESIDENT',7999,to_date('17-NOV-1981','DD-MON-YYYY'),5000,1000,10);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7844,'TURNER','SALESMAN',7698,to_date('08-SEP-1981','DD-MON-YYYY'),1500,0,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7876,'ADAMS','CLERK',7788,to_date('13-SEP-1993','DD-MON-YYYY'),1100,500,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7900,'JAMES','CLERK',7698,to_date('03-DEC-1981','DD-MON-YYYY'),950,200,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7902,'FORD','ANALYST',7566,to_date('03-DEC-1981','DD-MON-YYYY'),3000,NULL,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7934,'MILLER','CLERK',7782,to_date('23-JAN-1983','DD-MON-YYYY'),1300,50,10);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7369,'SMITH','CLERK',7902,to_date('17-DEC-1980','DD-MON-YYYY'),1200,800,20);
INSERT INTO ABTS_EMP_X2 VALUES - 
    (7499,'ALLEN','SALESMAN',7698,to_date('20-FEB-1981','DD-MON-YYYY'),1600,300,30);
INSERT INTO ABTS_EMP_X2 VALUES - 
    (7521,'WARD','SALESMAN',7698,to_date('22-FEB-1981','DD-MON-YYYY'),1250,500,30);
INSERT INTO ABTS_EMP_X2 VALUES
    (7566,'JONES','MANAGER',7839,to_date('02-APR-1981','DD-MON-YYYY'),2975,NULL,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7654,'MARTIN','SALESMAN',7698,to_date('28-SEP-1981','DD-MON-YYYY'),1250,1400,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7698,'BLAKE','MANAGER',7839,to_date('01-MAY-1981','DD-MON-YYYY'),2850,NULL,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7782,'CLARK','MANAGER',7839,to_date('09-JUN-1981','DD-MON-YYYY'),2450,10,10);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7788,'SCOTT','ANALYST',7566,to_date('10-AUG-1993','DD-MON-YYYY'),3000,20,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7839,'KING','PRESIDENT',7999,to_date('17-NOV-1981','DD-MON-YYYY'),5000,1000,10);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7844,'TURNER','SALESMAN',7698,to_date('08-SEP-1981','DD-MON-YYYY'),1500,0,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7876,'ADAMS','CLERK',7788,to_date('13-SEP-1993','DD-MON-YYYY'),1100,500,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7900,'JAMES','CLERK',7698,to_date('03-DEC-1981','DD-MON-YYYY'),950,200,30);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7902,'FORD','ANALYST',7566,to_date('03-DEC-1981','DD-MON-YYYY'),3000,NULL,20);
INSERT INTO ABTS_EMP_X2 VALUES -
    (7934,'MILLER','CLERK',7782,to_date('23-JAN-1983','DD-MON-YYYY'),1300,50,10);
COMMIT;

REM ====== ABTS_ROWS10K

prompt Creating table ABTS_ROWS10K
DROP TABLE ABTS_ROWS10K;
CREATE TABLE ABTS_ROWS10K (
   V1       NUMBER,
   V2       NUMBER,
   V3       NUMBER,
   V4       NUMBER,
   V5       NUMBER,
   V6       NUMBER,
   V7       NUMBER
);

DECLARE
    cnt        NUMBER := 0;
BEGIN
    FOR j IN 0..9 LOOP
      FOR i IN 1..1000 LOOP
        INSERT INTO ABTS_ROWS10K VALUES (i+cnt,i+cnt,i+cnt,i+cnt,i+cnt,i+cnt,i+cnt);
      END LOOP;
      cnt := cnt + 1000;
    END LOOP;
END;
/
COMMIT;

REM ====== ABTS_SCRATCH

prompt Creating table ABTS_SCRATCH
DROP TABLE ABTS_SCRATCH;
CREATE TABLE ABTS_SCRATCH (
    EMPNO       NUMBER(4),                          
    ENAME       VARCHAR(10),
    JOB         VARCHAR(9),
    MGR         NUMBER(4),
    HIREDATE    DATE,
    SAL         NUMBER(7,2),
    COMM        NUMBER(7,2),
    DEPTNO      NUMBER(2),
    MESSAGE     VARCHAR(200) );
COMMIT;


REM =========================================
REM    STORED PROCEDURES
REM =========================================

REM ====== Set User Privileges

GRANT EXECUTE ANY PROCEDURE TO "SCOTT"


REM ====== ABTS_ADD_NAME

create or replace procedure abts_add_name (input_name IN VARCHAR)
as begin

  insert into abts_scratch (ename) values (input_name);

end;
/
COMMIT;


REM =========================================
REM    TRIGGERS
REM =========================================


REM ====== ABTS_TRIGGER_TABLE

prompt Creating table ABTS_TRIGGER_TABLE
DROP TABLE ABTS_TRIGGER_TABLE;
CREATE TABLE ABTS_TRIGGER_TABLE (
    MESSAGE       VARCHAR(128));
COMMIT;

REM ====== ABTS_TRIG_TEST1

create or replace trigger ABTS_TRIG_TEST1
after insert on abts_trigger_table
for each row
declare
  status  number;
  msg     varchar2(128);
begin
  dbms_output.put_line('Trigger Alert - Insert !!');
  msg := 'Trigger Alert INSERT';
  dbms_pipe.purge('ABTS_TRIG_PIPE1');
  dbms_pipe.pack_message(msg);
  status := dbms_pipe.send_message('ABTS_TRIG_PIPE1');
  if status <> 0 then
    raise_application_error(-20000,'trig_pipe_error');
  end if;
end;
/
COMMIT;




SET TERMOUT ON

prompt
prompt  Done.
