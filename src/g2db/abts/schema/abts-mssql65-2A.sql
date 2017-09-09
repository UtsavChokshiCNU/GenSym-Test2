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
GO 


PRINT ' '
PRINT 'Step 2A Done !'
