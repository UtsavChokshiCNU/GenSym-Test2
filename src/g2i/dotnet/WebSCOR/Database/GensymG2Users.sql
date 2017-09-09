IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'GensymG2Users')
	DROP DATABASE [GensymG2Users]
GO

CREATE DATABASE [GensymG2Users]  ON (NAME = N'GensymG2Users_Data', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL\data\GensymG2Users_Data.MDF' , SIZE = 2, FILEGROWTH = 10%) LOG ON (NAME = N'GensymG2Users_Log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL\data\GensymG2Users_Log.LDF' , SIZE = 1, FILEGROWTH = 10%)
GO

exec sp_dboption N'GensymG2Users', N'autoclose', N'false'
GO

exec sp_dboption N'GensymG2Users', N'bulkcopy', N'false'
GO

exec sp_dboption N'GensymG2Users', N'trunc. log', N'false'
GO

exec sp_dboption N'GensymG2Users', N'torn page detection', N'true'
GO

exec sp_dboption N'GensymG2Users', N'read only', N'false'
GO

exec sp_dboption N'GensymG2Users', N'dbo use', N'false'
GO

exec sp_dboption N'GensymG2Users', N'single', N'false'
GO

exec sp_dboption N'GensymG2Users', N'autoshrink', N'false'
GO

exec sp_dboption N'GensymG2Users', N'ANSI null default', N'false'
GO

exec sp_dboption N'GensymG2Users', N'recursive triggers', N'false'
GO

exec sp_dboption N'GensymG2Users', N'ANSI nulls', N'false'
GO

exec sp_dboption N'GensymG2Users', N'concat null yields null', N'false'
GO

exec sp_dboption N'GensymG2Users', N'cursor close on commit', N'false'
GO

exec sp_dboption N'GensymG2Users', N'default to local cursor', N'false'
GO

exec sp_dboption N'GensymG2Users', N'quoted identifier', N'false'
GO

exec sp_dboption N'GensymG2Users', N'ANSI warnings', N'false'
GO

exec sp_dboption N'GensymG2Users', N'auto create statistics', N'true'
GO

exec sp_dboption N'GensymG2Users', N'auto update statistics', N'true'
GO

if( ( (@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 724) ) or ( (@@microsoftversion / power(2, 24) = 7) and (@@microsoftversion & 0xffff >= 1082) ) )
	exec sp_dboption N'GensymG2Users', N'db chaining', N'false'
GO

use [GensymG2Users]
GO

