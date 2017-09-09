			    Read Me First
			   November 30, 2015


G2 CLASSIC INSTALLATION
-----------------------

  By default, G2 Classic installs the software components on Windows
  operating systems in C:\Program Files\Gensym\g2-2015\, and on UNIX
  operating systems in /usr/gensym/g2-2015/.


PRODUCT DOCUMENTATION
---------------------

  The installation and authorization information in the component
  product documentation is no longer valid. It has been superseded by
  the G2 Classic Package installation process, which automatically
  installs the required g2.ok (OK) files.

  The CD liner for each operating system (Windows and UNIX) contains
  the installation instructions for the complete G2 Classic Package.
  These same instructions are repeated at the end of this file.


README.HTML FILE
----------------

  After installation, refer to the readme.htm file for a brief
  description of each component product, for important information on
  bridge products, and for a complete listing and file locations of
  the component documentation. The readme.htm file is located in the
  top-level directory of your G2 Classic installation.

  You should also refer to the G2 JavaLink and Telewindows2 Toolkit
  readme.html files for important information about the respective
  products.


DEPLOYMENT PACKAGE FUNCTIONALITY
--------------------------------

  The G2 2015 deployment package replaces the previous restricted
  license option. The package has the same functionality as that
  option. The deployment package limits the ability to interactively
  edit rules and procedures and use of the Profiling facilities.


G2 COMPONENT
------------

  The G2 2015 package ships with the G2 component, 12.0 Rev. 0.

  The G2 Reference Manual 2015 states that the -v11ok
  command-line option (or the equivalent G2V11_OK environment variable)
  specifies a custom location for an authorization file that is
  specific to G2 Version 11.0. For G2 12.0, the manual should state that
  the -v12ok command-line option (or equivalent G2V12_OK environment
  variable) specifies a custom location for an authorization file that
  is specific to G2 Version 12.0.


TELEWINDOWS COMPONENT
---------------------

  The Telewindows User's Guide 2015 states that the -v11ok
  command-line option (or the equivalent TWV11_OK environment variable)
  specifies a custom location for an authorization file that is
  specific to Telewindows Version 11.0. For Telewindows 12.0, the manual
  should state that the -v12ok command-line option (or equivalent
  TWV12_OK environment variable) specifies a custom location for an
  authorization file that is specific to Telewindows Version 12.0.


G2 PROTOOLS USERS
-----------------

  The G2 Protools KBs have been updated for the 12.0 release of the G2
  2015 Package. The G2 Protools directory on the CD contains one
  subdirectory for the G2 2011 KBs (kbs). The documentation for the KBs
  is located in the kbs\doc directory.


TELEWINDOWS2 TOOLKIT FOR ACTIVEX USERS
--------------------------------------

  Support for the Telewindows2 Toolkit ActiveX components has been
  discontinued as of 5.2r0.

  Note: Discontinuation of support for Telewindows2 Toolkit for
  ActiveX does not affect the status of G2 ActiveXLink, an unrelated
  product. G2 ActiveXLink is a separate component, which Gensym will
  continue to support in future releases.


INSTALLING G2 2015 ON THE WINDOWS OPERATING SYSTEM
-----------------------------------------------------

 INSTALLING ON WINDOWS 98/ME

  For Windows 98/Me the package software is limited to off-line use
  only. Use of bridge products, Telewindows2 Toolkit, G2 JavaLink, and
  G2 WebLink are not supported when G2 Classic is installed on a
  Windows 98/Me system.


 INSTALLING ON WINDOWS NT

  If you are installing with administrative privileges, the system
  without prompting installs for all users. If you wish to install as
  the current user, temporarily remove your administrative status. If
  your operating system is NT 4.0 with service pack 5 or less and you
  are installing with administrator privileges for all users, the
  installer sets your user environment variables instead of system
  environment variables. This is usually adequate for a single-user
  system. If you need to set system variables, use Windows NT 4.0 with
  service pack 6 or later.


 INSTALLING ON WINDOWS 2000 OR WINDOWS XP

  You must use administrator privileges to install on this operating
  system, otherwise the system generates this error: "Setup failed to
  launch install engine: Class not registered."


 REMOVING STAND-ALONE G2 JAVALINK AND TELEWINDOWS2 TOOLKIT
 INSTALLATIONS

  If you have previously installed G2 JavaLink or Telewindows2 Toolkit
  as stand-alone products (not as part of a G2 Classic installation),
  uninstall them before installing them as components of the G2
  Classic package. Use the Uninstall menu choice from the product menu
  shortcut and reboot your machine when the uninstall is complete.

  After uninstalling G2 Javalink or Telewindows2 Toolkit you must also
  remove from the PATH and CLASSPATH environment variables any entries
  that support the uninstalled products. Failure to do so may cause
  conflicts with changes that G2 Classic makes to these variables.

  Following is a list of elements that you may need to remove as they
  are no longer used by the Telewindows2 Toolkit:

	  %SWING_HOME%\windows.jar
	  %SWING_HOME%\swing.jar

  Following is a list of elements that will be added by the G2 Classic
  installer and should be removed to avoid conflicts:

	  %SEQUOIA_HOME%\classes
	  %SEQUOIA_HOME%\classes\coreui.jar
	  %SEQUOIA_HOME%\classes\sequoia.jar
	  %SEQUOIA_HOME%\classes\antlr.jar
	  %SEQUOIA_HOME%\classes\ax2jbeans.jar

  Note: Beginning with the G2 Classic 5.2 release, the Component
  Editor is no longer included in the sequoia.jar file.  However, you
  still may see vestiges of it in the documentation and in batch
  files.  These will be removed in future versions of the G2 Classic
  Package.

  Note: Beginning with the Telewindows2 Toolkit 1.2 release, the
  ax2jbeans.jar file is no longer added to the CLASSPATH when you
  install the product.

  This element is usually added to PATH when Telewindows2 Toolkit is
  installed:

	  %SEQUOIA_HOME%\bin

  These elements are usually added to CLASSPATH when G2 JavaLink is
  installed:

	  %JAVA_HOME%\lib\tools.jar
	  %JAVALINK_HOME%\classes
	  %JAVALINK_HOME%\classes\core.jar
	  %JAVALINK_HOME%\classes\classtools.jar
	  %JAVALINK_HOME%\classes\javalink.jar
	  %JAVALINK_HOME%\classes\beanbuilder.jar

  This element is usually added to PATH when G2 Javalink is installed:

	  %JAVALINK_HOME%\bin


 REMOVING PREVIOUS G2 INSTALLATIONS

  Before installing this version of G2 Classic, uninstall any previous
  installation of G2 Classic and reboot your machine. This removes all
  previous installation information from the Windows registry. If left
  in the Windows registry, this information will interfere with the
  new installation.

  To uninstall a previous G2 installation:

  1. Save any files you created or altered before removing the
     software.  This is particularly important for an OK file that you
     may have altered to contain user names and passwords. You can
     then use the saved OK file for the new installation or merge it
     with the OK file from the new installation. Alternatively, you
     may want to copy the entire previously installed directory tree
     to another location before you uninstall the previous version of
     G2 Classic.

  2. Use the %SEQUOIA_HOME%\bin\unInstallControls.bat to remove any
     ActiveX controls you have registered during Telewindows2 Toolkit
     ActiveX development.

  3. From Start, select Settings > Control Panel > Add/Remove
     Programs.

  4. Select Gensym G2 Development or G2 Deployment from the list of
     installed programs.

     You are presented with a confirmation dialog that will:
	  - Remove the files from the previously installed G2 Classic
	    directories.
	  - Delete environment variables created by the previous
	    installation.
	  - Remove shortcut program folders so that Gensym G2
	    Development or G2 Deployment no longer appears under
	    Programs in the Start menu.
	  - Delete Gensym G2 Development or G2 Deployment from your
	    system's database of installed programs.


 TROUBLESHOOTING PROBLEMS WITH TELEWINDOWS2 TOOLKIT

  If you find that your JAVALINK_HOME and SEQUOIA_HOME environment
  variables do not get expanded, you can expand them by following the
  steps below. Note that these steps are for Windows NT; the Windows
  2000 and XP System Properties dialogs differ slightly.

  1. Bring up the Systems Properties dialog by selecting Start >
     Settings > Control Panel and double-clicking on System.

  2. Select the Environment tab on the Systems Properties dialog. (On
     Windows 2000 and XP, select the Advanced tab.)

  3. Select JAVALINK_HOME from the System or Users Variable menu. The
     variable will appear in the Variable field.

  4. Place your cursor in the Variable field, select Set, then select
     Apply.

  5. Repeat steps 3 and 4 for the SEQUOIA_HOME environment variable.


 RUNNING TELEWINDOWS2 TOOLKIT FOR JAVA

  JDK version 1.3 or later is required.  After you install G2 Classic,
  see the Telewindows2 Toolkit Version 1.2 Rev. 1 Readme for more
  detailed information.

  To run Telewindows2 Toolkit, you must set the JAVA_HOME environment
  variable to the location of the JDK.


INSTALLING G2 2015 ON UNIX OPERATING SYSTEMS
-----------------------------------------------

  These instructions provide information for installing G2 Classic on
  machines running the Sun Solaris, IBM AIX, HP HP-UX, Compaq Tru64
  UNIX, and Red Hat Linux operating systems.


 BEFORE INSTALLING

  BACKUP THE G2.OK FILE.  If you have a previous installation of G2
  2015 on your machine, make a backup copy of the g2.ok (OK) file
  and save it to another directory. G2 Classic's installation process
  may overwrite the original g2.ok file (a file with the name
  "g2.ok").  The purpose of this step is to save any custom
  configuration information, including entries for user names,
  passwords, and privileges, that may have been added.  (If no such
  information was added to the OK file, this step can be skipped.)
  After the installation is complete, some or all of the contents of
  the g2.ok file may need to be merged back in with the new g2.ok file
  that the installation process writes.  This should be done any time
  that you modify the installation or uninstall the product.


 SYSTEM REQUIREMENTS

  - 2GB memory.
  - 1024 Mbytes disk space without online documentation (500 Mbytes for
    full installation).


 TO INSTALL

  1. Mount the CD. Following are examples of the mount command for
     each operating system. You must customize the command for your
     system, which means that it may be different than the examples
     shown here.

       Solaris  Automounts the CD.
       AIX      mount -rv cdrfs /dev/cd0 /cdrom
       HP-UX    mount -F cdfs /dev/dsk/c0t0d4 /cdrom
       Tru64    mount -t cdfs -o noversion,rrip /dev/rz3c /cdrom
       Linux    mount -t iso9660 -r /dev/cdrom /cdrom

  Note: For AIX, HP-UX, and Tru64 UNIX you may need root privileges to
  mount the CD.

  2. Install the package components by first logging in as the user
     who will own the installed files, then executing the install
     script from the directory in which your CD is mounted. Following
     are examples of executing the install script on each operating
     system.  The directory from which you execute the command may be
     different.

       Solaris  /cdrom/cdrom0/geninst
       AIX      /cdrom/geninst
       HP-UX    /cdrom/"GENINST.;1"
       Tru64    /cdrom/geninst
       Linux    /cdrom/geninst

  3. Follow the instructions on your screen. When prompted for the
     license key, enter the 25-digit license key printed on the CD
     case.

  4. Unmount the CD.  On most UNIX systems this can be achieved by
     executing the command below.

       umount /cdrom


INSTALLING G2 2015 ON WINDOWS OPERATING SYSTEMS
--------------------------------------------------

  These instructions provide information for installing G2 2015 on
  machines running the Windows 7/8.1/10/2008/2010 operating systems.


 BEFORE INSTALLING

  1. If you have a previous installation of G2 2015 on your
     machine, make a backup copy of the g2.ok file and save it to
     another directory. This should be done each time that you modify
     the installation or uninstall.

  2. Uninstall any previous installation of G2 Classic and reboot your
     machine. This removes all previous installation information from
     the Windows registry. If left in the registry, this information
     will interfere with the new installation. See the section
     Removing Previous G2 2015 Installations in this
     ReadMeFirst.txt file for further information.

  3. Uninstall any previously installed stand-alone versions (not as
     part of a G2 Classic installation) of G2 JavaLink or Telewindows2
     Toolkit and reboot your machine. After uninstalling the products
     you must also remove from the PATH and CLASSPATH environment
     variables any entries that support the uninstalled products.  See
     the section Removing Standalone G2 Javalink and Telewindows2
     Toolkit Installations in this ReadMeFirst.txt file for further
     information.


 SYSTEM REQUIREMENTS

  - Pentium processor.
  - 2GB memory.
  - 1024 Mbytes disk space without online documentation (500 Mbytes for
    full installation).


 WINDOWS OPERATING SYSTEMS CONSIDERATIONS

  The G2 2015 installation differs depending on the Windows
  operating system:

  - For Windows 98/Me, the package software is limited to off-line
    use.  This prevents the use of bridge products.

  - For Windows NT, the installation differs depending on your
    privileges when you install the product. See the section
    Installing on Windows NT Operating Systems in this ReadMeFirst.txt
    file for more information.

  - For Windows 2000 and XP, you must use administrator privileges to
    install.  If you do not, the system generates the error, "Setup
    failed to launch install engine: Class not registered."


 TO INSTALL

  1. Run the setup.exe file that is located in the top-level directory
     of the CD.

  2. Follow the installation instructions on your screen. When
     prompted for the license key, enter the 25-digit license key
     printed on the CD case.


CUSTOMER SUPPORT
----------------

  If you have questions for Gensym Customer Support, you can visit
  www.gensym-support.com; send email to service@gensym.com (US) or
  service-ema@gensym.com (Europe, Middle East, and Africa); or place a
  call to 1-800-896-3030 (US), +1-781-265-7301 (US), or +31-71-5682622
  (Europe, Middle East, and Africa).
