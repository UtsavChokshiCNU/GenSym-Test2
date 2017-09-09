@echo off
REM ------------------------------------------------------
REM This file should only be edited to change the following
REM paths to define NOLSTUDIO_HOME
REM updated March 12, 1999 by Brian O. Bush
REM
SET PATH=.;.\bin;.\jre\bin
SET CLASSPATH=.;.\jre\lib\rt.jar;.\jre\swingall.jar
SET GSI_ROOT=.

REM -- run NOL Studio --
jre -classpath %CLASSPATH% -mx140m com.gensym.license.Boot com.gensym.nols.main.NeurOnLine
