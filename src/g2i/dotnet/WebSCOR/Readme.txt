This directory contains the sources of the webSCOR ASP.NET web application, the OCX used to download
twng + documentaiton to the client machine and the project file to generate the cab file.

WebScorOCX:
-----------

WebScorOCX is the MFC project to build the OCX used to launch the twng session. This is a Visual
Studio 6 project and requires VS6 SP6 to be installed. After compiling the code with Visual Studio 6,
copy the desired (Debug, Release, etc) WebSCORax.ocx to the webScorCAB directory to include it in
the next CAB you create. Consider changing the version number (in the resources) of this OCX as
you make changes and reflect that version number in the webScorOCX/WebSCORax.INF.


WebScorCAB:
-----------

WebScorCAB is the project to create the CAB
file, which should be digitally signed (see Judy to do that). The content of the directory may
need to be updated with the latest code (WebScorOCX, twng, charting DLL) or updated documentation
(chm files). Judy Anderson is the person that can digitally sign the CAB file to ease download and
increase security. The CAB file is stored in the parent directory and you may either directly copy
it into the TwOnline project to be included in the next build or copy it to your deployed webserver
in the webScor/TwOnline virtual directory.

Streps to create the CAB file:

1. Code signing of twng.exe - sign it using our Code-signing certificate. 
2. I have done the following but you may want to double check: update WebSCORax.INF to reflect any
   version number changes. Note that the 
3. I have done the following but you may want to double check: update Project1.DDF.
4. Use MakeCab.exe to create the CAB file by running it using the following syntax: 

	MAKECAB.EXE /f "Project1.DDF"

 
The command [.Set DiskDirectoryTemplate=".."] in Project1.DDF directs the MakeCab utility to create the
CAB in the parent directory of Project1.DDF.

MakeCab.exe is found in "C:\Program Files\Microsoft Visual Studio\VB98\Wizards\PDWizard" on machines
that have the VB6 Packaging and Deployment Wizard installed. It's also available in the Microsoft
Cabinet Software Development Kit available at
http://support.microsoft.com/default.aspx?scid=kb;en-us;310618 <http://support.microsoft.com/default.aspx?scid=kb;en-us;310618>

5. Sign the resulting CAB file using your Code-signing certificate.


WebScorFileMgr {Setup}:
-----------------------

This web application is used to upload and download files to/from the server from the client machine. 
This applciation is typically setup with Windows security to enforce users to log in when accessed 
(using NT security) and displayed within TWNG usign the built in web browser.


TwOnline:
---------

This is the basic webSCOR web applications users log into. Note that the content of Web.Config also
refers to the CAB file version to download. You may need to update this to download newer versions.

