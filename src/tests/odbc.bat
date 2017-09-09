osql -E -Q "sp_attach_db @dbname = 'TestBridges', @filename1 = 'C:\G2\src\tests\bridges\database\TestBridges.mdf', @filename2 = 'C:\G2\src\tests\bridges\database\TestBridges_log.ldf'"


osql -E -Q "CREATE LOGIN gensym WITH PASSWORD='gensym',CHECK_POLICY=off"


osql -E -Q "EXEC master..sp_addsrvrolemember @loginame = N'gensym', @rolename = N'sysadmin'"

odbc.vbs

set GSI_ROOT=%SRCBOX%\tests
rem copy \G2\license\gsi.ok %GSI_ROOT%

%GSI_ROOT%\g2-odbc