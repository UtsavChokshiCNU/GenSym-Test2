@echo off

rem Java environment settings for STD and ENT, 32bit JVM for STD and 64bit JVM for ENT
rem Meanwhile, there is a local debug setting and remote deployment setting

rem STD environment: local debug setting
rem set STD_JAVA_HOME="C:\Program Files (x86)\Java\jre1.8.0_77"
rem STD environment: remote deployment setting
set STD_JAVA_HOME="C:\Program Files (x86)\Java\jdk1.8.0_92"

rem ENT environment: local debug setting
rem set ENT_JAVA_HOME="C:\Program Files\Java\jdk1.8.0_60"
rem ENT environment: remote deployment setting
set ENT_JAVA_HOME="C:\Program Files\Java\jdk1.8.0_92"
