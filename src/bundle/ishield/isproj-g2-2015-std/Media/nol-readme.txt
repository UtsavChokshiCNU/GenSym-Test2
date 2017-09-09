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
9. Known Installer Problems

___________________________________________________________________ 

1. NeurOn-Line Package Overview

Gensym's NeurOn-Line (NOL) platform enables process-manufacturing
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
NOL Studio packages are desktop tools in the Windows (98/NT/2000/XP) 
environment for analysis of process behavior, modeling, and design 
optimization. Typically, the source of data is a data historian or 
spreadsheet data arrays. Many technical decisions such as selection of 
relevant inputs, time delays, and network architecture are automated. 
Once a model has been built, NOL Studio enables users to discover more 
profitable ways to run their process through simulation and optimization.

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

To use NOL Packages on Windows 98 / NT / 2000 / XP:

   * A Pentium 166 MHz (or better) machine
   * Minimum 100 MB of RAM
   * Approximately 1 GB of disk space to install the software and
     documentation

6. Version Information

The NOL platform ships with these versions of software:

NOL Studio Version 4.1 Rev 1
NOL Classic Version 4.1 Rev 1
GDA Classic Version 4.1 Rev 1
G2 Classic Version 6.1 Rev 0
                     
7. How Can I Begin Using NeurOn-Line Packages?

After installing any NOL package, you can run the software by going 
to  Start->Programs->Gensym NOL> "Software Name".

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
          classic NeurOn-Line version 4.0 and one demo using nolstudio.kb.
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
C:\Program Files\Gensym\NOL\NOLStudio\doc and C:\Program Files\Gensym\NOL\NOL\noldoc

The default installation directory for most G2 Classic documentation 
files is C:\Program Files\Gensym\NOL\doc. The default installation 
directory for most NOL documentation files is inside the corresponding 
software directory.
  
 
9. Known Installer Problems

a.Windows 2000 and XP Users:
  To install the NOL bundle on Windows 2000 or XP, you must have administrator privileges. 
  Currently, when a user with non-administrator privileges logs in, the user cannot run 
  any software from the NOL bundle until the administrator follows these steps following 
  the installation: 
    1.Choose Properties on the folder that contains the NOL bundle software, nol, 
      by default.
    2.Click the Security tab, then click the Advanced button.
    3.Enable the "Reset permissions on all child objects and enable propagation of 
      inheritable permissions" option.
  Enabling this option allows the user to run any software without giving administrator   privileges. The user can now run nolstudio and G2. 

b.When you install the NOL bundle inside the "Program Files" directory,
  the NOL Classic package cannot launch the remote process from the
  default directory name in the launch dialog. The workaround is to 
  either (1) replace the "Program Files" string with "Progra~1", 
  which is the DOS name for that directory, or (2) install the 
  bundle in a directory with no spaces in its name, e.g. "C:\Gensym".

c.Windows 98 Users:
  1.Place the following command in your config.sys file:
       shell=c:\command.com /e:2048 /p
    This command sets the environment space to 2048 kb, which is required to run NOLStudio.
  2.Change your autoexec.bat to include the following:
       SET NOLSTUDIO_HOME=c:\Program Files\Gensym\nol\nolstudio
    where "c:\Program Files\Gensym\nol" is the location you install NOL bundle.
  NOTE:   Because G2/Javalink is not supported on Windows 98, NOLStudio deployment
  using G2/Javalink is supported ONLY on Windows NT.  We do support NOLStudio ActiveX
  deployment on Windows 98, in addition to Windows NT.


  ------------------------------------------------------------------------
Updated: February 20, 2002

