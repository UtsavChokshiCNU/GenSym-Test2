

WorkspaceBrowserApp demonstrates the following:

1. A JTree component used for viewing named workspaces 
   in the current connection. Note, this view is static.
   However, each time you switch connections, the JTree
   is rebuilt, and is current.

2. A MultipleWorkspacePanel for viewing the workspaces 
   displayed from the JTree.

3. A JSplitPane which contains the JTree and the 
   MultipleWorkspacePanel inside the application frame.

Clicking the right mouse button on a named workspace in 
the tree displays a popup menu for showing the workspace, 
or viewing its properties.

Known Demo Glitches:

1. The JSplitPane does not update itself correctly after 
   creating a connection. The user must resize the pane 
   in order for it to display itself properly.


