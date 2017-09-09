================================================================
InstallShield Requirements

This code was designed to run with InstallShield Java TM Edition
(version 2.01 was used at the time this file was commited)

================================================================
On extraction from CVS the initial directory tree will be :-

 runMeOnce.bat
 IbuildJLUnix.bat
 setup  - a directory containing the product specific files for  InstallShield Java TM Edition
 README.txt

1. Make sure that the Solaris javalink directory had been made
2. call runMeOnce.bat to set up the JInstallShield files:
	
	setup/solaris.ini - specifies how InstallShield Java is to build the distributable file
	(refer to InstallShield Java documentation for details) 
	runtime       - The resulting .tar file will be placed here
	distribution  - The staging will be copied before Java InstallShield builds

3. Call IbuildJLUnix.bat  -  takes single argument - the version  of javalink  eg 10b2 
                             and builds a self extracting shell script for distribution (in runtime) .
================================================================
Environmental variables 

JSHIELD_HOME must be setup to point to the Java InstallShield Installation dir

eg

set JSHIELD_HOME="d:\jshield"

================================================================

