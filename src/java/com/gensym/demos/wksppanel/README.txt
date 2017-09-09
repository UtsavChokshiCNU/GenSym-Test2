

This package contains two demo applications, SimpleWorkspaceApplication 
and BrowswerApplication. Both applications demonstrate how to use the 
MultipleWorkspacePanel component.

SimpleWorkspaceApplication extends com.gensym.core.UiApplication. This 
is the lowest level application foundation class provided by 
Telewindows2 Toolkit that supports applications with a user interface. 
It is responsible for creating its own frame and menu. In this 
application, menu items are created from the java.awt classes. State 
information is managed by the application. It is set up to be a single 
connection application, meaning that it can connect to just one G2 at 
a time.

To run SimpleWorkspaceApplication first start a G2 and load a KB. Then 
type the following at the DOS prompt:  

	java com.gensym.demos.wksppanel.SimpleWorkspaceApplication


WorkspaceBrowser extends com.gensym.shell.util.TW2Application. This is 
the lowest application foundation class that assumes that the 
application is a Telewindows2 Toolkit application and that it will be 
managing connections to G2. It is responsible for creating its own frame, 
menu and toolbar. In this application, the menu items and toolbar buttons 
are generated from commands (classes that extend com.gensym.ui.Command). 
State information that effects the menu items and toolbar buttons is 
managed by the commands instead of by the application. This application 
is a single connection application, meaning that it can connect to just 
one G2 at a time.

To run WorkspaceBrowser first start a G2 and load a KB. Then type the 
following at the DOS prompt:  

	java com.gensym.demos.wksppanel.BrowserApplication 


========================================================================
NOTE: other TW2 Toolkit application foundation classes include: 
GensymApplication, UiApplication, MDIApplication, TW2Application, and 
TW2MDIApplication.
========================================================================




