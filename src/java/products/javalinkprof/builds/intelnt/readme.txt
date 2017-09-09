================================================================
InstallShield Requirements

This code was designed to run with InstallShield3

================================================================
On extraction from CVS the initial directory tree will be :-

<INSTALLDIR>
		Data\
		Setup\
		buildjl.bat
		IbuildJLD.bat
		readme.txt
		runMeOnce.bat

Data - a directory containing .bmp images , a batch file to rename directories and a raw 
.com.gensym.properties file.

Setup - a directory containing the product specific files for InstallShield3

buildjl.bat takes single argument V - the version  of javalink professional  eg 1.0 and builds a self extracting .exe for distribution (see runtime) 

IbuildJLD.bat - a batch file called by buildjl.bat which actually builds the disk images.

runMeOnce.bat - a batch file which creates two additional directories 
<INSTALLDIR>
		disk1    - holds the installShield3 distribution disk image
		runtime - hold the self extrating .exe of disk1
			eg  javalink-professional1.0.exe

runMeOnce.bat also copies files from InstallShield3 into <INSTALLDIR>setup 
and <INSTALLDIR>disk1 in order for IbuildJLD.bat to funtion.


NOTE runMeOnce.bat must be run at least once in order for this build process to function.
*******
================================================================
Environmental variables 

change the settings in IbuildJLD.bat to reflect your installation

eg

set INSTALLSHIELD_HOME="C:\Program Files\InstallShield\InstallShield3"
set JAVALINK_PROF_RELEASE=c:\javalinkprof-distribution\javalinkprof
set JAVALINK_PROF_BUILD=c:\javalinkprof-distribution

================================================================
You may have to change the two entries in setup\mkexe.ini to point to your installation
This file is crearted automatically by RunMeOnce.bat

eg

SrcDir=c:\javalinkprof-distribution\disk1
DestDir=c:\javalinkprof-distribution\runtime

================================================================