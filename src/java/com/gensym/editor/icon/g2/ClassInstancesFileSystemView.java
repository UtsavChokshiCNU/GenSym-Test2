package com.gensym.editor.icon.g2;

import com.gensym.ntw.files.*;
import com.gensym.util.Symbol;
import java.io.File;
import java.io.IOException;
import com.gensym.files.URLFileSystemView;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.shell.dialogs.LoginDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwConnectionInfo;
import java.awt.Cursor;

public class ClassInstancesFileSystemView extends URLFileSystemView
{  
  public ClassInstancesFileSystemView(String startingPath,
				      Symbol className,
				      Symbol attributeToDisplayName)
  {
    super(new ClassInstancesDirectoryModel(startingPath,
					   className,
					   attributeToDisplayName));
  }

  @Override
  public File createNewFolder(File containingDir) 
       throws IOException
  {
    if (containingDir instanceof ModulesForConnectionFile) {
    } else if (containingDir instanceof ClassInstancesForModuleFile) {
    } else if (containingDir instanceof G2File) 
       openNewConnection();      
    return null;    
  }  

  private DialogClient dialogClient = new DialogClient();
  private void openNewConnection() {
     LoginDialog ld = new LoginDialog (null, 
 				      "Open Connection",
 				      true, dialogClient);
     ld.setVisible(true);    
   }

  class DialogClient implements StandardDialogClient {
    private ConnectionManager connectionManager = new ConnectionManager();;      
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()){
 	if (dlg instanceof LoginDialog)
	  dlg.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	return;
       }      
      if (dlg instanceof LoginDialog) {
 	LoginDialog  loginDialog = (LoginDialog)dlg;
	TwConnectionInfo connectionInfo = loginDialog.getConnectionInformation();
 	loginDialog.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));	
 	try {
	  if (connectionInfo != null)
	    connectionManager.openConnection(connectionInfo.getBrokerURL(),
						   connectionInfo.getHost(),
						   connectionInfo.getPort());
 	  G2File.registerG2ConnectionInfo(connectionInfo);		  
 	} catch (G2AccessException e) {
 	  //Trace.exception (e);
	  //displayError ("Error making connection", e.toString ());
	}
 	loginDialog.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	loginDialog.setVisible(false);
 	loginDialog.dispose();	
 
       }	
     }
  }    
}
