Gensym NeurOn-Line Platform
                     
____________________________________________________________________

Contents of this readme file:

1. NeurOn-Line Package Overview
2. NOL Studio Packages
3. NOL Classic Packages  
4. Available Bridges 
5. System Requirements 
6. Version Information
7. How Can I Begin Using NeurOn-Line Studio?
8. Online Documentation
9. Known Installer Bug

___________________________________________________________________ 

1. NeurOn-Line Package Overview

Gensymüs NeurOn-Line (NOL) platform enables process-manufacturing
companies in a variety of industries to realize substantial economic 
benefits from improved efficiency and product quality. Applications
of the NOL platform include inferential measurements of product quality, 
model-based control, and process fault detection.

The platform includes four packages: 

NOL Studio Development and Deployment packages for the development 
and deployment of neural network models and embedded deployment in 
Windows environments.

NOL Premium Development and Deployment packages for Windows and 
G2-based development and deployment. 

2. NOL Studio Packages 

NOL Studio packages can be used offline for model analysis or online 
for real-time, model-based diagnostics and control. For offline use, 
NOL Studio packages are desktop tools in the Windows (NT/98) environment 
for analysis of process behavior, modeling, and design optimization. 
Typically, the source of data is a data historian or spreadsheet data 
arrays. Many technical decisions such as selection of relevant inputs, 
time delays, and network architecture are automated. Once a model has 
been built, NOL Studio enables users to discover more profitable ways 
to run their process through simulation and optimization.

For online use, NOL Studio has two options. NOL Studio models can be:
Deployed as Microsoft ActiveX components in Windows applications.
Loaded into the standard G2-based NOL packages for execution in a
G2-based environment, which brings the added capabilities of G2          
for expert operations.

The NOL Studio Development and (Active X model) Deployment packages         
are restricted to a single model and single site per license. See           
your Gensym sales representative for pricing. 

Note that the NOL Studio Deployment package for ActiveX does not                    
offer user access to G2.
               
3. NOL Premium Packages

The NOL Premium packages include NOL Studio packages and additional 
packages that work in the G2 environment to deliver intelligent, 
real-time, process monitoring and analysis applications with a 
comprehensive suite of easy-to-use neural-network technology, 
provided through graphical object libraries. Powerful prediction 
diagrams of graphically connected NOL objects execute and document 
the application functionality, enabling fast deployment and easy 
maintenance.

The NOL Premium Development package includes a G2 development license,   
NOL Classic, and NOL Studio for online use. The package also offers G2 
ProTools, GDA, Telewindows 1 and 2, G2-WebLink, G2-JavaLink, 
G2-ActiveXLink, G2 Gateway (GSI), and any two of the five available 
bridges listed in the next section (4). The package is restricted to 
one user per license             						
   
The NOL Premium Deployment package provides you tools to build models   
from both NOL Classic and NOL Studio, in a graphical environment.  
The package gives you access to deployment-only G2s to extend the    
functionality of the application. Licensing is for single models          
on a per-server basis.

The package allows up to four users per license and includes G2,  
GDA, NOL Studio Deployment, and any two of the five available bridges

4. Available Bridges 

For NOL Classic Packages only (NOL Studio packages are not applicable).

OPCLink
CorbaLink Bridge
ODBC Bridge
Oracle Bridge
Sybase Bridge

Using two deployments of the same bridge count as two bridges. Bridges 
not included in the package will be billed in addition to the package.


5. System Requirements for Running NeurOn-Line Packages

To use NOL Packages on Windows 98 / NT:

   * A Pentium 166 MHz (or better) machine
   * Minimum 100 MB of RAM
   * Approximately 1 GB of disk space to install the software and
     documentation

6. Version Information

The NOL platform ships with these versions of software:

NOL Studio Version 2.2 Rev 0
NOL Classic Version 4.0 Rev 1
GDA Classic Version 4.0 Rev 1
G2 Classic Version 5.1 Rev 6
                     
7. How Can I Begin Using NeurOn-Line Packages?

After installing any NOL package, you can run the software by going 
to  Start->Programs->GensymNOLS> "Software Name".

   * Run the NOL Studio with example data series
          This release ships with 7 examples. Each of these can be found
          in the examples directory (nolstudio\examples\DataSet).               
		  These include example data series that can be loaded into
          NOL Studio.
   * Use demo projects in Visual Basic to test the implementation of
     ActiveX Controls.
          Three demos can be found in the examples directory
          (nolstudio\examples\ActiveXDemo). These include two demos for 
		  NOLPredictor and one for NOLOptimizer.
   * Use demo kbs to test the implementation of models and optimizations 		 
	      in G2.Two demos can be found in the examples directory
          (nolstudio\examples\kbdemo). These include one demo using
          nolexten.kb with classic NeurOn-Line version 4.0 and one demo
          using nolstudio.kb.
   * Use your own data to preprocess data, generate models, and deploy 
     them using either G2 or through ActiveX.
   * Query for the current list of bugs to make sure that you are not
     encountering known problems.

NOTES:   
 Because G2/Javalink is not supported on Windows 98, NOLStudio 
 Deployment using G2/Javalink is supported ONLY on Windows NT. We do 
 support NOLStudio ActiveX deployment on Windows 98 and Windows NT.

 Users of ActiveX Controls should refer to the NeurOn-Line Studio
    Release Notes, section "Upgrade Issues for Users of ActiveX Controls,"
    before proceeding with the NOL Studio 2.2 Installation.

8. Online Documentation

Online documentation is a part of each NOL Studio package. The default 
installation directories for NOL Studio and NOL Classic packages are:
C:\Program Files\Gensym\NOLS

The default installation directory for most G2 Classic documentation 
files is C:\Program Files\Gensym\NOLS\doc. The default installation 
directory for most NOL documentation files is inside the corresponding 
software directory.
  
The directory paths in the tables below are directly under the doc 
directory unless otherwise noted.

To access html documentation, open the titlepag.htm file for
each document in a web browser and navigate from there.
  
This documentation is also available through Help Link.

NOL Online Documentation:
_____________________________________________________________________
book titles							html directories	pdf files      
_____________________________________________________________________
NOL Studio 2.2 Release Notes		nolstudio/doc/html	nolstudio/doc
									/ReleaseNotes22r0	/nolstudioug.pdf

NOL Studio User's Guide				nolstudio/doc/html
									/UsersGuide2.1r0

NOL Classic Release Notes (4.0r1)   nol/noldoc

NOL Classic Reference Manual        nol/noldoc

NOL Classic User's Guide            nol/noldoc

  
G2 Online Documentation:
_____________________________________________________________________
book titles		   		html directories	      pdf files
_____________________________________________________________________

G2 Reference Manual		g2/g2/html/g2rm/		g2/g2/g2refman      
						  	
G2 Release Notes Update g2/starterkit/			g2/starterkit/
			   			html/g2rnupd/			g2rnupd   

G2 5.1r6 Readme          g2/starterkit/readme.htm 
			
G2 System Procedures	 g2/g2/html/g2sprm/		g2/g2/g2sprm 
  Reference Manual
	
G2 Class Reference       g2/g2/html/g2crm/      g2/g2/g2crm 
  Manual

G2 Developer's Guide	 g2/g2/html/g2dvg/      g2/g2/g2devgd 
_____________________________________________________________________

 
G2 Utilities Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

G2 Dynamic Displays		g2/utilities/html/		g2/utilities/
  User's Guide             gddug/                 gddug 

G2 Developer's Interface g2/utilities/html/     g2/utilities/   
  User's Guide             gdiug/                 gdiug 

G2 Foundation Resources	 g2/utilities/html/     g2/utilities/
  User's Guide             gfrug/                 gfrug 

G2 Menu System			g2/utilities/html/     g2/utilities/
  User's Guide             gmsug/                 gmsug 

G2 Online Documentation	 g2/utilities/html/     g2/utilities/
  Developer's Guide        golddg/ 		        golddug 

G2 GUIDE/UIL Procedures	 g2/utilities/html      g2/utilities/
  Reference Manual         guideprm/              guideprm 

G2 GUIDE User's Guide	 g2/utilities/html/     g2/utilities/
			   				guideug/			 guideug 

G2 XL Spreadsheet		g2/utilities/html/     g2/utilities/
  User's Guide	           gxlsug/		  gxlsug 
  
_____________________________________________________________________


G2 Diagnostic Assistant (GDA) Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

GDA User's Guide/       development/	   	
  Reference Manual		gda/gdadoc/

Gda Queues Api			development/ 
  Reference Section     gdadoc/queueapi/   
_____________________________________________________________________


G2 ProTools Online Documentation:
_____________________________________________________________________
book titles			html directories			pdf files
_____________________________________________________________________

G2ProTools User's 	development/protools
Guide  				/doc/
_____________________________________________________________________


G2 Gateway Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

G2 Gateway Bridge	 g2/g2/html/gsibdg/    		g2/g2/gsidbg
  Developer's Guide    
_____________________________________________________________________


G2 Bridge Products Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

G2 OPCLink User's Guide  bridges/opclink/       bridges/opclink/
                                                  opclink

G2 CORBA/Link            bridges/corbalink/     bridges/corbalink/
  User's Guide                                    corbalink

G2-ODBC Bridge			bridges/odbc/          bridges/odbc/g2-odbc
  Release Notes

G2-Oracle Bridge         bridges/oracle/        bridges/oracle/
  Release Notes                                   g2-oracle

G2-Sybase Bridge         bridges/sybase/        bridges/sybase/
  Release Notes                                   g2-sybase             
_____________________________________________________________________


Telewindows Online Documentation:
_____________________________________________________________________
book title				html directory	        	pdf file
_____________________________________________________________________

Telewindows User's       g2/starterkit/html/    g2/starterkit/
  Guide                    twug/                  twug
_____________________________________________________________________


Telewindows2 Toolkit ActiveX Online Documentation:
_____________________________________________________________________
book title				html directory	        	pdf file
_____________________________________________________________________

Telewindows2 Toolkit	 tw2/ActiveX/docs/      tw2/ActiveX/docs/ 
  Application              guides/index.html      guides/index.html
  Developer's Guide             
  for ActiveX	           
                                                 			                 
______________________________________________________________________ 

Telewindows2 Toolkit Java Online Documentation:
______________________________________________________________________
book titles				html directories			pdf files
______________________________________________________________________

Telewindows2 Toolkit	 tw2/java/docs/         tw2/java/docs/
  Release Notes            guides/index.html      guides/index.html
			   
Telewindows2 Toolkit     tw2/java/docs/  		tw2/java/docs/
  Java Developer's Guide:  guides/index.html      guides/index.html
  Components and Core      
  Classes                  
						  
Telewindows2 Toolkit     tw2/java/docs/         tw2/java/docs/
  Java Developers Guide:   guides/index.html      guides/index.html
  Application Classes      
                           			       
Telewindows2 Toolkit     tw2/java/docs/         tw2/java/docs/
  Component Editor        guides/index.html       guides/index.html
  User's Guide                          
                          

Telewindows Toolkit      tw2/java/docs/          tw2/java/docs/
  Java Demos Guide         guides/index.html       guides/index.html
			                
                                                  
BeanXporter User's       tw2/java/docs/          tw2/java/docs/
  Guide					guides/index.html        guides/index.html
			                 
_____________________________________________________________________


G2 Java Link/Gateway Online Documentation:
_____________________________________________________________________
book titles				html directories			pdf files
_____________________________________________________________________

G2 JavaLink/Gateway		javalink/docs/         javalink/docs/
  User's Guide             guides/index.html      guides/index.html
                           
G2 DownloadInterfaces	 javalink/docs/         javalink/docs/
  User's Guide             guides/index.html      guides/index.html
                           
G2 Bean Builder	         javalink/docs/         javalink/docs/
  User's Guide             guides/index.html      guides/index.html
                           
_____________________________________________________________________


G2 ActiveXLink Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

G2 ActiveXLink           development/
  User's Guide             g2activexlink/
_____________________________________________________________________


G2 WebLink Online Documentation:
_____________________________________________________________________
book titles		 html directories			pdf files
_____________________________________________________________________

G2 WebLink User's Guide  development/gw/
_____________________________________________________________________
 
 
9. Known Installer Bug

When you install the NOL bundle inside the "Program Files" directory,
the NOL Classic package cannot launch the remote process from the
default directory name in the launch dialog. The workaround is to 
either (1) replace the "Program Files" string with "Progra~1", 
which is the DOS name for that directory, or (2) install the 
bundle in a directory with no spaces in its name, e.g. "C:\Gensym".




  ------------------------------------------------------------------------
Updated:September 27, 2000

