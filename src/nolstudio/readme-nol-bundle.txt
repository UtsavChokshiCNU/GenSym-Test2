                         Gensym NeurOn-Line Platform

                             Version 4.2 Rev. 0

  ------------------------------------------------------------------------

Contents of this readme file:

   * NeurOn-Line Package Overview
   * NOL Studio Packages
   * NOL Premium Packages
   * Available Bridges
   * System Requirements
   * Version Information
   * How Can I Begin Using NeurOn-Line Packages?
   * Online Documentation
   * Known Problems

  ------------------------------------------------------------------------

NeurOn-Line Package Overview

Gensym's NeurOn-Line (NOL) platform enables process-manufacturing companies
in a variety of industries to realize substantial economic benefits from
improved efficiency and product quality. Applications of the NOL platform
include inferential measurements of product quality, model-based control,
and process fault detection.

The platform includes four packages:

*NOL Studio Development and Deployment packages for the development and
deployment of neural network models and embedded deployment in Windows
environments.
*NOL Premium Development and Deployment packages for Windows and G2-based
development and deployment.

NOL Studio Packages

NOL Studio packages can be used offline for model analysis or online for
real-time, model-based diagnostics and control. For offline use, NOL Studio
packages are desktop tools in the Windows (98/NT/2000/XP) environment for
analysis of process behavior, modeling, and design optimization. Typically,
the source of data is a data historian or spreadsheet data arrays. Many
technical decisions such as selection of relevant inputs, time delays, and
network architecture are automated. Once a model has been built, NOL Studio
enables users to discover more profitable ways to run their process through
simulation and optimization.

For online use, NOL Studio has two options. NOL Studio models can be:
Deployed as Microsoft ActiveX components in Windows applications. Loaded
into the standard G2-based NOL packages for execution in a G2-based
environment, which brings the added capabilities of G2 for expert
operations.

The NOL Studio Development and (Active X model) Deployment packages are
restricted to a single model and single site per license. See your Gensym
sales representative for pricing.

Note that the NOL Studio Deployment package for ActiveX does not offer user
access to G2.

NOL Premium Packages

The NOL Premium packages include NOL Studio packages and additional packages
that work in the G2 environment to deliver intelligent, real-time, process
monitoring and analysis applications with a comprehensive suite of
easy-to-use neural-network technology, provided through graphical object
libraries. Powerful prediction diagrams of graphically connected NOL objects
execute and document the application functionality, enabling fast deployment
and easy maintenance.

The NOL Premium Development package includes a G2 development license, NOL
Classic, and NOL Studio for online use. The package also offers G2 ProTools,
GDA, Telewindows 1 and 2, G2-WebLink, G2-JavaLink, G2-ActiveXLink, G2
Gateway (GSI), and any two of the five available bridges listed in the next
section (4). The package is restricted to one user per license

The NOL Premium Deployment package provides you tools to build models from
both NOL Classic and NOL Studio, in a graphical environment. The package
gives you access to deployment-only G2s to extend the functionality of the
application. Licensing is for single models on a per-server basis.

The package allows up to four users per license and includes G2, GDA, NOL
Studio Deployment, and any two of the five available bridges

Available Bridges

For NOL Classic Packages only (NOL Studio packages are not applicable).

   * OPCLink
   * CorbaLink Bridge
   * ODBC Bridge
   * Oracle Bridge
   * Sybase Bridge

Using two deployments of the same bridge count as two bridges. Bridges not
included in the package will be billed in addition to the package.

System Requirements for Running NeurOn-Line Packages

To use NOL Packages on Windows 98 / NT / 2000 / XP:

   * A Pentium 166 MHz (or better) machine
   * Minimum 100 MB of RAM
   * Approximately 1 GB of disk space to install the software and
     documentation

Version Information

The NOL platform ships with these versions of software:

   * NOL Studio Version 4.2 Rev 0
   * NOL Classic Version 4.2 Rev 0
   * GDA Classic Version 4.2 Rev 0
   * G2 Classic Version 7.0 Rev 1

How Can I Begin Using NeurOn-Line Packages?

   * Windows Platform

        o NOL Studio

          After installing NOL Studio you can run NOLStudio by going to
          Start menu Program Files-> Gensym NOL->NeurOnLine->NeurOn-Line
          Studio, which uses the nolstudio.bat to launch the NOLStudio main
          frame window.
             + Run the NOL Studio with example data series
                    This release ships with 7 examples. Each of these can be
                    found in examples directory
                    (%NOLSTUDIO_HOME%\examples\DataSet). They include
                    example data series that can be loaded into NOL Studio.
             + Use demo projects in Visual Basic to test the implementation
               of ActiveX Controls.
                    Three demos can be found in examples directory
                    (%NOLSTUDIO_HOME%\examples\ActiveXDemo). They include
                    two demos for NOLPredictor and one for NOLOptimizer.
             + Use your own data to preprocess data, generate models and
               deploy them using either G2 or through ActiveX.
             + Query for the current list of bugs to make sure that you are
               not encountering known problems.

        o Demos for G2 deployment of Classic NOL and NOLStudio models
             + Use demo kbs noldemo.kb to test the implementation of models
               developed from Classic NOL and NOLStudio. You can launch this
               demo through Start menu Program Files->Gensym
               NOL->NeurOnLine->NOL Classic Demo.
   * Unix Platform

        o NOL Studio
             + After installing NOL Studio you can launch NOLStudio by
               running the nolstudio script, which locates in the nolstudio
               directory.
             + Run the NOL Studio with example data series
             + Use your own data to preprocess data, generate models and
               deploy them using G2.

        o Demos for G2 deployment of Classic NOL and NOLStudio models
             + Use demo kbs noldemo.kb to test the implementation of models
               developed from Classic NOL and NOLStudio. You can launch this
               demo through Start menu Program Files->Gensym
               NOL->NeurOnLine->NOL Classic Demo.
     -----------------------------------------------------------------------
     NOTES:
          The nolexten.kb module in older version before 4.1r1 has been
          deleted. All the items are merged into nol.kb. If you have an
          existing nol application using ensemble model build from
          nolstudio, please follow these steps to upgrade to version later
          than 4.1r1:
             + Make a backup copy of the application.
             + Load your application with an empty nolexten module. An empty
               nolexten.kb is provided in the nol directory.
             + Once you load your application delete the nolexten module
               from your module hierachy.
             + Save the upgraded application.
     -----------------------------------------------------------------------
     -----------------------------------------------------------------------
     NOTES:
          Because G2/Javalink is not supported on Windows 98, NOLStudio
          Deployment using G2/Javalink is supported ONLY on Windows NT. We
          do support NOLStudio ActiveX deployment on Windows 98 and Windows
          NT. Users of ActiveX Controls should refer to the NeurOn-Line
          Studio Users Guide, section "Upgrade Issues for Users of ActiveX
          Controls," before proceeding with the NOL Studio 4.1r2
          Installation.
     -----------------------------------------------------------------------

Online Documentation

Online documentation is a part of each NOL Studio package. The default
installation directories for NOL Studio and NOL Classic packages are:
C:\Program Files\Gensym\NOL\NOLStudio\doc and C:\Program
Files\Gensym\NOL\NOL\noldoc

The default installation directory for most G2 Classic documentation files
is C:\Program Files\Gensym\NOL\doc. The default installation directory for
most NOL documentation files is inside the corresponding software directory.

Known Problems

   * Installer Problems

        o Windows 2000 and XP Users:
               To install the NOL bundle on Windows 2000 or XP, you must
               have administrator privileges. Currently, when a user with
               non-administrator privileges logs in, the user cannot run any
               software from the NOL bundle until the administrator follows
               these steps following the installation:
             + Choose Properties on the folder that contains the NOL bundle
               software, nol, by default.
             + Click the Security tab, then click the Advanced button.
             + Enable the "Reset permissions on all child objects and enable
               propagation of inheritable permissions" option. Enabling this
               option allows the user to run any software without giving
               administrator privileges. The user can now run nolstudio and
               G2.
        o When you install the NOL bundle inside the "Program Files"
          directory,
               the NOL Classic package cannot launch the remote process from
               the default directory name in the launch dialog. The
               workaround is to either (1) replace the "Program Files"
               string with "Progra~1", which is the DOS name for that
               directory, or (2) install the bundle in a directory with no
               spaces in its name, e.g. "C:\Gensym".
        o Windows 98 Users:
             + Place the following command in your config.sys file:
                    shell=c:\command.com /e:2048 /p This command sets the
                    environment space to 2048 kb, which is required to run
                    NOLStudio.
             + Change your autoexec.bat to include the following:
                    SET NOLSTUDIO_HOME=c:\Program Files\Gensym\nol\nolstudio
                    where "c:\Program Files\Gensym\nol" is the location you
                    install NOL bundle.
          ------------------------------------------------------------------
          NOTE: Because G2/Javalink is not supported on Windows 98,
          NOLStudio deployment using G2/Javalink is supported ONLY on
          Windows NT. We do support NOLStudio ActiveX deployment on Windows
          98, in addition to Windows NT.
          ------------------------------------------------------------------
   * Upgrade Problems

        o Upgrade ActiveX Control
               The ActiveX controls of NOL Studio contained in 4.1 are not
               backward-compatible with the controls in previous NOL Studio
               releases. If you have existing files from a COMcompliant
               environment (such as a VB project file) that incorporate NOL
               Studio controls, please follow the instruction explained in
               NOL Studio Users' Guide to upgrade your application.
        o Upgrade NOL kbs
               If you are loading an existing KB that was developed in NOL
               40r1 with a 2.2r0 bundle license into current 4.1r2 bundle,
               you may have NOL blocks with wrong UUIDs. You need to run
               gdl-force-total-recompile() after you load the KB. You can
               create an action button anywhere to start this procedure.
               That will flush & regenerate the UUIDs. You can delete the
               button you just create after this process.

   * GOLDUI on HP-UX B.11.00

          Due to a known G2 problem on HP-UX B.11.00, G2 OnLine
          Documentation User Interface (GOLDUI) is not supported on this
          platform. Currently the GOLDUI module is disabled in GDA and NOL
          environments. This problem will be fixed in the next bundle
          version.

  ------------------------------------------------------------------------
updated: June 05, 2003
