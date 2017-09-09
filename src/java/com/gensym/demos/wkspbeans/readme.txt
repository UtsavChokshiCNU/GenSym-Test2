
If properly constructed G2-JAVA-BEAN subclasses exist on a
kb-workspace, and this workspace is being displayed in a
WorkspaceView component, Java beans are instantiated
to represent these Items. This can be used to integrate
native controls and 3rd party widgets into a G2 application.
See ${SEQUOIA_HOME}/docs/BeansOnWorkspaces.html for the
specification and users' guide on how to use this
functionality.

Run the demo as follows:

On Windows NT: run 

% rundemo.bat

On Solaris: run

% rundemo.sh

This demo starts up G2 with the beans-demo KB. It also starts up the
prototype shell to connect to the KB. Use File -> Get Workspace
to display the BEANS-DEMO-TOP-LEVEL workspace. Display each of
the subworkspaces of the uil-buttons on this workspace for a
display of how to beans are hosted on WorkspaceViews.

There is a small README section for each section which is a
walk-through of the particular demo. There is also source code
to show how event listeners are implemented in G2.