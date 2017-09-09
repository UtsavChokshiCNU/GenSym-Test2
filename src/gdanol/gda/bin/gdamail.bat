@echo off
TITLE gdamail
REM ------------------------------------------------------
REM This file should only be edited to change the following
REM paths to define PATH, CLASSPATH

REM Last updated:  March 13, 2000
REM ------------------------------------------------------
SET PATH=.;.\bin;.\jre\bin;%JAVA_HOME%\jre\bin
SET CLASSPATH=.;.\jre\lib\rt.jar;.\jre\swingall.jar

REM -- run Emailer - piping to a log file --
java -classpath . com.gensym.gda.emailer.gdaMail %1 %2 %3 %4 %5 %6 > %7


