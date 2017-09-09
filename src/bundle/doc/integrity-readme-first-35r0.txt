
Integrity and Optegrity Product Packages
_________________________________________

Introduction

The Integrity Package provides an advanced suite of products that feature Network, System, Service, and Application Management tools and applications. Integrity applications maintain continuous availability in data and voice networks by detecting, diagnosing, and correcting problems before they impact services.

Optegrity is built on Gensym's Integrity, SymCure, and G2 Classic technologies.  Optegrity provides innovative tools for abnormal condition management that are vital to ensuring integrity in process operations

There are three sections in this readme file:

(1) Package Products  

    This section briefly describes the products contained in each package. Packages include
    Integrity Reasoner and Optegrity Reasoner. 

(2) Preinstallation Requirements
    
    (a) Installing the Java Developers Kit (if installing the Client software)

    (b) Setting Environment Variables

(3) Installation

(4) Running Integrity

(5) Documentation

    This section lists the document titles and their 
    directories.   
    
    
(1) Package Products

By default, the software components have been installed on Windows 
platforms in C:\gensym\Integrity\, and on Unix platforms in /usr/gensym/Integrity/.  The software component directories listed in this section are subdirectories immediately below Integrity or immedately below your custom installation directory path. 
     
-------------------------------------------
Integrity Core provides foundational components for network and system management
  applications. It includes: 

o Integrity Core Services - the foundation of the Integrity platform. Integrity Core Services provides essential capabilities for automating problem resolution, which are leveraged and extended in the other Integrity packages. 

o OPAC (Operator Action) - Integrity's general-purpose graphical language. OPAC provides  graphical representation of operational procedures often outlined in workflow procedure diagrams. Using "clone (by drag and drop from palettes), connect, and configure" visual programming, OPAC facilitates rapid deployment of new systems that require minimal customization. 

o HPOV Map Importer - imports HP OpenView formatted domain maps
o G2/SNMP Bridges - bridges between Integrity and SNMP
o G2/JAVA Socket Manager - 
o MPE - Message Parser Engine
o ODiE - OpEx Dispatch Engine
o OpWeb - Integrity OpWeb Interface
o Ping Manager - Provides ping management to network devices according
        to user specifications through a graphical interface. 
o DXI3 - Domain map importer
o SymCure - Model-based tool for fault modeling, and root cause failure analysis
o SymCure Library - a library of equipment fault models
o G2 Classic platform bundle - a platform for developing and deploying real-time expert system applications. For abnormal condition management, G2 Classic provides a platform for monitoring manufacturing processes and creating events from which Optegrity can perform root-cause analyses.  Note that G2 Classic includes several components including G2 Diagnostic Assistant (GDA), ProTools, Telewindows, Telewindows2 Toolkit, G2 Gateway Standard Interface, Links for ActiveX, Java, and Web browsers, and a choice of 2 standard bridges including relational databases and OLE for Process Control (OPC).  For Optegrity 3.4, G2 Classic ships as a separate installable CD and is restricted for use in one application in combination with the Optegrity bundle.  Gensym recommends that monitoring and event generation applications based on GDA be run in a separate computing process from root-cause analysis applications based on Optegrity SymCure. 

(2) Preinstallation Requirements

If the Java UI is to be used, then before installing Integrity, you must install the Sun Microsystem Java(TM) 2 SDK, Standard Edition 1.3.0, and you must set certain user environment variables. 

(a) Installing the Java Developers Kit

You must obtain the Sun Microsystems Java Developers Kit (Java(TM) 2 SDK, Standard Edition 1.3.0) from Sun Microsystems. You can download it for free from the following link:

http://java.sun.com/j2se/1.3/

Toward the top of this link's page, the three available platforms for the 1.3.0 version are shown. Click on the circled arrow under the version for your platform. Clicking on the platform link displays another page that lists options for your download. Scroll down and make your selections (the kit may be listed after some other products), then click on the Continue button. 

Review the License Agreement that appears, then click on the Accept button. Select the download method to begin your download. Follow any additional instructions on the Sun Microsystems site.


(b) Setting Environment Variables.

You must set the JAVA_HOME and CLASSPATH user environment variables to the appropriate files/directories. Be sure to include the %JAVA_HOME%\bin directory in the PATH user environment variable. 

After you create or modify any environment variable, you must reboot the computer before proceeding with the Integrity Client software installation.

The table below describes the user environment variables that must be defined before you install Integrity:
 
  
Variable Name      Description	                     Example
-------------------------------------------------------------------------
JAVA_HOME   Location where JDK 1.3 is installed    C:\jdk1.3
-------------------------------------------------------------------------
PATH 	    For the Java bin directory             %JAVA_HOME%\bin;%PATH%
-------------------------------------------------------------------------
CLASSPATH   Needed to locate Java Classes          %JAVA_HOME%\lib\dt.jar;
                                                       .
                                                       .
                                                       .
                                                    %JAVA_HOME%\lib\tools.jar
-------------------------------------------------------------------------

    
(3) Installation
(3.1) Integrity/Optegrity NT Installation


IMPORTANT NOTE: Choose an alternative installation directory other than the default directory ("C:\Program Files\Gensym\Integrity").


After configuring your system in accordance with the preinstallation requirements described in step 2, install the Integrity software by:

a. Insert the Integrity CD into your CD drive.

b. Navigate to the CD top-level directory and run Setup.exe. The InstallShield Wizard starts up.

c. If you have a previous version of Integrity loaded on this machine, you must uninstall it before installing the new version. To uninstall a previous version, click on the Remove option, then click on the Next button. After the previous version has been removed, run the setup again.

Note=> Completely removing Integrity components does not delete custom applications that were named with a custom prefix.  

d. After the InstallShield Wizard begins, enter the appropriate information in the Customer Information screen. Enter your user name, company name, and the Serial Number provided to you with your Integrity package. If you do not have the serial number for your package, contact Gensym Order Services. 

e. Choose the destination location. The default location is C:\Gensym\Integrity. To choose another location click on the Browse button and select the destination location. Click on the Next button.

f. Click on the Setup Type (usually Typical), then click on the Next button.

g. From the Start Copying Files window, click on the Next button. InstallShield displays the setup status. When the installation is complete and if the Java Client software was installed, a dos window will appear.  This command is configuring the Javalink environment.  Once completed, you will be asked if you wish to reboot your computer. You must reboot your computer to run the new Integrity installation.

NOTE: If the shortcut to start up G2 and load the appropriate KB does not work, then you must go to the Properties of the shortcut and remove the double-quotes (") surrounding the shortcut command.  Once this is done, the shortcut will behave correctly.

(3.2) Integrity/Optegrity UNIX Installation
a. Mount the CD.  The command to do so depends on the operating system on your machine.  Following are examples of the mount command for each operating system.  You must customize the command for your system, which means that it may be different than the examples shown here.
	Solaris	Automounts the CD.
	AIX	mount -rv cdrfs /dev/cd0 cdrom
	HP-UX	mount -F cdfs /dev/dsk/c0t0d4 /cdrom

Note: For AIX, HP-UX, and Tru64 Unix you may need root privileges to mount the CD.

b. Install the package components by first logging in as the user who will own the installed files, then executing the install script from the directory in which your CD is mounted.  Following are examples of executing the install script on each operating system.  The directory from which you execute the command may be different.
	Solaris	/cdrom/cdrom0/geninst
	AIX	/cdrom/geninst
	HP-UX	/cdrom/geninst

c. Follow the instructions on your screen.  When prompted for the license key, enter the 25-digit license key printed on the CD case or obtain the license key from Order Services at 781-265-7106.


(4) Running Integrity

After installation is complete, run Integrity by:

(4.1) Running Integrity on NT
NOTE: There is currently a problem with the InstallShield process where it does not make the correct link in some shortcuts.  If a shortcut does not work, modify the shortcut and remove the double-quotes around the command.

a. Load G2. To load G2, click on Start > Programs > Integrity/Optegrity > Integrity <package>.  (Where <package> is one of Core, Discover, Premium, or Reasoner.  Optegrity installations will just display Optegrity.  This will start G2 and load the appropriate KB.)

b. Start the Integrity/Optegrity Client. To start the client, click on Start > Programs > Integrity/Optegrity > Integrity/Optegrity Client.

Refer to the Integrity User Guide and other Integrity documentation for instructions on using Integrity.

(4.2) Running Integrity on UNIX
a. Load G2 by entering the following command:
	./g2
b. Load the appropriate knowledgbase for the package you purchased.  Below is a table of the available packages:

	Integrity Reasoner	opexpkg4.kb
	Optegrit  Reasoner	opteg.kb
c. Once the knowledgbase is loaded, it will automatically start.


(5) Documentation

Documentation is a part of the Integrity package and is located in the doc subdirectory within the Integrity directory in Adobe Acrobat .pdf format. The Adobe Acrobat Reader product is included to allow viewing the documentation. 
  
This documentation is also available through Help Link.

Documentation includes:

Integrity Installations:
Integrity Release Notes
Integrity User Guide
Integrity Reference Manual
Integrity SymCure Developer's Guide
Integrity SymCure Modeling Guide
Integrity Demo Guide
Integrity Utilities Manual
G2/SNMP Bridges Installation and User's Guide
G2/SNMP Bridges Java-Based Installation and User's Guide
G2/Java Socket Manager User's Guide

Optegrity Installations:
G2/Java Socket Manager User's Guide
Optegrity Reference Manual
Optegrity User Guide
Optegrity Release Notes
Optegrity SymCure Developer's Guide
Optegrity SymCure Modeling Guide
Integrity Utilities Guide
Integrity Demo Guide
  


  