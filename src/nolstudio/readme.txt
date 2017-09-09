                          Gensym NeurOn-Line Studio

                             Version 4.2 Rev. 0

  ------------------------------------------------------------------------

Contents

   * What is NeurOn-Line Studio?

   * Software Requirements

   * System Requirements

   * Changes in Latest versions

   * What's in this Release?

   * Setup Instructions

   * How can I begin using NeurOn-Line Studio?

   * Online Documentation

What is NeurOn-Line Studio?

NeurOn-Line Studio (NOL Studio) is a graphical, object-oriented software
product for building neural network applications. Using NOL Studio, you can
model dynamic, nonlinear phenomena that are difficult to describe by
analytical models, using historical data stored in databases, process data
historians, or text files. Typical applications include quality assurance,
sensor validation, diagnosis, and process modeling.


Software Requirements

For Windows platform, the installer installs all necessary software for NOL
bundle software products, which include NeurOn-Line Studio.

For unix platform, you need the following software correctly installed on
your machine to use NeurOn-Line Studio:

   * Solaris: Sun's Java 2 (JDK 1.3 Java Development Kit).

   * HP-UX: HP's Java 2 (JDK 1.3 Java Development Kit).

System Requirements

To use NOL Studio, you need:

   * Operating system (minimum version):

        o Windows NT Version 4.0 with Service Pack 6 running on a Pentium
          computer.
        o Windows 98 / 2000 / XP running on a Pentium computer.

        o Solaris 2.6 running on a Sun Sparc computer.

        o HP-UX 11.0 running on an HP9000 Series 700 computer.

   * Minimum of 64 MB of RAM.

   * Approximately 100 MB of disk space to install the software and
     documentation.

Changes in Latest versions

   * Changes in Version 4.2 Rev. 0

     New feature
        o New online training function for ensemble models and optimization
          models.
        o Add four new model types in NOLStudio, which include
          Backpropagation Net, Autoaccosiative Net, Radial Basis Function
          Net, and Rho Net. They are direct mappings to the model types in
          Classic NOL.
        o New export function for variable statistics.
        o Integrated NOL Classic and NOLStudio demos in premium deployment
          environment.
     Bugs
        o For a list of bugs that were addressed in this revisions, please
          log into Gensym HelpLink at http://www.gensym-support.com, and
          reference the Technical Bulletins for NeurOn-Line Studio..

   * Changes in Version 4.1 Rev. 3

     New feature
        o There is no major changes in NOLStudio 4.1r3. The version number
          reflects the version of NOL bundle.
     Bugs
        o For a list of bugs that were addressed in this revisions, please
          log into Gensym HelpLink at http://www.gensym-support.com, and
          reference the Technical Bulletins for NeurOn-Line Studio..

   * Changes in Version 4.1 Rev. 2

     New feature
        o Project tree-view will dynamically reflect the changes of objects

   * Changes in Version 4.1 Rev. 1

     New features
        o New option to train linear model only.
        o Use sensitivity values to help select model inputs.
        o Export prediction and validation data into a single file.
        o New information of model performance.
        o Integrated NOL KBs in premium development and deployment.

   * Changes in Version 2.2 Rev. 0

        o There is no major changes in NOLStudio 2.2r0. The version number
          reflects the version of NOL bundle.

   * Changes in Version 2.1 Rev. 1

     New features
        o Global preference settings for time/date format and maximum
          optimization iteration
        o New message dialogs for when there is no valid data for rank
          calculation.
        o New message dialog for optimizations that reach the maximum
          iteration point.  Users can increase the maximum and allow the
          optimization to continue.
        o Improved load/save dialogs with file type options in selection box
        o New file type options for exporting data series (.csv, .txt)
        o Exceptions when calling g2-api row-based methods on time-based
          models (and vice versa)
        o New ActiveX method:  isTimeBasedModel
   * For a list of bugs that were addressed in this and earlier revisions,
     please log into Gensym HelpLink at http://www.gensym-support.com, and
     reference the Technical Bulletins for NeurOn-Line Studio, or check
     known-bugs.txt.


   * Changes in Version 2.1 Rev. 0

     New features
        o Easier installation of ActiveX control
        o Language localization capability
        o Printing capability
        o Custom date/time formats for more flexible data importing
        o Option for reading in data with European number formatting
        o New buttons on data series workspace to display data series
          statistics and individual variable details
        o Ability to superimpose projection plots to compare the
          distribution of two or more data sets
        o Improved layout of several dialogs, including tab panes on the
          preprocessor workspace
        o Click-to-sort capabilities on several tables, including the input
          variable ratings in the model wizard
        o Automatic stopping option in training console
        o Improved validation capabilities and statistics for analyzing
          trained models
        o Extended ActiveX API including on-line optimization
        o G2 implementation of predictor and optimizer, using G2
          JavaLink/Gateway

What's in this Release?

This release of NOL Studio contains the following software and
documentation:

   * Components that implement offline NOL Studio.
   * ActiveX controls on the Windows 98 / NT /2000 /XP platforms.
   * KBs to implement models and optimizations in G2.through JavaLink
   * Complete User's Guide in pdf format.

The following directories and files are present under the NOL Studio
directory:

   * bin - binaries and ActiveX components required to run NOL Studio.
   * doc - NeurOn-Line Studio User's Guide
   * examples - example data sets to demonstrate the use of NOL Studio.
   * readme.html - this file.
   * known-bugs.txt - the list of open bugs in NOL Studio at the time of
     release.

Note: These links only work after you have installed the software and only
from the readme.html file in the NOL Studio directory.

Setup Instructions

*Windows Platforms

     NOL bundle installer will install and setup all necessary software for
     NOL Studio.

  ------------------------------------------------------------------------
Note: On Windows 98 platform, Place the following command in your config.sys
file:

     shell=c:\command.com /e:2048 /p

This command sets the environment space to 2048 kb, which is required to run
NOL Studio.
  ------------------------------------------------------------------------
*Unix Platforms

     You need to install the correct version of Java 2 (JDK 1.3 Java
     Development Kit or JRE 1.3 Java Runtime Environment) for your platform.
     -----------------------------------------------------------------------
     Note: This release will not work with JDK versions earlier than JDK
     1.2.
     -----------------------------------------------------------------------

   * Ensure that the following environment variables are set properly to
     reflect this installation:

     All unix platforms: JAVA_HOME, NOLSTUDIO_HOME JAVALINK_HOME, and
     CLASSPATH
     Solaris: LD_LIBRARY_PATH
     HP-UX: SHLIB_PATH

   * Setting Environment Variables

     To run NOL Studio offline and online package, the following environment
     variables must be set:

        o JAVA_HOME must point to the JDK directory.

        o NOLSTUDIO_HOME must point to the NOL Studio directory.

        o JAVALINK_HOME must point to the G2 JavaLink directory.

        o CLASSPATH must include the necessary NOL Studio, Java and G2
          JavaLink class files.

          E.g. in Solaris make CLASSPATH includes
          ./:{NOLSTUDIO_HOME}/NolStudioMath.jar:
          {NOLSTUDIO_HOME}\NolStudioGUI.jar:{NOLSTUDIO_HOME}\NolStudioData.jar

How can I begin using NeurOn-Line Studio?

   * Windows Platform

     After installing NOL Studio you can run NOLStudio by going to Start
     menu Program Files-> Gensym NOL->NeurOnLine->NeurOn-Line Studio, which
     uses the nolstudio.bat to launch the NOLStudio main frame window.
        o Run the NOL Studio with example data series
               This release ships with 7 examples. Each of these can be
               found in examples directory
               (%NOLSTUDIO_HOME%\examples\DataSet). They include example
               data series that can be loaded into NOL Studio.
        o Use demo projects in Visual Basic to test the implementation of
          ActiveX Controls.
               Three demos can be found in examples directory
               (%NOLSTUDIO_HOME%\examples\ActiveXDemo). They include two
               demos for NOLPredictor and one for NOLOptimizer.
        o Use demo kbs to test the implementation of models and
          optimizations in G2.
               Two demos can be found in examples directory
               (%NOLSTUDIO_HOME%\examples\kbdemo). They include one demo
               using classic NeurOn-Line version 4.x and one demo using
               nolstudio.kb.
        o Use your own data to preprocess data, generate models and deploy
          them using either G2 or through ActiveX.
        o Query for the current list of bugs to make sure that you are not
          encountering known problems.

   * Unix Platform

        o After installing NOL Studio you can launch NOLStudio by running
          the nolstudio script, which locates in the nolstudio directory.
        o Run the NOL Studio with example data series
        o Use demo kbs to test the implementation of models and
          optimizations in G2.
        o Use your own data to preprocess data, generate models and deploy
          them using G2.

Online Documentation

   * NeurOn-Line Studio User's Guide

     -----------------------------------------------------------------------
     updated: June 05, 2003
