Manually Editing Process of InstallShield 2013 Projects

NOTE: Do all steps when g2-2015-family.lisp is updated.
      Do only step 3 for each new monthly releases 

1. Installation Information -> General Information
Maintenance Experience: Multi-Instance

2. Application Data -> Prerequisites
Microsoft Visual C++ 2010 SP1 Redistributable Package (x86)
Microsoft Visual C++ 2010 SP1 Redistributable Package (x64) [ENT only]

3. User Interface -> String Editor
PRODUCT_VERSION = 12.0.<year>.<month-number>
This step can be done with the SetInstallShiledProject_PRODUCT_VERSION.vbs script.

4. Media -> Releases -> Default -> Setup.exe
Single .exe File Name: Gensym2015-STD.exe (or Gensym2015-ENT.exe)
