================================================================
InstallShield Requirements

This code was designed to run with InstallShield3

================================================================
On extraction from CVS the initial directory tree will be :-

<INSTALLDIR>
		Data\
		Setup\
		IbuildJLD.bat
		Javalink.pfw
                PackageJavaLinkWeb.bat
		readme.txt

Data - a directory containing .bmp images and a raw .com.gensym.properties file.

Setup - a directory containing the product specific files for InstallShield3

IbuildJLD.bat - a batch file which compiles the InstallShield script and
                copies the output and the data directory along with the 
                data directory and along some InstallShield files to the
                staging area.

Javalink.pfw - A Package For The Web 2 project file for building a self extracting exe.

PackageJavaLinkWeb.bat - a batch file that compresses the staging area into a
                         self extracting exe.
================================================================
Environmental variables 

IbuildJLD.bat builds into a directory relative to the DSTBOX
variable, gets the sources relative to the SRCBOX variable,
and needs to run and copy files relative to the
INSTALLSHIELD_HOME variable.

eg

set INSTALLSHIELD_HOME="C:\Program Files\InstallShield\InstallShield3"
set DSTBOX=c:\bt\jsmith
set SRCBOX=c:\bt\jsmith
================================================================
